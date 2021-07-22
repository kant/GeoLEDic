#include "SparklesAndTriangles.hpp"

SparklesAndTriangles::SparklesAndTriangles(const DomeWrapper& dome):
   m_dome(dome),
   m_red(0),
   m_green(0),
   m_blue(0),
   m_sparkle_probability(0),
   m_iteration(0)
{}

void SparklesAndTriangles::controlChange(uint8_t cc_num, uint8_t value)
{
   switch (cc_num)
   {
      case 16:
         m_red = value;
         break;
      case 17:
         m_green = value;
         break;
      case 18:
         m_blue = value;
         break;
      case 19:
         m_sparkle_probability = value ? 2 * (128 - value) : 0;
         break;
      default:
         break;
   }

}

void SparklesAndTriangles::run()
{
   for (unsigned t_ix = 0; t_ix < m_dome.size(); t_ix++)
   {
      Triangle& t(m_dome[t_ix]);
      if (m_notes[t_ix] > 0)
      {
         std::fill(t.begin(), t.end(), ColorFromPalette(RainbowColors_p, m_notes[t_ix]*2));
      }
      else
      {
         int c = 0;
         int next_sparkle = m_sparkle_probability ? random8(m_sparkle_probability) : -1;
         for(CRGB& led: t)
         {
            if (c == next_sparkle)
            {
               next_sparkle += random8(m_sparkle_probability) + 1;
               led = CRGB::White;
            }
            else
            {
               int c1 = c + m_iteration;
               int colr = (m_red *  (c1 % 200))/200;
               int colg = (m_green * ((c1+50) % 200))/200;
               int colb = (m_blue * ((c1+100) % 200))/200;
               
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
