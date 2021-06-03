#ifndef GEOLEDIC_TRIANGLE_HPP
#define GEOLEDIC_TRIANGLE_HPP

#include "Vector.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

#define FASTLED_INTERNAL // get rid of annoying version pragma
#ifdef WITH_FLOGL
#include "flogl/flogl.hpp"
#endif
#include "FastLED.h"

class Triangle {
public:
   Triangle(
            CRGB* led_strip,
            const Edge (&edges)[3],
            const Vertex (&vertices)[3]);
   
#ifdef WITH_FLOGL
   void createLeds(std::vector<flogl::LED>& leds) const;
#endif

   CRGB* begin();
   CRGB* end();
   
private:
   Vertex inset(const Vertex& v1, const Vertex& v2, const Vertex& v3, float fac);
      
   Edge   m_edges[3];
   Vertex m_vertices[3];
   Vertex m_led_corners[3];
   int m_first;
   int m_last;
   CRGB* m_strip;
};

#endif
