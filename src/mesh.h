#pragma once
#include <vector>
#include <unordered_map>
#include "node.h"
#include "triangle.h"

// The mesh class. It stores all the nodes and triangles that were defined in the input files and is responsible for calculating areas.

class mesh_t{
    private:
        std::vector<node_t> nodes_;
        std::vector<triangle_t> triangles_;

        // We need to map triangle id to triangle object (pointer to avoid copies) for faster lookups of individual triangles.
        // This is used when individual areas are requested based on triangle ids.
        std::unordered_map<size_t, const triangle_t*> id2triangle;
        void create_map();

    public:
        mesh_t(const std::vector<node_t>& nodes, const std::vector<triangle_t>& triangles);
        mesh_t(std::vector<node_t>&& nodes, std::vector<triangle_t>&& triangles);

        // A helper method for a test case scenario where individual areas of all the triangles are requested (see main.cpp).
        const std::vector<triangle_t>& get_triangles() const { return triangles_; }
        size_t get_num_triangles() const { return triangles_.size(); };

        // Methods to calculate the mesh's total area and the areas of individual triangles.
        double calc_total_area() const;
        std::vector<double> calc_individual_areas(const std::vector<size_t>& triangle_ids) const;
};