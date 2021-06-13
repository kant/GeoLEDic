#ifndef CRGB_iterator_hpp
#define CRGB_iterator_hpp

#define FASTLED_INTERNAL // get rid of annoying version pragma
#ifdef WITH_FLOGL
#include "flogl/flogl.hpp"
#endif
#include "FastLED.h"

#include <iterator>

struct CRGB_iterator: public std::iterator<std::forward_iterator_tag, CRGB>
{
   reference operator*() const { return *m_ptr; }
   pointer operator->() { return m_ptr; }

   // Prefix increment
   CRGB_iterator& operator++();

   // Postfix increment
   CRGB_iterator operator++(int);
   
   friend bool operator==(const CRGB_iterator& a, const CRGB_iterator& b);
   friend bool operator!=(const CRGB_iterator& a, const CRGB_iterator& b);
   
   struct invalid_iterator_tag{};
   enum Validity {VALID, INVALID};
   
   CRGB_iterator(pointer start_ptr, pointer strip_begin, pointer strip_end);
   
   // Use to create end() iterator
   CRGB_iterator(pointer ptr, invalid_iterator_tag invalid);

private:
   pointer m_ptr;
   pointer m_end;
   pointer m_strip_begin;
   pointer m_strip_end;
   Validity m_valid;
};

#endif /* CRGB_iterator_hpp */
