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
   
   void showMidiSources();
   
   Config&      m_config;
   GLFWwindow*  m_window;
   
   std::map<Config::MidiPorts::PortId, std::string> m_midi_sources;
};

}


#endif /* Menu_h */
