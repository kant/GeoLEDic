#ifndef GEOLEDIC_DEFAULT_RAINBOW_HPP
#define GEOLEDIC_DEFAULT_RAINBOW_HPP

#include "DomeWrapper.hpp"
#include "generated/DefaultRainbow.hpp"

class DefaultRainbow: public generated::DefaultRainbow
{
public:
   DefaultRainbow(const DomeWrapper& dome);
   
   virtual void noteOn(uint8_t note, uint8_t velocity, uint8_t /*channel*/);
   virtual void noteOff(uint8_t note, uint8_t /*channel*/);
   virtual void run();
   
private:
   const DomeWrapper& m_dome;
   int m_iteration;
};

#endif 
