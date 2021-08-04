#ifndef GEOLEDIC_PROGRAM_HPP
#define GEOLEDIC_PROGRAM_HPP

#include <stdint.h>

class Program
{
public:
   virtual ~Program(){}
   
   virtual void noteOn(uint8_t note, uint8_t velocity, uint8_t channel) = 0;
   virtual void noteOff(uint8_t note, uint8_t channel) = 0;
   virtual void controlChange(uint8_t cc_num, uint8_t value) = 0;
   virtual void run() = 0;

};

#endif // GEOLEDIC_PROGRAM_HPP
