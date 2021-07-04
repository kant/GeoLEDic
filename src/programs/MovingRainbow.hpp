#ifndef GEOLEDIC_MOVING_RAINBOW_HPP
#define GEOLEDIC_MOVING_RAINBOW_HPP

#include "DomeWrapper.hpp"
#include "Program.hpp"

class MovingRainbow: public Program
{
public:
   MovingRainbow(const DomeWrapper& dome);
   
   virtual void noteOn(uint8_t note, uint8_t velocity);
   virtual void noteOff(uint8_t note);
   virtual void controlChange(uint8_t cc_num, uint8_t value);
   virtual void run();
   
private:
   const DomeWrapper& m_dome;
   int m_stride_h;
   int m_speed_h;
   int m_stride_v;
   int m_speed_v;
   int m_iteration_h;
   int m_iteration_v;
};

#endif 
