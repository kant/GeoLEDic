#include "Edgy.hpp"
#include "colorutils.h"
#include <algorithm>

Edgy::Edgy(const DomeWrapper& dome):
   m_dome(dome)
{
}   

void Edgy::runProgram()
{
   uint8_t min_hue = getMinHue()<<1;
   uint8_t max_hue = std::max(min_hue, uint8_t(getMaxHue()*2));
   uint8_t min_sat = getMinSaturation()*2;
   uint8_t max_sat = std::max(min_sat, uint8_t(getMaxSaturation()*2));

   uint8_t base_edge_rate = isAnyTriangleSet() ? 0 : getEdgeRate();

   for (unsigned t_ix = 0; t_ix < m_dome.size(); t_ix++)
   {
      Triangle& t(m_dome[t_ix]);

      uint8_t edge_rate = getTriangleValue(t_ix) ? getKeyboardEdgeRate() : base_edge_rate;

      for (unsigned e_ix = 0; e_ix < 3; e_ix++)
      {
         const Edge& e(t.edge(e_ix));
         
         if (random8() < edge_rate)
         {
            std::fill(e.begin(), e.end(), CHSV(random8(min_hue, max_hue),
                                               random8(min_sat, max_sat),
                                               getBrightness()));
         }
         else
         {
            CRGB new_col = *e.begin();
            fadeToBlackBy(&new_col, 1, getDecay());
            std::fill(e.begin(), e.end(), new_col);
         }
      }
   }
}
