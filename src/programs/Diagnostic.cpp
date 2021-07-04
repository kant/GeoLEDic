#include "Diagnostic.hpp"
#include <algorithm>

namespace 
{
   const unsigned NONE(~0U);
#ifdef WITH_FLOGL
   // need to see a bit more on the dark background in the model
   // as we don't have the actual beams
   CRGB OFF(40,40,40);
#else
   CRGB OFF(CRGB::Black);
#endif
}

Diagnostic::Diagnostic(const DomeWrapper& dome, const Strips& strips):
   m_dome(dome),
   m_strips(strips),
   m_state(INTRO),
   m_iteration(0),
   m_accumulator(0),
   m_lit_led(NONE),
   m_strip_for_lit_led(0),
   m_lit_triangle(NONE),
   m_lit_strip(NONE),
   m_lit_phi(NONE),
   m_lit_theta(NONE)
{
}

void Diagnostic::noteOn(uint8_t note, uint8_t velocity)
{
   (void)velocity;
   m_lit_triangle = note;
   m_lit_strip = NONE;
   m_lit_led = NONE;
}

void Diagnostic::noteOff(uint8_t note)
{
   (void)note;
   if (note == m_lit_triangle) m_lit_triangle = NONE;
}

void Diagnostic::controlChange(uint8_t cc_num, uint8_t value)
{
   (void)cc_num;
   (void)value;
}

void Diagnostic::run()
{
   if (m_state == INTRO)
   {
      const unsigned stride = 20;
      for (unsigned i = 0; i < m_strips.size(); i++)
      {
         Strip leds(m_strips[i]);
         for (unsigned j = 0; j < leds.size(); j++)
         {
            if (j >= m_iteration and j < (m_iteration+stride))
            {
               leds[j] = CRGB::White;
            }
            else
            {
               leds[j] = OFF;
            }
         }
      }
      m_iteration += stride;
      if (m_iteration > m_strips.numLedsPerStrip())
      {
         m_state = WAIT;
      }
   }
   else
   {
      if (m_lit_led != NONE)
      {
         for (unsigned k = 0; k < m_strips.size(); k++)
         {
            Strip leds(m_strips[k]);
            std::fill(leds.begin(), leds.end(), OFF);
            if (k == m_strip_for_lit_led)
            {
               leds[m_lit_led] = CRGB::White;
            }
         }
      }
      else if (m_lit_triangle != NONE)
      {
         for (unsigned i = 0; i < m_dome.size(); i++)
         {
            Triangle& t(m_dome[i]);

            if (m_lit_triangle == i)
            {
               std::fill(t.edge(0).begin(), t.edge(0).end(), CRGB::Red);
               std::fill(t.edge(1).begin(), t.edge(1).end(), CRGB::Green);
               std::fill(t.edge(2).begin(), t.edge(2).end(), CRGB::Blue);
            }
            else
            {
               std::fill(t.begin(), t.end(), OFF);
            }
         }
      }
      else if (m_lit_phi != NONE)
      {
         for (Triangle& t: m_dome)
         {
            for (unsigned k = 0; k < 3; k++)
            {
               const Edge& e(t.edge(k));
               const Vertex c0(t.corner(k));
               const Vertex c1(t.corner((k+1)%3));

               int led_ix = 0;
               for (CRGB& l: e)
               {
                  if (interpolatePhi(c0, c1, led_ix, e.size()) == m_lit_phi)
                  {
                     l = CRGB::White;
                  }
                  else
                  {
                     l = OFF;
                  }
                  led_ix++;
               }
            }
         }
      }
      else if (m_lit_theta != NONE)
      {
         for (Triangle& t: m_dome)
         {
            for (unsigned k = 0; k < 3; k++)
            {
               const Edge& e(t.edge(k));
               const Vertex c0(t.corner(k));
               const Vertex c1(t.corner((k+1)%3));

               int led_ix = 0;
               for (CRGB& l: e)
               {
                  if (interpolateTheta(c0, c1, led_ix, e.size()) == m_lit_theta)
                  {
                     l = CRGB::White;
                  }
                  else
                  {
                     l = OFF;
                  }
                  led_ix++;
               }
            }
         }
      }
      else 
      {
         for (unsigned i = 0; i < m_strips.size(); i++)
         {
            std::fill(m_strips[i].begin(), m_strips[i].end(),
                     i == m_lit_strip ? CRGB::White : OFF);
         }
      }

   }
}

bool Diagnostic::processKeyboardInput(char c)
{
   switch (m_state)
   {         
      case WAIT:
         return processWaitState(c);
      
      case LED:
         return processLedState(c);

      case TRIANGLE:
         return processTriangleState(c);

      case STRIP:
         return processStripState(c);

      case PHI:
         return processPhiState(c);

      case THETA:
         return processThetaState(c);

      case INTRO:
      default:
         return false;
   }
}

bool Diagnostic::extractDigit(char c)
{
   if (not isdigit(c)) return false;
   
   m_accumulator = 10 * m_accumulator + (c - '0');
   return true;
}

bool Diagnostic::processWaitState(char c)
{
   m_accumulator = 0;
   switch (toupper(c))
   {
      case 'L':
         m_state = LED;
         return true;
      case 'T':
         m_state = TRIANGLE;
         return true;
      case 'S':
         m_state = STRIP;
         return true;
      case 'H':
         m_state = PHI;
         return true;
      case 'V':
         m_state = THETA;
         return true;
      case '=':
      case '+':
         if (m_lit_led != NONE)
         {
            m_lit_led++;
            return true;
         }
         return false;
      case '-':
      case '_':
         if (m_lit_led != NONE)
         {
            m_lit_led--;
            return true;
         }
         return false;
      default:
         return false;
   }
}

bool Diagnostic::processLedState(char c)
{
   if (extractDigit(c))
   {
      return true;
   }
   
   if (c == ':' or c == ';')
   {
      m_strip_for_lit_led = m_accumulator;
      m_accumulator = 0;
      return true;
   }
   
   if (c == '\r' or c == '\n')
   {
      m_lit_led = m_accumulator;
      m_lit_triangle = NONE;
      m_lit_strip = NONE;
      m_lit_phi = NONE;
      m_lit_theta = NONE;
      m_state = WAIT;
      return true;
   }

   return false;
}

bool Diagnostic::processTriangleState(char c)
{
   if (extractDigit(c))
   {
      return true;
   }
   
   if (c == '\n' or c == '\r')
   {
      m_lit_triangle = m_accumulator;
      m_lit_led = NONE;
      m_lit_strip = NONE;
      m_lit_phi = NONE;
      m_lit_theta = NONE;
      m_state = WAIT;
      return true;
   }
   
   return false;
}

bool Diagnostic::processStripState(char c)
{
   if (extractDigit(c))
   {
      return true;
   }
   
   if (c == '\n' or c == '\r')
   {
      m_lit_strip = m_accumulator;
      m_lit_led = NONE;
      m_lit_triangle = NONE;
      m_lit_phi = NONE;
      m_lit_theta = NONE;
      m_state = WAIT;
      return true;
   }
   
   return false;
}

bool Diagnostic::processPhiState(char c)
{
   if (extractDigit(c))
   {
      return true;
   }
   
   if (c == '\n' or c == '\r')
   {
      m_lit_phi = m_accumulator;
      m_lit_theta = NONE;
      m_lit_strip = NONE;
      m_lit_led = NONE;
      m_lit_triangle = NONE;
      m_state = WAIT;
      return true;
   }
   
   return false;
}

bool Diagnostic::processThetaState(char c)
{
   if (extractDigit(c))
   {
      return true;
   }
   
   if (c == '\n' or c == '\r')
   {
      m_lit_theta = m_accumulator;
      m_lit_phi = NONE;
      m_lit_strip = NONE;
      m_lit_led = NONE;
      m_lit_triangle = NONE;
      m_state = WAIT;
      return true;
   }
   
   return false;
}


