#ifndef GEOLEDIC_EDGE_HPP
#define GEOLEDIC_EDGE_HPP

struct Edge {
   enum Constants
   {
      SEGMENT_UNUSED = -1
   };
   
   Edge():
      first_led_seg0(SEGMENT_UNUSED),
      last_led_seg0(SEGMENT_UNUSED),
      first_led_seg1(SEGMENT_UNUSED),
      last_led_seg1(SEGMENT_UNUSED)
   {}
   
   // Contiguous edge
   Edge(unsigned short first_led, unsigned short last_led):
      first_led_seg0(first_led),
      last_led_seg0(last_led),
      first_led_seg1(SEGMENT_UNUSED),
      last_led_seg1(SEGMENT_UNUSED)
   {}
   // Edge consisting of two segments on the same strip, with the same direction
   Edge(unsigned short first_led_seg0, unsigned short last_led_seg0, unsigned short first_led_seg1, unsigned short last_led_seg1):
      first_led_seg0(first_led_seg0),
      last_led_seg0(last_led_seg0),
      first_led_seg1(first_led_seg1),
      last_led_seg1(last_led_seg1)
   {
   }
   
   int first_led_seg0;
   int last_led_seg0;
   int first_led_seg1;
   int last_led_seg1;
};


#endif
