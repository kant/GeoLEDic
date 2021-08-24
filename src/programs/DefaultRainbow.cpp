#include "DefaultRainbow.hpp"

DefaultRainbow::DefaultRainbow(const DomeWrapper& dome):
   m_dome(dome),
   m_iteration(0)
{}

void DefaultRainbow::noteOn(uint8_t note, uint8_t velocity, uint8_t channel)
{
   (void)note;
   (void)velocity;
   (void)channel;
}

void DefaultRainbow::noteOff(uint8_t note, uint8_t channel)
{
   (void)note;
   (void)channel;
}

void DefaultRainbow::run()
{
   int sparkle_probability = getSparkleProbability() ? 4 * (128 - getSparkleProbability()) : 0;
   for (unsigned t_ix = 0; t_ix < m_dome.size(); t_ix++)
   {
      Triangle& t(m_dome[t_ix]);
      CHSV hsv;
      hsv.hue = t_ix + m_iteration;
      hsv.val = 150; // 255 is blindingly bright
      hsv.sat = 240;
      int next_sparkle = sparkle_probability ? random16(sparkle_probability) : -1;
      for (CRGB& led: t)
      {
         if (next_sparkle == 0)
         {
            led = CRGB::White;
            next_sparkle =  random16(sparkle_probability) + 1;
         }
         else if (led.r > 20 && led.r == led.g && led.g == led.b)
         {
            led.subtractFromRGB(20);
         }
         else
         {
            led = hsv;
         }
         hsv.hue += getStride();
         next_sparkle--;
      }
   }
   m_iteration += getSpeed();
}
