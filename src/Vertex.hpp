#ifndef GEOLEDIC_VERTEX_HPP
#define GEOLEDIC_VERTEX_HPP

#ifdef WITH_FLOGL
#include "flogl/flogl.hpp"
#endif

struct Vector;

struct Vertex {
  Vertex();
  Vertex(float x, float y, float z);
  explicit Vertex(const Vector& v);
  
  float x, y, z;

  Vertex operator+(const Vector& v) const;
  Vertex operator-(const Vector& v) const;
  Vector operator-(const Vertex& v) const;
   
#ifdef WITH_FLOGL
  operator flogl::LED() const;
#endif
};

#endif
