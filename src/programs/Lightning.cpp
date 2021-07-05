#include "Lightning.hpp"

Lightning::Lightning(const DomeWrapper& dome):
   m_dome(dome),
   m_probability(128),
   m_forking_probability(1024),
   m_iteration(0)
{
   memset(m_lit_map, 0, sizeof(m_lit_map));
}

void Lightning::noteOn(uint8_t note, uint8_t velocity)
{
   (void)note;
   (void)velocity;
}

void Lightning::noteOff(uint8_t note)
{
   (void)note;
}

void Lightning::controlChange(uint8_t cc_num, uint8_t value)
{
   switch (cc_num)
   {
      case 16:
         m_probability = int(value)*128;
         break;
      case 17:
         m_forking_probability = int(value)*128;
         break;
      default:
         break;
   }
}

void Lightning::run()
{
   for (unsigned t_ix = 0; t_ix < m_dome.size(); t_ix++)
   {
      Triangle& t(m_dome[t_ix]);

      for (unsigned k = 0; k < 3; k++)
      {
         const Edge& e(t.edge(k));
         const Vertex& c0(t.corner(k));
         const Vertex& c1(t.corner(k+1));

         uint16_t r = random16();
         
         // start lightning bolts at the top
         if (c0.theta > 250 or c1.theta > 250)
         {
            if (r < m_probability)
            {
               CRGB flash_col = r&1 ? CRGB::LightCyan : CRGB::LightBlue;
               fill_solid(&*e.begin(), e.size(), flash_col);
            }
         }
         
         // fork lightning bolts downwards
         if (abs(int(c0.theta) - c1.theta) > 20) // don't light up horizontal edges
         {
            unsigned h,v;
            // get coordinates from top end
            if (c0.theta > c1.theta)
            {
               v = c0.theta / (Vertex::NUM_THETA_STEPS/NUM_V);
               h = c0.phi / (Vertex::NUM_PHI_STEPS/NUM_H);
            }
            else
            {
               v = c1.theta / (Vertex::NUM_THETA_STEPS/NUM_V);
               h = c1.phi / (Vertex::NUM_PHI_STEPS/NUM_H);
            }
            
            if (m_lit_map[h][v].b > 100 && r < m_forking_probability)
            {
               CRGB flash_col = m_lit_map[h][v];
               flash_col.addToRGB(10);
               fill_solid(&*e.begin(), e.size(), flash_col);
            }
         }
         else if (c0.theta < 2 && c1.theta < 2)
         {
            // if a lightning bolt gets all the way to the bottom, light the
            // horizontal line on ground level bright orange
            unsigned v = c0.theta / (Vertex::NUM_THETA_STEPS/NUM_V);
            unsigned h0 = c0.phi / (Vertex::NUM_PHI_STEPS/NUM_H);
            unsigned h1 = c0.phi / (Vertex::NUM_PHI_STEPS/NUM_H);
            if (m_lit_map[h0][v].b > 10 or m_lit_map[h1][v].b > 10)
            {
               fill_solid(&*e.begin(), e.size(), CRGB::Orange);
            }
         }
         
         // refresh downsampled map of lightning strikes
         if (!!*e.begin())
         {
            unsigned h,v;
            // get coordinates from bottom end
            if (c0.theta > c1.theta)
            {
               v = c1.theta / (Vertex::NUM_THETA_STEPS/NUM_V);
               h = c1.phi / (Vertex::NUM_PHI_STEPS/NUM_H);
            }
            else
            {
               v = c0.theta / (Vertex::NUM_THETA_STEPS/NUM_V);
               h = c0.phi / (Vertex::NUM_PHI_STEPS/NUM_H);
            }
            m_lit_map[h][v] = *e.begin();
         }
      }

      // fade everything to black
      for (CRGB& l: t)
      {
         l.subtractFromRGB(10);
      }
   }
   m_iteration++;
}
