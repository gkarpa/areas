#pragma once
#include <array>
#include <cstddef>
#include "node.h"
#include "surface.h"

// A triangle class that inherits from surface. These are created from records of the ebc file.

class triangle_t : public surface_t{
    private:
        std::array<node_t, 3> nodes_;

    public:
        triangle_t(size_t id, const node_t& n0, const node_t& n1, const node_t& n2) :
            surface_t{id},
            nodes_{n0, n1, n2}
        {}

        double area() const override;
        virtual ~triangle_t() {}
};