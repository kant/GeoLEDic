#include <gmock/gmock.h>
#include "Vertex.hpp"


// Assume we're standing at 0,0,0, looking into the dome

TEST(Angles, theta0AtGroundLevel)
{
   Vertex v1(0, 0, 1);
   Vertex v2(100, 0, -1000);

   EXPECT_EQ(0, v1.theta);
   EXPECT_EQ(0, v2.theta);
}

TEST(Angles, theta255AtTop)
{
   Vertex v1(0, 1, 0);
   Vertex v2(0, 1000, 0);

   EXPECT_EQ(255, v1.theta);
   EXPECT_EQ(255, v2.theta);
}

TEST(Angles, theta128At45DegUp)
{
   Vertex v1(0, 1, -1);
   Vertex v2(10, 10, 0);

   EXPECT_EQ(128, v2.theta);
   EXPECT_EQ(128, v2.theta);
}

TEST(Angles, phi0BehindUs)
{
   Vertex v1(0, 0, 1);
   Vertex v2(0, 100, 100);

   EXPECT_EQ(0, v1.phi);
   EXPECT_EQ(0, v2.phi);
}

TEST(Angles, phi512AheadOfUs)
{
   Vertex v1(0, 0, -1000);
   Vertex v2(0, 10, -100);

   EXPECT_EQ(512, v1.phi);
   EXPECT_EQ(512, v2.phi);
}

TEST(Angles, phi256LeftOfUs)
{
   Vertex v1(-1, 0, 0);
   Vertex v2(-100, 100, 0);

   EXPECT_EQ(256, v1.phi);
   EXPECT_EQ(256, v2.phi);
}

TEST(Angles, phi768RightOfUs)
{
   Vertex v1(1, 0, 0);
   Vertex v2(100, 100, 0);

   EXPECT_EQ(768, v1.phi);
   EXPECT_EQ(768, v2.phi);
}

TEST(Angles, phi1023BehindUsButEverSoSlightlyToTheRight)
{
   Vertex v1(0.0001, 0, 1);
   Vertex v2(0.001, 100, 100);

   EXPECT_EQ(1023, v1.phi);
   EXPECT_EQ(1023, v2.phi);
}

TEST(Angles, interpolateThetaForward)
{
   Vertex v1(0, 1, 1);
   Vertex v2(0, 1, 0);
   ASSERT_EQ(128, v1.theta);
   ASSERT_EQ(255, v2.theta);
   
   EXPECT_EQ(128, interpolateTheta(v1, v2, 0, 4));
   EXPECT_EQ(159, interpolateTheta(v1, v2, 1, 4));
   EXPECT_EQ(191, interpolateTheta(v1, v2, 2, 4));
   EXPECT_EQ(223, interpolateTheta(v1, v2, 3, 4));
}

TEST(Angles, interpolateThetaBackward)
{
   Vertex v1(0, 1, 1);
   Vertex v2(0, 1, 0);
   ASSERT_EQ(128, v1.theta);
   ASSERT_EQ(255, v2.theta);
   
   EXPECT_EQ(255, interpolateTheta(v2, v1, 0, 4));
   EXPECT_EQ(224, interpolateTheta(v2, v1, 1, 4));
   EXPECT_EQ(192, interpolateTheta(v2, v1, 2, 4));
   EXPECT_EQ(160, interpolateTheta(v2, v1, 3, 4));
}

TEST(Angles, interpolatePhiForward)
{
   Vertex v1(-1, 0, 0);
   Vertex v2(0, 0, -1);
   ASSERT_EQ(256, v1.phi);
   ASSERT_EQ(512, v2.phi);

   EXPECT_EQ(256, interpolatePhi(v1, v2, 0, 4));
   EXPECT_EQ(320, interpolatePhi(v1, v2, 1, 4));
   EXPECT_EQ(384, interpolatePhi(v1, v2, 2, 4));
   EXPECT_EQ(448, interpolatePhi(v1, v2, 3, 4));
}

TEST(Angles, interpolatePhiBackward)
{
   Vertex v1(-1, 0, 0);
   Vertex v2(0, 0, -1);
   ASSERT_EQ(256, v1.phi);
   ASSERT_EQ(512, v2.phi);

   EXPECT_EQ(512, interpolatePhi(v2, v1, 0, 4));
   EXPECT_EQ(448, interpolatePhi(v2, v1, 1, 4));
   EXPECT_EQ(384, interpolatePhi(v2, v1, 2, 4));
   EXPECT_EQ(320, interpolatePhi(v2, v1, 3, 4));
}

TEST(Angles, interpolatePhiAcross0)
{
   Vertex v1(-1, 0, 1);
   Vertex v2(1, 0, 1);
   ASSERT_EQ(127, v1.phi); // irrelevant rounding artifact, 128 would be expected
   ASSERT_EQ(896, v2.phi);
   
   EXPECT_EQ(127, interpolatePhi(v1, v2, 0, 4));
   EXPECT_EQ(64,  interpolatePhi(v1, v2, 1, 4));
   EXPECT_EQ(0,   interpolatePhi(v1, v2, 2, 4));
   EXPECT_EQ(960, interpolatePhi(v1, v2, 3, 4));
}

TEST(Angles, interpolatePhiAcross0TheOtherWay)
{
   Vertex v1(-1, 0, 1);
   Vertex v2(1, 0, 1);
   ASSERT_EQ(127, v1.phi); // irrelevant rounding artifact, 128 would be expected
   ASSERT_EQ(896, v2.phi);
   
   EXPECT_EQ(896,  interpolatePhi(v2, v1, 0, 4));
   EXPECT_EQ(959,  interpolatePhi(v2, v1, 1, 4));
   EXPECT_EQ(1023, interpolatePhi(v2, v1, 2, 4));
   EXPECT_EQ(63,   interpolatePhi(v2, v1, 3, 4));
}
