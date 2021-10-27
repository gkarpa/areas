#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <unordered_map>
#include "parse.h"


namespace parse{
    std::vector<crd_record_t> crd(const std::string& filename){
        std::ifstream crd{ filename };
        if (!crd) throw std::runtime_error("Error: Unable to open file " + filename + " for reading!");

        std::vector<crd_record_t> records;
        int id = 0;
        while (crd >> id){
            double x, y, z;
            crd >> x >> y >> z;
            records.emplace_back(id, x, y, z);
        }
        return records;
    }

    std::vector<ebc_record_t> ebc(const std::string& filename){
        std::ifstream ebc{ filename };
        if (!ebc) throw std::runtime_error("Error: Unable to open file " + filename + " for reading!");

        std::vector<ebc_record_t> records;
        size_t id = 0;
        while (ebc >> id){
            int n0, n1, n2;
            ebc >> n0 >> n1 >> n2;
            records.emplace_back(id, n0, n1, n2);
        }
        return records;
    }

    mesh_t input(const std::string& crd_file, const std::string& ebc_file){
        try {
            const auto crd_records = parse::crd(crd_file);
            const auto ebc_records = parse::ebc(ebc_file);

            std::vector<node_t> nodes;  // All the nodes of our mesh will be stored here
            nodes.reserve(crd_records.size());

            // We need a map to store where in the nodes vector is each node id, so the triangles below get their correct nodes.
            // (Assuming that the id of the nodes aren't necessarily in the range [0..size) )
            std::unordered_map<int, size_t> position_of_node;
            position_of_node.reserve(crd_records.size());

            for (size_t i = 0; i < crd_records.size(); ++i){
                const auto& [node_id, x, y, z] = crd_records.at(i);
                nodes.emplace_back(node_id, x, y, z);
                position_of_node[node_id] = i;
            }

            std::vector<triangle_t> triangles;  // All the triangles of our mesh will be stored here. Based on their node "indices" we look them up in the nodes vector via the map.
            triangles.reserve(ebc_records.size());
            for (const auto& record : ebc_records){
                const auto& [srf_id, n0, n1, n2] = record;
                triangles.emplace_back(srf_id, nodes.at(position_of_node[n0]), nodes.at(position_of_node[n1]), nodes.at(position_of_node[n2]));
            }

            mesh_t mesh{std::move(nodes), std::move(triangles)}; // Data are being moved to our final mesh object
            return mesh;
        } catch (...){
            throw;
        }
    }
}

namespace write{
    void areas(const std::vector<areas_record_t>& records, const std::string& filename){
        std::ofstream outfile{ filename };
        if (!outfile) throw std::runtime_error("Error: Unable to create file " + filename + " for writing!");

        outfile << std::scientific << std::setprecision(std::numeric_limits<double>::digits10);
        for (const auto& record : records){
            outfile << std::get<0>(record) << '\t' << std::get<1>(record) << '\n';
        }
    }
}