#ifndef Notes_hpp
#define Notes_hpp

#include "Controls.hpp"
#include "MidiDefs.hpp"

class Notes: public Controls
{
public:
   Notes();
   virtual void noteOn(uint8_t note, uint8_t velocity, uint8_t channel);
   virtual void noteOff(uint8_t note, uint8_t channel);
   
   uint8_t note(uint8_t note) const;

   virtual void run(){}
   
protected:
   uint8_t m_notes[NOTE_HIGHEST+1];
};

#endif /* Notes_hpp */
