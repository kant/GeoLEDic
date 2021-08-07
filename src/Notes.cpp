#include "Notes.hpp"
#include <vector>
#include <algorithm>

namespace {

typedef std::vector<std::vector<uint8_t> >  PentagonNoteMap;
PentagonNoteMap pentagon0 =
{
   {118, 119, 120, 121, 122},
   {103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117},
   {78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102},
   {52, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77},
   {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51},
   {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24}
};

PentagonNoteMap pentagon1 =
{
   {29, 30, 31, 57, 58},
   {2, 3, 4, 5, 6, 32, 33, 60, 59, 84, 83, 56, 55, 27, 28},
   {0, 1, 7, 8, 34, 35, 62, 61, 86, 85, 107, 106, 82, 81, 54, 53, 25, 26},
   {9, 10, 36, 37, 64, 63, 88, 87, 109, 108, 120, 119, 105, 104, 80, 79, 52},
   {11, 12, 38, 39, 65, 66, 89, 90, 110, 111, 121, 122, 118, 117, 103, 102, 78},
   {13, 14, 40, 41, 67, 68, 91, 92, 112, 113, 114, 115, 116, 100, 101},
   {15, 16, 42, 43, 69, 70, 93, 94, 95, 96, 97, 98, 99},
   {17, 18, 44, 45, 71, 72, 73, 74, 75, 76, 77},
   {19, 20, 46, 47, 48, 49, 50, 51},
   {21, 22, 23, 24}
};

PentagonNoteMap pentagon2 =
{
   {37, 38, 39, 65, 64},
   {10, 11, 12, 13, 14, 40, 41, 67, 66, 89, 88, 63, 62, 35, 36},
   {15, 16, 42, 43, 69, 68, 91, 90, 110, 109, 87, 86, 61, 60, 33, 34, 8, 9},
   {17, 18, 44, 45, 71, 70, 93, 92, 112, 111, 121, 120, 108, 107, 85, 84, 59, 58, 31, 32, 6, 7},
   {19, 20, 46, 47, 72, 73, 94, 95, 113, 114, 122, 118, 119, 105, 106, 82, 83, 56, 57, 29, 30, 4, 5},
   {21, 22, 48, 49, 74, 75, 96, 97, 115, 116, 117, 103, 104, 80, 81, 54, 55, 27, 28, 2, 3},
   {23, 24, 50, 51, 76, 77, 98, 99, 100, 101, 102, 78, 79, 52, 53, 25, 26, 0, 1},
};

PentagonNoteMap pentagon3 =
{
   {45, 46, 47, 72, 71},
   {18, 19, 20, 21, 22, 48, 49, 74, 73, 94, 93, 70, 69, 43, 44},
   {23, 24, 50, 51, 76, 75, 96, 95, 113, 112, 92, 91, 68, 67, 41, 42, 16, 17},
   {77, 98, 97, 115, 114, 122, 121, 111, 110, 90, 89, 66, 65, 39, 40, 14, 15},
   {99, 100, 116, 117, 118, 119, 120, 108, 109, 87, 88, 63, 64, 37, 38, 12, 13},
   {101, 102, 103, 104, 105, 106, 107, 85, 86, 61, 62, 35, 36, 10, 11},
   {78, 79, 80, 81, 82, 83, 84, 59, 60, 33, 34, 8, 9},
   {52, 53, 54, 55, 56, 57, 58, 31, 32, 6, 7},
   {25, 26, 27, 28, 29, 30, 4, 5},
   {0, 1, 2, 3}
};

void setPentagon(uint8_t (&notes)[NOTE_HIGHEST+1], uint8_t note, uint8_t velocity)
{
   PentagonNoteMap* pentagon = nullptr;
   if (note >= NOTE_C2 && note < NOTE_C2 + pentagon0.size())
   {
      note -= NOTE_C2;
      pentagon = &pentagon0;
   }
   else if (note >= NOTE_C3 && note < NOTE_C3 + pentagon1.size())
   {
      note -= NOTE_C3;
      pentagon = &pentagon1;
   }
   else if (note >= NOTE_C4 && note < NOTE_C4 + pentagon2.size())
   {
      note -= NOTE_C4;
      pentagon = &pentagon2;
   }
   else if (note >= NOTE_C5 && note < NOTE_C5 + pentagon3.size())
   {
      note -= NOTE_C5;
      pentagon = &pentagon3;
   }
   else
   {
      return;
   }
   
   for (uint8_t mapped_note: pentagon->at(note))
   {
      notes[mapped_note] = velocity;
   }
}

}

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

void NotesWithMappings::noteOn(uint8_t note, uint8_t velocity, uint8_t channel)
{
   switch (channel)
   {
      case 0:
      default:
         Notes::noteOn(note, velocity, 0);
         break;
      case 1:
         setPentagon(m_notes, note, velocity);
         break;
   }
}