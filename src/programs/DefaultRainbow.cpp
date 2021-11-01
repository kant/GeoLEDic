#include "DefaultRainbow.hpp"

DefaultRainbow::DefaultRainbow(const DomeWrapper& dome):
   m_dome(dome),
   m_iteration(0)
{}

void DefaultRainbow::runProgram()
{
   const uint8_t HUE_SCALE = 2;
   CHSV hsv;
   hsv.sat = 240;
   for (unsigned t_ix = 0; t_ix < m_dome.size(); t_ix++)
   {
      Triangle& t(m_dome[t_ix]);
      int sparkle_spacing = getSparkleProbability() ?  100 * (128 - getSparkleProbability()) : 0;

      // use a scaled hue so we get a finer resolution in speed and stride
      uint16_t scaled_hue = (t_ix<<HUE_SCALE) + m_iteration;
      
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
            hsv.hue = scaled_hue >> HUE_SCALE;
            led = hsv;
         }
         scaled_hue += getStride();
         next_sparkle--;
      }
   }
   m_iteration += getSpeed();
}
