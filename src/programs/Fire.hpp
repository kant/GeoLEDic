#ifndef Fire_hpp
#define Fire_hpp

#include "DomeWrapper.hpp"
#include "generated/Fire.hpp"

class Fire: public generated::Fire
{
public:
   Fire(const DomeWrapper& dome);
   
   virtual void runProgram();
   
private:
   enum {
      NUM_V = 32,
      NUM_H = 49
   };
   
   void calcFire();
   
   const DomeWrapper& m_dome;
   uint8_t m_heat[NUM_H][NUM_V];
   float m_h_offset;
};

#endif /* Fire_hpp */
