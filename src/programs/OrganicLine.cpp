#include "OrganicLine.hpp"
#include "colorutils.h"
#include "Palettes.hpp"

OrganicLine::OrganicLine(const DomeWrapper& dome):
   m_dome(dome),
   m_time(0)
{
}   

uint32_t toValue(const CRGB& c)
{
   return (uint32_t(c.r) << 16) + (uint32_t(c.g) << 8) + c.b;
}

void OrganicLine::run()
{
   CRGBPalette16 hue_palette =
   {
      CRGB::Black,
      CHSV(getHue0()*2, 255, 255),
      CRGB::Black,
      CRGB::Black,

      CHSV(getHue1()*2, 255, 255),
      CRGB::Black,
      CRGB::Black,
      CHSV(getHue2()*2, 255, 255),

      CRGB::Black,
      CRGB::Black,
      CHSV(getHue3()*2, 255, 255),
      CRGB::Black,

      CHSV(getHue0()*2, 255, 255),
      CHSV(getHue1()*2, 255, 255),
      CHSV(getHue2()*2, 255, 255),
      CHSV(getHue3()*2, 255, 255),
   };
   
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
         if (isUseHues())
         {
            led = ColorFromPalette(hue_palette, line_noise[h], getBrightness());
         }
         else
         {
            led = ColorFromPalette(PartyStripes_p, line_noise[h], getBrightness());
         }
         led_ix++;
      }
   }
   
   m_time += getSpeed()<<4;
}
