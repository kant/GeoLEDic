#ifndef GEOLEDIC_DOME_HPP
#define GEOLEDIC_DOME_HPP

#include "Triangle.hpp"

#define DOME_NUM_TRIANGLES 123
#define NUM_STRIPS 32
#define LEDS_PER_STRIP 1265

extern CRGB leds[NUM_STRIPS * LEDS_PER_STRIP];
extern Triangle dome[DOME_NUM_TRIANGLES];
#endif

