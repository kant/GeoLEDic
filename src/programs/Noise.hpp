#ifndef Noise_hpp
#define Noise_hpp

#include "DomeWrapper.hpp"
#include "generated/Noise.hpp"

class Noise: public generated::Noise
{
public:
   Noise(const DomeWrapper& dome);
   
   virtual void run();
   
private:
   enum {
      NUM_V = 8,
      NUM_H = 16
   };
   
   void calcNoise();
   
   const DomeWrapper& m_dome;
   uint8_t m_noise[NUM_H][NUM_V];
   uint16_t m_x;
   uint16_t m_y;
   uint16_t m_t;
   float m_h_offset;
};

#endif /* Noise_hpp */
