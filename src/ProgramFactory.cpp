#include "ProgramFactory.hpp"

#include "programs/SparklesAndTriangles.hpp"
#include "programs/DefaultRainbow.hpp"

ProgramFactory::ProgramFactory(Triangle* triangles, unsigned num_triangles):
      m_triangles(triangles),
      m_num_triangles(num_triangles),
      m_current_program(nullptr)
{
}

Program* ProgramFactory::changeProgram(uint8_t program)
{
   delete m_current_program;
   switch (program)
   {
   case 1:
      m_current_program = new SparklesAndTriangles(m_triangles, m_num_triangles);
      break;
   default:
      m_current_program = new DefaultRainbow(m_triangles, m_num_triangles);
   }
   return m_current_program;
}

ProgramFactory::~ProgramFactory()
{
   delete m_current_program;
}
