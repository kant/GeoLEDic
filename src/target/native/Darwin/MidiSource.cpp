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

class MidiSource::Impl: public gfx::Config::MidiPorts
{
public:
   
   Impl():
      m_selected_midi_source(0)
   {
      pthread_mutex_init(&m_mutex, NULL);
      pthread_mutex_init(&m_midi_source_mutex, NULL);

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
      result = MIDIInputPortCreate(m_midi_client, CFSTR(MIDI_PORT_NAME), &Impl::processMidi, this,  &m_port );
      if (result != noErr) {
         std::cerr << "MIDIInputPortCreate() error:" << result;
         return;
      }
      
      updateMidiSources();
   }
   
   void updateMidiSources()
   {
      pthread_mutex_lock(&m_midi_source_mutex);

      int num_sources = MIDIGetNumberOfSources();
      
      std::set<MIDIEndpointRef> to_remove;
      for (const auto& pair: m_midi_sources)
      {
         to_remove.insert(pair.first);
      }
      
      // add new devices, if any
      for (int i = 0; i < num_sources; i++)
      {
         MIDIEndpointRef dev = MIDIGetSource(i);
         if (m_midi_sources.count(dev))
         {
            to_remove.erase(dev);
            continue;
         }
         
         std::stringstream description;
         CFStringRef name;
         char tmp[64];
         MIDIObjectGetStringProperty(dev, kMIDIPropertyModel, &name);
         CFStringGetCString(name, tmp, sizeof(tmp), 0);
         description << tmp << ": ";
         MIDIObjectGetStringProperty(dev, kMIDIPropertyName, &name);
         CFStringGetCString(name, tmp, sizeof(tmp), 0);
         description << tmp;
         m_midi_sources[dev] = description.str();         
      }
      
      // remove the ones that were no longer present
      for (MIDIEndpointRef dev: to_remove)
      {
         if (m_selected_midi_source == dev)
         {
            MIDIPortDisconnectSource(m_port, dev);
            m_selected_midi_source = 0;
         }
         m_midi_sources.erase(dev);
      }
      
      pthread_mutex_unlock(&m_midi_source_mutex);
   }
   
   void processMidiPackets(const MIDIPacketList *packets)
   {
      const MIDIPacket *packet = static_cast<const MIDIPacket *>(packets->packet);
            
      // push messages into a queue to hand them over to the working thread which
      // will consume them via read()
      pthread_mutex_lock(&m_mutex);
      for (unsigned int i = 0; i < packets->numPackets; ++i) {
         MidiMessage msg;
         msg.length = std::min(UInt16(sizeof(msg.data)), packet->length);
         std::copy(packet->data, packet->data + msg.length, msg.data);
         m_packets.push(msg);
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
         updateMidiSources();
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
   
   virtual void updateAvailablePorts(std::map<PortId, std::string>& port_map, PortId& selected_port)
   {
      selected_port = m_selected_midi_source;
      
      pthread_mutex_lock(&m_midi_source_mutex);
      // remove non-existing ones
      for (auto it = port_map.cbegin(); it != port_map.cend(); )
      {
         if (m_midi_sources.count(it->first))
         {
            ++it;
         }
         else
         {
            port_map.erase(it++);
         }
      }
      
      // add new ones
      for (const auto& pair: m_midi_sources)
      {
         if (port_map.count(pair.first) == 0)
         {
            port_map[pair.first] = pair.second;
         }
      }
      pthread_mutex_unlock(&m_midi_source_mutex);
   }
   
   virtual void selectPort(PortId selected_port)
   {
      pthread_mutex_lock(&m_midi_source_mutex);
      if (selected_port != m_selected_midi_source)
      {
         MIDIPortDisconnectSource(m_port, m_selected_midi_source);
         m_selected_midi_source = 0;
      }
      
      if (not m_midi_sources.count(selected_port))
      {
         pthread_mutex_unlock(&m_midi_source_mutex);
         return;
      }
      
      int result = MIDIPortConnectSource(m_port, selected_port, this);
      if (result != noErr) {
         std::cerr << "MIDIPortConnectSource() error:" << result;
         selected_port = 0;
      }
      m_selected_midi_source = selected_port;
      pthread_mutex_unlock(&m_midi_source_mutex);
   }
   
   MIDIClientRef   m_midi_client;
   MIDIEndpointRef m_midi_out;
   MIDIPortRef     m_port;
   
   std::queue<MidiMessage> m_packets;
   pthread_mutex_t   m_mutex;
   MidiMessage       m_last_returned_message;
   pthread_mutex_t   m_midi_source_mutex;
   std::map<MIDIEndpointRef, std::string> m_midi_sources;
   MIDIEndpointRef  m_selected_midi_source;
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

gfx::Config::MidiPorts* MidiSource::getMidiPorts()
{
   return &m_i;
}
