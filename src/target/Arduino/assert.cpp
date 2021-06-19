#include "assert.hpp"
#include "Arduino.h"


void do_assert(const char* msg, const char* file, int line)
{
    // just loop endlessly, printing the message every 2 seconds
    // so it can be seen if the serial console is opened after
    // the assert happened
    while (true)
    {
        Serial.printf("Assertion failed: %s in %s, line %d\n", msg, file, line);
        delay(2000);
    }
}