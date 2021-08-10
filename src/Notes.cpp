#include "Notes.hpp"
#include <vector>
#include <algorithm>

Notes::Notes()
{
   std::fill(m_notes, m_notes+NOTE_HIGHEST+1, 0);
}

void Notes::noteOn(uint8_t note, uint8_t velocity, uint8_t channel)
{
   if (note <= NOTE_HIGHEST)
   {
      m_notes[note] = velocity;
   }
}

void Notes::noteOff(uint8_t note, uint8_t channel)
{
   noteOn(note, 0, channel);
}

uint8_t Notes::note(uint8_t note) const
{
   if (note > NOTE_HIGHEST) return 0;
   return m_notes[note];
}
