#ifndef GEOLEDIC_DOME_HPP
#define GEOLEDIC_DOME_HPP

#include "Triangle.hpp"
#include <FastLED.h>

#define DOME_NUM_TRIANGLES 123
#define DOME_NUM_LEDS (DOME_NUM_TRIANGLES * 300)

extern CRGB colors[DOME_NUM_LEDS];
extern Triangle dome[DOME_NUM_TRIANGLES];

#endif
