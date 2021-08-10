#include <gmock/gmock.h>
#include "NotesWithMappings.hpp"

namespace {
const unsigned NUM_TRIANGLES = 123;
const unsigned NUM_BLOBS = 52;

enum {
   CHANNEL_SINGLE_NOTES = 0,
   CHANNEL_PENTAGONS = 1,
   CHANNEL_BLOBS = 2
};

class TestNotesWithMappings: public testing::Test, public NotesWithMappings
{
public:
   TestNotesWithMappings()
   {}
   
   struct ExpectedNotes{
      ExpectedNotes(uint8_t velocity, const std::vector<uint8_t>& notes):
         velocity(velocity),
         notes(notes)
      {}
      
      uint8_t velocity;
      std::vector<uint8_t> notes;
   };
   
   void expectNotesSet(const std::vector<ExpectedNotes>& expected_notes)
   {
      for (unsigned k = 0; k < NUM_TRIANGLES; k++)
      {
         bool found = false;
         for (const ExpectedNotes& en: expected_notes)
         {
            for (uint8_t expected_note: en.notes)
            {
               if (expected_note == k)
               {
                  EXPECT_EQ(en.velocity, note(k)) << "expected note " << k << " to be set to " << +en.velocity;
                  found = true;
                  break;
               }
            }
            if (found) break;
         }
         if (found) continue;
         EXPECT_EQ(0, note(k)) << "didn't expect note " << k << " to be set";
      }
   }
   
   virtual void controlChange(uint8_t, uint8_t){};
   virtual void run(){};
};

// Set and clear blob 0 (bottom left)
TEST_F(TestNotesWithMappings, singleBlob)
{
   const uint8_t NOTE_VELOCITY = 1;
   noteOn(NOTE_C2, NOTE_VELOCITY, CHANNEL_BLOBS);
   expectNotesSet({{NOTE_VELOCITY, {0, 1, 2, 26, 27, 28}}});
   
   noteOff(NOTE_C2, CHANNEL_BLOBS);
   expectNotesSet({});
}

// Set and clear blob 0 (bottom left) and blob 51 (the pentagon at the top)
TEST_F(TestNotesWithMappings, twoBlobs)
{
   const uint8_t NOTE_VELOCITY_1 = 1;
   const uint8_t NOTE_VELOCITY_2 = 100;
   noteOn(NOTE_C2, NOTE_VELOCITY_1, CHANNEL_BLOBS);
   noteOn(NOTE_C2 + NUM_BLOBS - 1, NOTE_VELOCITY_2, CHANNEL_BLOBS);
   expectNotesSet({{NOTE_VELOCITY_1, {0, 1, 2, 26, 27, 28}},
                   {NOTE_VELOCITY_2, {118, 119, 120, 121, 122}}
                  });
   
   noteOff(NOTE_C2, CHANNEL_BLOBS);
   expectNotesSet({{NOTE_VELOCITY_2, {118, 119, 120, 121, 122}}});

   noteOff(NOTE_C2 + NUM_BLOBS - 1, CHANNEL_BLOBS);
   expectNotesSet({});
}

// Set and clear pentagon 0
TEST_F(TestNotesWithMappings, singlePentagon)
{
   const uint8_t NOTE_VELOCITY = 1;
   noteOn(NOTE_C2, NOTE_VELOCITY, CHANNEL_PENTAGONS);
   expectNotesSet({{NOTE_VELOCITY, {118, 119, 120, 121, 122}}});
   
   noteOff(NOTE_C2, CHANNEL_PENTAGONS);
   expectNotesSet({});
}

// Set and clear pentagon 0 and pentagon 0's second ring
TEST_F(TestNotesWithMappings, singlePentagonAndRing)
{
   const uint8_t NOTE_VELOCITY_1 = 1;
   const uint8_t NOTE_VELOCITY_2 = 2;
   noteOn(NOTE_C2, NOTE_VELOCITY_1, CHANNEL_PENTAGONS);
   noteOn(NOTE_C2+2, NOTE_VELOCITY_2, CHANNEL_PENTAGONS);
   expectNotesSet({{NOTE_VELOCITY_1, {118, 119, 120, 121, 122}},
                   {NOTE_VELOCITY_2, {78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102}}});

   noteOff(NOTE_C2, CHANNEL_PENTAGONS);
   expectNotesSet({{NOTE_VELOCITY_2, {78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102}}});
   
   noteOff(NOTE_C2+2, CHANNEL_PENTAGONS);
   expectNotesSet({});
}




}
