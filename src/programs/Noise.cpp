#include "Noise.hpp"
#include "Palettes.hpp"
#include "colorutils.h"
#include "ProgramHelpers.hpp"
#include <math.h>
#include <algorithm>

namespace {

 const TProgmemRGBPalette16* palette(Noise::Palette palette)
 {
    switch (palette)
    {
    default:
    case Noise::Palette_Fire:
       return &HeatColors_p;
    case Noise::Palette_Ocean:
       return &OceanFromBlack_p;
    case Noise::Palette_OceanStripes:
       return &OceanStripes_p;
    case Noise::Palette_Cloud:
       return &Clouds_p;
    case Noise::Palette_Forest:
       return &ForestColors_p;
    case Noise::Palette_Lava:
       return &LavaColors_p;
    case Noise::Palette_Rainbow:
       return &RainbowColors_p;
    case Noise::Palette_RainbowStripes:
       return &RainbowStripeColors_p;
    case Noise::Palette_Party:
       return &PartyColors_p;
     case Noise::Palette_PartyStripes:
       return &PartyStripes_p;
    }
 }

}

Noise::Noise(const DomeWrapper& dome):
   m_dome(dome),
   m_x(0),
   m_y(0),
   m_t(0),
   m_h_offset(0)
{
   memset(m_noise, 0, sizeof(m_noise));
}

void Noise::calcNoise()
{
   unsigned sx = unsigned(getScaleX()) << 9;
   unsigned sy = unsigned(getScaleY()) << 9;
   for (unsigned h = 0; h < NUM_H; h++)
   {
      for (unsigned v = 0; v < NUM_V; v++)
      {
         int noise = 128 + inoise16_raw(m_x + h*sx, m_y + v*sy, m_t)/100;
         noise = std::max(std::min(noise, 255), 0);
         if (isXYSwapped())
         {
            (&m_noise[0][0])[h + v * NUM_H] = noise;
         }
         else
         {
            m_noise[h][v] = noise;
         }
      }
   }
}

void Noise::run()
{
   calcNoise();
   auto* pal = palette(getPalette());

   for (unsigned t_ix = 0; t_ix < m_dome.size(); t_ix++)
   {
      Triangle& t(m_dome[t_ix]);
      // if the keyboard is used to light up triangles, only show the
      //  ones actually set by the keyboard
      if (isKeyActivated() and getTriangleValue(t_ix) == 0)
      {
         std::fill_n(t.begin(), t.size(), CRGB::Black);
         continue;
      }
      
      for (unsigned k = 0; k < 3; k++)
      {
         const Edge& e(t.edge(k));
         const Vertex& c0(t.corner(k));
         const Vertex& c1(t.corner((k + 1) % 3));

         int led_ix = 0;
         for (CRGB& led: e)
         {
            float v = float(interpolateTheta(c0, c1, led_ix, e.size())) / (Vertex::NUM_THETA_STEPS/(NUM_V-1));
            float h = float(interpolatePhi(c0, c1, led_ix, e.size())) / (Vertex::NUM_PHI_STEPS/(NUM_H-1));
            h += m_h_offset;
            if (h  >= NUM_H ) h = h - NUM_H;

            uint8_t index = 0;
            if (isNoInterpolation())
            {
               index = m_noise[int(h)][int(v)];
            }
            else
            {
               index = interpolate(m_noise, h, v);
            }
            
            led = ColorFromPalette(*pal, index, getBrightness());
            
            led_ix++;
         }
      }
   }
   m_x += unsigned(getSpeedX()) << 8;
   m_y += unsigned(getSpeedY()) << 8;
   m_t += unsigned(getSpeedT()) << 8;
   m_h_offset += float(getRotationSpeed())/100.f;
   if (m_h_offset >= NUM_H) m_h_offset = 0;
}
