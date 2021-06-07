#include "DefaultRainbow.hpp"

DefaultRainbow::DefaultRainbow(const DomeWrapper& dome):
   m_dome(dome),
   m_sparkle_probability(511),
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
   switch (cc_num)
   {
      case 19:
         m_sparkle_probability = value ? 4 * (128 - value) : 0;
         break;
      default:
         break;
   }
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
      int next_sparkle = m_sparkle_probability ? random16(m_sparkle_probability) : -1;
      for (CRGB& led: t)
      {
         if (next_sparkle == 0)
         {
            led = CRGB::White;
            next_sparkle =  random16(m_sparkle_probability) + 1;
         }
         else if (led.r > 20 && led.r == led.g && led.g == led.b)
         {
            led.subtractFromRGB(20);
         }
         else
         {
            led = hsv;
         }
         hsv.hue += 1;
         next_sparkle--;
      }
   }
   m_iteration++;
}
