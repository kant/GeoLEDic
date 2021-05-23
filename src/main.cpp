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


#ifdef USB_MIDI_SERIAL    
class LoadMonitor
{
public:
    LoadMonitor(unsigned pin): m_accumulated_time_ms(0), m_count(0), m_pin(pin)
    {
        pinMode(m_pin, OUTPUT);
    }

    void end(unsigned time_ms)
    {
#ifdef USB_MIDI_SERIAL

        m_accumulated_time_ms += time_ms;
        m_count++;
        if (m_count == FRAME_RATE * 2) // print every 2 seconds
        {
            Serial.printf("%f%%\n",100*(float(m_accumulated_time_ms)/float(m_count))/FRAME_INTERVAL_MS);
            m_accumulated_time_ms = 0;
            m_count = 0;
        }
#else
        (void)time_ms;
#endif
        digitalWrite(m_pin, LOW);
    }

    void start()
    {
        digitalWrite(m_pin, HIGH);
    }

    unsigned m_accumulated_time_ms;
    unsigned m_count;
    unsigned m_pin;
};

static LoadMonitor load_monitor(LOADMON_PIN);
#endif


void setup() {
#ifdef USB_MIDI_SERIAL    
    Serial.begin(115200); 
#endif   
    delay(3000); // sanity delay

    setupGeoLEDic();
    leds.begin();
}

void loop()
{
    uint32_t time_before = millis();
    load_monitor.start();
    loopGeoLEDic();
    leds.show();

    uint32_t dt = millis() - time_before;
    load_monitor.end(dt);
    delay(FRAME_INTERVAL_MS - dt);
}
