#include <gmock/gmock.h>
#include "Triangle.hpp"
#include <numeric>

void PrintTo(const CRGB& c, ::std::ostream* os)
{
   *os << "RGB(" << +c.r << "," << +c.g << "," << +c.b << ")";
}

static const Vertex ARBITRARY_COORDINATES[3] = {{0, 0, 0}, {0, 1, 0}, {1, 0, 0}};

TEST(TriangleOrientation, stripStartingInFirstCornerRunningClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], CRGB::White);
   
   Triangle t(strip, {{0, 2}, {3, 5}, {6, 8}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 1);

   EXPECT_THAT(strip, testing::ElementsAreArray({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(TriangleOrientation, stripStartingInSecondCornerRunningClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], CRGB::White);
   
   Triangle t(strip, {{6, 8}, {0, 2}, {3, 5}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 1);
   
   EXPECT_THAT(strip, testing::ElementsAreArray({4, 5, 6, 7, 8, 9, 1, 2, 3}));
}

TEST(TriangleOrientation, stripStartingInThirdCornerRunningClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], CRGB::White);
   
   Triangle t(strip, {{3, 5}, {6, 8}, {0, 2}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 1);
   
   EXPECT_THAT(strip, testing::ElementsAreArray({7, 8, 9, 1, 2, 3, 4, 5, 6}));
}
