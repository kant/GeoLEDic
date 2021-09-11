#ifndef GEOLEDIC_MIDI_SOURCE_HPP
#define GEOLEDIC_MIDI_SOURCE_HPP

#include "MidiMessage.hpp"

#define MIDI_CLIENT_NAME "GeoLEDic Client"
#define MIDI_PORT_NAME "GeoLEDic In"
#define MIDI_OUT_PORT_NAME "GeoLEDic Out"

#ifdef WITH_GFX
#include <string>
#include <map>
#endif

class MidiSource
{
public:
   MidiSource();
   ~MidiSource();
   
   const MidiMessage* read();
   
#ifdef WITH_GFX
   class MidiPorts {
   public:
      typedef int PortId;
      virtual ~MidiPorts(){};
      virtual void updateAvailablePorts(std::map<PortId, std::string>& port_map, PortId& selected_port) = 0;
      virtual void selectPort(PortId selected_port) = 0;
   };

   class MidiSender
   {
   public:
      virtual ~MidiSender(){};
      virtual bool enabled() const = 0;
      virtual void enable(bool ena) = 0;
      virtual void sendControlChange(uint8_t cc_num, uint8_t val) = 0;
      virtual void sendProgramChange(uint8_t program) = 0;
   };

   MidiPorts* getMidiInPorts();
   MidiPorts* getMidiOutPorts();
   MidiSender* getSender();

   void enableMidiThrough(bool enabled);
#endif
   
private:
   class Impl;
   Impl& m_i;
};

#endif // GEOLEDIC_MIDI_SOURCE_HPP
