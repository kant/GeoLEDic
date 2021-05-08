#include "flogl/flogl.hpp"
#include "flogl/Config.hpp"
#include <FastLED.h>
#include <math.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

#include <iostream>

struct Vertex {
   Vertex(): x(), y(), z()
   {}
  
   /* ordering is deliberate, for some reason z is up in SketchUp */
   Vertex(float x, float z, float y): x(x), y(y), z(z)
   {}
   float x;
   float y;
   float z;

   Vertex operator+(const Vertex& v) const
   {
      return Vertex(x + v.x, z + v.z, y + v.y);
   }

   Vertex operator-(const Vertex& v) const
   {
      return Vertex(x - v.x, z - v.z, y - v.y);
   }

   Vertex operator*(float v) const
   {
      return Vertex(x*v, z*v, y*v);
   }

   Vertex operator/(float v) const
   {
      return Vertex(x/v, z/v, y/v);
   }

};

std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
   return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}


struct Edge {
   Edge(): first_led(), last_led()
   {}
   Edge(int first_led, int last_led): first_led(first_led), last_led(last_led)
   {}
   int first_led;
   int last_led;
};


class Triangle {
public:

   Triangle(
      const Edge (&edges)[3],
      const Vertex (&vertices)[3]):
         m_edges(),
         m_vertices(),
         m_led_corners()
   {
      float fac = 0.95;
      std::copy(&edges[0], &edges[3], &m_edges[0]);
      std::copy(&vertices[0], &vertices[3], &m_vertices[0]);
      m_led_corners[0] = inset(m_vertices[0], m_vertices[1], m_vertices[2], fac);
      m_led_corners[1] = inset(m_vertices[1], m_vertices[2], m_vertices[0], fac);
      m_led_corners[2] = inset(m_vertices[2], m_vertices[0], m_vertices[1], fac);
   }

   Vertex inset(const Vertex& v1, const Vertex& v2, const Vertex& v3, float fac)
   {
      return (v1 * fac + v2 * ((1-fac)/2) + v3 * ((1-fac)/2));
   }
      
   Edge   m_edges[3];
   Vertex m_vertices[3];
   Vertex m_led_corners[3];
};

int default_led(int step)
{
   static int led = 0;
   int old = led;
   led += step;
   return old;
}

#define DEFAULT_TRIANGLE {{default_led(50), default_led(1)},{default_led(50), default_led(1)},{default_led(50), default_led(1)}}



Triangle dome[] =
{
// row 0
{DEFAULT_TRIANGLE,    {{ 5.10,  2.68,  1.66},{ 5.71,  1.85,  0.00},{ 5.71,  0.83,  1.66}}},
{DEFAULT_TRIANGLE,    {{ 5.71,  1.85,  0.00},{ 5.71,  0.83,  1.66},{ 6.00,  0.00,  0.00}}},
{DEFAULT_TRIANGLE,    {{ 5.71,  0.83,  1.66},{ 6.00,  0.00,  0.00},{ 5.73, -0.93,  1.51}}},
{DEFAULT_TRIANGLE,    {{ 6.00,  0.00,  0.00},{ 5.73, -0.93,  1.51},{ 5.71, -1.85,  0.00}}},
{DEFAULT_TRIANGLE,    {{ 5.73, -0.93,  1.51},{ 5.71, -1.85,  0.00},{ 5.19, -2.62,  1.51}}},
{DEFAULT_TRIANGLE,    {{ 5.71, -1.85,  0.00},{ 5.19, -2.62,  1.51},{ 4.85, -3.53,  0.00}}},
{DEFAULT_TRIANGLE,    {{ 5.19, -2.62,  1.51},{ 4.85, -3.53,  0.00},{ 4.13, -4.02,  1.66}}},
{DEFAULT_TRIANGLE,    {{ 4.85, -3.53,  0.00},{ 4.13, -4.02,  1.66},{ 3.53, -4.85,  0.00}}},
{DEFAULT_TRIANGLE,    {{ 4.13, -4.02,  1.66},{ 3.53, -4.85,  0.00},{ 2.55, -5.17,  1.66}}},
{DEFAULT_TRIANGLE,    {{ 3.53, -4.85,  0.00},{ 2.55, -5.17,  1.66},{ 1.85, -5.71,  0.00}}},
{DEFAULT_TRIANGLE,    {{ 2.55, -5.17,  1.66},{ 1.85, -5.71,  0.00},{ 0.89, -5.74,  1.51}}},
{DEFAULT_TRIANGLE,    {{ 1.85, -5.71,  0.00},{ 0.89, -5.74,  1.51},{ 0.00, -6.00,  0.00}}},
{DEFAULT_TRIANGLE,    {{ 0.89, -5.74,  1.51},{ 0.00, -6.00,  0.00},{-0.89, -5.74,  1.51}}},
{DEFAULT_TRIANGLE,    {{ 0.00, -6.00,  0.00},{-0.89, -5.74,  1.51},{-1.85, -5.71,  0.00}}},
{DEFAULT_TRIANGLE,    {{-0.89, -5.74,  1.51},{-1.85, -5.71,  0.00},{-2.55, -5.17,  1.66}}},
{DEFAULT_TRIANGLE,    {{-1.85, -5.71,  0.00},{-2.55, -5.17,  1.66},{-3.53, -4.85,  0.00}}},
{DEFAULT_TRIANGLE,    {{-2.55, -5.17,  1.66},{-3.53, -4.85,  0.00},{-4.13, -4.02,  1.66}}},
{DEFAULT_TRIANGLE,    {{-3.53, -4.85,  0.00},{-4.13, -4.02,  1.66},{-4.85, -3.53,  0.00}}},
{DEFAULT_TRIANGLE,    {{-4.13, -4.02,  1.66},{-4.85, -3.53,  0.00},{-5.19, -2.62,  1.51}}},
{DEFAULT_TRIANGLE,    {{-4.85, -3.53,  0.00},{-5.19, -2.62,  1.51},{-5.71, -1.85,  0.00}}},
{DEFAULT_TRIANGLE,    {{-5.19, -2.62,  1.51},{-5.71, -1.85,  0.00},{-5.73, -0.93,  1.51}}},
{DEFAULT_TRIANGLE,    {{-5.71, -1.85,  0.00},{-5.73, -0.93,  1.51},{-6.00,  0.00,  0.00}}},
{DEFAULT_TRIANGLE,    {{-5.73, -0.93,  1.51},{-6.00,  0.00,  0.00},{-5.71,  0.83,  1.66}}},
{DEFAULT_TRIANGLE,    {{-6.00,  0.00,  0.00},{-5.71,  0.83,  1.66},{-5.71,  1.85,  0.00}}},
{DEFAULT_TRIANGLE,    {{-5.71,  0.83,  1.66},{-5.71,  1.85,  0.00},{-5.10,  2.86,  1.66}}},
// row 1
{DEFAULT_TRIANGLE,    {{ 4.09,  3.19,  3.01},{ 5.10,  2.68,  1.66},{ 4.85,  1.58,  3.15}}},
{DEFAULT_TRIANGLE,    {{ 5.10,  2.68,  1.66},{ 4.85,  1.58,  3.15},{ 5.71,  0.83,  1.66}}},
{DEFAULT_TRIANGLE,    {{ 4.85,  1.58,  3.15},{ 5.71,  0.83,  1.66},{ 5.19, -0.18,  3.01}}},
{DEFAULT_TRIANGLE,    {{ 5.71,  0.83,  1.66},{ 5.19, -0.18,  3.01},{ 5.73, -0.93,  1.51}}},
{DEFAULT_TRIANGLE,    {{ 5.19, -0.18,  3.01},{ 5.73, -0.93,  1.51},{ 5.10, -1.66,  2.68}}},
{DEFAULT_TRIANGLE,    {{ 5.73, -0.93,  1.51},{ 5.10, -1.66,  2.68},{ 5.19, -2.62,  1.51}}},
{DEFAULT_TRIANGLE,    {{ 5.10, -1.66,  2.68},{ 5.19, -2.62,  1.51},{ 4.30, -2.90,  3.01}}},
{DEFAULT_TRIANGLE,    {{ 5.19, -2.62,  1.51},{ 4.30, -2.90,  3.01},{ 4.13, -4.02,  1.66}}},
{DEFAULT_TRIANGLE,    {{ 4.30, -2.90,  3.01},{ 4.13, -4.02,  1.66},{ 3.00, -4.13,  3.15}}},
{DEFAULT_TRIANGLE,    {{ 4.13, -4.02,  1.66},{ 3.00, -4.13,  3.15},{ 2.55, -5.17,  1.66}}},
{DEFAULT_TRIANGLE,    {{ 3.00, -4.13,  3.15},{ 2.55, -5.17,  1.66},{ 1.43, -4.99,  3.01}}},
{DEFAULT_TRIANGLE,    {{ 2.55, -5.17,  1.66},{ 1.43, -4.99,  3.01},{ 0.89, -5.74,  1.51}}},
{DEFAULT_TRIANGLE,    {{ 1.43, -4.99,  3.01},{ 0.89, -5.74,  1.51},{ 0.00, -5.37,  2.68}}},
{DEFAULT_TRIANGLE,    {{ 0.89, -5.74,  1.51},{ 0.00, -5.37,  2.68},{-0.89, -5.74,  1.51}}},
{DEFAULT_TRIANGLE,    {{ 0.00, -5.37,  2.68},{-0.89, -5.74,  1.51},{-1.43, -4.99,  3.01}}},
{DEFAULT_TRIANGLE,    {{-0.89, -5.74,  1.51},{-1.43, -4.99,  3.01},{-2.55, -5.17,  1.66}}},
{DEFAULT_TRIANGLE,    {{-1.43, -4.99,  3.01},{-2.55, -5.17,  1.66},{-3.00, -4.13,  3.15}}},
{DEFAULT_TRIANGLE,    {{-2.55, -5.17,  1.66},{-3.00, -4.13,  3.15},{-4.13, -4.02,  1.66}}},
{DEFAULT_TRIANGLE,    {{-3.00, -4.13,  3.15},{-4.13, -4.02,  1.66},{-4.30, -2.90,  3.01}}},
{DEFAULT_TRIANGLE,    {{-4.13, -4.02,  1.66},{-4.30, -2.90,  3.01},{-5.19, -2.62,  1.51}}},
{DEFAULT_TRIANGLE,    {{-4.30, -2.90,  3.01},{-5.19, -2.62,  1.51},{-5.10, -1.66,  2.68}}},
{DEFAULT_TRIANGLE,    {{-5.19, -2.62,  1.51},{-5.10, -1.66,  2.68},{-5.73, -0.93,  1.51}}},
{DEFAULT_TRIANGLE,    {{-5.10, -1.66,  2.68},{-5.73, -0.93,  1.51},{-5.19, -0.18,  3.01}}},
{DEFAULT_TRIANGLE,    {{-5.73, -0.93,  1.51},{-5.19, -0.18,  3.01},{-5.71,  0.83,  1.66}}},
{DEFAULT_TRIANGLE,    {{-5.19, -0.18,  3.01},{-5.71,  0.83,  1.66},{-4.85,  1.58,  3.15}}},
{DEFAULT_TRIANGLE,    {{-5.71,  0.83,  1.66},{-4.85,  1.58,  3.15},{-5.10,  2.86,  1.66}}},
{DEFAULT_TRIANGLE,    {{-4.85,  1.58,  3.15},{-5.10,  2.86,  1.66},{-4.09,  3.19,  3.01}}},
// row 2
{DEFAULT_TRIANGLE,    {{ 2.66,  3.66,  3.95},{ 4.09,  3.19,  3.01},{ 3.53,  2.17,  4.34}}},
{DEFAULT_TRIANGLE,    {{ 4.09,  3.19,  3.01},{ 3.53,  2.17,  4.34},{ 4.85,  1.58,  3.15}}},
{DEFAULT_TRIANGLE,    {{ 3.53,  2.17,  4.34},{ 4.85,  1.58,  3.15},{ 4.13,  0.32,  4.34}}},
{DEFAULT_TRIANGLE,    {{ 4.85,  1.58,  3.15},{ 4.13,  0.32,  4.34},{ 5.19, -0.18,  3.01}}},
{DEFAULT_TRIANGLE,    {{ 4.13,  0.32,  4.34},{ 5.19, -0.18,  3.01},{ 4.30, -1.40,  3.95}}},
{DEFAULT_TRIANGLE,    {{ 5.19, -0.18,  3.01},{ 4.30, -1.40,  3.95},{ 5.10, -1.66,  2.68}}},
{DEFAULT_TRIANGLE,    {{ 5.10, -1.66,  2.68},{ 4.30, -1.40,  3.95},{ 4.30, -2.90,  3.01}}},
{DEFAULT_TRIANGLE,    {{ 4.30, -1.40,  3.95},{ 4.30, -2.90,  3.01},{ 3.15, -2.68,  4.34}}},
{DEFAULT_TRIANGLE,    {{ 4.30, -2.90,  3.01},{ 3.15, -2.68,  4.34},{ 3.00, -4.13,  3.15}}},
{DEFAULT_TRIANGLE,    {{ 3.15, -2.68,  4.34},{ 3.00, -4.13,  3.15},{ 1.58, -3.83,  4.34}}},
{DEFAULT_TRIANGLE,    {{ 3.00, -4.13,  3.15},{ 1.58, -3.83,  4.34},{ 1.43, -4.99,  3.01}}},
{DEFAULT_TRIANGLE,    {{ 1.58, -3.83,  4.34},{ 1.43, -4.99,  3.01},{ 0.00, -4.52,  3.95}}},
{DEFAULT_TRIANGLE,    {{ 1.43, -4.99,  3.01},{ 0.00, -4.52,  3.95},{ 0.00, -5.37,  2.68}}},
{DEFAULT_TRIANGLE,    {{-0.00, -5.37,  2.68},{-0.00, -4.52,  3.95},{-1.43, -4.99,  3.01}}},
{DEFAULT_TRIANGLE,    {{-0.00, -4.52,  3.95},{-1.43, -4.99,  3.01},{-1.58, -3.83,  4.34}}},
{DEFAULT_TRIANGLE,    {{-1.43, -4.99,  3.01},{-1.58, -3.83,  4.34},{-3.00, -4.13,  3.15}}},
{DEFAULT_TRIANGLE,    {{-1.58, -3.83,  4.34},{-3.00, -4.13,  3.15},{-3.15, -2.68,  4.34}}},
{DEFAULT_TRIANGLE,    {{-3.00, -4.13,  3.15},{-3.15, -2.68,  4.34},{-4.30, -2.90,  3.01}}},
{DEFAULT_TRIANGLE,    {{-3.15, -2.68,  4.34},{-4.30, -2.90,  3.01},{-4.30, -1.40,  3.95}}},
{DEFAULT_TRIANGLE,    {{-4.30, -2.90,  3.01},{-4.30, -1.40,  3.95},{-5.10, -1.66,  2.68}}},
{DEFAULT_TRIANGLE,    {{-5.10, -1.66,  2.68},{-4.30, -1.40,  3.95},{-5.19, -0.18,  3.01}}},
{DEFAULT_TRIANGLE,    {{-4.30, -1.40,  3.95},{-5.19, -0.18,  3.01},{-4.13,  0.32,  4.34}}},
{DEFAULT_TRIANGLE,    {{-5.19, -0.18,  3.01},{-4.13,  0.32,  4.34},{-4.85,  1.58,  3.15}}},
{DEFAULT_TRIANGLE,    {{-4.13,  0.32,  4.34},{-4.85,  1.58,  3.15},{-3.53,  2.17,  4.34}}},
{DEFAULT_TRIANGLE,    {{-4.85,  1.58,  3.15},{-3.53,  2.17,  4.34},{-4.09,  3.19,  3.01}}},
{DEFAULT_TRIANGLE,    {{-3.53,  2.17,  4.34},{-4.09,  3.19,  3.01},{-2.66,  3.66,  3.95}}},
// row 3
{DEFAULT_TRIANGLE,    {{ 0.97,  4.02,  4.34},{ 2.66,  3.66,  3.95},{ 1.85,  2.55,  5.10}}},
{DEFAULT_TRIANGLE,    {{ 2.66,  3.66,  3.95},{ 1.85,  2.55,  5.10},{ 3.53,  2.17,  4.34}}},
{DEFAULT_TRIANGLE,    {{ 1.85,  2.55,  5.10},{ 3.53,  2.17,  4.34},{ 2.55,  0.83,  5.37}}},
{DEFAULT_TRIANGLE,    {{ 3.53,  2.17,  4.34},{ 2.55,  0.83,  5.37},{ 4.13,  0.32,  4.34}}},
{DEFAULT_TRIANGLE,    {{ 2.55,  0.83,  5.37},{ 4.13,  0.32,  4.34},{ 3.00, -0.97,  5.10}}},
{DEFAULT_TRIANGLE,    {{ 4.13,  0.32,  4.34},{ 3.00, -0.97,  5.10},{ 4.30, -1.40,  3.95}}},
{DEFAULT_TRIANGLE,    {{ 4.30, -1.40,  3.95},{ 3.00, -0.97,  5.10},{ 3.15, -2.68,  4.34}}},
{DEFAULT_TRIANGLE,    {{ 3.00, -0.97,  5.10},{ 3.15, -2.68,  4.34},{ 1.58, -2.17,  5.37}}},
{DEFAULT_TRIANGLE,    {{ 3.15, -2.68,  4.34},{ 1.58, -2.17,  5.37},{ 1.58, -3.83,  4.34}}},
{DEFAULT_TRIANGLE,    {{ 1.58, -2.17,  5.37},{ 1.58, -3.83,  4.34},{ 0.00, -3.15,  5.10}}},
{DEFAULT_TRIANGLE,    {{ 1.58, -3.83,  4.34},{ 0.00, -3.15,  5.10},{ 0.00, -4.52,  3.95}}},
{DEFAULT_TRIANGLE,    {{-0.00, -4.52,  3.95},{-0.00, -3.15,  5.10},{-1.58, -3.83,  4.34}}},
{DEFAULT_TRIANGLE,    {{-0.00, -3.15,  5.10},{-1.58, -3.83,  4.34},{-1.58, -2.17,  5.37}}},
{DEFAULT_TRIANGLE,    {{-1.58, -3.83,  4.34},{-1.58, -2.17,  5.37},{-3.15, -2.68,  4.34}}},
{DEFAULT_TRIANGLE,    {{-1.58, -2.17,  5.37},{-3.15, -2.68,  4.34},{-3.00, -0.97,  5.10}}},
{DEFAULT_TRIANGLE,    {{-3.15, -2.68,  4.34},{-3.00, -0.97,  5.10},{-4.30, -1.40,  3.95}}},
{DEFAULT_TRIANGLE,    {{-4.30, -1.40,  3.95},{-3.00, -0.97,  5.10},{-4.13,  0.32,  4.34}}},
{DEFAULT_TRIANGLE,    {{-3.00, -0.97,  5.10},{-4.13,  0.32,  4.34},{-2.55,  0.83,  5.37}}},
{DEFAULT_TRIANGLE,    {{-4.13,  0.32,  4.34},{-2.55,  0.83,  5.37},{-3.53,  2.17,  4.34}}},
{DEFAULT_TRIANGLE,    {{-2.55,  0.83,  5.37},{-3.53,  2.17,  4.34},{-1.85,  2.55,  5.10}}},
{DEFAULT_TRIANGLE,    {{-3.53,  2.17,  4.34},{-1.85,  2.55,  5.10},{-2.66,  3.66,  3.95}}},
{DEFAULT_TRIANGLE,    {{-1.85,  2.55,  5.10},{-2.66,  3.66,  3.95},{-0.97,  4.02,  4.34}}},
// row 4
{DEFAULT_TRIANGLE,    {{-0.97,  4.02,  4.34},{ 0.97,  4.02,  4.34},{ 0.00,  2.68,  5.37}}},
{DEFAULT_TRIANGLE,    {{ 0.97,  4.02,  4.34},{ 0.00,  2.68,  5.37},{ 1.85,  2.55,  5.10}}},
{DEFAULT_TRIANGLE,    {{ 0.00,  2.68,  5.37},{ 1.85,  2.55,  5.10},{ 0.89,  1.22,  5.81}}},
{DEFAULT_TRIANGLE,    {{ 1.85,  2.55,  5.10},{ 0.89,  1.22,  5.81},{ 2.55,  0.83,  5.37}}},
{DEFAULT_TRIANGLE,    {{ 0.89,  1.22,  5.81},{ 2.55,  0.83,  5.37},{ 1.43, -0.47,  5.81}}},
{DEFAULT_TRIANGLE,    {{ 2.55,  0.83,  5.37},{ 1.43, -0.47,  5.81},{ 3.00, -0.97,  5.10}}},
{DEFAULT_TRIANGLE,    {{ 3.00, -0.97,  5.10},{ 1.43, -0.47,  5.81},{ 1.58, -2.17,  5.37}}},
{DEFAULT_TRIANGLE,    {{ 1.43, -0.47,  5.81},{ 1.58, -2.17,  5.37},{ 0.00, -1.51,  5.81}}},
{DEFAULT_TRIANGLE,    {{ 1.58, -2.17,  5.37},{ 0.00, -1.51,  5.81},{ 0.00, -3.15,  5.10}}},
{DEFAULT_TRIANGLE,    {{-0.00, -3.15,  5.10},{-0.00, -1.51,  5.81},{-1.58, -2.17,  5.37}}},
{DEFAULT_TRIANGLE,    {{-0.00, -1.51,  5.81},{-1.58, -2.17,  5.37},{-1.43, -0.47,  5.81}}},
{DEFAULT_TRIANGLE,    {{-1.58, -2.17,  5.37},{-1.43, -0.47,  5.81},{-3.00, -0.97,  5.10}}},
{DEFAULT_TRIANGLE,    {{-3.00, -0.97,  5.10},{-1.43, -0.47,  5.81},{-2.55,  0.83,  5.37}}},
{DEFAULT_TRIANGLE,    {{-1.43, -0.47,  5.81},{-2.55,  0.83,  5.37},{-0.89,  1.22,  5.81}}},
{DEFAULT_TRIANGLE,    {{-2.55,  0.83,  5.37},{-0.89,  1.22,  5.81},{-1.85,  2.55,  5.10}}},
{DEFAULT_TRIANGLE,    {{-0.89,  1.22,  5.81},{-1.85,  2.55,  5.10},{-0.00,  2.68,  5.37}}},
{DEFAULT_TRIANGLE,    {{-1.85,  2.55,  5.10},{-0.00,  2.68,  5.37},{-0.97,  4.02,  4.34}}},
// row 5
{DEFAULT_TRIANGLE,    {{ 0.00,  2.68,  5.37},{-0.89,  1.22,  5.81},{ 0.89,  1.22,  5.81}}},
{DEFAULT_TRIANGLE,    {{-0.89,  1.22,  5.81},{ 0.89,  1.22,  5.81},{ 0.00,  0.00,  6.00}}},
{DEFAULT_TRIANGLE,    {{ 0.89,  1.22,  5.81},{ 0.00,  0.00,  6.00},{ 1.43, -0.47,  5.81}}},
{DEFAULT_TRIANGLE,    {{ 1.43, -0.47,  5.81},{ 0.00, -1.51,  5.81},{ 0.00,  0.00,  6.00}}},
{DEFAULT_TRIANGLE,    {{ 0.00, -1.51,  5.81},{ 0.00,  0.00,  6.00},{-1.43, -0.47,  5.81}}},
{DEFAULT_TRIANGLE,    {{ 0.00,  0.00,  6.00},{-1.43, -0.47,  5.81},{-0.89,  1.22,  5.81}}},

};


int main()
{
   std::vector<flogl::LED> leds;
   std::vector<CRGB> colors;

   std::vector<flogl::Config::View> views =
     {
     // x     y    z   FOV  horz vert
       {0,   30, 140,  45,    0,    0},  // front
       {0, -140, -20,  45,    0,   90},  // up
     };
   


   for (const Triangle& t: dome)
   {
      for (const Vertex& v: t.m_vertices)
      {
         //leds.push_back({-v.x*10, v.y*10, v.z*10});
         //colors.push_back(CRGB::Blue);
      }

      int i = 0;
      for (const Edge& e: t.m_edges)
      {
         int j = (i+1)%3;

         Vertex vec = t.m_led_corners[j] - t.m_led_corners[i];

         int d = e.last_led - e.first_led;
         for (int l = 0; l <= d; l++)
         {
            Vertex lv(t.m_led_corners[i] + vec * ((float(l)+0.5)/(float(d)+1.0)));
            //std::cout << l << " " << t.m_led_corners[i] << " " << vec << " " << lv << std::endl;
            leds.push_back({-lv.x*10, lv.y*10, lv.z*10, 0.3});
            colors.push_back(CRGB::Black);
         }
         
         i++;
      }
   }
   flogl::Flogl flogl(&leds[0], leds.size(),
		      flogl::Config()
		      .views(views));
   flogl.add(&colors[0], leds.size());

   int r = 0;
   int g = 0;
   int b = 0;
   int c0 = 0;
   
   do {
      int c1 = 0;
      for (CRGB& l: colors)
      {
         int c = c0 + c1;
         if (rand() % 100 == 0)
         {
            l = CRGB::White;
         }
         else
         {
            int colr = float(r)/2 * float(c % 100)/100;
            int colg = float(g)/2 * float((c+30) % 100)/100;
            int colb = float(b)/2 * float((c+60) % 100)/100;
            
            l = CRGB(colr < 255 ? colr : 255,
                     colg < 255 ? colg : 255,
                     colb < 255 ? colb : 255);
         }
         c1++;
      }

      usleep(30000);
      if (r < 2*200) r++;
      else if (g < 2*200) g++;
      else if (b < 2*200) b++;
      
      c0++;
   } while(flogl.draw());
   
   return 0;
}
