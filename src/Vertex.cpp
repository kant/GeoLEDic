#include "Vertex.hpp"
#include "Vector.hpp"
#include "flogl/flogl.hpp"

Vertex::Vertex(): x(0), y(0), z(0)
{}

Vertex::Vertex(float x, float y, float z): x(x), y(y), z(z)
{}

Vertex::Vertex(const Vector& v): x(v.x), y(v.y), z(v.z)
{}
  
Vertex Vertex::operator+(const Vector& v) const
{
  return Vertex(x + v.x, y + v.y, z + v.z);
}

Vertex Vertex::operator-(const Vector& v) const
{
  return Vertex(x - v.x, y - v.y, z - v.z);
}

Vector Vertex::operator-(const Vertex& v) const
{
  return Vector(x - v.x, y - v.y, z - v.z);
}

Vertex::operator flogl::LED() const
{
   const auto LED_SIZE = 0.3f;
   return {x, y, z, LED_SIZE};
}

std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
  return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
