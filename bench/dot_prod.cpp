#include "sci++.hpp"
#include <thread>


using namespace scipp; 
using namespace math; 
using namespace physics; 
using namespace geometry;
using namespace tools; 


int main() {


    std::vector<int> measures = {1, 2, 3, 4, 5};
    vector<time_um, 5> times;

    std::transform(std::execution::par,
                   times.data.begin(), times.data.end(), 
                   times.data.begin(),
                   [&](const auto&) {
                        auto v1 = make_random_vector<length_m, 3>();
                        auto v2 = make_random_vector<length_m, 3>();
                        return bench<500000>([&v1, &v2]() 
                            {
                                [[maybe_unused]] auto x = op::dot(v1, v2);
                            }
                        );
                    });

    print(times);

    plt::title("Testing the math::op::dot function over 10000000 iterations");
    plt::named_plot("measure", measures, static_cast<std::vector<double>>(times.values()));
    plt::named_plot("uncertainty", measures, static_cast<std::vector<double>>(times.uncertainties()));
    plt::tight_layout();
    plt::legend();
    plt::show();


    return 0; 

}