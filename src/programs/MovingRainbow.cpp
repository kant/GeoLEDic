#include "MovingRainbow.hpp"

MovingRainbow::MovingRainbow(const DomeWrapper& dome):
   m_dome(dome),
   m_stride_h(0),
   m_speed_h(0),
   m_stride_v(4),
   m_speed_v(2),
   m_iteration_h(0),
   m_iteration_v(0)
{}

void MovingRainbow::noteOn(uint8_t note, uint8_t velocity, uint8_t channel)
{
   (void)note;
   (void)velocity;
   (void)channel;
}

void MovingRainbow::noteOff(uint8_t note, uint8_t channel)
{
   (void)note;
   (void)channel;
}

void MovingRainbow::controlChange(uint8_t cc_num, uint8_t value)
{
   switch (cc_num)
   {
      case 16:
         m_speed_v = value;
         break;
      case 17:
         m_stride_v = value;
         break;
      case 18:
         m_speed_h = value;
         break;
      case 19:
         m_stride_h = value;
         break;
      default:
         break;
   }
}

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
            unsigned v = (unsigned(interpolateTheta(c0, c1, led_ix, e.size())) * m_stride_v)/4 + m_iteration_v;
            unsigned h = (unsigned(interpolatePhi(c0, c1, led_ix, e.size())) * m_stride_h)/4 + m_iteration_h;

            hsv.hue = (h + v)/4;
            led = hsv;
            led_ix++;
         }
      }
   }
   m_iteration_h += m_speed_h;
   m_iteration_v += m_speed_v;
}
