#include "flogl/flogl.hpp"
#include "flogl/Config.hpp"

#include <math.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include "MidiSource.hpp"
#include "ProgramFactory.hpp"
#include "Dome.hpp"

void setupGeoLEDic();
void loopGeoLEDic();

int main()
{

   std::vector<flogl::LED> leds;

   std::vector<flogl::Config::View> views =
     {
     // x     y    z   FOV  horz vert
       {0,   30, 140,  45,    0,    0},  // front
       {0, -140, -20,  45,    0,   90},  // up
     };

   for (const Triangle& t: dome)
   {
      t.createLeds(leds);
   }
   flogl::Flogl flogl(&leds[0], leds.size(),
		      flogl::Config()
		      .views(views));
   
   setupGeoLEDic();
   
   do {
      loopGeoLEDic();
      usleep(30000);
   } while(flogl.draw());
   
   return 0;
}

namespace {
MidiSource midi_source;
ProgramFactory factory(dome, sizeof(dome)/sizeof(*dome));
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
