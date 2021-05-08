#ifndef GEOLEDIC_VERTEX_HPP
#define GEOLEDIC_VERTEX_HPP

#include <iostream>

struct Vertex {
  Vertex(): x(0), y(0), z(0)
  {}

  // TODO: order xzy, as that's what I got out of SketchUp
  Vertex(float x, float z, float y): x(x), y(y), z(z)
  {}

  float x, y, z;

  Vertex operator+(const Vertex& v) const
  {
    return Vertex(x + v.x, z + v.z, y + v.y);
  }
  
  Vertex operator-(const Vertex& v) const
  {
    return Vertex(x - v.x, z - v.z, y - v.y);
  }
  
  Vertex operator*(float v) const
  {
    return Vertex(x*v, z*v, y*v);
  }
  
  Vertex operator/(float v) const
  {
    return Vertex(x/v, z/v, y/v);
  }
  
};

std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
  return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

#endif
