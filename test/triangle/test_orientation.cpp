#include <gmock/gmock.h>
#include "Triangle.hpp"

namespace {
static const Vertex ARBITRARY_COORDINATES[3] = {{0, 0, 0}, {0, 1, 0}, {1, 0, 0}};

TEST(TriangleOrientation, stripStartingInFirstCornerRunningClockwise)
{
   CRGB strip[9];
   Triangle t(strip, {{0, 2}, {3, 5}, {6, 8}}, ARBITRARY_COORDINATES);
   
   uint32_t ix = 1;
   for (CRGB& led: t)
   {
      led = ix++;
   }
   
   EXPECT_THAT(strip, testing::ElementsAreArray({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

}
