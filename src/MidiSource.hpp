#ifndef GEOLEDIC_MIDI_SOURCE_HPP
#define GEOLEDIC_MIDI_SOURCE_HPP

#include "MidiMessage.hpp"

#define MIDI_CLIENT_NAME "GeoLEDic Client"
#define MIDI_PORT_NAME "GeoLEDic In"

#ifdef WITH_GFX
#include "gfx/Config.hpp"
#endif

class MidiSource
{
public:
   MidiSource();
   ~MidiSource();
   
   const MidiMessage* read();
   
#ifdef WITH_GFX
   gfx::Config::MidiPorts* getMidiPorts();
#endif
   
private:
   class Impl;
   Impl& m_i;
};

#endif // GEOLEDIC_MIDI_SOURCE_HPP
