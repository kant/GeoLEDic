#include "GeoLEDic.hpp"
#include "flogl/flogl.hpp"
#include <vector>
#include <unistd.h>

int main()
{

   std::vector<flogl::LED> leds;

   std::vector<flogl::Config::View> views =
     {
     // x     y    z   FOV  horz vert
       {0,   30, 140,  45,    0,    0},  // front
       {0, -140, -20,  45,    0,   90},  // up
     };

   for (const Triangle& t: dome)
   {
      t.createLeds(leds);
   }
   flogl::Flogl flogl(&leds[0], leds.size(),
            flogl::Config()
            .views(views));
   
   setupGeoLEDic();
   
   do {
      loopGeoLEDic();
      usleep(30000);
   } while(flogl.draw());
   
   return 0;
}
