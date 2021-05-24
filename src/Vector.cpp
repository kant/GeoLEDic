#include "Vector.hpp"
#include "Vertex.hpp"


Vector::Vector(): x(0), y(0), z(0)
{}

Vector::Vector(float x, float y, float z): x(x), y(y), z(z)
{}

Vector::Vector(const Vertex& v): x(v.x), y(v.y), z(v.z)
{}

Vector Vector::operator+(const Vector& v) const
{
  return Vector(x + v.x, y + v.y, z + v.z);
}
  
Vector Vector::operator-(const Vector& v) const
{
  return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator*(float v) const
{
  return Vector(x*v, y*v, z*v);
}
  
Vector Vector::operator/(float v) const
{
  return Vector(x/v, y/v, z/v);
}

