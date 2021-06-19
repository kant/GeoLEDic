#ifndef assert_hpp
#define assert_hpp

#include <iostream>

#define ASSERT_CMP(a, op, b, msg) \
   if (not (a op b)){ \
      std::cerr << "Assertion failed: "#a"(" << a << ")" #op #b "("<< b << "); " << msg << " in " __FILE__ << ", line " << __LINE__; \
      throw "Assertion failed"; \
   }

#endif /* assert_hpp */
