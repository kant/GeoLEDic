#ifndef GELOEDIC_MidiMessage_h
#define GELOEDIC_MidiMessage_h

#include <stdint.h>
#ifndef NO_STREAM
#include <ostream>
#endif

struct MidiMessage
{
   enum Type {
      NOTE_OFF         = 0x8,
      NOTE_ON          = 0x9,
      AFTERTOUCH       = 0xA,
      CONTROL_CHANGE   = 0xB,
      PROGRAM_CHANGE   = 0xC,
      CHANNEL_PRESSURE = 0xD,
      PITCH_WHEEL      = 0xE
   };
   
   Type type() const { return Type(data[0] >> 4); }
   unsigned channel() const { return data[0] & 0xF; }
   
   uint16_t length;
   uint8_t  data[4];

   static MidiMessage makeNote(uint8_t num, uint8_t velocity, uint8_t channel);

   static int lengthForStatusByte(uint8_t first_byte);
};

class MidiMessageSink
{
public:
   virtual ~MidiMessageSink(){}
   virtual void sink(const MidiMessage& msg) = 0;
};

#ifndef NO_STREAM
std::ostream& operator<<(std::ostream& os, const MidiMessage& m);
#endif

#endif /* GELOEDIC_MidiMessage_h */
