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

using namespace tools; 
using namespace math; 
using namespace math::calculus; 
using namespace math::calculus::curves; 
using namespace physics;
using namespace physics::units; 


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
    

    variable<measurement<metre>> x = 3.0;
    std::array<variable<measurement<metre>>, 2> point, centre;

    auto r = line(2.0, 1.0 * m, x);
    auto par = parabola(1.0 / m, 0.0, 0.0 * m, x);

    point = r();
    print("x", point[0]);
    print("y", point[1]);
    
    auto [dydx] = derivatives(point[1], wrt(x)); 
    print(dydx);

    point = par();
    print("x", point[0]);
    print("y", point[1]);
    
    auto [dydx_] = derivatives(point[1], wrt(x)); 
    print(dydx_);

    // auto cir = circle(centre, 1.0 * m, x);
    // point = cir();
    // print("x", point[0]);
    // print("y", point[1]);

    // auto [dydx__] = derivatives(point[1], wrt(x)); 
    // print(dydx__);

    return 0; 

    
} // main