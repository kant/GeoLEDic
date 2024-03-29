#ifndef LAUNCHPAD_HPP
#define LAUNCHPAD_HPP

#include "MidiMessage.hpp"
#define FASTLED_INTERNAL // get rid of annoying version pragma
#include "platform.h"
#include "FastLED.h"

class LaunchPad
{
public:
    LaunchPad(MidiMessageSink& to_launchpad, MidiMessageSink& to_geoledic);
    ~LaunchPad();

    void updateFromMidi(const MidiMessage& msg);
    void updateFromCtrl(const MidiMessage& msg);
    void refreshUi();
private:
    enum Mode {
        LIVE,
        PROGRAMMER
    };
    void enterMode(Mode mode);
    void sendText(const char* text, const CRGB& color = CRGB::Red);
    void sendColors();

    MidiMessageSink& m_to_launchpad;
    MidiMessageSink& m_to_geoledic;
    union SysexMsg;
    SysexMsg& m_sysex_message;

    enum
    {
        NUM_ROWS = 9,
        NUM_COLS = 9
    };
    struct PadColor
    {
    public:
        PadColor();
        void operator=(const CRGB& color);
        bool m_dirty;
        CRGB m_color;    
    };
    PadColor m_pad_colors[NUM_COLS][NUM_ROWS];

    uint8_t m_last_col_val[NUM_COLS];
    bool m_fine_fader_resolution;
};

#endif // LAUNCHPAD_HPP