#ifndef NotesWithMappings_hpp
#define NotesWithMappings_hpp

#include "Program.hpp"
#include "MidiDefs.hpp"
#include <map>

class NotesWithMappings: public Program
{
public:
   enum Channel {
      CHANNEL_SINGLE_TRIANGLE = 0,
      CHANNEL_PENTAGONS = 1,
      CHANNEL_BLOBS = 2
   };
   
   NotesWithMappings();
   virtual void noteOn(uint8_t note, uint8_t velocity, uint8_t channel);
   virtual void noteOff(uint8_t note, uint8_t channel);
   
   uint8_t note(uint8_t note) const;
   
private:
   void setBlob(uint8_t note, uint8_t velocity);
   void setPentagon(uint8_t note, uint8_t velocity);

   void setNote(uint8_t note, uint8_t velocity, Channel channel, uint8_t index_in_channel);
   void clearNote(uint8_t note, Channel channel, uint8_t index_in_channel);

   enum PrivateConsts {
      MAX_SETTERS = 4
   };
   
   struct Setter {
      Setter();
      Setter(Channel channel, uint8_t index, uint8_t velocity);
      
      Channel channel;
      uint8_t index;
      uint8_t velocity;
   };
   
   struct Setters
   {
      Setters();
      
      void set(const Setter& setter);
      void clear(Channel channel, uint8_t index_in_channel);

      uint8_t velocity() const;
      
      uint8_t num_setters;
      Setter setters[MAX_SETTERS];
   };
   
   std::map<uint8_t, Setters> m_notes;
   uint8_t m_notes_old[NOTE_HIGHEST+1];
};

#endif /* NotesWithMappings_hpp */
