#ifndef GEOLEDIC_PROGRAM_FACTORY
#define GEOLEDIC_PROGRAM_FACTORY

#include "Triangle.hpp"
#include "Program.hpp"

class ProgramFactory
{
public:
   ProgramFactory(Triangle* triangles, unsigned num_triangles, CRGB* strips, unsigned num_strips, unsigned leds_per_strip);
   ~ProgramFactory();
   Program* changeProgram(uint8_t program);

private:
   Triangle* m_triangles;
   unsigned m_num_triangles;
   CRGB* m_strips;
   unsigned m_num_strips;
   unsigned m_leds_per_strip;

   Program* m_current_program;
};

#endif // GEOLEDIC_PROGRAM_FACTORY
