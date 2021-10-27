#include "vector3.h"
#include <cmath>


double vec3_t::magnitude() const{
    return sqrt(x_*x_ + y_*y_ + z_*z_);
}

vec3_t vec3_t::operator-(const vec3_t& other) const{
    return vec3_t(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

vec3_t vec3_t::cross(const vec3_t& other) const{
    vec3_t c;

    c.x_ = y_*other.z_ - z_*other.y_;
    c.y_ = z_*other.x_ - x_*other.z_;
    c.z_ = x_*other.y_ - y_*other.x_;

    return c;
}