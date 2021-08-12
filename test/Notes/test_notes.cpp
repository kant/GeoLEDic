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

TEST_F(TestNotesWithMappings, singleNotes)
{
   const uint8_t NOTE_VELOCITY_1 = 5;
   const uint8_t NOTE_VELOCITY_2 = 6;
   
   noteOn(NOTE_LOWEST,     NOTE_VELOCITY_1, CHANNEL_SINGLE_NOTES);
   noteOn(NOTE_LOWEST+NUM_TRIANGLES-1, NOTE_VELOCITY_2, CHANNEL_SINGLE_NOTES);

   expectNotesSet({{NOTE_VELOCITY_1, {0}},
                   {NOTE_VELOCITY_2, {NUM_TRIANGLES-1}}});

   noteOff(NOTE_LOWEST, CHANNEL_SINGLE_NOTES);
   expectNotesSet({{NOTE_VELOCITY_2, {NUM_TRIANGLES-1}}});

   noteOff(NOTE_LOWEST+NUM_TRIANGLES-1, CHANNEL_SINGLE_NOTES);
   expectNotesSet({});

}

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

// Set blob 0, then blob 1, then clear blob 1 and expect all triangles of blob 0 remaining set
TEST_F(TestNotesWithMappings, twoOverlappingBlobsReleasedInRevers)
{
   const uint8_t NOTE_VELOCITY_1 = 1;
   const uint8_t NOTE_VELOCITY_2 = 100;
   noteOn(NOTE_C2, NOTE_VELOCITY_1, CHANNEL_BLOBS);
   noteOn(NOTE_C2 + 1, NOTE_VELOCITY_2, CHANNEL_BLOBS);
   expectNotesSet({{NOTE_VELOCITY_1, {0, 1, 26, 27}},  // triangles 2 and 28 are covered by blob 1
                   {NOTE_VELOCITY_2, {2, 3, 4, 28, 29, 30}}
                  });
   
   noteOff(NOTE_C2 + 1, CHANNEL_BLOBS);
   expectNotesSet({{NOTE_VELOCITY_1, {0, 1, 2, 26, 27, 28}}});

   noteOff(NOTE_C2, CHANNEL_BLOBS);
   expectNotesSet({});
}

// Set blob 0, then blob 1, then clear blob 0 and expect all triangles of blob 1 remaining set
TEST_F(TestNotesWithMappings, twoOverlappingBlobsReleasedInOrder)
{
   const uint8_t NOTE_VELOCITY_1 = 1;
   const uint8_t NOTE_VELOCITY_2 = 100;
   noteOn(NOTE_C2, NOTE_VELOCITY_1, CHANNEL_BLOBS);
   noteOn(NOTE_C2 + 1, NOTE_VELOCITY_2, CHANNEL_BLOBS);
   expectNotesSet({{NOTE_VELOCITY_1, {0, 1, 26, 27}},  // triangles 2 and 28 are covered by blob 1
                   {NOTE_VELOCITY_2, {2, 3, 4, 28, 29, 30}}
                  });
   
   noteOff(NOTE_C2, CHANNEL_BLOBS);
   expectNotesSet({{NOTE_VELOCITY_2, {2, 3, 4, 28, 29, 30}}});

   noteOff(NOTE_C2 + 1, CHANNEL_BLOBS);
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


// overlap single note with pentagon and blob
TEST_F(TestNotesWithMappings, overlappingSingleNotePentagonAndBlob)
{
   const uint8_t NOTE_VELOCITY_1 = 1;
   const uint8_t NOTE_VELOCITY_2 = 127;
   const uint8_t NOTE_VELOCITY_3 = 2;
   
   noteOn(NOTE_LOWEST+83, NOTE_VELOCITY_1, CHANNEL_SINGLE_TRIANGLE);
   noteOn(NOTE_C2+2,      NOTE_VELOCITY_2, CHANNEL_PENTAGONS);
   noteOn(NOTE_C2+26,     NOTE_VELOCITY_3, CHANNEL_BLOBS);
   expectNotesSet({/*{NOTE_VELOCITY_1, {83}},*/  // single triangle covered by the other two
                   {NOTE_VELOCITY_2, {78, 79, 80, /*81, 82, 83,*/ 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102}},
                   //                                ^--v  ring partially covered by blob
                   {NOTE_VELOCITY_3, {54, 55, 56,   81, 82, 83}}});

   noteOff(NOTE_C2+26, CHANNEL_BLOBS);
   expectNotesSet({/*{NOTE_VELOCITY_1, {83}},*/  // single triangle covered by RING
                   {NOTE_VELOCITY_2, {78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102}}});
   
   noteOn(NOTE_C2+26, NOTE_VELOCITY_3, CHANNEL_BLOBS);
   noteOff(NOTE_C2+2, CHANNEL_PENTAGONS);

   expectNotesSet({/*{NOTE_VELOCITY_1, {83}},*/  // single triangle covered by blob
                   {NOTE_VELOCITY_3, {54, 55, 56,   81, 82, 83}}});

   noteOff(NOTE_C2+26, CHANNEL_BLOBS);
   expectNotesSet({{NOTE_VELOCITY_1, {83}}});

   noteOff(NOTE_LOWEST+83, CHANNEL_SINGLE_TRIANGLE);
   expectNotesSet({});
}

// set all notes on all channels, then clear them all and ensure we're with nothing left
TEST_F(TestNotesWithMappings, setAllClearAll)
{
   for (unsigned channel: {CHANNEL_SINGLE_TRIANGLE, CHANNEL_PENTAGONS, CHANNEL_BLOBS})
   {
      for (unsigned note = NOTE_LOWEST; note <= NOTE_HIGHEST; note++)
      {
         noteOn(note, channel+5, channel);
      }
   }
   
   for (unsigned channel: {CHANNEL_SINGLE_TRIANGLE, CHANNEL_PENTAGONS, CHANNEL_BLOBS})
   {
      for (unsigned note = NOTE_LOWEST; note <= NOTE_HIGHEST; note++)
      {
         noteOff(note, channel);
      }
   }
   expectNotesSet({});
}


// fuzz inputs (occasionally invalid on purpose) and see if it crashes
TEST_F(TestNotesWithMappings, fuzz)
{
   srand(0);
   unsigned iterations = 100000;
   while (iterations--)
   {
      noteOn(rand() % (NOTE_HIGHEST + 10), rand(), rand() % (CHANNEL_BLOBS + 1));
      noteOff(rand() % (NOTE_HIGHEST + 10), rand() % (CHANNEL_BLOBS + 1));
   }
}


}
