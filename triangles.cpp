#include "flogl/flogl.hpp"
#include "flogl/Config.hpp"
#include "Triangle.hpp"
#include <FastLED.h>
#include <math.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

#include <iostream>

int default_led(int step)
{
   static int led = 0;
   int old = led;
   led += step;
   return old;
}

#define DEFAULT_TRIANGLE {{default_led(50), default_led(1)},{default_led(50), default_led(1)},{default_led(50), default_led(1)}}

#include "dome.hpp"

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
   
   std::vector<CRGB> colors(leds.size(), CRGB::Black);
   CRGB* col = colors.data();
   for (flogl::LED& led: leds)
   {
      led.color = col++;
   }

   int r = 0;
   int g = 0;
   int b = 0;
   int c0 = 0;
   
   do {
      int c1 = 0;
      for (CRGB& l: colors)
      {
         int c = c0 + c1;
         if (rand() % 100 == 0)
         {
            l = CRGB::White;
         }
         else
         {
            int colr = float(r)/2 * float(c % 100)/100;
            int colg = float(g)/2 * float((c+30) % 100)/100;
            int colb = float(b)/2 * float((c+60) % 100)/100;
            
            l = CRGB(colr < 255 ? colr : 255,
                     colg < 255 ? colg : 255,
                     colb < 255 ? colb : 255);
         }
         c1++;
      }

      usleep(30000);
      if (r < 2*200) r++;
      else if (g < 2*200) g++;
      else if (b < 2*200) b++;
      
      c0++;
   } while(flogl.draw());
   
   return 0;
}
