#include "Arduino.h"
#include "FastLED.h"
#include "GeoLEDic.hpp"

#define LED_PIN     1
#define COLOR_ORDER RGB
#define CHIPSET     WS2813
#define NUM_LEDS    1200

#define NUM_STRIPS 1
#define FRAME_RATE 24

static const unsigned FRAME_INTERVAL_MS = 1000 / FRAME_RATE;

#ifdef USB_MIDI_SERIAL    
class LoadMonitor
{
public:
    LoadMonitor(): m_accumulated_time_ms(0), m_count(0)
    {}

    void update(unsigned time_ms)
    {
        m_accumulated_time_ms += time_ms;
        m_count++;
        if (m_count == FRAME_RATE * 2) // print every 2 seconds
        {
            Serial.printf("%f%%\n",100*(float(m_accumulated_time_ms)/float(m_count))/FRAME_INTERVAL_MS);
            m_accumulated_time_ms = 0;
            m_count = 0;
        }
    }

    unsigned m_accumulated_time_ms;
    unsigned m_count;
};

static LoadMonitor load_monitor;
#endif


void setup() {
#ifdef USB_MIDI_SERIAL    
    Serial.begin(115200); 
#endif   
    delay(3000); // sanity delay
    FastLED.addLeds<NUM_STRIPS, CHIPSET, LED_PIN, COLOR_ORDER>(colors, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(50);

    setupGeoLEDic();
}

void loop()
{
    uint32_t time_before = millis();
    loopGeoLEDic();
    FastLED.show(); 

    uint32_t dt = millis() - time_before;
#ifdef USB_MIDI_SERIAL
    load_monitor.update(dt);
#endif
    if (dt < FRAME_INTERVAL_MS)
    {
        FastLED.delay(FRAME_INTERVAL_MS - dt);
    }
}
