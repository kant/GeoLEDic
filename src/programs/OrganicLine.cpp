#include "OrganicLine.hpp"
#include "colorutils.h"
#include "Palettes.hpp"

OrganicLine::OrganicLine(const DomeWrapper& dome):
   m_dome(dome),
   m_time(0)
{
}   

void OrganicLine::run()
{
   const unsigned MIN_PHI = 178;
   const unsigned MAX_PHI = 846;
   uint8_t line_noise[MAX_PHI - MIN_PHI + 1];
   for (unsigned i = 0; i < sizeof(line_noise); i++)
   {
      line_noise[i] = 128 + inoise16_raw((i * (140 - getSize())) << 4, m_time)/100;
   }
   
   // only the first two lines, and only even triangles
   for (unsigned t_ix = 0; t_ix <= 50; t_ix += 2)
   {
      Triangle& t(m_dome[t_ix]);
      // on first row, the first edge is the horizontal one, on the second row it's the last edge
      const Edge& e(t.edge(t_ix <= 24 ? 0 : 2));
      const Vertex& c0(t.corner(t_ix <= 24 ? 0 : 2));
      const Vertex& c1(t.corner(t_ix <= 24 ? 1 : 0));

      int led_ix = 0;
      for (CRGB& led: e)
      {
         unsigned h = interpolatePhi(c0, c1, led_ix, e.size()) - MIN_PHI;
         led = ColorFromPalette(PartyStripes_p, line_noise[h], getBrightness());
         led_ix++;
      }
   }
   
   m_time += getSpeed()<<4;
}
