#ifndef GEOLEDIC_SparklesAndTriangles_hpp
#define GEOLEDIC_SparklesAndTriangles_hpp

#include "DomeWrapper.hpp"
#include "generated/SparklesAndTriangles.hpp"

class SparklesAndTriangles: public generated::SparklesAndTriangles
{
public:
   SparklesAndTriangles(const DomeWrapper& dome);
   
   virtual void runProgram();

private:
   const DomeWrapper& m_dome;
   int m_iteration;
   
};

#endif /* GEOLEDIC_SparklesAndTriangles_hpp */
