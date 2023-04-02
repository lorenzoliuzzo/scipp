#include "sci++.hpp"


using namespace scipp; 
using namespace geometry; 
using namespace physics;
using namespace math; 


int main() {

    vector<length_m, 3> origin(0.0m, 3.0m, -5.0m);
    vector<length_m, 3> v1(1.0m, 0.0m, 3.0m);
    vector<length_m, 3> v2(-2.0m, 1.0m, 2.0m);
    auto v3 = op::cross(v1, v2);

    // std::map<std::string, std::string> keywords;
    // keywords["color"] = "'grey', 'red', 'green'";
    // keywords["scale"] = "15";

    plt::quiver(
        static_cast<std::vector<double>>(origin), 
        static_cast<std::vector<double>>(v1), 
        static_cast<std::vector<double>>(v2),
        static_cast<std::vector<double>>(v3)
    );

    plt::show(); 


    return 0; 

}