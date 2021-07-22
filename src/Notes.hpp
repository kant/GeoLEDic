#ifndef Notes_hpp
#define Notes_hpp

#include "Program.hpp"
#include "MidiDefs.hpp"

class Notes: public Program
{
public:
   Notes();
   virtual void noteOn(uint8_t note, uint8_t velocity);
   virtual void noteOff(uint8_t note);
   
   enum Constants {
      NUM_NOTES = 128
   };
   
protected:
   unsigned m_notes[NUM_NOTES];
};

#endif /* Notes_hpp */
