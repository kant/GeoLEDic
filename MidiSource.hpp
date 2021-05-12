#ifndef GEOLEDIC_MIDI_SOURCE_HPP
#define GEOLEDIC_MIDI_SOURCE_HPP

#include "MidiMessage.hpp"

class MidiSource
{
public:
   MidiSource();
   ~MidiSource();
   
   const MidiMessage* read();
private:
   class Impl;
   Impl& m_i;
};

#endif // GEOLEDIC_MIDI_SOURCE_HPP
