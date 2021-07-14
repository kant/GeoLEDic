#include "GeoLEDic.hpp"
#include "flogl/flogl.hpp"
#include <vector>
#include <unistd.h>
#include "Serial.hpp"
#include <iostream>

int main()
{
   
   std::vector<flogl::LED> leds;
   std::vector<flogl::Triangle> triangles;

   std::vector<flogl::Config::View> views =
     {
     // x     y    z   FOV  horz vert
       {0,   30, 140,  45,    0,    0},  // front
       {0, -140, -20,  45,    0,   90},  // up
     };

   try {
      int i = 0;
      for (const Triangle& t: dome)
      {
         t.createLeds(leds, triangles, i);
         i++;
      }
      flogl::Flogl flogl(
               leds,
               triangles,
               flogl::Config()
                  .views(views)
                  .keyboardHandler(&Serial));
      
      setupGeoLEDic();
      
      do {
         loopGeoLEDic();
         usleep(30000);
      } while(flogl.draw());
   }
   catch (std::exception& e)
   {
      std::cerr << std::endl << "=== Exception: " << e.what() << " ===" << std::endl << std::endl;
      return 1;
   }
   return 0;
}
