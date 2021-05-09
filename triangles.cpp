#include "flogl/flogl.hpp"
#include "flogl/Config.hpp"
#include "Vector.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include <FastLED.h>
#include <math.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

#include <iostream>




class Triangle {
public:

   Triangle(
      const Edge (&edges)[3],
      const Vertex (&vertices)[3]):
         m_edges(),
         m_vertices(),
         m_led_corners()
   {
      float fac = 0.95;
      std::copy(&edges[0], &edges[3], &m_edges[0]);
      std::copy(&vertices[0], &vertices[3], &m_vertices[0]);
      m_led_corners[0] = inset(m_vertices[0], m_vertices[1], m_vertices[2], fac);
      m_led_corners[1] = inset(m_vertices[1], m_vertices[2], m_vertices[0], fac);
      m_led_corners[2] = inset(m_vertices[2], m_vertices[0], m_vertices[1], fac);
   }

   Vertex inset(const Vertex& v1, const Vertex& v2, const Vertex& v3, float fac)
   {
     return Vertex(Vector(v1) * fac +
		   Vector(v2) * ((1-fac)/2) +
		   Vector(v3) * ((1-fac)/2));
   }
      
   Edge   m_edges[3];
   Vertex m_vertices[3];
   Vertex m_led_corners[3];
};

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
   std::vector<CRGB> colors;

   std::vector<flogl::Config::View> views =
     {
     // x     y    z   FOV  horz vert
       {0,   30, 140,  45,    0,    0},  // front
       {0, -140, -20,  45,    0,   90},  // up
     };
   


   for (const Triangle& t: dome)
   {
      int i = 0;
      for (const Edge& e: t.m_edges)
      {
         int j = (i+1)%3;

         Vector vec = t.m_led_corners[j] - t.m_led_corners[i];

         int d = e.last_led - e.first_led;
         for (int l = 0; l <= d; l++)
         {
            Vertex lv(t.m_led_corners[i] + vec * ((float(l)+0.5)/(float(d)+1.0)));
            leds.push_back({-lv.x*10, lv.y*10, lv.z*10, 0.3});
            colors.push_back(CRGB::Black);
         }
         
         i++;
      }
   }
   flogl::Flogl flogl(&leds[0], leds.size(),
		      flogl::Config()
		      .views(views));
   flogl.add(&colors[0], leds.size());

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
