#ifndef GEOLEDIC_EDGE_HPP
#define GEOLEDIC_EDGE_HPP

#include "CRGB_iterator.hpp"

class Edge
{
   
public:
   Edge();
   
   // Contiguous edge
   Edge(unsigned short first_led, unsigned short last_led);
   
   // Edge consisting of two segments on the same strip, with the same direction
   Edge(unsigned short first_led_seg0, unsigned short last_led_seg0, unsigned short first_led_seg1, unsigned short last_led_seg1);
   
   CRGB_iterator begin() const;
   CRGB_iterator end() const;
   // Number of LEDs on edge
   unsigned size() const;
   
   unsigned firstLedOnStrip() const;
   unsigned lastLedOnStrip() const;
   unsigned firstLedOnEdge() const;
   unsigned lastLedOnEdge() const;

   // split, or non-contiguous, consisting of two segments
   bool isSplit() const;
   
   // LEDs run backwards on strip
   bool isReverse() const;
   
   void assign(CRGB* strip);
   
private:
   
   struct {
      int first_led;
      int last_led;
   } m_segments[2];
   CRGB* m_strip;
};

#endif
