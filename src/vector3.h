#pragma once

// A small struct for a 3d vector with operations needed in area calculations.
// It's used to denote the position of a node.

struct vec3_t{
    double x_, y_, z_;

    vec3_t() :
        x_{0.0},
        y_{0.0},
        z_{0.0}
    {}

    vec3_t(double x, double y, double z) :
        x_{x},
        y_{y},
        z_{z}
    {}

    double magnitude() const;
    vec3_t operator-(const vec3_t& other) const;
    vec3_t cross(const vec3_t& other) const;
};