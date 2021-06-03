#include "DefaultRainbow.hpp"

DefaultRainbow::DefaultRainbow(const DomeWrapper& dome):
   m_dome(dome),
   m_iteration(0)
{}

void DefaultRainbow::noteOn(uint8_t note, uint8_t velocity)
{
   (void)note;
   (void)velocity;
}

void DefaultRainbow::noteOff(uint8_t note)
{
   (void)note;
}

void DefaultRainbow::controlChange(uint8_t cc_num, uint8_t value)
{
   (void)cc_num;
   (void)value;
}

void DefaultRainbow::run()
{
   for (unsigned t_ix = 0; t_ix < m_dome.size(); t_ix++)
   {
      Triangle& t(m_dome[t_ix]);
      CHSV hsv;
      hsv.hue = t_ix + m_iteration;
      hsv.val = 150; // 255 is blindingly bright
      hsv.sat = 240;      
      for (CRGB& led: t)
      {
         led = hsv;
         hsv.hue += 1;
      }
   }
   m_iteration++;
}
