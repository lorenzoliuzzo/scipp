/**
 * @file    test/physics/potentials.cpp
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


int main() { 

    print("Simulating a spring potential...");      

    /// variables
    variable<measurement<metre>> x = 6.0;                           
    variable<measurement<metre_per_second>> x_dot = 1.0;
    variable<measurement<second>> t = 0.0;

    /// parameters
    measurement<metre> l0 = 2.0; 
    measurement<newton_per_metre> k = 50.0;     
    measurement<kilogram> m1 = 20.0;

    /// potential
    auto V = potential_energy(potentials::elastic(k, l0));    
    print("\nspring potential", V(x)); 
    print("force", V.force(x));

    auto L = lagrangian(m1, x, x_dot, t, V);
    print("\nL", L());
    print("T", L.T);
    print("V", L.V);
    print("x", L.x);
    print("xdot", L.x_dot);

    auto [dL_dx, dL_dxdot, dL_dt] = L.derivatives();
    print("\ndL_dx", dL_dx);
    print("dL_dxdot", dL_dxdot);
    print("dL_dt", dL_dt);

    auto H = hamiltonian(L);
    print("\nH", H());
    print("T", H.T);
    print("V", H.V);
    print("x", H.x);
    print("p", H.p);
    print("t", H.t);

    auto [_dH_dx, _dH_dp, _dH_dt] = H.derivatives();
    print("\ndH_dx", _dH_dx);
    print("dH_dp", _dH_dp); 
    print("dH_dt", _dH_dt);   

    H.plot_evolution<500>(10.0 * s);    

    print("\nH", H());
    print("T", H.T);
    print("V", H.V);
    print("x", H.x);
    print("p", H.p);
    print("t", H.t);

    auto [__dH_dx, __dH_dp, __dH_dt] = H.derivatives();
    print("\ndH_dx", __dH_dx);
    print("dH_dp", __dH_dp); 
    print("dH_dt", __dH_dt);   


    print(sizeof(x));
    print(sizeof(L));
    print(sizeof(H));

    return 0; 

}