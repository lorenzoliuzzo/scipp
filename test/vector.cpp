#include "sci++.hpp"

using namespace scipp; 
using namespace scipp::geometry::linear_algebra;


int main() {


    vector<basis::metre, 3> vec1(1 * m, 2 * cm, 3 * mm);
    vector<basis::metre, 3> vec2(1 * m, 2 * cm, 3 * mm);

    std::cout << vec1 << '\n'; 

    std::cout << vec2 << "\n";

    vector<basis::metre, 3> vec3(42.2 * m, 56 * mm, 354 * cm); 
    std::cout << vec3 << '\n'; 


    // auto matrix_tuple(std::make_tuple<vector<basis::metre, 3>>(vec1, vec3)); 

    
    // std::cout << std::get<0>(matrix_tuple) << '\n'; 
    // std::cout << std::get<1>(matrix_tuple) << '\n'; 


    // matrix2<3, 2, vector<basis::metre, 3>> mat({vec1, vec2}); 

    return 0; 

}