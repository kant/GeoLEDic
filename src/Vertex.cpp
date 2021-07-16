#include "Vertex.hpp"
#include "Vector.hpp"
#include <math.h>

Vertex::Vertex(): x(0), y(0), z(0), theta(0)
{}

Vertex::Vertex(float x, float y, float z): x(x), y(y), z(z), theta(0), phi(0)
{
   updateAngles();
}

Vertex::Vertex(const Vector& v): x(v.x), y(v.y), z(v.z), theta(0), phi(0)
{
   updateAngles();
}
  
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

void Vertex::updateAngles()
{
   float r = sqrt(x*x + y*y + z*z);
   float theta_f = asin(y/r);
   unsigned theta_u = theta_f/(M_PI_2/NUM_THETA_STEPS);
   theta = theta_u < THETA_MAX ? theta_u : THETA_MAX;
   
   r = sqrt(x*x + z*z);
   float phi_f = acos(z/r);
   if (x > 0)
   {
      phi_f = 2*M_PI - phi_f;
   }
   phi = isnan(phi_f) ? 0 : phi_f/(2*M_PI/NUM_PHI_STEPS);
   if (phi > PHI_MAX) phi = PHI_MAX;
}

uint8_t interpolateTheta(const Vertex& from, const Vertex& to, int step, int num_steps)
{
   return from.theta + (step*(int(to.theta)-int(from.theta))) / num_steps;
}

uint16_t interpolatePhi(const Vertex& from, const Vertex& to, int step, int num_steps)
{
   int d_phi = int(to.phi) - int(from.phi);
   if (d_phi < -Vertex::NUM_PHI_STEPS/2) d_phi += Vertex::NUM_PHI_STEPS;
   else if (d_phi > Vertex::NUM_PHI_STEPS/2) d_phi -=  Vertex::NUM_PHI_STEPS;

   int phi = int(from.phi) + (step*d_phi) / num_steps;

   if (phi < 0) phi += Vertex::NUM_PHI_STEPS;
   else if (phi >= Vertex::NUM_PHI_STEPS) phi -= Vertex::NUM_PHI_STEPS;
   return phi;
}


#ifdef WITH_FLOGL
Vertex::operator flogl::LED() const
{
   const auto SCALE = 10.0f; // convert from meters to the OpenGL coordinate system
   return {x * SCALE, y * SCALE, z * SCALE};
}
#endif


