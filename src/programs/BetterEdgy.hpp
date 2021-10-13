#ifndef BetterEdgy_hpp
#define BetterEdgy_hpp

#include "DomeWrapper.hpp"
#include "generated/BetterEdgy.hpp"

class BetterEdgy: public generated::BetterEdgy
{
public:
   BetterEdgy(const DomeWrapper& dome);
   
   virtual void runProgram();
   
private:
   const DomeWrapper& m_dome;
};

#endif /* BetterEdgy_hpp */
