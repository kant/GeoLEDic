#ifndef DecayingShapesFromNotes_hpp
#define DecayingShapesFromNotes_hpp

#include "ShapesFromNotes.hpp"

class DecayingShapesFromNotes: public ShapesFromNotes
{
public:
   DecayingShapesFromNotes();

   // call at the beginning of the run() function of the program to decay velocity values
   void updateDecayingShapes();

   void setDecayRate(uint8_t rate);

   uint8_t getTriangleValue(uint8_t note) const;
   
private:
   uint8_t m_decay_rate;
   uint8_t m_decaying_triangles[DOME_NUM_TRIANGLES];
};

#endif /* DecayingShapesFromNotes_hpp */
