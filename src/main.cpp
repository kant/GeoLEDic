#include "Arduino.h"
#include <OctoWS2811.h>
#include "FastLED.h"
#include "GeoLEDic.hpp"

#define LED_PIN     1
#define COLOR_ORDER RGB
#define CHIPSET     WS2813
#define NUM_LEDS    1200
#define NUM_STRIPS  1

#define FRAME_RATE 24
static const unsigned FRAME_INTERVAL_MS = 1000 / FRAME_RATE;

static const int LOADMON_PIN = 14;

DMAMEM int dma_mem[NUM_LEDS * 3 * (NUM_STRIPS + 3)/4];
static const uint8_t pinlist[NUM_STRIPS] = {0};

OctoWS2811 leds(NUM_LEDS, dma_mem, colors, WS2811_RGB | WS2813_800kHz, NUM_STRIPS, pinlist);

void setup() {
#ifdef USB_MIDI_SERIAL    
    Serial.begin(115200); 
#endif   
    delay(1000); // sanity delay
    pinMode(LOADMON_PIN, OUTPUT);

    setupGeoLEDic();
    leds.begin();
}

void loop()
{
    uint32_t time_before = millis();
    digitalWrite(LOADMON_PIN, HIGH);
    loopGeoLEDic();
    leds.show();

    uint32_t dt = millis() - time_before;
    digitalWrite(LOADMON_PIN, LOW);
    delay(FRAME_INTERVAL_MS - dt);
}
