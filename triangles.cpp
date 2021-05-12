#include "flogl/flogl.hpp"
#include "flogl/Config.hpp"
#include "Triangle.hpp"
#include <FastLED.h>
#include <math.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include "MidiSource.hpp"


int default_led(int step)
{
   static int led = 0;
   int old = led;
   led += step;
   return old;
}

#define DEFAULT_TRIANGLE {{default_led(50), default_led(1)},{default_led(50), default_led(1)},{default_led(50), default_led(1)}}

#include "dome.hpp"


int main()
{
   MidiSource midi_source;

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
   
   std::vector<CRGB> colors(leds.size(), CRGB::Black);
   CRGB* col = colors.data();
   for (flogl::LED& led: leds)
   {
      led.color = col++;
   }

   int r = 0;
   int g = 0;
   int b = 0;
   int p = 0;
   int c0 = 0;
   
   std::map<unsigned, unsigned> notes;
   
   do {
      const MidiMessage* msg;
      while ((msg = midi_source.read()))
      {
         std::cout << "have: " << std::hex;
         std::copy(msg->data, msg->data + msg->length, std::ostream_iterator<unsigned>(std::cout, ", "));
         std::cout << std::dec << std::endl;
         switch (msg->type())
         {
            case MidiMessage::NOTE_ON:
               std::cout << "note on" << std::endl;
               notes[msg->data[1]] = msg->data[2];
               break;
            case MidiMessage::NOTE_OFF:
               std::cout << "note off" << std::endl;
               notes[msg->data[1]] = 0;
               break;
            case MidiMessage::PROGRAM_CHANGE:
               std::cout << "program" << std::endl;
               break;
            case MidiMessage::CONTROL_CHANGE:
               std::cout << "control" << std::endl;
               switch (msg->data[1])
               {
                  case 0x4a:
                     r = msg->data[2];
                     break;
                  case 0x47:
                     g = msg->data[2];
                     break;
                  case 0x5b:
                     b = msg->data[2];
                     break;
                  case 0x5d:
                     p = msg->data[2];
                     break;
                  default:
                     break;
               }
               break;
            default:
               break;
         }
      }
         
      
      int c1 = 0;
      for (CRGB& l: colors)
      {
         int c = c0 + c1;
         if (rand() % (10000 / (p+1)) == 0)
         {
            l = CRGB::White;
         }
         else
         {
            int colr = float(r) * 2 * float(c % 100)/100;
            int colg = float(g) * 2 * float((c+30) % 100)/100;
            int colb = float(b) * 2 * float((c+60) % 100)/100;
            
            l = CRGB(colr < 255 ? colr : 255,
                     colg < 255 ? colg : 255,
                     colb < 255 ? colb : 255);
         }
         c1++;
      }
      
      for (std::pair<unsigned, unsigned> e: notes)
      {
         if (e.second > 0)
         {
            unsigned triangle_ix = e.first;
            for (unsigned k = triangle_ix * 153; k < (triangle_ix + 1) * 153; k++)
            {
               colors[k] = CRGB::Yellow;
            }
         }
      }

      usleep(30000);      
      c0++;
   } while(flogl.draw());
   
   return 0;
}
