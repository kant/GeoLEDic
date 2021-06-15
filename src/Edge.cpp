#include "Edge.hpp"

Edge::Edge():
   first_led_seg0(SEGMENT_UNUSED),
   last_led_seg0(SEGMENT_UNUSED),
   first_led_seg1(SEGMENT_UNUSED),
   last_led_seg1(SEGMENT_UNUSED),
   strip(nullptr)
{}

// Contiguous edge
Edge::Edge(unsigned short first_led, unsigned short last_led):
   first_led_seg0(first_led),
   last_led_seg0(last_led),
   first_led_seg1(SEGMENT_UNUSED),
   last_led_seg1(SEGMENT_UNUSED),
   strip(nullptr)
{}
// Edge consisting of two segments on the same strip, with the same direction
Edge::Edge(unsigned short first_led_seg0, unsigned short last_led_seg0, unsigned short first_led_seg1, unsigned short last_led_seg1):
   first_led_seg0(first_led_seg0),
   last_led_seg0(last_led_seg0),
   first_led_seg1(first_led_seg1),
   last_led_seg1(last_led_seg1),
   strip(nullptr)
{
}

CRGB_iterator Edge::begin() const
{
   if (first_led_seg0 < last_led_seg0)
   {
      return {&strip[first_led_seg0],
              &strip[first_led_seg0],
              &strip[last_led_seg0 + 1],
              CRGB_iterator::FORWARD};
   }
   else
   {
      return {&strip[first_led_seg0],
              &strip[last_led_seg0],
              &strip[first_led_seg0 + 1],
              CRGB_iterator::BACKWARD};
   }
}

CRGB_iterator Edge::end() const
{
   return {&strip[first_led_seg0], CRGB_iterator::invalid_iterator_tag()};
}

unsigned Edge::size() const
{
   if (first_led_seg0 < last_led_seg0)
   {
      return last_led_seg0 - first_led_seg0 + 1;
   }
   else
   {
      return first_led_seg0 - last_led_seg0 + 1;
   }
}
