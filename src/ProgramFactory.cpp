#include "ProgramFactory.hpp"

#include "programs/SparklesAndTriangles.hpp"
#include "programs/DefaultRainbow.hpp"
#include "programs/Diagnostic.hpp"

ProgramFactory::ProgramFactory(const DomeWrapper& dome, CRGB* strips, unsigned num_strips, unsigned leds_per_strip):
      m_dome(dome),
      m_strips(strips),
      m_num_strips(num_strips),
      m_leds_per_strip(leds_per_strip),
      m_current_program(nullptr)
{
}

Program* ProgramFactory::changeProgram(uint8_t program)
{
   delete m_current_program;
   switch (program)
   {
   case 1:
      m_current_program = new SparklesAndTriangles(m_dome);
      break;
   case 127:
      m_current_program = new Diagnostic(m_dome, m_strips, m_num_strips, m_leds_per_strip);
      break;
   default:
      m_current_program = new DefaultRainbow(m_dome);
   }
   return m_current_program;
}

ProgramFactory::~ProgramFactory()
{
   delete m_current_program;
}
