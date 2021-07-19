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

   EXPECT_NEAR(128, v2.theta, 1);
   EXPECT_NEAR(128, v2.theta, 1);
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

   EXPECT_NEAR(512, v1.phi, 1);
   EXPECT_NEAR(512, v2.phi, 1);
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
   ASSERT_NEAR(128, v1.theta, 1);
   ASSERT_EQ(255, v2.theta);
   
   EXPECT_NEAR(128, interpolateTheta(v1, v2, 0, 5), 1);
   EXPECT_NEAR(160, interpolateTheta(v1, v2, 1, 5), 1);
   EXPECT_NEAR(192, interpolateTheta(v1, v2, 2, 5), 1);
   EXPECT_NEAR(224, interpolateTheta(v1, v2, 3, 5), 1);
   EXPECT_NEAR(255, interpolateTheta(v1, v2, 4, 5), 1);
}

TEST(Angles, interpolateThetaBackward)
{
   Vertex v1(0, 1, 1);
   Vertex v2(0, 1, 0);
   ASSERT_NEAR(128, v1.theta, 1);
   ASSERT_EQ(255, v2.theta);
   
   EXPECT_NEAR(255, interpolateTheta(v2, v1, 0, 5), 1);
   EXPECT_NEAR(224, interpolateTheta(v2, v1, 1, 5), 1);
   EXPECT_NEAR(192, interpolateTheta(v2, v1, 2, 5), 1);
   EXPECT_NEAR(160, interpolateTheta(v2, v1, 3, 5), 1);
   EXPECT_NEAR(128, interpolateTheta(v2, v1, 4, 5), 1);
}

TEST(Angles, interpolateThetaBothWaysIdentical)
{
   Vertex v1(0, 0, 0);
   Vertex v2(0, 1, 6);

   const unsigned NUM = 10;
   for (unsigned k = 0; k < NUM; k++)
   {
      EXPECT_EQ(interpolateTheta(v1, v2, k, NUM),
                interpolateTheta(v2, v1, NUM-k-1, NUM)) << "k=" << k;
   }
   
}


TEST(Angles, interpolatePhiForward)
{
   Vertex v1(-1, 0, 0);
   Vertex v2(0, 0, -1);
   ASSERT_NEAR(256, v1.phi, 1);
   ASSERT_NEAR(512, v2.phi, 1);

   EXPECT_NEAR(256, interpolatePhi(v1, v2, 0, 5), 1);
   EXPECT_NEAR(320, interpolatePhi(v1, v2, 1, 5), 1);
   EXPECT_NEAR(384, interpolatePhi(v1, v2, 2, 5), 1);
   EXPECT_NEAR(448, interpolatePhi(v1, v2, 3, 5), 1);
   EXPECT_NEAR(512, interpolatePhi(v1, v2, 4, 5), 1);
}

TEST(Angles, interpolatePhiBackward)
{
   Vertex v1(-1, 0, 0);
   Vertex v2(0, 0, -1);
   ASSERT_EQ(256, v1.phi);
   ASSERT_NEAR(512, v2.phi, 1);

   EXPECT_NEAR(512, interpolatePhi(v2, v1, 0, 5), 1);
   EXPECT_NEAR(448, interpolatePhi(v2, v1, 1, 5), 1);
   EXPECT_NEAR(384, interpolatePhi(v2, v1, 2, 5), 1);
   EXPECT_NEAR(320, interpolatePhi(v2, v1, 3, 5), 1);
   EXPECT_NEAR(256, interpolatePhi(v2, v1, 4, 5), 1);
}

TEST(Angles, interpolatePhiAcross0)
{
   Vertex v1(-1, 0, 1);
   Vertex v2(1, 0, 1);
   ASSERT_NEAR(128, v1.phi, 1);
   ASSERT_NEAR(896, v2.phi, 1);
   
   EXPECT_NEAR(128, interpolatePhi(v1, v2, 0, 5), 1);
   EXPECT_NEAR(64,  interpolatePhi(v1, v2, 1, 5), 1);
   EXPECT_NEAR(0,   interpolatePhi(v1, v2, 2, 5), 1);
   EXPECT_NEAR(960, interpolatePhi(v1, v2, 3, 5), 1);
   EXPECT_NEAR(896, interpolatePhi(v1, v2, 4, 5), 1);
}

TEST(Angles, interpolatePhiAcross0TheOtherWay)
{
   Vertex v1(-1, 0, 1);
   Vertex v2(1, 0, 1);
   ASSERT_NEAR(128, v1.phi, 1);
   ASSERT_NEAR(896, v2.phi, 1);
   
   EXPECT_NEAR(896,  interpolatePhi(v2, v1, 0, 5), 1);
   EXPECT_NEAR(960,  interpolatePhi(v2, v1, 1, 5), 1);
   EXPECT_NEAR(0,    interpolatePhi(v2, v1, 2, 5), 1);
   EXPECT_NEAR(64,   interpolatePhi(v2, v1, 3, 5), 1);
   EXPECT_NEAR(128,  interpolatePhi(v2, v1, 4, 5), 1);
}


TEST(Angles, interpolatePhiBothWaysIdentical)
{
   Vertex v1(-1, 0, 0);
   Vertex v2( 0, 0, 1);

   const unsigned NUM = 10;
   for (unsigned k = 0; k < NUM; k++)
   {
      EXPECT_EQ(interpolatePhi(v1, v2, k, NUM),
                interpolatePhi(v2, v1, NUM-k-1, NUM)) << "k=" << k;
   }
   
}
