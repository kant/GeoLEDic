#include "MidiSource.hpp"

class MidiSource::Impl
{
};

MidiSource::MidiSource():
   m_i(*new Impl)
{
}

MidiSource::~MidiSource()
{
   delete &m_i;
}

const MidiMessage* MidiSource::read()
{
   return nullptr;
}
