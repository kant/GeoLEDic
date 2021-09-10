#ifndef MidiMenu_hpp
#define MidiMenu_hpp

#include "gfx/Config.hpp"
#include "MidiSource.hpp"
#include "ProgramFactory.hpp"

class MidiMenu: public gfx::Config::MenuPresenter
{
public:
   MidiMenu(MidiSource& midi_source, ProgramFactory& program_factory);
   
   virtual void drawMenu();
   
private:
   typedef std::map<MidiSource::MidiPorts::PortId, std::string> MidiPortMap;
   
   void showMidiPorts(MidiSource::MidiPorts& ports, MidiPortMap& map);

   MidiSource& m_midi_source;
   ProgramFactory& m_factory;
   
   MidiPortMap m_midi_sources;
   MidiPortMap m_midi_destinations;
};

#endif /* MidiMenu_hpp */
