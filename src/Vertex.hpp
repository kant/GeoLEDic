#ifndef GEOLEDIC_VERTEX_HPP
#define GEOLEDIC_VERTEX_HPP

#include <iostream>

namespace flogl {
class LED;
}

struct Vector;

struct Vertex {
  Vertex();
  Vertex(float x, float y, float z);
  explicit Vertex(const Vector& v);
  
  float x, y, z;

  Vertex operator+(const Vector& v) const;
  Vertex operator-(const Vector& v) const;
  Vector operator-(const Vertex& v) const;
   
  operator flogl::LED() const;
};

std::ostream& operator<<(std::ostream& os, const Vertex& v);

#endif
