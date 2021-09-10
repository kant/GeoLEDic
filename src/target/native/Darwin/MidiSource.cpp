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
};

class MidiInputPort: public MidiPort
{
public:
   MidiInputPort():
      MidiPort()
   {
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


class MidiOutputPort: public MidiPort
{
public:
   MidiOutputPort():
      MidiPort()
   {
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
   }
   
   void send(const MIDIPacketList* packet_list)
   {
      if (m_selected_endpoint == 0) return;
      MIDISend(m_port, m_selected_endpoint, packet_list);
   }
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
      result = MIDIDestinationCreate(m_midi_client, CFSTR(MIDI_PORT_NAME), &Impl::processMidi, this, &m_midi_out );
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
   
      // forward directly to whoever's connected
      m_output.send(packets);
      
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
   MIDIEndpointRef m_midi_out;
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
