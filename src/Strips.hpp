#ifndef Strips_h
#define Strips_h

#define FASTLED_INTERNAL // get rid of annoying version pragma
#include "FastLED.h"

class Strip
{
public:
   Strip(CRGB* leds, unsigned num_leds):
      m_leds(leds),
      m_num_leds(num_leds)
   {
   }
   
   unsigned size() const
   {
      return m_num_leds;
   }
   
   CRGB* begin() const
   {
      return &m_leds[0];
   }
   
   CRGB* end() const
   {
      return &m_leds[m_num_leds];
   }
   
   CRGB& operator[](unsigned ix) const
   {
      if (ix >= m_num_leds) ix = m_num_leds - 1;
      return m_leds[ix];
   }
   
private:
   CRGB* m_leds;
   const unsigned m_num_leds;
};

class Strips
{
public:
   Strips(CRGB* leds, unsigned num_strips, unsigned leds_per_strip):
      m_leds(leds),
      m_num_strips(num_strips),
      m_leds_per_strip(leds_per_strip)
   {
   }
   
   unsigned size() const
   {
      return m_num_strips;
   }
   
   Strip operator[](unsigned ix) const
   {
      if (ix >= m_num_strips) ix = m_num_strips - 1;
      return Strip(&m_leds[ix*m_leds_per_strip], m_leds_per_strip);
   }
   
   unsigned numLedsPerStrip() const
   {
      return m_leds_per_strip;
   }
   
private:
   CRGB* m_leds;
   const unsigned m_num_strips;
   const unsigned m_leds_per_strip;
};

#endif /* Strips_h */
