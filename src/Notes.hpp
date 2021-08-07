#ifndef Notes_hpp
#define Notes_hpp

#include "Program.hpp"
#include "MidiDefs.hpp"

class Notes: public Program
{
public:
   Notes();
   virtual void noteOn(uint8_t note, uint8_t velocity, uint8_t channel);
   virtual void noteOff(uint8_t note, uint8_t channel);
   
   uint8_t note(uint8_t note) const;
   
protected:
   uint8_t m_notes[NOTE_HIGHEST+1];
};

class NotesWithMappings: public Notes
{
public:
   virtual void noteOn(uint8_t note, uint8_t velocity, uint8_t channel);
};


#endif /* Notes_hpp */