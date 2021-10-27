#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "parse.h"
#include "math.hpp"
#include "mesh.h"


// Helper method to print the calculated results (areas, mean, standard deviation) in the standard output.
void print_results(
    size_t total_triangles, size_t selected_triangles, double total_area, double selected_area, double selected_mean, double selected_std_dev
){
    std::cout << std::scientific << std::setprecision(8)
        << "\n** Total triangles in mesh: " << total_triangles << ". Selected triangles: " << selected_triangles << " **\n" << std::left
        << std::setw(35) << "Total Area (mesh)              : " << total_area << '\n'
        << std::setw(35) << "Total Area (selected)          : " << selected_area << '\n'
        << std::setw(35) << "Mean Area (selected)           : " << selected_mean << '\n'
        << std::setw(35) << "Standard Deviation (selected)  : " << selected_std_dev << std::endl;
}

int main(int argc, char** argv){
    if (argc != 3){
        std::cout << "Error: Invalid input! Proper use: 'areas <file.crd> <file.ebc>'" << std::endl;
        return 1;
    }

    try{
        const auto mesh = parse::input(argv[1], argv[2]);  // Create the mesh from the input files.
        const double mesh_area = mesh.calc_total_area();  // Calculate its total area.

        //- The below code snippet can be used to demonstrate & test two different scenarios of individual areas requested:
        // 1) all the triangles of the ebc file (bool select_all = true, then we get the triangles from the mesh object and extract their ids), or
        // 2) specific triangle ids that we obtain somehow (bool select_all = false, the selected_ids vector fills with values at will).
        //    If invalid id is given, an exception will be thrown during the area calculation).
        const bool select_all = true;
        std::vector<size_t> selected_ids;
        if (select_all){
            const auto& triangles = mesh.get_triangles();
            selected_ids.resize(triangles.size());
            std::transform(triangles.begin(), triangles.end(), selected_ids.begin(), [](const triangle_t& tri){ return tri.id(); });
        } else {
            selected_ids = {40, 41, 42, 43, 44, 45, 10000, 14878, 14879, 14876};
        }
        //- end

        // After the definition of the selected triangle ids, we proceed with the area calculations and print the results.
        const auto areas = mesh.calc_individual_areas(selected_ids); // Returns a vector with an area for each selected triangle id.
        const double selected_area = math::sum(areas);
        const double selected_mean = math::mean(areas);
        const double selected_std_dev = math::standard_deviation(areas);
        print_results(mesh.get_num_triangles(), selected_ids.size(), mesh_area, selected_area, selected_mean, selected_std_dev);

        // Finally we transform our data into suitable records/tuples in order to write them to a file.
        std::vector<write::areas_record_t> area_records;
        for (size_t i = 0; i < selected_ids.size(); ++i){
            area_records.emplace_back(selected_ids.at(i), areas.at(i));
        }
        write::areas(area_records, "test.areas");
        std::cout << "File 'test.areas' created successfully" << std::endl;

        return 0;
    } catch (const std::exception& e){
        std::cout << e.what() << std::endl;
        return 1;
    }
}