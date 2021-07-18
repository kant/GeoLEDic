#include "GeoLEDic.hpp"
#include "gfx/Gfx.hpp"
#include <vector>
#include "Serial.hpp"
#include <iostream>

int main()
{
   
   std::vector<gfx::LED> leds;
   std::vector<gfx::Triangle> triangles;

   std::vector<gfx::Config::View> views =
     {
       // x     y    z   FOV  horz vert
       {  0,   30, 140,  45,    0,    0},  // front
       {  0, -140, -20,  45,    0,   90},  // up
       {-78,   12, 102,  45,  -35,    6},  // slightly left
     };

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
                  .attenuationConstant(0.4)
                  .attenuationLinear(13.0)
                  .attenuationSquare(9)
                  .keyboardHandler(&Serial));
      
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
