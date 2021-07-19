#include <gmock/gmock.h>
#include "Vector.hpp"

TEST(Vector, crossTrivial)
{
   Vector a(1, 0, 0);
   Vector b(0, 1, 0);
   
   Vector c = cross(a, b);
   
   EXPECT_FLOAT_EQ(0, c.x);
   EXPECT_FLOAT_EQ(0, c.y);
   EXPECT_FLOAT_EQ(1, c.z);
}

TEST(Vector, cross)
{
   Vector a(2, 3, 4);
   Vector b(5, 6, 7);
   
   Vector c = cross(a, b);
   
   EXPECT_FLOAT_EQ(-3, c.x);
   EXPECT_FLOAT_EQ( 6, c.y);
   EXPECT_FLOAT_EQ(-3, c.z);
}

TEST(Vector, dot)
{
   Vector a(2, 3, 4);
   Vector b(1, 2, 3);
   
   EXPECT_EQ(2*1 + 3*2 + 4*3, dot(a,b));
}

TEST(Vector, length)
{
   Vector a(1, 0, 0);
   Vector b(1, 2, 3);
   
   EXPECT_FLOAT_EQ(1, a.length());
   EXPECT_FLOAT_EQ(sqrt(1.f+4.f+9.f), b.length());
}

TEST(Vector, normalise)
{
   Vector a(1, 2, 3);
   
   Vector b = normalise(a);
   
   float length = sqrt(1.f*1.f + 2.f*2.f + 3.f*3.f);
   EXPECT_FLOAT_EQ(1.0/length, b.x);
   EXPECT_FLOAT_EQ(2.0/length, b.y);
   EXPECT_FLOAT_EQ(3.0/length, b.z);
}

TEST(Vector, angle)
{
   Vector a(2, 0, 0);
   Vector b(0, 2, 2);
   Vector c(0, 2, 0);
   
   EXPECT_FLOAT_EQ(M_PI/2, angleRad(a,b));
   EXPECT_FLOAT_EQ(M_PI/4, angleRad(b,c));
}
