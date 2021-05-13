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

CRGB colors[20000];

#define DEFAULT_TRIANGLE colors, {{default_led(50), default_led(1)},{default_led(50), default_led(1)},{default_led(50), default_led(1)}}

#include "dome.hpp"


const TProgmemRGBPalette16 RainbowColors_p  =
{
      0xFF0000, 0xD52A00, 0xAB5500, 0xAB7F00,
      0xABAB00, 0x56D500, 0x00FF00, 0x00D52A,
      0x00AB55, 0x0056AA, 0x0000FF, 0x2A00D5,
      0x5500AB, 0x7F0081, 0xAB0055, 0xD5002B
};

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
   
   CRGB* col = colors;
   for (flogl::LED& led: leds)
   {
      led.color = col++;
   }

   int r = 0;
   int g = 0;
   int b = 0;
   int p = 0;
   int c0 = 0;
   
   unsigned notes[128] = {0};
   
   do {
      const MidiMessage* msg;
      while ((msg = midi_source.read()))
      {
         switch (msg->type())
         {
            case MidiMessage::NOTE_ON:
               notes[msg->data[1]] = msg->data[2];
               break;
            case MidiMessage::NOTE_OFF:
               notes[msg->data[1]] = 0;
               break;
            case MidiMessage::PROGRAM_CHANGE:
               break;
            case MidiMessage::CONTROL_CHANGE:
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
                     p = msg->data[2] ? 4 * ((128 - msg->data[2])) : 0;
                     break;
                  default:
                     break;
               }
               break;
            default:
               break;
         }
      }
         
      int t_ix = 0;
      for (Triangle& t: dome)
      {
         if (notes[t_ix] > 0)
         {
            std::fill(t.begin(), t.end(), RainbowColors_p[notes[t_ix]/8]);
         }
         else
         {
            int c = 0;
            int next_sparkle = p ? rand() % p : -1;
            for(CRGB& led: t)
            {
               if (c == next_sparkle)
               {
                  next_sparkle += (rand() % p) + 1;
                  led = CRGB::White;
               }
               else
               {
                  int c1 = c + c0 + t_ix*20;
                  int colr = (r * (c1 % 128))/64;
                  int colg = (g * ((c1+30) % 128))/64;
                  int colb = (b * ((c1+60) % 128))/64;
                  
                  led = CRGB(colr < 255 ? colr : 255,
                             colg < 255 ? colg : 255,
                             colb < 255 ? colb : 255);
               }
               c++;
            }
         }
         t_ix++;
      }

      usleep(30000);      
      c0++;
   } while(flogl.draw());
   
   return 0;
}
