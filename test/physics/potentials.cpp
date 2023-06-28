/**
 * @file    test/physics/potentials.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-28
 * 
 * @copyright Copyright (c) 2023
 */



#include "sci++.hpp"


using namespace scipp;

using namespace tools; 
using namespace math; 
using namespace math::op; 
using namespace math::calculus; 
using namespace physics;
using namespace physics::units; 


int main() { 

    print("Simulating a spring potential...");      

    /// variables
    variable<measurement<metre>> x = 6.0;                           
    variable<measurement<metre_per_second>> x_dot = 1.0;

    /// parameters
    measurement<metre> l0 = 2.0; 
    measurement<newton_per_metre> k = 50.0;     
    measurement<kilogram> m1 = 20, m2 = 40e20;

    /// potentials
    auto V_spring = spring_potential(k, l0);    
    print("\nspring potential", V_spring(x)); 
    print("force", V_spring.force(x));

    auto V_grav = gravitational_potential(m1, m2);    
    print("\ngravitational potential", V_grav(x)); 
    print("force", V_grav.force(x));

    /// total potential
    auto V = potential_energy(V_spring, V_grav);
    print("\ntotal potential", V(x));
    print("force", V.force(x));

    auto L = Lagrangian(m1, x, x_dot, V);
    auto L_v = L();
    print("L", L_v);
    print("T", L.T);
    print("V", L.V);

    // L.x = 2.0;
    // L.x_dot = 0.0;
    // print("T", L.T());
    // print("V", L.V());
    // print("L", L());

    variable<measurement<kilogram_metre_per_second>> p = std::get<0>(derivatives(L_v, wrt(L.x_dot)));
    print("p", p);
    print("p address", &p);

    variable<measurement<metre_per_second>> X_dot = p / m1;

    auto L_ = Lagrangian(m1, x, X_dot, V);

    variable<measurement<joule>> H_v = p * L_.x_dot - L_();
    print("H", H_v);

    auto [dH_dx, dH_dp] = derivatives(H_v, wrt(L_.x, p));
    print("dH_dx", dH_dx);
    print("dH_dp", dH_dp);    

    return 0; 

}