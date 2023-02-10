/**
 * @file    measurement.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-05
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp; 
using namespace physics; 


int main() {


    using hallah = units::base_prod<units::metre, length_m::base>::type;

    tools::omp_timer time; 

    time.start(); 
    time.stop(); 
    std::cout << "empty?: " << time.elapsed() << '\n';

    constexpr length_m l1 = 1.0;
    constexpr length_m l2(1.0, units::mm);
    constexpr length_m l3(1.0, units::Km);

    time.start();
    constexpr length_m l4 = l2 + l3;
    time.stop();
    std::cout << "constexpr?: " << time.elapsed() << '\n';

    l4.print(units::mm);

    time.start();
    auto x = (3.36 * units::mm) * l4;
    time.stop();
    std::cout << "auto?: " << time.elapsed() << '\n';




    return 0; 

}