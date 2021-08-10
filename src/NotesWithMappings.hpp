#ifndef NotesWithMappings_hpp
#define NotesWithMappings_hpp

#include "Program.hpp"
#include "MidiDefs.hpp"

class NotesWithMappings: public Program
{
public:
   NotesWithMappings();
   virtual void noteOn(uint8_t note, uint8_t velocity, uint8_t channel);
   virtual void noteOff(uint8_t note, uint8_t channel);
   
   uint8_t note(uint8_t note) const;
   
protected:
   uint8_t m_notes[NOTE_HIGHEST+1];
};

#endif /* NotesWithMappings_hpp */
