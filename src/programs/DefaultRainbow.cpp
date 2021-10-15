#include "DefaultRainbow.hpp"

DefaultRainbow::DefaultRainbow(const DomeWrapper& dome):
   m_dome(dome),
   m_iteration(0)
{}

void DefaultRainbow::runProgram()
{
   for (unsigned t_ix = 0; t_ix < m_dome.size(); t_ix++)
   {
      Triangle& t(m_dome[t_ix]);
      int sparkle_spacing = getSparkleProbability() ?  100 * (128 - getSparkleProbability()) : 0;

      CHSV hsv;
      hsv.hue = t_ix + m_iteration;
      hsv.sat = 240;

      if (isKeysOnly())
      {
         hsv.val = getTriangleValue(t_ix) * 2;
      }
      else
      {
         hsv.val = getBrightness();
         if (getTriangleValue(t_ix))
         {
            sparkle_spacing = (150 - getTriangleValue(t_ix));
         }
      }

      int next_sparkle = sparkle_spacing ? random16(sparkle_spacing) : -1;
      for (CRGB& led: t)
      {
         if (next_sparkle == 0)
         {
            led = CRGB::White;
            next_sparkle =  random16(sparkle_spacing) + 1;
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
