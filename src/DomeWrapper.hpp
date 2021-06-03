#ifndef DomeWrapper_h
#define DomeWrapper_h

#include "Triangle.hpp"

class DomeWrapper
{
public:
   DomeWrapper(Triangle* dome, unsigned num_triangles):
      m_dome(dome),
      m_num_triangles(num_triangles)
   {
   }
   
   Triangle* begin() const
   {
      return &m_dome[0];
   }
   
   Triangle* end() const
   {
      return &m_dome[m_num_triangles];
   }
   
   unsigned size() const
   {
      return m_num_triangles;
   }
   
   Triangle& operator[](unsigned ix) const
   {
      return m_dome[ix < m_num_triangles ? ix : m_num_triangles - 1];
   }
   
private:
   Triangle* m_dome;
   const unsigned m_num_triangles;
};

#endif /* DomeWrapper_h */
