#ifndef GEOLEDIC_DEFAULT_RAINBOW_HPP
#define GEOLEDIC_DEFAULT_RAINBOW_HPP

#include "DomeWrapper.hpp"
#include "generated/DefaultRainbow.hpp"

class DefaultRainbow: public generated::DefaultRainbow
{
public:
   DefaultRainbow(const DomeWrapper& dome);
   
   virtual void runProgram();
   
private:
   const DomeWrapper& m_dome;
   int m_iteration;
};

#endif 
