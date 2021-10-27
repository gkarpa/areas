#include <functional>
#include <numeric>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "mesh.h"


mesh_t::mesh_t(const std::vector<node_t>& nodes, const std::vector<triangle_t>& triangles) : nodes_(nodes), triangles_(triangles) {
    create_map();
}

mesh_t::mesh_t(std::vector<node_t>&& nodes, std::vector<triangle_t>&& triangles) : nodes_(std::move(nodes)), triangles_(std::move(triangles)) {
    create_map();
}

// Calculate the total area of the mesh. Each triangle contributes its own area.
double mesh_t::calc_total_area() const {
    const double sum = std::accumulate(triangles_.begin(), triangles_.end(), 0.0, [](double sum, const triangle_t& triangle){
        return sum + triangle.area();
    });

    return sum;
}

// Calculate individual areas and return a collection of them. Use the aforementioned map to find the requested object much faster.
// If an invalid triangle id was passed then an exception is thrown.
std::vector<double> mesh_t::calc_individual_areas(const std::vector<size_t>& triangle_ids) const {
    std::vector<double> areas(triangle_ids.size());

    std::transform(triangle_ids.begin(), triangle_ids.end(), areas.begin(), [&](size_t id){
        if (id2triangle.find(id) == id2triangle.end()){
            throw std::runtime_error("Error: Invalid triangle id '" + std::to_string(id) + "'!");
        }
        return id2triangle.at(id)->area();
    });

    return areas;
}

void mesh_t::create_map(){
    id2triangle.reserve(triangles_.size());
    for (const auto& triangle : triangles_){
        id2triangle.emplace(triangle.id(), &triangle);
    }
}