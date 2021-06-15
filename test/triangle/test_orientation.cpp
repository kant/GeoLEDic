#include <gmock/gmock.h>
#include "Triangle.hpp"
#include <numeric>
#include "common-test-helpers.hpp"

TEST(TriangleOrientation, stripStartingInFirstCornerRunningClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], UNSET);
   
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
   std::fill(strip, &strip[9], UNSET);
   
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
   std::fill(strip, &strip[9], UNSET);
   
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
   std::fill(strip, &strip[9], UNSET);
   
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
   std::fill(strip, &strip[9], UNSET);
   
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
   std::fill(strip, &strip[9], UNSET);
   
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

TEST(TriangleOrientation, stripStartingOnSecondLedOfFirstEdgeRunningClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], UNSET);
   
   /*
                1 2
              0     3
    begin-> 8         4
    end-1 --> 7  6  5
   */
   Triangle t(strip, {{8, 8, 0, 1}, {2, 4}, {5, 7}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 0);

   EXPECT_THAT(strip, testing::ElementsAreArray({1, 2, 3, 4, 5, 6, 7, 8, 0}));
}

TEST(TriangleOrientation, stripStartingOnLastLedOfFirstEdgeRunningClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], UNSET);
   
   /*
                0 1
              8     2
    begin-> 7         3
    end-1 --> 6  5  4
   */
   Triangle t(strip, {{7, 8, 0, 0}, {2, 4}, {5, 7}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 0);

   EXPECT_THAT(strip, testing::ElementsAreArray({2, 3, 4, 5, 6, 7, 8, 0, 1}));
}

TEST(TriangleOrientation, stripStartingOnLastLedOfLastEdgeRunningClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], UNSET);
   
   /*
                3 4
              2     5
    begin-> 1         6
    end-1 --> 0  8  7
   */
   Triangle t(strip, {{1, 3}, {4, 6}, {7, 8, 0, 0}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 0);

   EXPECT_THAT(strip, testing::ElementsAreArray({8, 0, 1, 2, 3, 4, 5, 6, 7}));
}

TEST(TriangleOrientation, stripStartingOnSecondLedOfSecondEdgeRunningCounterClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], UNSET);
   
   /*
                2 1
              3     0
    begin-> 4         8
    end-1 --> 5  6  7
   */
   Triangle t(strip, {{4, 2}, {1, 0, 8, 8}, {7, 5}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 0);

   EXPECT_THAT(strip, testing::ElementsAreArray({4, 3, 2, 1, 0, 8, 7, 6, 5}));
}

TEST(TriangleOrientation, stripStartingOnFirstLedOfThirdEdgeRunningCounterClockwise)
{
   CRGB strip[9];
   std::fill(strip, &strip[9], UNSET);
   
   /*
                4 3
              5     2
    begin-> 6         1
    end-1 --> 7  8  0
   */
   Triangle t(strip, {{6, 4}, {3, 1}, {0, 0, 8, 7}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 0);

   EXPECT_THAT(strip, testing::ElementsAreArray({6, 5, 4, 3, 2, 1, 0, 8, 7}));
}

TEST(TriangleOrientation, stripStartingAt2OnFirstLedOfThirdEdgeRunningCounterClockwise)
{
   CRGB strip[11];
   std::fill(strip, &strip[11], UNSET);
   
   /*
                6 5
              7     4
    begin-> 8         3
    end-1 --> 9  10 2
   */
   Triangle t(strip, {{8, 6}, {5, 3}, {2, 2, 10, 9}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 0);

   EXPECT_THAT(strip, testing::ElementsAreArray({int(UNSET), int(UNSET), 6, 5, 4, 3, 2, 1, 0, 8, 7}));
}

TEST(TriangleOrientation, stripStartingOnSecondEdgeRunningCounterClockwiseLargerExample)
{
   CRGB strip[16];
   std::fill(strip, &strip[16], UNSET);
   
   /*
                    3  2
                  4      1
                5          0
              6              15
    begin-> 7                  14
    end-1 --> 8  9  10 11 12 13
   */
   Triangle t(strip, {{7, 3}, {2, 0, 15, 14}, {13, 8}}, ARBITRARY_COORDINATES);
   
   std::iota(t.begin(), t.end(), 0);

   EXPECT_THAT(strip, testing::ElementsAreArray({7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8}));
}

TEST(TriangleOrientation, size)
{
   CRGB strip[9];
   Triangle t(strip, {{0, 2}, {3, 5}, {6, 8}}, ARBITRARY_COORDINATES);

   EXPECT_EQ(9, t.size());
}

TEST(TriangleOrientation, sizeWithSplitEdge)
{
   CRGB strip[9];
   Triangle t(strip, {{6, 4}, {3, 1}, {0, 0, 8, 7}}, ARBITRARY_COORDINATES);

   EXPECT_EQ(9, t.size());
}
