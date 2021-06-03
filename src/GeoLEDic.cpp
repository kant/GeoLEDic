#include "GeoLEDic.hpp"
#include "MidiSource.hpp"
#include "ProgramFactory.hpp"
#include "programs/Diagnostic.hpp"
#ifdef WITH_FLOGL
#include "Serial.hpp"
#endif

namespace {
MidiSource midi_source;
ProgramFactory factory({dome, DOME_NUM_TRIANGLES}, leds, NUM_STRIPS, LEDS_PER_STRIP);
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

#if defined(USB_MIDI_SERIAL) or defined(WITH_FLOGL)
   static Diagnostic* diagnostic_mode = nullptr;
   while (Serial.available())
   {
      char c = Serial.read();
      if (c == 'd' or c == 'D')
      {
         program  = factory.changeProgram(127);
         diagnostic_mode = reinterpret_cast<Diagnostic*>(program);
         Serial.println("Diagnostic mode entered");
      }
      else if (c == 'x' or c == 'X')
      {
         program = factory.changeProgram(0);
         Serial.println("Diagnostic mode exited");
         diagnostic_mode = nullptr;
      }
      else if (diagnostic_mode)
      {
         if (diagnostic_mode->processKeyboardInput(c))
         {
            if (c == '\r' or c == '\n')
            {
               Serial.println();
            }
            else
            {
               Serial.print(c);
            }
         }
      }
   }
#endif

   program->run();
}
