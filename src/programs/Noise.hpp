#ifndef Noise_hpp
#define Noise_hpp

#include "DomeWrapper.hpp"
#include "generated/Noise.hpp"

class Noise: public generated::Noise
{
public:
   Noise(const DomeWrapper& dome);
   
   virtual void runProgram();
   
private:
   enum {
      NUM_V = 8,
      NUM_H = 16
   };
   
   void calcNoise();
   
   const DomeWrapper& m_dome;
   uint8_t m_noise[NUM_H][NUM_V];
   unsigned m_x;
   unsigned m_y;
   unsigned m_t;
   float m_h_offset;
};

#endif /* Noise_hpp */
