#ifndef assert_hpp
#define assert_hpp

void do_assert(const char* msg, const char* file, int line);

#define ASSERT_CMP(a, op, b, msg) \
   if (not (a op b)){ \
      do_assert(#a #op #b, __FILE__, __LINE__); \
   }

#endif /* assert_hpp */
