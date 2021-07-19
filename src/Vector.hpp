#ifndef GEOLEDIC_VECTOR_HPP
#define GEOLEDIC_VECTOR_HPP

struct Vertex;

struct Vector {
  Vector();
  Vector(float x, float y, float z);
  explicit Vector(const Vertex& v);

  Vector operator+(const Vector& v) const;
  Vector operator-(const Vector& v) const;
  Vector operator*(float v) const;
  Vector operator/(float v) const;

  float length() const;

  float x, y, z;

};

Vector cross(const Vector& a, const Vector& b);
float dot(const Vector& a, const Vector& b);
Vector normalise(const Vector& v);
float angleRad(const Vector& a, const Vector& b);

#endif
