#ifndef GEOLEDIC_DEFAULT_RAINBOW_HPP
#define GEOLEDIC_DEFAULT_RAINBOW_HPP

#include "Triangle.hpp"
#include "Program.hpp"

class DefaultRainbow: public Program
{
public:
   DefaultRainbow(Triangle* triangles, unsigned num_triangles);
   
   virtual void noteOn(uint8_t note, uint8_t velocity);
   virtual void noteOff(uint8_t note);
   virtual void controlChange(uint8_t cc_num, uint8_t value);
   virtual void run();
   
private:
   Triangle* m_triangles;
   unsigned m_num_triangles;
   int m_iteration;
};

#endif 
