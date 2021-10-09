#ifndef Edgy_hpp
#define Edgy_hpp

#include "DomeWrapper.hpp"
#include "generated/Edgy.hpp"

class Edgy: public generated::Edgy
{
public:
   Edgy(const DomeWrapper& dome);
   
   virtual void runProgram();
   
private:
   const DomeWrapper& m_dome;
};

#endif /* Edgy_hpp */
