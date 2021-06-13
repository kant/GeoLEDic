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
   
   /*
                2 3
              1     4
    begin-> 0         5
    end-1 --> 8  7  6
   */
   Triangle t(strip, {{0, 2}, {3, 5}, {6, 8}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 0);

   EXPECT_THAT(strip, testing::ElementsAreArray({0, 1, 2, 3, 4, 5, 6, 7, 8}));
}

TEST(TriangleOrientation, stripStartingInSecondCornerRunningClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], CRGB::White);
   
   /*
                8 0
              7     1
    begin-> 6         2
    end-1 --> 5  4  3
   */
   Triangle t(strip, {{6, 8}, {0, 2}, {3, 5}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 0);
   
   EXPECT_THAT(strip, testing::ElementsAreArray({3, 4, 5, 6, 7, 8, 0, 1, 2}));
}

TEST(TriangleOrientation, stripStartingInThirdCornerRunningClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], CRGB::White);
   
   /*
                5 6
              4     7
    begin-> 3         8
    end-1 --> 2  1  0
   */
   Triangle t(strip, {{3, 5}, {6, 8}, {0, 2}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 0);
   
   EXPECT_THAT(strip, testing::ElementsAreArray({6, 7, 8, 0, 1, 2, 3, 4, 5}));
}

TEST(TriangleOrientation, stripStartingInFirstCornerRunningCounterClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], CRGB::White);
   
   /*
                6 5
              7     4
    begin-> 8         3
    end-1 --> 0  1  2
   */
   Triangle t(strip, {{8, 6}, {5, 3}, {2, 0}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 0);

   EXPECT_THAT(strip, testing::ElementsAreArray({8, 7, 6, 5, 4, 3, 2, 1, 0}));
}

TEST(TriangleOrientation, stripStartingInSecondCornerRunningCounterClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], CRGB::White);
   
   /*
                0 8
              1     7
    begin-> 2         6
    end-1 --> 3  4  5
   */
   Triangle t(strip, {{2, 0}, {8, 6}, {5, 3}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 0);

   EXPECT_THAT(strip, testing::ElementsAreArray({2, 1, 0, 8, 7, 6, 5, 4, 3}));
}

TEST(TriangleOrientation, stripStartingInThirdCornerRunningCounterClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], CRGB::White);
   
   /*
                3 2
              4     1
    begin-> 5         0
    end-1 --> 6  7  8
   */
   Triangle t(strip, {{5, 3}, {2, 0}, {8, 6}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 0);

   EXPECT_THAT(strip, testing::ElementsAreArray({5, 4, 3, 2, 1, 0, 8, 7, 6}));
}

