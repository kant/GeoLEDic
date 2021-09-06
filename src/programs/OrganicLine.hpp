#ifndef OrganicLine_hpp
#define OrganicLine_hpp

#include "DomeWrapper.hpp"
#include "generated/OrganicLine.hpp"

class OrganicLine: public generated::OrganicLine
{
public:
   OrganicLine(const DomeWrapper& dome);
   
   virtual void run();
   
private:
   const DomeWrapper& m_dome;
   unsigned m_time;
};

#endif /* OrganicLine_hpp */
