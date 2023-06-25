/**
 * @file    test/math/meta.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-24
 * 
 * @copyright Copyright (c) 2023
 */



#include "sci++.hpp"


using namespace scipp; 
using namespace math; 
using namespace physics; 
using namespace geometry; 


int main() {


    // std::cout << multiply_t<units::metre, units::second>::to_string() << " -> m s" << std::endl;
    // std::cout << multiply_t<units::metre, units::second, units::second>::to_string() << " -> m s^2" << std::endl;
    // std::cout << meta::divide_t<units::second, units::second>::to_string() << " -> " << std::endl;
    // std::cout << meta::pow_t<units::metre, 3>::to_string() << " -> m^3" << std::endl;
    // std::cout << meta::pow_t<units::metre, 2>::to_string() << " -> m^2" << std::endl;
    // std::cout << meta::root_t<units::metre3, 3>::to_string() << " -> m" << std::endl;
    // std::cout << meta::root_t<units::metre2, 2>::to_string() << " -> m" << std::endl;

    // std::cout << meta::pow_t<units::millimetre, 2>::to_string() << " -> m^2" << std::endl;
    // auto x = op::pow<2>(units::mm);
    // std::cout << x.to_string() << " -> m^2" << std::endl;
    // std::cout << op::pow<2>(units::mm).mult << std::endl;
    // std::cout << units::mm.mult << std::endl;
    // std::cout << (units::mm * units::mm).mult << std::endl;
    // std::cout << meta::pow_t<units::millimetre, 2>::mult << std::endl;
    // std::cout << meta::pow_t<units::millimetre, 2>::to_string() << std::endl;
    // std::cout << meta::pow_t<length_m, 2>() << std::endl;


    // std::cout << "size of base_quantity: " << sizeof(units::metre) << std::endl;
    // std::cout << "size of unit: " << sizeof(units::millimetre) << std::endl;
    // std::cout << "size of measurement: " << sizeof(length_m) << std::endl;


    // vector<length_m, 3> v1(1.0m, 2.0m, 3.0e-15m);
    // vector<length_m, 3> v2(1.0m, 2.0m, 3.0e-6m);

    // std::cout << op::dot(v1, v2) << std::endl;


    // std::cout << physics::constants::c << '\n'; 


    // auto op = meta::abs_impl<length_m>();
    // std::cout << op(1.0m) << std::endl;
    // std::cout << op(-1.0m) << std::endl;
    // std::cout << op::abs(-1.0m) << std::endl;      
    // std::cout << op::inv(-2.0m) << std::endl;

    // // umeasurement y(1.0m, 0.0m);
    // // std::cout << y << std::endl;
    // // std::cout << op::abs(y) << std::endl;
    // // std::cout << op::inv(y) << std::endl;

    // std::cout << op::abs(-v1) << '\n'; 
    // std::cout << op::inv(v1) << '\n'; 

    // std::cout << op::sin(0.05) << '\n'; 
    // std::cout << op::sin(scalar_m(0.05)) << '\n';
    // std::cout << op::sin(complex(scalar_m(0.05), scalar_m(0.05))) << '\n';
    
    // std::cout << op::cos(0.05) << '\n'; 
    // std::cout << op::cos(scalar_m(0.05)) << '\n'; 

    std::cout << op::pow<2>(2.5) << '\n';
    std::cout << op::pow<2>(0.05m) << '\n';
    std::cout << op::square(0.05m) << '\n';

    std::cout << op::sin(0.004) << '\n'; 

    std::cout << op::pow<2>(math::constants::i) << '\n'; 
    std::cout << op::cb(math::constants::i) << '\n'; 
    std::cout << op::pow(math::constants::i, scalar_m(4.0) * math::constants::i) << '\n'; 

    return 0; 

}