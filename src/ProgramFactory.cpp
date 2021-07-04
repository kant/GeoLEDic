#include "ProgramFactory.hpp"

#include "programs/SparklesAndTriangles.hpp"
#include "programs/DefaultRainbow.hpp"
#include "programs/Diagnostic.hpp"
#include "programs/Fire.hpp"
#include "programs/MovingRainbow.hpp"

ProgramFactory::ProgramFactory(const DomeWrapper& dome, const Strips& strips):
      m_dome(dome),
      m_strips(strips),
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
   case 2:
      m_current_program = new Fire(m_dome);
      break;
   case 3:
      m_current_program = new MovingRainbow(m_dome);
      break;
   case 127:
      m_current_program = new Diagnostic(m_dome, m_strips);
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
