#include "common-test-helpers.hpp"

void PrintTo(const CRGB& c, ::std::ostream* os)
{
   *os << "RGB(" << +c.r << "," << +c.g << "," << +c.b << ")";
}

const Vertex ARBITRARY_COORDINATES[3] = {{0, 0, 0}, {0, 1, 0}, {1, 0, 0}};
const CRGB::HTMLColorCode UNSET(CRGB::White);
