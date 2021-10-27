#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <fstream>
#include "mesh.h"

// Methods for reading and writing the required files.

namespace parse{
    // We want the parsing of the crd and ebc files to be agnostic in general so we read them into tuples and process them elsewhere.
    using crd_record_t = std::tuple<int, double, double, double>;
    using ebc_record_t = std::tuple<size_t, int, int, int>;

    std::vector<crd_record_t> crd(const std::string& filename);
    std::vector<ebc_record_t> ebc(const std::string& filename);

    // Wrapper method that parses the two files and converts their records (tuples) into our final mesh (nodes & triangles).
    mesh_t input(const std::string& crd_file, const std::string& ebc_file);
}

namespace write{
    using areas_record_t = std::tuple<size_t, double>;

    // Method to write individual triangles and areas to file, in the requested format (surface id, area)
    void areas(const std::vector<areas_record_t>& records, const std::string& filename);
}