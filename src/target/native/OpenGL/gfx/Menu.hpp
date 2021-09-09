#ifndef Menu_h
#define Menu_h

#include "Config.hpp"

struct GLFWwindow;

namespace gfx {

class Menu
{
public:
   Menu(Config& config, GLFWwindow* window);
   ~Menu();
   
   void draw();
   
private:
   typedef std::map<Config::MidiPorts::PortId, std::string> MidiPortMap;

   void showMidiPorts(Config::MidiPorts& ports, MidiPortMap& map);

   Config&      m_config;
   GLFWwindow*  m_window;
   
   MidiPortMap m_midi_sources;
   MidiPortMap m_midi_destinations;
};

}


#endif /* Menu_h */
