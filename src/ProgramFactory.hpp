#ifndef GEOLEDIC_PROGRAM_FACTORY
#define GEOLEDIC_PROGRAM_FACTORY

#include "DomeWrapper.hpp"
#include "Program.hpp"

class ProgramFactory
{
public:
   ProgramFactory(const DomeWrapper& dome, CRGB* strips, unsigned num_strips, unsigned leds_per_strip);
   ~ProgramFactory();
   Program* changeProgram(uint8_t program);

private:
   
   DomeWrapper m_dome;
   CRGB* m_strips;
   unsigned m_num_strips;
   unsigned m_leds_per_strip;

   Program* m_current_program;
};

#endif // GEOLEDIC_PROGRAM_FACTORY
