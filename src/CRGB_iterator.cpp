#include "CRGB_iterator.hpp"

// Prefix increment
CRGB_iterator& CRGB_iterator::operator++()
{
   if (m_direction == FORWARD)
   {
      m_ptr++;
   }
   else
   {
      m_ptr--;
   }
   
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

CRGB_iterator::CRGB_iterator(pointer start_ptr, pointer strip_begin, pointer strip_end, Direction direction):
   m_ptr(start_ptr),
   m_end(start_ptr),
   m_strip_begin(direction == FORWARD ? strip_begin : strip_end),
   m_strip_end(direction == FORWARD ? strip_end + 1 : strip_begin - 1),
   m_valid(VALID),
   m_direction(direction)
{}

CRGB_iterator::CRGB_iterator(pointer ptr, invalid_iterator_tag invalid):
   m_ptr(ptr),
   m_end(),
   m_strip_begin(),
   m_strip_end(),
   m_valid(INVALID),
   m_direction(FORWARD)
{}

CRGB_iterator::CRGB_iterator(pointer first_segment_begin,
                             pointer first_segment_end,
                             pointer second_segment_begin,
                             pointer second_segment_end,
                             Direction direction):
   m_ptr(first_segment_begin),
   m_end(direction == FORWARD ? second_segment_end + 1 : second_segment_end - 1),
   m_strip_begin(second_segment_begin),
   m_strip_end(direction == FORWARD ? first_segment_end + 1 : first_segment_end - 1),
   m_valid(VALID),
   m_direction(direction)
{
   
}
