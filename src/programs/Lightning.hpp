#ifndef GEOLEDIC_LIGHTNING_HPP
#define GEOLEDIC_LIGHTNING_HPP

#include "DomeWrapper.hpp"
#include "Program.hpp"

class Lightning: public Program
{
public:
   Lightning(const DomeWrapper& dome);
   
   virtual void noteOn(uint8_t note, uint8_t velocity, uint8_t channel);
   virtual void noteOff(uint8_t note, uint8_t channel);
   virtual void controlChange(uint8_t cc_num, uint8_t value);
   virtual void run();
   
private:
   const DomeWrapper& m_dome;
   int m_probability;
   int m_forking_probability;
   int m_iteration;
   enum {
      NUM_H = 32,
      NUM_V = 8
   };
   CRGB m_lit_map[NUM_H][NUM_V];
};

#endif 
