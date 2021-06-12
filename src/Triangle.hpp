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

#include <iterator>

class Triangle {
public:
   Triangle(
            CRGB* led_strip,
            const Edge (&edges)[3],
            const Vertex (&vertices)[3]);
   
#ifdef WITH_FLOGL
   void createLeds(std::vector<flogl::LED>& leds) const;
#endif

   struct CRGB_iterator: public std::iterator<std::forward_iterator_tag, CRGB>
   {
      CRGB_iterator(pointer ptr): m_ptr(ptr) {}

      reference operator*() const { return *m_ptr; }
      pointer operator->() { return m_ptr; }

      // Prefix increment
      CRGB_iterator& operator++() { m_ptr++; return *this; }

      // Postfix increment
      CRGB_iterator operator++(int) { CRGB_iterator tmp = *this; ++(*this); return tmp; }

      friend bool operator== (const CRGB_iterator& a, const CRGB_iterator& b) { return a.m_ptr == b.m_ptr; };
      friend bool operator!= (const CRGB_iterator& a, const CRGB_iterator& b) { return a.m_ptr != b.m_ptr; };

  private:
      pointer m_ptr;
   };
   
   CRGB_iterator begin();
   CRGB_iterator end();
   
private:
   Vertex inset(const Vertex& v1, const Vertex& v2, const Vertex& v3, float fac);
      
   Edge   m_edges[3];
   Vertex m_led_corners[3];
   int m_first;
   int m_last;
   CRGB* m_strip;
};

#endif
