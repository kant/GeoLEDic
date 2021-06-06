#include "Diagnostic.hpp"

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
   m_lit_strip(NONE)
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
            fill_solid(leds.begin(), leds.size(), OFF);
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

            fill_solid(t.begin(), t.end() - t.begin(), 
                     i == m_lit_triangle ? CRGB::White : OFF);
         }
      }
      else
      {
         for (unsigned i = 0; i < m_strips.size(); i++)
         {
            fill_solid(m_strips[i].begin(), m_strips.numLedsPerStrip(),
                     i == m_lit_strip ? CRGB::White : OFF);
         }
      }

   }
}

bool Diagnostic::processKeyboardInput(char c)
{
   bool input_accepted = false;
   switch (m_state)
   {         
      case WAIT:
         m_accumulator = 0;
         switch (c)
         {
            case 'l':
            case 'L':
               m_state = LED;
               input_accepted = true;
               break;
            case 't':
            case 'T':
               m_state = TRIANGLE;
               input_accepted = true;
               break;
            case 's':
            case 'S':
               m_state = STRIP;
               input_accepted = true;
               break;
            default:
               break;

         }
         break;
      
      case LED:
         if (isdigit(c))
         {
            m_accumulator = 10 * m_accumulator + (c - '0');
            input_accepted = true;
         }
         else if (c == ':' or c == ';')
         {
            m_strip_for_lit_led = m_accumulator;
            m_accumulator = 0;
            input_accepted = true;
         }
         else if (c == '\r' or c == '\n')
         {
            m_lit_led = m_accumulator;
            m_lit_triangle = NONE;
            m_lit_strip = NONE;
            input_accepted = true;
            m_state = WAIT;
         }
         break;

      case TRIANGLE:
         if (isdigit(c))
         {
            m_accumulator = 10 * m_accumulator + (c - '0');
            input_accepted = true;
         }
         else if (c == '\n' or c == '\r')
         {
            m_lit_triangle = m_accumulator;
            m_lit_led = NONE;
            m_lit_strip = NONE;
            input_accepted = true;
            m_state = WAIT;
         }
         break;

      case STRIP:
         if (isdigit(c))
         {
            m_accumulator = 10 * m_accumulator + (c - '0');
            input_accepted = true;
         }
         else if (c == '\n' or c == '\r')
         {
            m_lit_strip = m_accumulator;
            m_lit_led = NONE;
            m_lit_triangle = NONE;
            input_accepted = true;
            m_state = WAIT;
         }
         break;

      case INTRO:
      default:
         break;
   }
   return input_accepted;
}
