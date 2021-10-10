#ifndef WarpDriveMandala_hpp
#define WarpDriveMandala_hpp

#include "DomeWrapper.hpp"
#include "generated/WarpDriveMandala.hpp"

class WarpDriveMandala: public generated::WarpDriveMandala
{
public:
   WarpDriveMandala(const DomeWrapper& dome);
   
   virtual void runProgram();
   
private:
   void shiftAndFillRings();
   bool findKey(uint8_t& hue, uint8_t& saturation);

   const DomeWrapper& m_dome;
   CRGB m_rings[Vertex::NUM_THETA_STEPS];
};

#endif /* WarpDriveMandala_hpp */
