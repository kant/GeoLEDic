#ifndef common_test_helpers_hpp
#define common_test_helpers_hpp

#include "Triangle.hpp"
#include <iostream>

void PrintTo(const CRGB& c, ::std::ostream* os);
extern const Vertex ARBITRARY_COORDINATES[3];
extern const CRGB::HTMLColorCode UNSET;


#endif /* common_test_helpers_hpp */
