#ifndef DecayingShapesFromNotes_hpp
#define DecayingShapesFromNotes_hpp

#include "ShapesFromNotes.hpp"

class DecayingShapesFromNotes: public ShapesFromNotes
{
public:
   DecayingShapesFromNotes();

   virtual void run();

   void setDecayRate(uint8_t rate);

   uint8_t getTriangleValue(uint8_t note) const;
   bool isAnyTriangleSet() const;
   
private:
   uint8_t m_decay_rate;
   bool m_any_triangle_set;
   uint8_t m_decaying_triangles[DOME_NUM_TRIANGLES];
};

#endif /* DecayingShapesFromNotes_hpp */
