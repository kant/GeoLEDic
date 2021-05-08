#ifndef GEOLEDIC_VERTEX_HPP
#define GEOLEDIC_VERTEX_HPP

#include <iostream>

struct Vector;

struct Vertex {
  Vertex();
  Vertex(float x, float y, float z);
  explicit Vertex(const Vector& v);
  
  float x, y, z;

  Vertex operator+(const Vector& v) const;
  Vertex operator-(const Vector& v) const;
  Vector operator-(const Vertex& v) const;
};

std::ostream& operator<<(std::ostream& os, const Vertex& v);

#endif
