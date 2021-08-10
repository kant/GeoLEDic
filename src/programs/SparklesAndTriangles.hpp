#ifndef GEOLEDIC_SparklesAndTriangles_hpp
#define GEOLEDIC_SparklesAndTriangles_hpp

#include "DomeWrapper.hpp"
#include "NotesWithMappings.hpp"

class SparklesAndTriangles: public NotesWithMappings
{
public:
   SparklesAndTriangles(const DomeWrapper& dome);
   
   virtual void controlChange(uint8_t cc_num, uint8_t value);
   virtual void run();
   
private:
   const DomeWrapper& m_dome;
   int m_red;
   int m_green;
   int m_blue;
   int m_sparkle_probability;
   int m_iteration;
   
};

#endif /* GEOLEDIC_SparklesAndTriangles_hpp */
