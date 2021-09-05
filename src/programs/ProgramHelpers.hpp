#ifndef ProgramHelpers_hpp
#define ProgramHelpers_hpp

#include <algorithm>

template <unsigned width, unsigned height>
uint8_t interpolate(uint8_t (&array)[width][height], float h, float v)
{
   unsigned v0 = v;
   unsigned v1 = std::min(v0+1, height-1);
   float rv0 =  v1 - v;
   float rv1 = 1 - rv0;
   unsigned h0 = h;
   unsigned h1 = h0 == width-1 ? 0 : h0+1;
   float rh0 = (h0+1) - h;
   float rh1 = 1 - rh0;
   
   return array[h0][v0] * rh0 * rv0 +
          array[h0][v1] * rh0 * rv1 +
          array[h1][v0] * rh1 * rv0 +
          array[h1][v1] * rh1 * rv1;
}

#endif /* ProgramHelpers_hpp */
