/**
 * @file    vector.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-05
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp; 
using namespace physics; 
using namespace math; 
using namespace geometry;


int main() {


    vector<physics::length_m, 3> v1(1.0 * units::m, 2.0 * units::m, 3.0 * units::m);
    position3 v2(1.0 * units::m, 2.0 * units::m, 3.0 * units::m);

    v1.print(); 

    v1 += v2; 

    v1.print();
    v1.print(units::Km);


    return 0; 

}