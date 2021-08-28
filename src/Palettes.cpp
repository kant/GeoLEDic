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