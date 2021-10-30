#include "LaunchPad.hpp"
#include <algorithm>
#include <iostream>

namespace {
const uint8_t HEADER_LENGTH = 6;
const uint8_t SYSEX_HEADER[HEADER_LENGTH] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x0D};
const uint8_t SYSEX_END = 0xF7;

struct ColorSpec
{
    ColorSpec(){}
    ColorSpec(uint8_t row, uint8_t col, uint8_t r, uint8_t g, uint8_t b):
        spec_type(3/* RGB */),
        index((row + 1) * 10 + col + 1),
        r(r),
        g(g),
        b(b)
    {}
    uint8_t spec_type;
    uint8_t index;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} __attribute__((packed));

struct AllLeds 
{
    AllLeds():
        end(SYSEX_END)
    {
        std::copy_n(SYSEX_HEADER, HEADER_LENGTH, header);
    }
    uint16_t length;
    uint8_t header[HEADER_LENGTH];
    uint8_t command;
    ColorSpec led[81];
    uint8_t end;
} __attribute__((packed));

}


union LaunchPad::SysexMsg
{
    SysexMsg():
        all_leds()
    {

    }
   
    MidiMessage msg;
    struct {
        uint16_t length;
        uint8_t data[32];
    } raw;
    AllLeds all_leds;
}  __attribute__((packed));

LaunchPad::LaunchPad(MidiMessageSink& to_launchpad, MidiMessageSink& to_geoledic):
    m_to_launchpad(to_launchpad),
    m_to_geoledic(to_geoledic),
    m_sysex_message(*new SysexMsg()),
    m_last_col_val(),
    m_fine_fader_resolution(false)
{
    std::fill_n(m_leds[0], NUM_ROWS*NUM_COLS, CRGB::Black);

    // enter programmer mode
    m_sysex_message.raw.data[HEADER_LENGTH] = 0xE;
    m_sysex_message.raw.data[HEADER_LENGTH+1] = 1;
    m_sysex_message.raw.data[HEADER_LENGTH+2] = SYSEX_END;
    m_sysex_message.raw.length = HEADER_LENGTH+3;
    m_to_launchpad.sink(m_sysex_message.msg);

}

LaunchPad::~LaunchPad()
{
    // leave programmer mode
    m_sysex_message.raw.data[HEADER_LENGTH] = 0xE;
    m_sysex_message.raw.data[HEADER_LENGTH+1] = 0;
    m_sysex_message.raw.data[HEADER_LENGTH+2] = SYSEX_END;
    m_sysex_message.raw.length = HEADER_LENGTH+3;    
    m_to_launchpad.sink(m_sysex_message.msg);
    delete &m_sysex_message;
}

void LaunchPad::sendColors()
{
    uint8_t i = 0;
    for (unsigned row = 0; row < NUM_ROWS; row++)
    {
        for (unsigned col = 0; col < NUM_COLS; col++)
        {
            CRGB& l(m_leds[col][row]);
            m_sysex_message.all_leds.led[i++] = ColorSpec(row, col, l.r/2, l.g/2, l.b/2);
        }
    }
    m_sysex_message.all_leds.led[i].spec_type = SYSEX_END;
    m_sysex_message.all_leds.length = HEADER_LENGTH + 2 + i * sizeof(ColorSpec);
    m_sysex_message.all_leds.command = 0x03;
    m_sysex_message.all_leds.end = SYSEX_END;
    m_to_launchpad.sink(m_sysex_message.msg);
}

void LaunchPad::updateFromMidi(const MidiMessage& msg)
{
    if (msg.type() == MidiMessage::CONTROL_CHANGE)
    {
        if (msg.data[1] != 7 && (msg.data[1] < 16 || msg.data[1] > 22)) return;

        uint8_t index = msg.data[1] == 7 ? 0 : msg.data[1] - 15;
        uint8_t value = msg.data[2];

        m_last_col_val[index] = value;

        for (unsigned k = 0; k < NUM_ROWS-1; k++)
        {
            if (value/18 > k)
            {
                m_leds[index][k] = ColorFromPalette(RainbowColors_p, index*24, 255);
            }
            else if (value/18 == k)
            {
                m_leds[index][k] = ColorFromPalette(RainbowColors_p, index*24, (value % 18)*14 + 17);
            }
            else
            {
                m_leds[index][k] = CRGB::Black;
            }
        }
    }
}

void LaunchPad::updateFromCtrl(const MidiMessage& msg)
{
    const uint8_t col_to_ctrl[8] = {7, 16, 17, 18, 19, 20, 21, 22};
    if (msg.type() == MidiMessage::NOTE_ON || msg.type() == MidiMessage::CONTROL_CHANGE)
    {
        if (msg.data[1] == 29)
        {
            m_fine_fader_resolution = msg.data[2] > 0;
            return;
        }

        if (msg.data[2] == 0) return;

        uint8_t row = (msg.data[1] / 10) - 1;
        uint8_t col = (msg.data[1] % 10) - 1;
        if (col >= 8) return;

        uint8_t val =       row == 7 ? 127 : row * 18;
        uint8_t upper_val = row >= 6 ? 127 : (row+1) * 18;
        if (m_last_col_val[col] >= val && m_last_col_val[col] < upper_val)
        {
            m_last_col_val[col] += (m_fine_fader_resolution ? 1 : 6);
            if (m_last_col_val[col] >= upper_val)
            {
                m_last_col_val[col] = val;
            }
        }
        else
        {
            m_last_col_val[col] = val;
        }

        MidiMessage msg;
        msg.data[0] = MidiMessage::CONTROL_CHANGE << 4;
        msg.data[1] = col_to_ctrl[col];
        msg.data[2] = m_last_col_val[col];
        msg.length = 3;
        m_to_geoledic.sink(msg);
    }
}

void LaunchPad::refreshUi()
{
    sendColors();
}