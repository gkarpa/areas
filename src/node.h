#pragma once
#include "vector3.h"

// The node that is created from a record of the crd file.

class node_t{
    private:
        int id_;
        vec3_t pos_;

    public:
        node_t(int id) :
            id_{id},
            pos_{0.0, 0.0, 0.0}
        {}

        node_t(int id, double x, double y, double z) :
            id_{id},
            pos_{x, y, z}
        {}

        int id() const { return id_; }
        const vec3_t& pos() const { return pos_; }
};