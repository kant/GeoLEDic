#include "SparklesAndTriangles.hpp"

SparklesAndTriangles::SparklesAndTriangles(const DomeWrapper& dome):
   m_dome(dome),
   m_iteration(0)
{}

void SparklesAndTriangles::run()
{
   int sparkle_spacing = getSparkleProbability() ? 100 * (128 - getSparkleProbability()) : 0;
   for (unsigned t_ix = 0; t_ix < m_dome.size(); t_ix++)
   {
      Triangle& t(m_dome[t_ix]);
      if (getTriangleValue(t_ix) > 0)
      {
         std::fill_n(t.firstLed(), t.size(), ColorFromPalette(RainbowColors_p, getTriangleValue(t_ix)*2, getBrightness()));
      }
      else
      {
         int c = 0;
         int next_sparkle = sparkle_spacing ? random16(sparkle_spacing) : -1;
         for(CRGB& led: t)
         {
            if (next_sparkle == 0)
            {
               next_sparkle += random16(sparkle_spacing) + 1;
               led = CRGB::White;
            }
            else if (led.r > 20 && led.r == led.g && led.g == led.b)
            {
               led.subtractFromRGB(20);
            }
            else
            {
               int c1 = c + m_iteration;
               int colr = (getRedWorm() *  (c1 % 200))/200;
               int colg = (getGreenWorm() * ((c1+50) % 200))/200;
               int colb = (getBlueWorm() * ((c1+100) % 200))/200;
               
               led = CRGB(colr < 255 ? colr : 255,
                          colg < 255 ? colg : 255,
                          colb < 255 ? colb : 255);
            }
            next_sparkle--;
            c++;
         }
      }
   }
   m_iteration++;
}
