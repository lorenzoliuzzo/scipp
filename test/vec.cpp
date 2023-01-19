#include "sci++.hpp"

using namespace scipp; 
using namespace scipp::geometry::linear_algebra;


int main() {


    vector<basis::metre, 3> vec1({1 * m, 2 * cm, 3 * mm});
    vector<basis::metre, 3> vec2(1 * m, 2 * cm, 3 * mm);

    std::cout << vec1 << '\n'; 

    std::cout << vec2 << "\n";

    vector<basis::metre, 3> vec3(42.2 * m, 56 * mm, 354 * cm); 
    std::cout << vec3 << '\n'; 


    return 0; 

}