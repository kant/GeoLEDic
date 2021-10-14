#include "WarpDriveMandala.hpp"
#include "colorutils.h"
#include "Palettes.hpp"

WarpDriveMandala::WarpDriveMandala(const DomeWrapper& dome):
   m_dome(dome),
   m_rings()
{
   std::fill_n(m_rings, sizeof(m_rings)/sizeof(*m_rings), CRGB::Black);
}   

bool WarpDriveMandala::findKey(uint8_t& hue, uint8_t& saturation)
{
   const unsigned NUM_NOTES = 24;
   for (unsigned n = NOTE_C1; n < NOTE_C1 + NUM_NOTES; n++)
   {
      uint8_t velocity = note(n);
      if (velocity)
      {
         saturation = 255 - velocity * 2;
         hue = 255*(n - NOTE_C1)/NUM_NOTES;
         return true;
      }
   }
   return false;
}


void WarpDriveMandala::shiftAndFillRings()
{
   const uint8_t center_hue = getHue()*2;
   const uint8_t range_hue  = getHueRange();
   const uint8_t center_sat = getSaturation()*2;
   const uint8_t range_sat  = getSaturationRange();
   const uint8_t min_sat = center_sat < range_sat ? 0 : center_sat - range_sat;
   const uint8_t max_sat = (255 - center_sat < range_sat) ? 255 : center_sat + range_sat;
   
   uint8_t advance_width = getSpeed();
   uint8_t fill_width = getThickness() + 1;

   CRGB* shift_to   = m_rings + (isUpwards() ? advance_width : 0);
   CRGB* shift_from = m_rings + (isUpwards() ? 0             : advance_width);

   CRGB* fill_from  = m_rings + (isUpwards() ? 0 : Vertex::NUM_THETA_STEPS - fill_width);
   CRGB* blank_advance_from = m_rings + (isUpwards() ? 0 : Vertex::NUM_THETA_STEPS - advance_width);

   memmove(shift_to, shift_from, sizeof(m_rings) - advance_width*sizeof(*m_rings));
   std::fill_n(blank_advance_from,
               advance_width,
               CRGB::Black);

   uint8_t hue, sat;
   if (findKey(hue, sat))
   {
      std::fill_n(fill_from, 
                  fill_width,
                  CHSV(hue,
                       sat,
                       getBrightness()));

   }
   else if (random8() < getSpawnRate())
   {
      // hue is circular, so it wraps around...
      uint8_t hue = random8(0, 2*range_hue) + center_hue - range_hue;
      
      std::fill_n(fill_from, 
                  fill_width,
                  CHSV(hue,
                       random8(min_sat, max_sat),
                       getBrightness()));
   }
}

void WarpDriveMandala::runProgram()
{
   shiftAndFillRings();

   for (unsigned t_ix = 0; t_ix < m_dome.size(); t_ix++)
   {
      Triangle& t(m_dome[t_ix]);

      for (unsigned e_ix = 0; e_ix < 3; e_ix++)
      {
         const Edge& e(t.edge(e_ix));
         const Vertex& c0(t.corner(e_ix));
         const Vertex& c1(t.corner((e_ix+1) % 3));

         if (isSkipHorizontals())
         {
            // skip horizontal edges
            if (c0.theta == c1.theta)
            {
               std::fill(e.begin(), e.end(), CRGB::Black);
               continue;
            }
         }

         int led_ix = 0;
         for (CRGB& led: e)
         {
            unsigned theta = interpolateTheta(c0, c1, led_ix, e.size());
            led = m_rings[theta];
            led_ix++;
         }
      }
   }
}
