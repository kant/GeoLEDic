#ifndef GEOLEDIC_MOVING_RAINBOW_HPP
#define GEOLEDIC_MOVING_RAINBOW_HPP

#include "DomeWrapper.hpp"
#include "generated/MovingRainbow.hpp"

class MovingRainbow: public generated::MovingRainbow
{
public:
   MovingRainbow(const DomeWrapper& dome);
   
   virtual void run();
   
private:
   const DomeWrapper& m_dome;
   int m_iteration_h;
   int m_iteration_v;
};

#endif 
