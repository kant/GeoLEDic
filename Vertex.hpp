#ifndef GEOLEDIC_VERTEX_HPP
#define GEOLEDIC_VERTEX_HPP

#include <iostream>

struct Vertex {
  Vertex(): x(0), y(0), z(0)
  {}

  Vertex(float x, float y, float z): x(x), y(y), z(z)
  {}

  float x, y, z;

  Vertex operator+(const Vertex& v) const
  {
    return Vertex(x + v.x, y + v.y, z + v.z);
  }
  
  Vertex operator-(const Vertex& v) const
  {
    return Vertex(x - v.x, y - v.y, z - v.z);
  }
  
  Vertex operator*(float v) const
  {
    return Vertex(x*v, y*v, z*v);
  }
  
  Vertex operator/(float v) const
  {
    return Vertex(x/v, y/v, z/v);
  }
  
};

std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
  return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

#endif
