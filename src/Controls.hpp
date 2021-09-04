#ifndef GEOLEDIC_CONTROLS_HPP
#define GEOLEDIC_CONTROLS_HPP

#include "Program.hpp"
#include <stdint.h>

class Controls: public Program
{
public:
   Controls();
   virtual void controlChange(uint8_t cc_num, uint8_t value);

protected:
   uint8_t getBrightness() const;

   uint8_t getControlValue(uint8_t cc_num) const;
   void setControlValue(uint8_t cc_num, uint8_t value);

private:
   uint8_t m_control_values[128];
};

#endif // GEOLEDIC_PROGRAM_HPP
