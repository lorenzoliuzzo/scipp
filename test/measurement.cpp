/**
 * @file    measurement.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"
#include <cassert>

using namespace scipp; 
using namespace physics; 


int main() {

    tools::omp_timer time; 

    time.start(); 
    time.stop(); 


    // static_assert(units::is_unit_v<decltype(units::Km)>); 

    // std::cout << units::Km.convert(1.0, units::mm) << '\n';
    // std::cout << units::Km.convert(1.0, units::m) << '\n';

    // measurement x = 3.43 * units::Km; 
    // std::cout << x.convert(units::mm) << '\n';

    // measurement y = 4.33 * units::m; 
    // measurement z = x - y; 

    // x.print(); 
    // y.print(units::mm); 
    // z.print(units::Km); 

    // math::op::abs(z).print(units::Km); 


    time.start(); 
    length_m l1 = 1.0;
    time.stop(); 
    std::cout << "measurement: " << time.elapsed() << '\n';


    time.start(); 
    scalar d1 = 1.0;
    time.stop(); 
    std::cout << "scalar: " << time.elapsed() << '\n';


    std::cout << sizeof(scalar) << '\n'; 
    std::cout << sizeof(decltype(l1)) << '\n'; 


    l1.print(units::mm);
    l1.print(units::Km);


    return 0; 

}