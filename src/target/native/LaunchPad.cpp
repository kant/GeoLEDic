#include "LaunchPad.hpp"
#include <algorithm>
#include <iostream>

namespace {
const uint8_t HEADER_LENGTH = 6;
const unsigned MAX_SYSEX_DATA_LENGTH = 256;
const uint8_t SYSEX_HEADER[HEADER_LENGTH] = {0xF0, 0x00, 0x20, 0x29, 0x02, 0x0D};
const uint8_t SYSEX_END = 0xF7;

enum SysexCommand 
{
    PROGRAMMER_MODE = 0x0E,
    SET_COLORS = 0x03,
};

}

union LaunchPad::SysexMsg
{
    SysexMsg()
    {
        std::copy_n(SYSEX_HEADER, HEADER_LENGTH, raw.header);
    }

    MidiMessage msg;
    struct {
        uint16_t length;
        uint8_t header[HEADER_LENGTH];
        uint8_t command;
        uint8_t data[MAX_SYSEX_DATA_LENGTH];
    } raw;
}  __attribute__((packed));

LaunchPad::PadColor::PadColor():
    m_dirty(true),
    m_color(CRGB::Black)
{
}

void LaunchPad::PadColor::operator=(const CRGB& color)
{
    if (m_color != color)
    {
        m_dirty = true;
        m_color = color;
    }
}

LaunchPad::LaunchPad(MidiMessageSink& to_launchpad, MidiMessageSink& to_geoledic):
    m_to_launchpad(to_launchpad),
    m_to_geoledic(to_geoledic),
    m_sysex_message(*new SysexMsg()),
    m_pad_colors(),
    m_last_col_val(),
    m_fine_fader_resolution(false)
{
    enterMode(PROGRAMMER);
}

LaunchPad::~LaunchPad()
{
    enterMode(LIVE);
    delete &m_sysex_message;
}

void LaunchPad::enterMode(Mode mode)
{
    m_sysex_message.raw.command = 0xE;
    m_sysex_message.raw.data[0] = mode == PROGRAMMER ? 1 : 0;
    m_sysex_message.raw.data[1] = SYSEX_END;
    m_sysex_message.raw.length = HEADER_LENGTH+3;    
    m_to_launchpad.sink(m_sysex_message.msg);
}

void LaunchPad::sendColors()
{
    m_sysex_message.raw.command = SET_COLORS;
    uint8_t* p = m_sysex_message.raw.data;
    for (unsigned row = 0; row < NUM_ROWS; row++)
    {
        for (unsigned col = 0; col < NUM_COLS; col++)
        {
            if (p - m_sysex_message.raw.data + 6 > MAX_SYSEX_DATA_LENGTH)
            {
                // the 5 bytes for the color item plus the end marker won't fit,
                // send the remainder in the next message
                break;
            }

            PadColor& pad(m_pad_colors[col][row]);
            if (not pad.m_dirty) continue;

            *p++ = 0x3; // use RGB
            *p++ = (row + 1) * 10 + col + 1;
            *p++ = pad.m_color.r/2;
            *p++ = pad.m_color.g/2;
            *p++ = pad.m_color.b/2;

            pad.m_dirty = false;
        }
    }
    if (p == m_sysex_message.raw.data) return; // no messages added

    *p++ = SYSEX_END;
    m_sysex_message.raw.length = p - m_sysex_message.raw.header;
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
                m_pad_colors[index][k] = ColorFromPalette(RainbowColors_p, index*24, 255);
            }
            else if (value/18 == k)
            {
                m_pad_colors[index][k] = ColorFromPalette(RainbowColors_p, index*24, (value % 18)*14 + 17);
            }
            else
            {
                m_pad_colors[index][k] = CRGB::Black;
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