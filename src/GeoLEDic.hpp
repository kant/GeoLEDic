#ifndef GeoLEDic_h
#define GeoLEDic_h

#include "Dome.hpp"
#include "MidiSource.hpp"

void setupGeoLEDic();
void loopGeoLEDic();

#ifdef WITH_GFX
gfx::Config::MidiPorts* getMidiPorts();
gfx::Config::MidiPorts* getMidiOutPorts();
#endif

#endif /* GeoLEDic_h */
