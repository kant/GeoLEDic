#ifndef FLOGL_HPP
#define FLOGL_HPP

#include "platform.h"
#include "FastLED.h"
#include "Config.hpp"

namespace flogl {

struct LED{
   LED(float x, float y, float z):
         x(x), y(y), z(z),
         color(NULL)
   {
   }

	float x, y, z;
   CRGB* color;
};

struct Vertex {
   Vertex():
      x(0), y(0), z(0)
   {}
   Vertex(float x, float y, float z):
      x(x), y(y), z(z)
   {}
   float x, y, z;
   int start_led_ix;
   int num_leds;
};

struct Triangle {
   Triangle()
   {
   }
   
   Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, int start_led_ix, int num_leds)
   {
      vertices[0] = v0;
      // Only set the index and count on the first vertex.
      // The only reason we have the members on all 3 vertices is
      // so the vertices are evenly spaced, and we can use sizeof(Vertex)
      // as stride in the vertex buffer
      vertices[0].start_led_ix = start_led_ix;
      vertices[0].num_leds = num_leds;
      vertices[1] = v1;
      vertices[2] = v2;
   }
   
   Vertex vertices[3];
};

class Flogl
{
public:
   Flogl(std::vector<LED>& led_coordinates, const Config& config = Config());
   Flogl(std::vector<LED>& led_coordinates, std::vector<Triangle>& triangles, const Config& config = Config());

   bool draw();
   
   ~Flogl();
private:
   class Impl;
   Impl& m_i;
};

}
#endif // FLOGL_HPP
