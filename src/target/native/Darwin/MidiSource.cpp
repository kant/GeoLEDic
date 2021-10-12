#include "MidiSource.hpp"
#include "gfx/Config.hpp"
#include <CoreMIDI/CoreMIDI.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <pthread.h>

namespace {

int messageSize(uint8_t first_byte)
{
   switch (first_byte >> 4)
   {
      case MidiMessage::NOTE_OFF:
      case MidiMessage::NOTE_ON:
      case MidiMessage::AFTERTOUCH:
      case MidiMessage::CONTROL_CHANGE:
      case MidiMessage::PITCH_WHEEL:
         return 3;
      case MidiMessage::PROGRAM_CHANGE:
      case MidiMessage::CHANNEL_PRESSURE:
         return 2;
      default:
         // discard remainder, SYSEX etc not handled
         return -1;
   }
}

class MidiPort: public MidiSource::MidiPorts
{
public:
   MidiPort():
      m_selected_endpoint(0)
   {
      pthread_mutex_init(&m_endpoints_mutex, NULL);
   }
   
   virtual int getNumEndpoints() = 0;
   virtual MIDIEndpointRef getEndpoint(int num) = 0;
   virtual void disconnectEndpoint(MIDIEndpointRef endpoint) = 0;
   virtual bool connectEndpoint(MIDIEndpointRef endpoint) = 0;

   bool excludePort(const std::string& name)
   {
      for (std::string& exclude_name: m_port_blacklist)
      {
         if (name.substr(0, exclude_name.size()) == exclude_name)
         {
            return true;
         }
      }
      return false;
   }

   void refreshPorts()
   {
      pthread_mutex_lock(&m_endpoints_mutex);

      int num_sources = getNumEndpoints();
      
      std::set<MIDIEndpointRef> to_remove;
      for (const auto& pair: m_endpoints)
      {
         to_remove.insert(pair.first);
      }
      
      // add new devices, if any
      for (int i = 0; i < num_sources; i++)
      {
         MIDIEndpointRef dev = getEndpoint(i);
         if (m_endpoints.count(dev))
         {
            to_remove.erase(dev);
            continue;
         }
         
         std::stringstream description;
         CFStringRef name;
         char tmp[64];
         if (MIDIObjectGetStringProperty(dev, kMIDIPropertyModel, &name) == noErr)
         {
            CFStringGetCString(name, tmp, sizeof(tmp), 0);
            description << tmp << ": ";
         }
         if (MIDIObjectGetStringProperty(dev, kMIDIPropertyName, &name) == noErr)
         {
            CFStringGetCString(name, tmp, sizeof(tmp), 0);
            description << tmp;
         }
         if (description.str().size() == 0)
         {
            description << "Unknown device " << i;
         }

         if (excludePort(description.str())) continue;

         m_endpoints[dev] = description.str();
      }
      
      // remove the ones that were no longer present
      for (MIDIEndpointRef dev: to_remove)
      {
         if (m_selected_endpoint == dev)
         {
            disconnectEndpoint(dev);
            m_selected_endpoint = 0;
         }
         m_endpoints.erase(dev);
      }
      
      pthread_mutex_unlock(&m_endpoints_mutex);
   }
   
   virtual void updateAvailablePorts(std::map<PortId, std::string>& port_map, PortId& selected_port)
   {
      selected_port = m_selected_endpoint;
      
      pthread_mutex_lock(&m_endpoints_mutex);
      // remove non-existing ones
      for (auto it = port_map.cbegin(); it != port_map.cend(); )
      {
         if (m_endpoints.count(it->first))
         {
            ++it;
         }
         else
         {
            port_map.erase(it++);
         }
      }
      
      // add new ones
      for (const auto& pair: m_endpoints)
      {
         if (port_map.count(pair.first) == 0)
         {
            port_map[pair.first] = pair.second;
         }
      }
      pthread_mutex_unlock(&m_endpoints_mutex);
   }
   
   virtual void selectPort(PortId selected_port)
   {
      pthread_mutex_lock(&m_endpoints_mutex);
      if (selected_port != m_selected_endpoint)
      {
         disconnectEndpoint(m_selected_endpoint);
         m_selected_endpoint = 0;
      }
      
      if (not m_endpoints.count(selected_port))
      {
         pthread_mutex_unlock(&m_endpoints_mutex);
         return;
      }
      
      if (not connectEndpoint(selected_port))
      {
         selected_port = 0;
      }
      m_selected_endpoint = selected_port;
      pthread_mutex_unlock(&m_endpoints_mutex);
   }
protected:
   MIDIPortRef       m_port;
   pthread_mutex_t   m_endpoints_mutex;
   std::map<MIDIEndpointRef, std::string> m_endpoints;
   MIDIEndpointRef   m_selected_endpoint;
   std::vector<std::string> m_port_blacklist;
};

class MidiInputPort: public MidiPort
{
public:
   MidiInputPort():
      MidiPort()
   {
      // exclude confusing ports
      m_port_blacklist.push_back("Teensy MIDI");
      m_port_blacklist.push_back("Komplete Kontrol DAW");
   }
   
   virtual int getNumEndpoints()
   {
      return MIDIGetNumberOfSources();
   }
   
   virtual MIDIEndpointRef getEndpoint(int num)
   {
      return MIDIGetSource(num);
   }
   
   virtual void disconnectEndpoint(MIDIEndpointRef endpoint)
   {
      MIDIPortDisconnectSource(m_port, endpoint);
   }
   
   virtual bool connectEndpoint(MIDIEndpointRef endpoint)
   {
      int result = MIDIPortConnectSource(m_port, endpoint, this);
      if (result != noErr) {
         std::cerr << "MIDIPortConnectSource() error:" << result;
      }
      return result == noErr;
   }

   void createPort(MIDIClientRef client, MIDIReadProc read_proc, void* impl)
   {
      OSStatus result =  MIDIInputPortCreate(client, CFSTR(MIDI_PORT_NAME), read_proc, impl,  &m_port );
      if (result != noErr) {
         std::cerr << "MIDIInputPortCreate() error:" << result;
         return;
      }
   }
};


class MidiOutputPort: public MidiPort, public MidiSource::MidiSender
{
public:
   enum DestinationType{
      TO_PORT_AND_VIRTUAL, 
      TO_PORT_ONLY // use e.g. to prevent stuff received on virtual in to be sent to virtual out
   };

   MidiOutputPort():
      MidiPort(),
      m_enabled(true)
   {
      // exclude confusing ports
      m_port_blacklist.push_back("Komplete Kontrol DAW");
      m_port_blacklist.push_back(MIDI_PORT_NAME);
   }
   
   virtual int getNumEndpoints()
   {
      return MIDIGetNumberOfDestinations();
   }
   
   virtual MIDIEndpointRef getEndpoint(int num)
   {
      return MIDIGetDestination(num);
   }
   
   virtual void disconnectEndpoint(MIDIEndpointRef endpoint)
   {
      // no need to disconnect from output
      (void)endpoint;
   }
   
   virtual bool connectEndpoint(MIDIEndpointRef endpoint)
   {
      // no need to connect to output
      (void)endpoint;
      return true;
   }

   void createPort(MIDIClientRef client)
   {
      OSStatus result =  MIDIOutputPortCreate(client, CFSTR(MIDI_OUT_PORT_NAME), &m_port);
      if (result != noErr) {
         std::cerr << "MIDIInputPortCreate() error:" << result;
         return;
      }

      result = MIDISourceCreate(client, CFSTR(MIDI_OUT_PORT_NAME), &m_virtual_midi_out);
      if (result != noErr) {
         std::cerr << "MIDISourceCreate() error:" << result;
         return;
      }
   }
   
   virtual void enable(bool ena)
   {
      m_enabled = ena;
   }

   virtual bool enabled() const
   {
      return m_enabled;
   }

   virtual void sendControlChange(uint8_t cc_num, uint8_t val)
   {
      uint8_t buf[64];
      MIDIPacketList* packet_list = reinterpret_cast<MIDIPacketList*>(buf);
      MIDIPacket     *pkt = MIDIPacketListInit(packet_list);
      uint8_t message[] = {MidiMessage::CONTROL_CHANGE << 4, cc_num, val};
      MIDIPacketListAdd(packet_list, sizeof(buf), pkt, 0, sizeof(message), message);
      
      send(packet_list, TO_PORT_AND_VIRTUAL);
   }

   virtual void sendProgramChange(uint8_t program)
   {
      uint8_t buf[64];
      MIDIPacketList* packet_list = reinterpret_cast<MIDIPacketList*>(buf);
      MIDIPacket     *pkt = MIDIPacketListInit(packet_list);
      uint8_t message[] = {MidiMessage::PROGRAM_CHANGE << 4, program};
      MIDIPacketListAdd(packet_list, sizeof(buf), pkt, 0, sizeof(message), message);
      
      send(packet_list, TO_PORT_AND_VIRTUAL);
   }
   void send(const MIDIPacketList* packet_list, DestinationType dest_type)
   {
      if (not m_enabled) return;

      if (m_selected_endpoint)
      {
         MIDISend(m_port, m_selected_endpoint, packet_list);
      }

      if (dest_type == TO_PORT_AND_VIRTUAL)
      {
         MIDIReceived(m_virtual_midi_out, packet_list);
      }
   }

   bool m_enabled;
   MIDIEndpointRef m_virtual_midi_out;
};

}

class MidiSource::Impl
{
public:
   
   Impl():
      m_input()
   {
      pthread_mutex_init(&m_mutex, NULL);

      OSStatus result = noErr;
      result = MIDIClientCreate(CFSTR(MIDI_CLIENT_NAME), &Impl::notifyMidi, this, &m_midi_client );
      if (result != noErr) {
         std::cerr << "MIDIClientCreate() error:" << result;
         return;
      }
      result = MIDIDestinationCreate(m_midi_client, CFSTR(MIDI_PORT_NAME), &Impl::processMidi, this, &m_midi_in);
      if (result != noErr) {
         std::cerr << "MIDIDestinationCreate() error:" << result;
         return;
      }
      
      m_input.createPort(m_midi_client, &Impl::processMidi, this);
      m_input.refreshPorts();

      m_output.createPort(m_midi_client);
      m_output.refreshPorts();
   }
   
   void processMidiPackets(const MIDIPacketList *packets)
   {
      const MIDIPacket *packet = static_cast<const MIDIPacket *>(packets->packet);
   
      // forward directly to whoever's connected, but don't echo to virtual output
      m_output.send(packets, MidiOutputPort::TO_PORT_ONLY);

      // push messages into a queue to hand them over to the working thread which
      // will consume them via read()
      pthread_mutex_lock(&m_mutex);
      for (unsigned int i = 0; i < packets->numPackets; ++i)
      {
         int remaining_length = packet->length;
         const uint8_t* p = packet->data;
         while (remaining_length > 0)
         {
            int length = messageSize(*p);
            
            if (length < 0) break; // skip remainder of message
            if (length > remaining_length) break; 

            MidiMessage msg;
            msg.length = length;
            std::copy_n(p, length, msg.data);
            p += length;
            remaining_length -= length;
            m_packets.push(msg);
         }
         packet = MIDIPacketNext(packet);
      }
      pthread_mutex_unlock(&m_mutex);
   }
   
   static void processMidi(const MIDIPacketList *packets,
                           void *ref_con, void *data)
   {
      if (ref_con != nullptr) static_cast<Impl*>(ref_con)->processMidiPackets(packets);
   }
   
   void processMidiNotification(const MIDINotification *message)
   {
      if (message->messageID == kMIDIMsgObjectAdded or
          message->messageID == kMIDIMsgObjectRemoved)
      {
         m_input.refreshPorts();
         m_output.refreshPorts();
      }
   }
   
   static void notifyMidi(const MIDINotification *message, void *ref_con)
   {
      if (ref_con != nullptr) static_cast<Impl*>(ref_con)->processMidiNotification(message);
   }
   
   const MidiMessage* read()
   {
      if (m_packets.empty()) return nullptr;
      
      pthread_mutex_lock(&m_mutex);
      m_last_returned_message = m_packets.front();
      m_packets.pop();
      pthread_mutex_unlock(&m_mutex);
      return &m_last_returned_message;
   }
   
   MIDIClientRef   m_midi_client;
   MIDIEndpointRef m_midi_in;

   MidiInputPort   m_input;
   MidiOutputPort  m_output;

   std::queue<MidiMessage> m_packets;
   pthread_mutex_t   m_mutex;
   MidiMessage       m_last_returned_message;
};

MidiSource::MidiSource():
   m_i(* new(Impl))
{
}

MidiSource::~MidiSource()
{
   delete &m_i;
}

const MidiMessage* MidiSource::read()
{
   return m_i.read();
}

MidiSource::MidiPorts* MidiSource::getMidiInPorts()
{
   return &m_i.m_input;
}

MidiSource::MidiPorts* MidiSource::getMidiOutPorts()
{
   return &m_i.m_output;
}

MidiSource::MidiSender*  MidiSource::getSender()
{
   return &m_i.m_output;
}
