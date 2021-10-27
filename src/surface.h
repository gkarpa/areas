#pragma once
#include <cstddef>

// Abstract class to denote a generic surface with an id. Derived classes are expected to implement the area() method.

class surface_t{
    protected:
        size_t id_;
        surface_t(size_t id) :
            id_{id}
        {}

    public:
        size_t id() const { return id_; }
        void id(size_t id) { id_ = id; }
        virtual double area() const = 0;
        virtual ~surface_t() {}
};