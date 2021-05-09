#ifndef GEOLEDIC_TRIANGLE_HPP
#define GEOLEDIC_TRIANGLE_HPP

#include "Vector.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

#include "flogl/flogl.hpp"

class Triangle {
public:
   Triangle(
      const Edge (&edges)[3],
            const Vertex (&vertices)[3]);
   
   void createLeds(std::vector<flogl::LED>& leds) const;
    
private:
   Vertex inset(const Vertex& v1, const Vertex& v2, const Vertex& v3, float fac);
      
   Edge   m_edges[3];
   Vertex m_vertices[3];
   Vertex m_led_corners[3];
};

#endif
