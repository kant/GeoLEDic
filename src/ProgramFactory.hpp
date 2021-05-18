#ifndef GEOLEDIC_PROGRAM_FACTORY
#define GEOLEDIC_PROGRAM_FACTORY

#include "Triangle.hpp"
#include "Program.hpp"

class ProgramFactory
{
public:
   ProgramFactory(Triangle* triangles, unsigned num_triangles);
   ~ProgramFactory();
   Program* changeProgram(uint8_t program);

private:
   Triangle* m_triangles;
   unsigned m_num_triangles;
   Program* m_current_program;
};

#endif // GEOLEDIC_PROGRAM_FACTORY
