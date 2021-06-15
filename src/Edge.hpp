#ifndef GEOLEDIC_EDGE_HPP
#define GEOLEDIC_EDGE_HPP

#include "CRGB_iterator.hpp"

struct Edge {
   enum Constants
   {
      SEGMENT_UNUSED = -1
   };
   
   Edge();
   
   // Contiguous edge
   Edge(unsigned short first_led, unsigned short last_led);
   
   // Edge consisting of two segments on the same strip, with the same direction
   Edge(unsigned short first_led_seg0, unsigned short last_led_seg0, unsigned short first_led_seg1, unsigned short last_led_seg1);
   
   CRGB_iterator begin() const;
   CRGB_iterator end() const;
   // Number of LEDs on edge
   unsigned size() const;
   
   int first_led_seg0;
   int last_led_seg0;
   int first_led_seg1;
   int last_led_seg1;
   CRGB* strip;
};

#endif
