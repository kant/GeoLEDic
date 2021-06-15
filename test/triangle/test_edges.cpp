#include <gmock/gmock.h>
#include "Triangle.hpp"

#include <numeric>
#include "common-test-helpers.hpp"

class TriangleEdgesContiguous: public testing::Test
{
public:
   TriangleEdgesContiguous():
   /*
                2 3
              1     4
    begin-> 0         5
    end-1 --> 8  7  6
   */
   t(strip, {{0, 2}, {3, 5}, {6, 8}}, ARBITRARY_COORDINATES)
   {
      std::fill(strip, &strip[9], UNSET);
   }
   
   CRGB strip[9];
   Triangle t;
};

TEST_F(TriangleEdgesContiguous, accessFirstEdge)
{
   std::iota(t.edge(0).begin(), t.edge(0).end(), 0);
   
   EXPECT_THAT(strip, testing::ElementsAreArray({0, 1, 2, int(UNSET), int(UNSET), int(UNSET), int(UNSET), int(UNSET), int(UNSET)}));
   EXPECT_EQ(3, t.edge(0).size());
}

TEST_F(TriangleEdgesContiguous, accessSecondEdge)
{
   std::iota(t.edge(1).begin(), t.edge(1).end(), 0);
   
   EXPECT_THAT(strip, testing::ElementsAreArray({int(UNSET), int(UNSET), int(UNSET), 0, 1, 2, int(UNSET), int(UNSET), int(UNSET)}));
   EXPECT_EQ(3, t.edge(1).size());
}

TEST_F(TriangleEdgesContiguous, accessThirdEdge)
{
   std::iota(t.edge(2).begin(), t.edge(2).end(), 0);
   
   EXPECT_THAT(strip, testing::ElementsAreArray({int(UNSET), int(UNSET), int(UNSET), int(UNSET), int(UNSET), int(UNSET), 0, 1, 2}));
   EXPECT_EQ(3, t.edge(2).size());
}

class TriangleEdgesContiguousCounterClockWise: public testing::Test
{
public:
   TriangleEdgesContiguousCounterClockWise():
   /*
                6 5
              7     4
    begin-> 8         3
    end-1 --> 0  1  2
   */
   t(strip, {{8, 6}, {5, 3}, {2, 0}}, ARBITRARY_COORDINATES)
   {
      std::fill(strip, &strip[9], UNSET);
   }
   
   CRGB strip[9];
   Triangle t;
};

TEST_F(TriangleEdgesContiguousCounterClockWise, accessFirstEdge)
{
   std::iota(t.edge(0).begin(), t.edge(0).end(), 0);
   
   EXPECT_THAT(strip, testing::ElementsAreArray({int(UNSET), int(UNSET), int(UNSET), int(UNSET), int(UNSET), int(UNSET), 2, 1, 0}));
   EXPECT_EQ(3, t.edge(0).size());
}

TEST_F(TriangleEdgesContiguousCounterClockWise, accessSecondEdge)
{
   std::iota(t.edge(1).begin(), t.edge(1).end(), 0);
   
   EXPECT_THAT(strip, testing::ElementsAreArray({int(UNSET), int(UNSET), int(UNSET), 2, 1, 0, int(UNSET), int(UNSET), int(UNSET)}));
   EXPECT_EQ(3, t.edge(1).size());
}

TEST_F(TriangleEdgesContiguousCounterClockWise, accessThirdEdge)
{
   std::iota(t.edge(2).begin(), t.edge(2).end(), 0);
   
   EXPECT_THAT(strip, testing::ElementsAreArray({2, 1, 0, int(UNSET), int(UNSET), int(UNSET), int(UNSET), int(UNSET), int(UNSET)}));
   EXPECT_EQ(3, t.edge(2).size());
}

