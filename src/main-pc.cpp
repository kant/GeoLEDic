#include "GeoLEDic.hpp"
#include "gfx/Gfx.hpp"
#include <vector>
#include "Serial.hpp"
#include <iostream>
#include "ProgramFactory.hpp"

extern ProgramFactory factory;
extern Program* program;

int main()
{
   std::vector<gfx::LED> leds;
   std::vector<gfx::Triangle> triangles;

   std::vector<gfx::Config::View> views =
     {
       //  x     y     z   FOV  horz vert
       {   0,   3,    14,  45,    0,    0},  // front
       {   0, -14,    -2,  45,    0,   90},  // up
       {-7.8, 1.2,  10.2,  45,  -35,    6},  // slightly left
     };

   class ProgramMenu: public gfx::Config::MenuPresenter
   {
   public:
      virtual void drawMenu()
      {
         factory.drawMenu(&program);
         if (program) program->drawMenu();
      }
   } program_menu;
   
   try {
      int i = 0;
      for (const Triangle& t: dome)
      {
         t.createLeds(leds, triangles, i);
         i++;
      }
      gfx::Gfx gfx(
               leds,
               triangles,
               gfx::Config()
                  .views(views)
                  .framesPerSecond(30)
                  .strafingSpeed(2)
                  .cutoffDistance(0.6)
                  .attenuationConstant(0.4)
                  .attenuationLinear(130.0)
                  .attenuationSquare(900.0)
                  .keyboardHandler(&Serial)
                  .midiPorts(getMidiPorts())
                  .midiOutPorts(getMidiOutPorts())
                  .topMenuPresenter(&program_menu));
      
      setupGeoLEDic();
      
      do {
         loopGeoLEDic();
      } while(gfx.draw());
   }
   catch (std::exception& e)
   {
      std::cerr << std::endl << "=== Exception: " << e.what() << " ===" << std::endl << std::endl;
      return 1;
   }
   return 0;
}
