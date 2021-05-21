#include "MidiSource.hpp"
#if defined(USB_MIDI) || defined(USB_MIDI_SERIAL)
#include "MIDIUSB.h"
#define WITH_MIDI
#else
#pragma message Building without MIDI support
#endif
#include "Arduino.h"

#define MIDI_ACTIVITY_LED_PIN 13

static class MidiSource::Impl
{
public:
   Impl():
      m_activity_count(0)
   {
      pinMode(MIDI_ACTIVITY_LED_PIN, OUTPUT);
   }

   void active()
   {
      digitalWrite(MIDI_ACTIVITY_LED_PIN, HIGH);
      m_activity_count = 5;
   }

   void inactive()
   {
      if (m_activity_count == 1)
      {
         digitalWrite(MIDI_ACTIVITY_LED_PIN, LOW);
      }
      if (m_activity_count > 0) m_activity_count--;
   }

   const MidiMessage* read()
   {
#ifdef WITH_MIDI
      midiEventPacket_t rx;
      rx = MidiUSB.read();
      if (rx.header != 0)
      {
         m_msg.length = 3;
         m_msg.data[0] = rx.byte1;
         m_msg.data[1] = rx.byte2;
         m_msg.data[2] = rx.byte3;
         m_msg.data[3] = 0;
         active();
         return &m_msg;
      }
      else
      {
         inactive();
         return nullptr;
      }
#else
      return nullptr;
#endif
   }

   MidiMessage m_msg;
   int m_activity_count;
} dummy;

MidiSource::MidiSource():
   m_i(dummy)
{
}

MidiSource::~MidiSource()
{
}

const MidiMessage* MidiSource::read()
{
   return m_i.read();
}
