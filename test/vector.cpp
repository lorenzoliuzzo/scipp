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


    vector<physics::units::metre, 3> v1(1.0 * units::m, 2.0 * units::m, 3.0 * units::m);
    position3 v2(1.0 * units::m, 2.0 * units::m, 3.0 * units::m);

    std::cout << v2.normalize() << '\n';


    constexpr auto x = 0.23Km;
    auto y = 35.23m;
    
    std::cout << x << '\n';
    std::cout << y << '\n';

    length_m l1 = x + y / 3.;
    std::cout << l1 << '\n'; 

    v1.print(); 

    v1 += v2; 

    v1.print();
    v1.print(units::Km);


    constexpr position3 p1(1.0 * units::m, 2.0 * units::m, 3.0 * units::m);
    constexpr position3 p2(1.0 * units::m, 2.0 * units::m, 3.0 * units::m);

    constexpr auto p3 = p1 + p2;
    p3.print();


    std::cout << p3[2] << '\n'; 
    std::cout << p3[1] << '\n'; 

    return 0; 

}