#ifndef GEOLEDIC_DIAGNOSTIC_HPP
#define GEOLEDIC_DIAGNOSTIC_HPP

#include "DomeWrapper.hpp"
#include "Strips.hpp"
#include "Program.hpp"

class Diagnostic: public Program
{
public:
   Diagnostic(const DomeWrapper& dome, const Strips& strips);
   
   virtual void noteOn(uint8_t note, uint8_t velocity);
   virtual void noteOff(uint8_t note);
   virtual void controlChange(uint8_t cc_num, uint8_t value);
   virtual void run();

   bool processKeyboardInput(char c);
   
private:
   const DomeWrapper& m_dome;
   const Strips& m_strips;

   enum {
      INTRO,
      WAIT,
      LED,
      TRIANGLE,
      STRIP
   } m_state;

   unsigned m_iteration;
   unsigned m_accumulator;
   unsigned m_lit_led;
   unsigned m_strip_for_lit_led;
   unsigned m_lit_triangle;
   unsigned m_lit_strip;
};

#endif 
