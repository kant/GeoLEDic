#include "GeoLEDic.hpp"
#include "gfx/Gfx.hpp"
#include <vector>
#include "Serial.hpp"
#include "MidiMenu.hpp"
#include <iostream>


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

   MidiMenu midi_menu(getMidiSource(), getProgramFactory());
   
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
                  .menu(&midi_menu));
            
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
