#include "Notes.hpp"
#include <algorithm>

Notes::Notes()
{
   std::fill(m_notes, m_notes+NUM_NOTES, 0);
}

void Notes::noteOn(uint8_t note, uint8_t velocity)
{
   m_notes[note] = velocity;
}

void Notes::noteOff(uint8_t note)
{
   m_notes[note] = 0;
}
