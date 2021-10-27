#include <vector>
#include <numeric>
#include <cmath>

// Simple math operations (sum, mean, standard deviation) to perform on a collection of values (areas, in this case).
// They are templated so they can accept various datatypes (int, float, double etc) however the mean and standard deviation
// are always computed as doubles.

namespace math{
    template<typename T>
    T sum(const std::vector<T>& values){
        return std::accumulate(values.begin(), values.end(), static_cast<T>(0));
    }

    template<typename T>
    double mean(const std::vector<T>& values){
        return static_cast<double>(math::sum(values)) / values.size();
    }

    template<typename T>
    double standard_deviation(const std::vector<T>& values){
        const double mean = math::mean(values);
        const double sum = std::accumulate(values.begin(), values.end(), 0.0, [&](double sum, T value){
            double v = static_cast<double>(value);
            return sum + (v - mean)*(v - mean);
        });

        return std::sqrt(sum / values.size());
    }
}