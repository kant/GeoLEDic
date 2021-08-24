#ifndef GEOLEDIC_LIGHTNING_HPP
#define GEOLEDIC_LIGHTNING_HPP

#include "DomeWrapper.hpp"
#include "generated/Lightning.hpp"

class Lightning: public generated::Lightning
{
public:
   Lightning(const DomeWrapper& dome);

   virtual void run();
   
private:
   const DomeWrapper& m_dome;
   int m_iteration;
   enum {
      NUM_H = 32,
      NUM_V = 8
   };
   CRGB m_lit_map[NUM_H][NUM_V];
};

#endif 
