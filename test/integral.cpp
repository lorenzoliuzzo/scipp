/**
 * @file    integral.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-05
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"
#include "cassert"

using namespace scipp; 
using namespace physics; 
using namespace math; 


int main() {


    tools::omp_timer t; 
    t.start(); 
    t.stop(); 

    std::function<measurement<units::metre2>(measurement<units::metre>)> f = [](measurement<units::metre> x) -> measurement<units::metre2> { return x * x; }; 

    // std::cout << f(1. * units::m) << '\n'; 

    measurement<units::metre3> result_mid, result_trap, result_simp;

    
    t.start(); 
    
        result_mid = integral::midpoint(f, 0.0 * units::m, measurement<units::metre>(2.0 * math::constants::pi), 100000000); 

    t.stop();
    std::cout << result_mid << "\nelapsed: " << t.elapsed() << '\n'; 

    t.start(); 
    
        result_trap = integral::trapexoid(f, measurement<units::metre>(0.0), measurement<units::metre>(2.0 * math::constants::pi), 100000000); 

    t.stop();
    std::cout << result_trap << "\nelapsed: " << t.elapsed() << '\n'; 

    t.start(); 
    
        result_simp = integral::simpson(f, measurement<units::metre>(0.0), measurement<units::metre>(2.0 * math::constants::pi), 100000000); 

    t.stop();
    std::cout << result_simp << "\nelapsed: " << t.elapsed() << '\n'; 


    std::cout << result_mid - result_trap << '\n'; 
    std::cout << result_mid - result_simp << '\n'; 
    std::cout << result_simp - result_trap << '\n'; 


    // assert(result_mid == result_trap); 


    // t.start(); 
    
    //     std::cout << integral::midpoint(f, measurement<units::metre>(0.0), measurement<units::metre>(2.0 * math::constants::pi), 1000) << '\n'; 

    // t.stop();
    // std::cout << "elapsed: " << t.elapsed() << '\n'; 

    // t.start(); 
    
    //     std::cout << integral::midpoint(f, measurement<units::metre>(0.0), measurement<units::metre>(2.0 * math::constants::pi), 10000) << '\n'; 

    // t.stop();
    // std::cout << "elapsed: " << t.elapsed() << '\n'; 


    // std::function<scalar_m(angle_m)> g = [](angle_m x) -> scalar_m { return math::op::sin(x); };

    // std::cout << integral::midpoint(g, angle_m(0.0), angle_m(2.0 * math::constants::pi), 10) << '\n'; 
    // std::cout << integral::midpoint(g, angle_m(0.0), angle_m(2.0 * math::constants::pi), 50) << '\n'; 
    // std::cout << integral::midpoint(g, angle_m(0.0), angle_m(2.0 * math::constants::pi), 100) << '\n'; 
    // std::cout << integral::midpoint(g, angle_m(0.0), angle_m(2.0 * math::constants::pi), 500) << '\n'; 
    // std::cout << integral::midpoint(g, angle_m(0.0), angle_m(2.0 * math::constants::pi), 1000) << '\n'; 


    // t.start(); 
    // std::cout << integral::midpoint(g, angle_m(0.0), angle_m(math::constants::pi), 10000) << '\n';
    // t.stop();
    // std::cout << "elapsed: " << t.elapsed() << '\n'; 

    // t.start(); 
    // std::cout << integral::midpoint_fixed(g, angle_m(0.0), angle_m(math::constants::pi), 1.e-6) << '\n'; 
    // t.stop();
    // std::cout << "elapsed: " << t.elapsed() << '\n'; 


    // std::cout << integral::midpoint_fixed(g, angle_m(0.0), angle_m(math::constants::pi), 1.e-6).value - 2.0 << '\n'; 

    // integral integ; 


    // t.start(); 
    // integ.midpoint_fixed(0.0, math::constants::pi, [](double x) -> double { return std::sin(x); }, 1.e-6);
    // t.stop();
    // std::cout << "elapsed: " << t.elapsed() << '\n'; 

    // std::cout << integ.result() << '\n';





    return 0; 

}