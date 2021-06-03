#ifndef GEOLEDIC_PROGRAM_FACTORY
#define GEOLEDIC_PROGRAM_FACTORY

#include "DomeWrapper.hpp"
#include "Strips.hpp"
#include "Program.hpp"

class ProgramFactory
{
public:
   ProgramFactory(const DomeWrapper& dome, const Strips& strips);
   ~ProgramFactory();
   Program* changeProgram(uint8_t program);

private:
   
   DomeWrapper m_dome;
   Strips m_strips;

   Program* m_current_program;
};

#endif // GEOLEDIC_PROGRAM_FACTORY
