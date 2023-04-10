#include "sci++.hpp"


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
                        auto x = 3.566m;
                        auto y = -2.345m;
                        return bench<1000000>([&x, &y]() 
                            {
                                [[maybe_unused]] auto z = x * y;
                            }
                        );
                    });

    print(times);

    plt::title("Testing the product of two measurements over 1000000 iterations");
    plt::named_plot("measure", measures, static_cast<std::vector<double>>(times.values()));
    plt::named_plot("uncertainty", measures, static_cast<std::vector<double>>(times.uncertainties()));
    plt::tight_layout();
    plt::legend();
    plt::show();


    return 0; 

}