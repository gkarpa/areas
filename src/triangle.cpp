#include "triangle.h"
#include "vector3.h"

// Compute the area as the half of the magnitude of the cross product of two sides.
double triangle_t::area() const{
    const vec3_t p = nodes_[0].pos();
    const vec3_t a = nodes_[1].pos() - p;
    const vec3_t b = nodes_[2].pos() - p;

    return a.cross(b).magnitude() / 2.0;
}