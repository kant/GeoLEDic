#include "SparklesAndTriangles.hpp"

SparklesAndTriangles::SparklesAndTriangles(Triangle* triangles, unsigned num_triangles):
   m_triangles(triangles),
   m_num_triangles(num_triangles),
   m_red(0),
   m_green(0),
   m_blue(0),
   m_sparkle_probability(0),
   m_iteration(0),
   m_notes()
{}

void SparklesAndTriangles::noteOn(uint8_t note, uint8_t velocity)
{
   m_notes[note] = velocity;
}

void SparklesAndTriangles::noteOff(uint8_t note)
{
   m_notes[note] = 0;
}

void SparklesAndTriangles::controlChange(uint8_t cc_num, uint8_t value)
{
   switch (cc_num)
   {
      case 0x4a:
         m_red = value;
         break;
      case 0x47:
         m_green = value;
         break;
      case 0x5b:
         m_blue = value;
         break;
      case 0x5d:
         m_sparkle_probability = value ? 2 * (128 - value) : 0;
         break;
      default:
         break;
   }

}

void SparklesAndTriangles::run()
{
   for (unsigned t_ix = 0; t_ix < m_num_triangles; t_ix++)
   {
      Triangle& t(m_triangles[t_ix]);
      if (m_notes[t_ix] > 0)
      {
         fill_solid(t.begin(), t.end() - t.begin(), ColorFromPalette(RainbowColors_p, m_notes[t_ix]*2));
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
               int c1 = c + m_iteration + t_ix*20;
               int colr = (m_red * (c1 % 128))/64;
               int colg = (m_green * ((c1+30) % 128))/64;
               int colb = (m_blue * ((c1+60) % 128))/64;
               
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
