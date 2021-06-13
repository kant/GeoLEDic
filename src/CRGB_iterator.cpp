#include "CRGB_iterator.hpp"

// Prefix increment
CRGB_iterator& CRGB_iterator::operator++()
{
   m_ptr++;
   if (m_ptr == m_strip_end)
   {
      m_ptr = m_strip_begin;
   }
   if (m_ptr == m_end)
   {
      m_valid = INVALID;
   }
   return *this;
}

// Postfix increment
CRGB_iterator CRGB_iterator::operator++(int)
{
   CRGB_iterator tmp = *this;
   ++(*this);
   return tmp;
}

bool operator==(const CRGB_iterator& a, const CRGB_iterator& b)
{
   if (a.m_valid != b.m_valid) return false;
   return a.m_ptr == b.m_ptr or a.m_valid == CRGB_iterator::INVALID;
}

bool operator!=(const CRGB_iterator& a, const CRGB_iterator& b)
{
   return not (a == b);
}

CRGB_iterator::CRGB_iterator(pointer start_ptr, pointer strip_begin, pointer strip_end):
   m_ptr(start_ptr),
   m_end(start_ptr),
   m_strip_begin(strip_begin),
   m_strip_end(strip_end),
   m_valid(VALID)
{}

CRGB_iterator::CRGB_iterator(pointer ptr, invalid_iterator_tag invalid):
   m_ptr(ptr),
   m_end(),
   m_strip_begin(),
   m_strip_end(),
   m_valid(INVALID)
{}
