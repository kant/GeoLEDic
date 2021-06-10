#include <gtest/gtest.h>
#include "Edge.hpp"

TEST(Edge, construct)
{
    Edge e(0,10);

    EXPECT_EQ(0, e.first_led);
    EXPECT_EQ(10, e.last_led);
}
