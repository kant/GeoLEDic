#include "Vector.hpp"
#include "Vertex.hpp"
#include <math.h>

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

float Vector::length() const
{
   return sqrt(dot(*this, *this));
}

Vector cross(const Vector& a, const Vector& b)
{
   return Vector(a.y*b.z - a.z*b.y,
                 a.z*b.x - a.x*b.z,
                 a.x*b.y - a.y*b.x);
}

float dot(const Vector& a, const Vector& b)
{
   return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector normalise(const Vector& v)
{
   return v/v.length();
}

float angleRad(const Vector& a, const Vector& b)
{
   return acos(dot(a, b)/(a.length() * b.length()));
}
