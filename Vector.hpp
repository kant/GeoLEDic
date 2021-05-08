#ifndef GEOLEDIC_VECTOR_HPP
#define GEOLEDIC_VECTOR_HPP

#include <iostream>

struct Vertex;

struct Vector {
  Vector();
  Vector(float x, float y, float z);
  explicit Vector(const Vertex& v);

  Vector operator+(const Vector& v) const;
  Vector operator-(const Vector& v) const;
  Vector operator*(float v) const;
  Vector operator/(float v) const;

  float x, y, z;

};

std::ostream& operator<<(std::ostream& os, const Vector& v);

#endif
