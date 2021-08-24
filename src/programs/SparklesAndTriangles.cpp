#include "SparklesAndTriangles.hpp"

SparklesAndTriangles::SparklesAndTriangles(const DomeWrapper& dome):
   m_dome(dome),
   m_iteration(0)
{}

void SparklesAndTriangles::run()
{
   int sparkle_probability = getSparkleProbability() ? 2 * (128 - getSparkleProbability()) : 0;
   for (unsigned t_ix = 0; t_ix < m_dome.size(); t_ix++)
   {
      Triangle& t(m_dome[t_ix]);
      if (getTriangleValue(t_ix) > 0)
      {
         std::fill(t.begin(), t.end(), ColorFromPalette(RainbowColors_p, getTriangleValue(t_ix)*2));
      }
      else
      {
         int c = 0;
         int next_sparkle = sparkle_probability ? random8(sparkle_probability) : -1;
         for(CRGB& led: t)
         {
            if (c == next_sparkle)
            {
               next_sparkle += random8(sparkle_probability) + 1;
               led = CRGB::White;
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
            c++;
         }
      }
   }
   m_iteration++;
}
