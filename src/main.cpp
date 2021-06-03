#include "Arduino.h"
#include <OctoWS2811.h>
#include "FastLED.h"
#include "GeoLEDic.hpp"

#define LED_PIN     1
#define COLOR_ORDER RGB
#define CHIPSET     WS2813

#define FRAME_RATE 24
static const unsigned FRAME_INTERVAL_MS = 1000 / FRAME_RATE;

static const int LOADMON_PIN = 34;

DMAMEM int dma_mem[LEDS_PER_STRIP * 3 * (NUM_STRIPS + 3)/4];
static const uint8_t pinlist[NUM_STRIPS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

OctoWS2811 octo_ws(LEDS_PER_STRIP, dma_mem, leds, WS2811_RGB | WS2813_800kHz, NUM_STRIPS, pinlist);

void setup() {
#ifdef USB_MIDI_SERIAL    
    Serial.begin(115200); 
#endif   
    delay(1000); // sanity delay
    pinMode(LOADMON_PIN, OUTPUT);

    setupGeoLEDic();
    octo_ws.begin();
}

void loop()
{
    uint32_t time_before = millis();
    digitalWrite(LOADMON_PIN, HIGH);
    loopGeoLEDic();
    octo_ws.show();

    uint32_t dt = millis() - time_before;
    digitalWrite(LOADMON_PIN, LOW);
    delay(FRAME_INTERVAL_MS - dt);
}
