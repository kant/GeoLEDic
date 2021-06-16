#include "Edge.hpp"
#include <algorithm>

namespace {
const int SEGMENT_UNUSED = -1;
}

Edge::Edge():
   m_segments{{SEGMENT_UNUSED, SEGMENT_UNUSED}, {SEGMENT_UNUSED, SEGMENT_UNUSED}},
   m_strip(nullptr)
{}

// Contiguous edge
Edge::Edge(unsigned short first_led, unsigned short last_led):
   m_segments{{first_led, last_led}, {SEGMENT_UNUSED, SEGMENT_UNUSED}},
   m_strip(nullptr)
{}
// Edge consisting of two segments on the same strip, with the same direction
Edge::Edge(unsigned short first_led_seg0, unsigned short last_led_seg0, unsigned short first_led_seg1, unsigned short last_led_seg1):
   m_segments{{first_led_seg0, last_led_seg0}, {first_led_seg1, last_led_seg1}},
   m_strip(nullptr)
{
}

CRGB_iterator Edge::begin() const
{
   if (not isSplit())
   {
      return {&m_strip[m_segments[0].first_led],
                 &m_strip[firstLedOnStrip()],
                 &m_strip[lastLedOnStrip()],
                 isReverse() ? CRGB_iterator::BACKWARD : CRGB_iterator::FORWARD
      };
   }
   else
   {
      return {&m_strip[m_segments[0].first_led],
              &m_strip[m_segments[0].last_led],
              &m_strip[m_segments[1].first_led],
              &m_strip[m_segments[1].last_led],
              isReverse() ? CRGB_iterator::BACKWARD : CRGB_iterator::FORWARD
      };
   }
}

CRGB_iterator Edge::end() const
{
   if (not isSplit())
   {
      return {&m_strip[m_segments[0].first_led], CRGB_iterator::invalid_iterator_tag()};
   }
   else
   {
      if (not isReverse())
      {
         return {&m_strip[m_segments[1].last_led + 1], CRGB_iterator::invalid_iterator_tag()};
      }
      else
      {
         return {&m_strip[m_segments[1].first_led + 1], CRGB_iterator::invalid_iterator_tag()};
      }
   }
}

unsigned Edge::size() const
{
   unsigned sz = abs(m_segments[0].last_led - m_segments[0].first_led) + 1;
   if (isSplit())
   {
      sz += abs(m_segments[1].last_led - m_segments[1].first_led) + 1;
   }
   return sz;
}

unsigned Edge::firstLedOnStrip() const
{
   int first_led = std::min(m_segments[0].first_led, m_segments[0].last_led);
   if (isSplit())
   {
      first_led = std::min(first_led, std::min(m_segments[1].first_led, m_segments[1].last_led));
   }
   return first_led;
}

unsigned Edge::lastLedOnStrip() const
{
   int last_led = std::max(m_segments[0].first_led, m_segments[0].last_led);
   if (isSplit())
   {
      last_led = std::max(last_led, std::max(m_segments[1].first_led, m_segments[1].last_led));
   }
   return last_led;
}

unsigned Edge::firstLedOnEdge() const
{
   return m_segments[0].first_led;
}

bool Edge::isSplit() const
{
   return m_segments[1].first_led != SEGMENT_UNUSED;
}

bool Edge::isReverse() const
{
   return m_segments[0].first_led > m_segments[0].last_led;
}

void Edge::assign(CRGB* strip)
{
   m_strip = strip;
}

