#include "GeoLEDic.hpp"
#include "MidiSource.hpp"
#include "ProgramFactory.hpp"

namespace {
MidiSource midi_source;
ProgramFactory factory(dome, DOME_NUM_TRIANGLES);
Program* program;
}

void setupGeoLEDic()
{
   program = factory.changeProgram(0);
}

void loopGeoLEDic()
{
   const MidiMessage* msg;
   while ((msg = midi_source.read()))
   {
      switch (msg->type())
      {
         case MidiMessage::NOTE_ON:
            program->noteOn(msg->data[1], msg->data[2]);
            break;
         case MidiMessage::NOTE_OFF:
            program->noteOff(msg->data[1]);
            break;
         case MidiMessage::PROGRAM_CHANGE:
            program = factory.changeProgram(msg->data[1]);
            break;
         case MidiMessage::CONTROL_CHANGE:
            program->controlChange(msg->data[1], msg->data[2]);
            break;
         default:
            break;
      }
   }
      
   program->run();
}
