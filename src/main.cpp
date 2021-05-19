#include "Arduino.h"
#include "FastLED.h"
#include "GeoLEDic.hpp"

#define LED_PIN     1
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define NUM_LEDS    11

#define NUM_STRIPS 1

void setup() {
    Serial.begin(115200);    
    delay(3000); // sanity delay
    FastLED.addLeds<NUM_STRIPS, CHIPSET, LED_PIN, COLOR_ORDER>(colors, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(255);

    setupGeoLEDic();
}

void loop()
{
    loopGeoLEDic();
    FastLED.show(); 
    FastLED.delay(30);
}