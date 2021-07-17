#ifndef Fire_hpp
#define Fire_hpp

#include "DomeWrapper.hpp"
#include "Program.hpp"

class Fire: public Program
{
public:
   Fire(const DomeWrapper& dome);
   
   virtual void noteOn(uint8_t note, uint8_t velocity);
   virtual void noteOff(uint8_t note);
   virtual void controlChange(uint8_t cc_num, uint8_t value);
   virtual void run();
   
private:
   enum {
      NUM_V = 32,
      NUM_H = 64
   };
   
   void calcFire();
   
   const DomeWrapper& m_dome;
   uint8_t m_heat[NUM_H][NUM_V];
   uint8_t m_sparking;
   uint8_t m_cooling;
};

#endif /* Fire_hpp */
