#define FASTLED_INTERNAL
#include "FastLED.h"
#include "colorutils.h"
#include "Palettes.hpp"

extern const TProgmemRGBPalette16 OceanFromBlack_p FL_PROGMEM =
{
    CRGB::Black,
    CRGB::MidnightBlue,
    CRGB::DarkBlue,
    CRGB::Navy,

    CRGB::DarkBlue,
    CRGB::MediumBlue,
    CRGB::SeaGreen,
    CRGB::Teal,

    CRGB::CadetBlue,
    CRGB::Blue,
    CRGB::DarkCyan,
    CRGB::CornflowerBlue,

    CRGB::Aquamarine,
    CRGB::SeaGreen,
    CRGB::Aqua,
    CRGB::LightSkyBlue
};

extern const TProgmemRGBPalette16 OceanStripes_p FL_PROGMEM =
{
    CRGB::Black,
    CRGB::MidnightBlue,
    CRGB::Black,
    CRGB::Navy,

    CRGB::Black,
    CRGB::MediumBlue,
    CRGB::Black,
    CRGB::Teal,

    CRGB::Black,
    CRGB::Blue,
    CRGB::Black,
    CRGB::CornflowerBlue,

    CRGB::Black,
    CRGB::SeaGreen,
    CRGB::Black,
    CRGB::LightSkyBlue
};

extern const TProgmemRGBPalette16 Clouds_p FL_PROGMEM =
{
    0x0000040,
    CRGB::Blue,
    CRGB::DarkBlue,
    CRGB::Blue,

    CRGB::SkyBlue,
    CRGB::DarkBlue,
    CRGB::DarkBlue,
    CRGB::DarkBlue,

    CRGB::Blue,
    CRGB::DarkBlue,
    CRGB::SkyBlue,
    CRGB::LightBlue,

    CRGB::White,
    CRGB::Gray,
    CRGB::DarkGray,
    CRGB::SkyBlue
};

extern const TProgmemRGBPalette16 PartyStripes_p FL_PROGMEM =
{
    0x5500AB, 0x000000, 0xB5004B, 0x000000,
    0xE81700, 0xB84700, 0x000000, 0xABAB00,
    0xAB5500, 0x000000, 0xF2000E, 0xC2003E,
    0x000000, 0x5F00A1, 0x2F00D0, 0x000000
};
