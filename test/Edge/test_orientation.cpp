#include <gmock/gmock.h>
#include "Edge.hpp"

TEST(EdgeOrientation, nonSegmentedNonReverse)
{
   EXPECT_FALSE(Edge(0, 3).isReverse());
}

TEST(EdgeOrientation, nonSegmentedReverse)
{
   EXPECT_TRUE(Edge(3, 0).isReverse());
}

TEST(EdgeOrientation, segmentedNonReverse)
{
   EXPECT_FALSE(Edge(7, 9, 0, 3).isReverse());
}

TEST(EdgeOrientation, segmentedReverse)
{
   EXPECT_TRUE(Edge(3, 0, 9, 7).isReverse());
}

TEST(EdgeOrientation, segmentedFirstSegmentSingleLedNonReverse)
{
   EXPECT_FALSE(Edge(7, 7, 1, 3).isReverse());
}

TEST(EdgeOrientation, segmentedSecondSegmentSingleLedNonReverse)
{
   EXPECT_FALSE(Edge(7, 8, 3, 3).isReverse());
}

TEST(EdgeOrientation, segmentedFirstSegmentSingleLedReverse)
{
   EXPECT_TRUE(Edge(3, 3, 9, 7).isReverse());
}

TEST(EdgeOrientation, segmentedSecondSegmentSingleLedReverse)
{
   EXPECT_TRUE(Edge(3, 3, 9, 7).isReverse());
}

TEST(EdgeOrientation, cantHaveSingleLed)
{
   EXPECT_ANY_THROW(Edge(3, 3));
}

TEST(EdgeOrientation, cantHaveSingleLedOnBothSegments)
{
   EXPECT_ANY_THROW(Edge(3, 3, 5, 5));
}

TEST(EdgeOrientation, cantHaveSegmentsWithDifferentOrientationFirstSegmentForward)
{
   EXPECT_ANY_THROW(Edge(3, 4, 2, 1));
}

TEST(EdgeOrientation, cantHaveSegmentsWithDifferentOrientationFirstSegmentRevers)
{
   EXPECT_ANY_THROW(Edge(4, 3, 1, 2));
}
