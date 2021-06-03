#ifndef GEOLEDIC_DIAGNOSTIC_HPP
#define GEOLEDIC_DIAGNOSTIC_HPP

#include "DomeWrapper.hpp"
#include "Program.hpp"

class Diagnostic: public Program
{
public:
   Diagnostic(const DomeWrapper& dome, CRGB* strips, unsigned num_strips, unsigned m_leds_per_strip);
   
   virtual void noteOn(uint8_t note, uint8_t velocity);
   virtual void noteOff(uint8_t note);
   virtual void controlChange(uint8_t cc_num, uint8_t value);
   virtual void run();

   bool processKeyboardInput(char c);
   
private:
   const DomeWrapper& m_dome;
   CRGB* m_strips;
   int m_num_strips;
   int m_leds_per_strip;

   enum {
      INTRO,
      WAIT,
      LED,
      TRIANGLE,
      STRIP
   } m_state;

   int m_iteration;
   unsigned m_accumulator;
   int m_lit_led;
   int m_lit_triangle;
   int m_lit_strip;
};

#endif 
