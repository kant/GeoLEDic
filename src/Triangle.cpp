#include "Triangle.hpp"
#include <climits>
#include <algorithm>

Triangle::Triangle(
   CRGB* strip,
   const Edge (&edges)[3],
   const Vertex (&vertices)[3]):
      m_edges(),
      m_led_corners(),
      m_first_corner_led(edges[0].firstLedOnEdge()),
      m_first_led(INT_MAX),
      m_last_led(0),
      m_reverse(edges[0].isReverse()),
      m_strip(strip)
{
   float fac = 0.95;
   std::copy(&edges[0], &edges[3], &m_edges[0]);
   // the LEDs are not on the triangle's edge, but slightly inset.
   m_led_corners[0] = inset(vertices[0], vertices[1], vertices[2], fac);
   m_led_corners[1] = inset(vertices[1], vertices[2], vertices[0], fac);
   m_led_corners[2] = inset(vertices[2], vertices[0], vertices[1], fac);
   
   // find the first and the last led of strip
   for (Edge& e: m_edges)
   {
      // we're passing this in here because it would have made the constructor more verbose,
      //  leading to even more stuff to supply in Dome.cpp
      e.assign(strip);
      m_first_led = std::min(e.firstLedOnStrip(), m_first_led);
      m_last_led  = std::max(e.lastLedOnStrip(), m_last_led);
   }
}

CRGB_iterator Triangle::begin()
{
   return {&m_strip[m_first_corner_led],
           &m_strip[m_first_led],
           &m_strip[m_last_led],
           m_reverse ? CRGB_iterator::BACKWARD : CRGB_iterator::FORWARD
   };
}

CRGB_iterator Triangle::end()
{
   return {&m_strip[m_first_corner_led], CRGB_iterator::invalid_iterator_tag()};
}

Vertex Triangle::inset(const Vertex& v1, const Vertex& v2, const Vertex& v3, float fac)
{
   return Vertex(Vector(v1) * fac +
                 Vector(v2) * ((1-fac)/2) +
                 Vector(v3) * ((1-fac)/2));
}

unsigned Triangle::size() const
{
   return m_last_led - m_first_led + 1;
}

const Edge& Triangle::edge(unsigned edge_ix)
{
   if (edge_ix > 2) edge_ix = 2;
   return m_edges[edge_ix];
}

#ifdef WITH_FLOGL
void Triangle::createLeds(std::vector<flogl::LED>& leds) const
{
   auto i = 0;
   for (const Edge& e: m_edges)
   {
      // distribute LEDs along edge
      const Vertex& start_corner = m_led_corners[i];
      const Vertex& end_corner = m_led_corners[(i+1)%3];
      const Vector edge_vector = end_corner - start_corner;

      int num_leds = e.size();
      int led_ix = 0;
      for (CRGB& led: e)
      {
         Vertex led_vertex(start_corner + edge_vector * ((float(led_ix)+0.5)/float(num_leds)));
         leds.push_back(led_vertex);
         leds.back().color = &led;
         led_ix++;
      }
      
      i++;
   }
}
#endif
