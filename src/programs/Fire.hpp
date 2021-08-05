#ifndef Fire_hpp
#define Fire_hpp

#include "DomeWrapper.hpp"
#include "Notes.hpp"

class Fire: public Notes
{
public:
   Fire(const DomeWrapper& dome);
   
   virtual void controlChange(uint8_t cc_num, uint8_t value);
   virtual void run();
   
private:
   enum {
      NUM_V = 32,
      NUM_H = 49
   };
   
   void calcFire();
   
   const DomeWrapper& m_dome;
   uint8_t m_heat[NUM_H][NUM_V];
   uint8_t m_sparking;
   uint8_t m_cooling;
   const TProgmemRGBPalette16* m_palette;
   bool m_reverse_palette;
   bool m_reverse_direction;
};

#endif /* Fire_hpp */
