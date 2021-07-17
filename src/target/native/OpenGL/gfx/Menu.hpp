#ifndef Menu_h
#define Menu_h

#include "Config.hpp"

struct GLFWwindow;

namespace gfx {

class Menu
{
public:
   Menu(const Config& config, GLFWwindow* window);
   ~Menu();
   
   void draw();
   
private:
   GLFWwindow*  m_window;
};

}


#endif /* Menu_h */
