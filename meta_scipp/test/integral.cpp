/**
 * @file    integral.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp; 
using namespace physics; 
using namespace math; 


int main() {


    tools::omp_timer t; 

    std::function<measurement<units::metre2>(measurement<units::metre>)> f = [](measurement<units::metre> x) -> measurement<units::metre2> { return x * x; }; 

    std::cout << f(1. * units::m) << '\n'; 
    
    t.start(); 
    
        std::cout << integral2::midpoint(f, 0.0 * units::m, measurement<units::metre>(2.0 * constants::pi), 10) << '\n'; 

    t.stop();
    std::cout << "elapsed: " << t.elapsed() << '\n'; 

    t.start(); 
    
        std::cout << integral2::midpoint(f, measurement<units::metre>(0.0), measurement<units::metre>(2.0 * constants::pi), 100) << '\n'; 

    t.stop();
    std::cout << "elapsed: " << t.elapsed() << '\n'; 

    t.start(); 
    
        std::cout << integral2::midpoint(f, measurement<units::metre>(0.0), measurement<units::metre>(2.0 * constants::pi), 1000) << '\n'; 

    t.stop();
    std::cout << "elapsed: " << t.elapsed() << '\n'; 

    t.start(); 
    
        std::cout << integral2::midpoint(f, measurement<units::metre>(0.0), measurement<units::metre>(2.0 * constants::pi), 10000) << '\n'; 

    t.stop();
    std::cout << "elapsed: " << t.elapsed() << '\n'; 


    std::function<scalar_m(angle_m)> g = [](angle_m x) -> scalar_m { return math::op::sin(x); };

    std::cout << integral2::midpoint(g, angle_m(0.0), angle_m(2.0 * constants::pi), 10) << '\n'; 
    std::cout << integral2::midpoint(g, angle_m(0.0), angle_m(2.0 * constants::pi), 50) << '\n'; 
    std::cout << integral2::midpoint(g, angle_m(0.0), angle_m(2.0 * constants::pi), 100) << '\n'; 
    std::cout << integral2::midpoint(g, angle_m(0.0), angle_m(2.0 * constants::pi), 500) << '\n'; 
    std::cout << integral2::midpoint(g, angle_m(0.0), angle_m(2.0 * constants::pi), 1000) << '\n'; 


    t.start(); 
    std::cout << integral2::midpoint(g, angle_m(0.0), angle_m(constants::pi), 10000) << '\n';
    t.stop();
    std::cout << "elapsed: " << t.elapsed() << '\n'; 

    t.start(); 
    std::cout << integral2::midpoint_fixed(g, angle_m(0.0), angle_m(constants::pi), 1.e-6) << '\n'; 
    t.stop();
    std::cout << "elapsed: " << t.elapsed() << '\n'; 


    std::cout << integral2::midpoint_fixed(g, angle_m(0.0), angle_m(constants::pi), 1.e-6).value - 2.0 << '\n'; 

    integral integ; 


    t.start(); 
    integ.midpoint_fixed(0.0, constants::pi, [](double x) -> double { return std::sin(x); }, 1.e-6);
    t.stop();
    std::cout << "elapsed: " << t.elapsed() << '\n'; 

    std::cout << integ.result() << '\n';





    return 0; 

}