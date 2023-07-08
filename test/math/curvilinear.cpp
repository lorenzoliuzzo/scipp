/**
 * @file    test/math/curvilinear.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-07-08
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"

using namespace scipp;
using tools::print; 

using namespace math; 
using namespace math::calculus; 
using namespace physics;
using namespace physics::base; 
using namespace physics::units::literals;


int main() { 

    variable<double> x = 0.0; 
    auto f = function<double, double>([]([[maybe_unused]] auto x) { return 1.0; }, x);
    auto gamma = curve<double, double>([&](auto x) { return op::sin(x); }, x, interval(0.0, 2.0 * std::numbers::pi));
    
    print("initial point = ", gamma());

    auto integral = integrals::curvilinear<100>(gamma, f);
    print("integral = ", integral);

    print("final point = ", gamma());

    auto length_ = integrals::curvilinear<500>(gamma);
    print("length = ", length_);

    auto segment = curves::segment<measurement<length>, measurement<length>>(0.5, 0.0m, interval(-1.0cm, 10.0m));
    auto length_segment = integrals::curvilinear<500>(segment);
    print("length segment = ", length_segment);

    print(segment.length<100>());     


    return 0; 

}