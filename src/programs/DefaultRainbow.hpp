#ifndef GEOLEDIC_DEFAULT_RAINBOW_HPP
#define GEOLEDIC_DEFAULT_RAINBOW_HPP

#include "DomeWrapper.hpp"
#include "Program.hpp"

class DefaultRainbow: public Program
{
public:
   DefaultRainbow(const DomeWrapper& dome);
   
   virtual void noteOn(uint8_t note, uint8_t velocity, uint8_t /*channel*/);
   virtual void noteOff(uint8_t note, uint8_t /*channel*/);
   virtual void controlChange(uint8_t cc_num, uint8_t value);
   virtual void run();
   
private:
   const DomeWrapper& m_dome;
   int m_sparkle_probability;
   int m_stride;
   int m_speed;
   int m_iteration;
};

#endif 
