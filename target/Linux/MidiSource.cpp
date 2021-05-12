#include "MidiSource.hpp"

class MidiSource::Impl
{
public:
   
   Impl()
   {
   }
      
   const MidiMessage* read()
   {
      return nullptr;
   }
};

MidiSource::MidiSource():
   m_i(* new(Impl))
{
}

MidiSource::~MidiSource()
{
   delete &m_i;
}

const MidiMessage* MidiSource::read()
{
   return m_i.read();
}
