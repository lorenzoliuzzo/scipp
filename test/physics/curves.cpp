/**
 * @file    test/physics/curves.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-29
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


// void plot_circle() { 

//     constexpr size_t N = 50;
//     constexpr auto dtheta = 2.1 * std::numbers::pi / N; 
//     std::vector<double> x(N), y(N);

//     /// variables
//     variable<measurement<metre>> rho = 1.0;       
//     variable<measurement<radian>> theta = 0.0;

//     auto c = circle(rho, theta);

//     meta::for_<N + 1>(
        
//         [&](auto i) constexpr {
//             auto p = c();   
//             theta += dtheta;
//             x[i] = val(p[0]).value;
//             y[i] = val(p[1]).value;
//         }

//     );

//     plt::figure();
//     plt::title("Circle");
//     plt::plot(x, y);
//     plt::xlabel("x");
//     plt::ylabel("y");
//     plt::axis("equal");
//     plt::grid(true);
//     plt::show();

// } 


int main() {
    

    variable<measurement<length>> rho = 1.0m;
    
    auto line = unary_function<measurement<length>, measurement<length>>([](auto& x) { return x; }, rho); 
    auto I = interval(-10.0m, 10.0m);
    auto gamma = curve(line, I);
    print("y = ", gamma());
    print("dy = ", gamma.gradient());

    variable<measurement<angle>> theta = 0.0 * rad;
    auto circle_x = unary_function<measurement<length>, measurement<angle>>([rho](auto& theta) { return rho * op::cos(theta); }, theta);
    auto circle_y = unary_function<measurement<length>, measurement<angle>>([rho](auto& theta) { return rho * op::sin(theta); }, theta);
    auto circle = curve(circle_x, circle_y, interval(0.0, 2.0 * std::numbers::pi));




    return 0; 

    
} // main