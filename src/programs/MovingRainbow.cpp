#include "MovingRainbow.hpp"

MovingRainbow::MovingRainbow(const DomeWrapper& dome):
   m_dome(dome),
   m_iteration_h(0),
   m_iteration_v(0)
{}

void MovingRainbow::run()
{
   for (Triangle& t: m_dome)
   {
      CHSV hsv;
      hsv.val = 150; // 255 is blindingly bright
      hsv.sat = 255;
      
      for (unsigned k = 0; k < 3; k ++)
      {
         const Edge& e(t.edge(k));
         const Vertex& c0(t.corner(k));
         const Vertex& c1(t.corner((k + 1) % 3));

         int led_ix = 0;
         for (CRGB& led: e)
         {
            unsigned v = (unsigned(interpolateTheta(c0, c1, led_ix, e.size())) * getStrideVertical())/4 + m_iteration_v;
            unsigned h = (unsigned(interpolatePhi(c0, c1, led_ix, e.size())) * getStrideHorizontal())/4 + m_iteration_h;

            hsv.hue = (h + v)/4;
            led = hsv;
            led_ix++;
         }
      }
   }
   m_iteration_h += getSpeedHorizontal();
   m_iteration_v += getSpeedVertical();
}
