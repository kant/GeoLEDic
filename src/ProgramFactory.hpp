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
   void changeProgram(uint8_t program);
   Program& program();

#ifdef WITH_GFX
   void drawMenu(MidiSource::MidiSender* sender);
#endif

private:
   
   DomeWrapper m_dome;
   Strips m_strips;

   Program* m_current_program;
   uint8_t  m_program_number;
};

#endif // GEOLEDIC_PROGRAM_FACTORY
