/**
 * @file    test/physics/multidim.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-28
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"


using namespace scipp;

using namespace tools; 
using namespace math; 
using namespace math::op; 
using namespace math::calculus; 
using namespace physics;
using namespace physics::units; 
using namespace physics::potentials;
using namespace geometry;


int main() { 

    measurement<kilogram> m = 1.0;
    variable<measurement<metre>> rho = 6.0;
    variable<measurement<radian>> theta = 0.4;

    variable<measurement<metre>> x_ = rho * cos(theta);
    variable<measurement<metre>> y_ = rho * sin(theta);

    std::array<variable<measurement<metre>>, 2> x = { x_, y_ };
    std::array<variable<measurement<metre_per_second>>, 2> x_dot = { 1. * m_s, 0. * m_s };

    auto [dxdrho, dxdtheta] = derivatives(x[0], wrt(rho, theta));
    print("dxdrho", dxdrho);
    print("dxdtheta", dxdtheta);
    
    variable<measurement<second>> t = 0.0;  

    print("x", x[0]);
    print("x_dot", x_dot[0]);
    print("y", x[1]);
    print("y_dot", x_dot[1]);

    lagrangian_multidim<2> L(m, x, x_dot, t); //, potential_energy(potentials::elastic(50.0, 2.0)));
    print("\nL", L());
    print("T", L.T);

    auto [dL_drho, dL_dtheta, dL_dx_dot, dL_dy_dot] = derivatives(L(), wrt(rho, theta, x_dot[0], x_dot[1]));
    print("\ndL_drho", dL_drho);
    print("dL_dtheta", dL_dtheta);
    print("dL_dx_dot", dL_dx_dot);
    print("dL_dy_dot", dL_dy_dot);

    lagrangian_multi L_i(m, [&](auto rho, auto theta) -> std::array<variable<measurement<metre>>, 2> { return {rho * (theta), rho * sin(theta)}; }, rho, theta);

    return 0; 

}