#ifndef GEOLEDIC_SparklesAndTriangles_hpp
#define GEOLEDIC_SparklesAndTriangles_hpp

#include "Triangle.hpp"
#include "Program.hpp"

class SparklesAndTriangles: public Program
{
public:
   SparklesAndTriangles(Triangle* triangles, unsigned num_triangles);
   
   virtual void noteOn(uint8_t note, uint8_t velocity);
   virtual void noteOff(uint8_t note);
   virtual void controlChange(uint8_t cc_num, uint8_t value);
   virtual void run();
   
private:
   Triangle* m_triangles;
   unsigned m_num_triangles;
   int m_red;
   int m_green;
   int m_blue;
   int m_sparkle_probability;
   int m_iteration;
   unsigned m_notes[128];
   
};

#endif /* GEOLEDIC_SparklesAndTriangles_hpp */
