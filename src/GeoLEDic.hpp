#ifndef GeoLEDic_h
#define GeoLEDic_h

#include "Dome.hpp"
#include "MidiSource.hpp"

void setupGeoLEDic();
void loopGeoLEDic();

#ifdef WITH_GFX
gfx::Config::MidiPorts* getMidiPorts();
#endif

#endif /* GeoLEDic_h */
