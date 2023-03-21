/**
 * @file    vector.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-17
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp; 
using namespace physics; 
using namespace physics::units;
using namespace math; 
using namespace geometry;


int main() {


    std::cout << "Default position: " << position3() << '\n'; 

    auto v1 = position3(1.1m, 2.1m, 3.1m);
    std::cout << v1 << '\n'; 

    vector v2 = position3(1.1m, 2.1m, 3.1m);
    std::cout << v2 << '\n';

    auto v3 = make_vector(1.1m, 2.1m, 3.1m);
    std::cout << v3 << '\n';

    vector v4 = make_vector(1.1m, 2.1m, 3.1m);
    std::cout << v4 << '\n';

    auto v5 = make_vector<length_m>(1.1m, 2.1m, 3.1m);
    std::cout << v5 << '\n';

    std::cout << "sizeof a 2D vector: " << sizeof(position2) << '\n';
    std::cout << "sizeof a 3D vector: " << sizeof(position3) << '\n'; 


    return 0;   


}