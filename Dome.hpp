#ifndef GEOLEDIC_DOME_HPP
#define GEOLEDIC_DOME_HPP

#include "Triangle.hpp"
#include <FastLED.h>

#define DOME_NUM_LEDS 20000
#define DOME_NUM_TRIANGLES 123

extern CRGB colors[DOME_NUM_LEDS];
extern Triangle dome[DOME_NUM_TRIANGLES];

#endif
