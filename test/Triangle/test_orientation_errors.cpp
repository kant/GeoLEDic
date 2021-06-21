#include <gmock/gmock.h>
#include "Triangle.hpp"
#include "common-test-helpers.hpp"

TEST(TriangleOrientationErrors, allEdgesMustGoInSameDirectionButSecondDoesnt)
{
   CRGB strip[9];
 
   EXPECT_ANY_THROW(Triangle(strip, {{0, 2}, {5, 3}, {6, 8}}, ARBITRARY_COORDINATES));
}

TEST(TriangleOrientationErrors, allEdgesMustGoInSameDirectionButThirdDoesnt)
{
   CRGB strip[9];
 
   EXPECT_ANY_THROW(Triangle(strip, {{0, 2}, {3, 5}, {8, 6}}, ARBITRARY_COORDINATES));
}

TEST(TriangleOrientationErrors, noDiscontinuitiesButFirstCornerHasOneClockwise)
{
   CRGB strip[9];
 
   EXPECT_ANY_THROW(Triangle(strip, {{7, 8}, {0, 2}, {3, 5}}, ARBITRARY_COORDINATES));
}

TEST(TriangleOrientationErrors, noDiscontinuitiesButSecondCornerHasOneClockwise)
{
   CRGB strip[9];
 
   EXPECT_ANY_THROW(Triangle(strip, {{0, 2}, {1, 5}, {6, 8}}, ARBITRARY_COORDINATES));
}

TEST(TriangleOrientationErrors, noDiscontinuitiesButThirdCornerHasOneClockwise)
{
   CRGB strip[9];
 
   EXPECT_ANY_THROW(Triangle(strip, {{0, 2}, {3, 5}, {7, 8}}, ARBITRARY_COORDINATES));
}

TEST(TriangleOrientationErrors, noDiscontinuitiesButFirstCornerHasOneCounterClockwise)
{
   CRGB strip[9];
 
   EXPECT_ANY_THROW(Triangle(strip, {{4, 0}, {8, 6}, {5, 3}}, ARBITRARY_COORDINATES));
}

TEST(TriangleOrientationErrors, noDiscontinuitiesButSecondCornerHasOneCounterClockwise)
{
   CRGB strip[9];
 
   EXPECT_ANY_THROW(Triangle(strip, {{8, 6}, {4, 3}, {2, 0}}, ARBITRARY_COORDINATES));
}

TEST(TriangleOrientationErrors, noDiscontinuitiesButThirdCornerHasOneCounterClockwise)
{
   CRGB strip[9];
 
   EXPECT_ANY_THROW(Triangle(strip, {{8, 6}, {5, 3}, {3, 0}}, ARBITRARY_COORDINATES));
}

TEST(TriangleOrientationErrors, noDiscontinuitiesButSecondCornerHasOneClockwiseWithSplitEdge)
{
   CRGB strip[9];
 
   EXPECT_ANY_THROW(Triangle(strip, {{7, 8}, {10, 12, 0, 2}, {3, 5}}, ARBITRARY_COORDINATES));
}

TEST(TriangleOrientationErrors, noDiscontinuitiesButThirdCornerHasOneCounterClockwiseWithSplitEdge)
{
   CRGB strip[9];
 
   EXPECT_ANY_THROW(Triangle(strip, {{8, 6}, {5, 3}, {3, 0, 11, 9}}, ARBITRARY_COORDINATES));
}
