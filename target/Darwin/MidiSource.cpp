#include "MidiSource.hpp"
#include <CoreMIDI/CoreMIDI.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <pthread.h>

class MidiSource::Impl
{
public:
   
   Impl()
   {
      OSStatus result = noErr;
      result = MIDIClientCreate(CFSTR("Dome MIDI Client"), nullptr, nullptr, &m_midi_client );
      if (result != noErr) {
         std::cerr << "MIDIClientCreate() error:" << result;
         return;
      }
      result = MIDIDestinationCreate(m_midi_client, CFSTR("Dome"), &Impl::processMidi, this, &m_midi_out );
      if (result != noErr) {
         std::cerr << "MIDIDestinationCreate() error:" << result;
         return;
      }
      result = MIDIInputPortCreate(m_midi_client, CFSTR("Dome"), &Impl::processMidi, this,  &m_port );
      if (result != noErr) {
         std::cerr << "MIDIInputPortCreate() error:" << result;
         return;
      }
      
      pthread_mutex_init(&m_mutex, NULL);
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
   MIDIPortRef     m_port;
   
   std::queue<MidiMessage> m_packets;
   pthread_mutex_t m_mutex;
   MidiMessage     m_last_returned_message;
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
