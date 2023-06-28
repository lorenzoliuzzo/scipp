/**
 * @file    test/physics/spring.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06/25
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

    constexpr size_t N = 800;                                       /// number of points to plot
    std::vector<double> x_i(N), p_i(N), E_i(N), t_i(N);             /// value containers for plotting


    measurement<kilogram> mass = 20;                      /// mass
    constexpr measurement<newton_per_metre> k = 50.0;               /// spring_constant
    constexpr measurement<metre> l0 = 2.0; 

    print("\nParameters");
    print("mass", mass);
    print("k", k);
    print("l0", l0);

    variable<measurement<metre>> x = 6.0;                           /// initial position
    variable<measurement<metre_per_second>> x_dot = 1.0;            /// initial velocity 
    variable<measurement<second>> t;                                /// time              

    lagrangian L(x, x_dot, t, mass, k, l0);                            /// build the lagrangian
    hamiltonian H(L);                                               /// build the hamiltonian

    print("\nVariables");
    print("x", H.x); 
    print("p", H.p);
    print("t", H.t);

    print("\nEnergy values");
    print("T", L.T()); 
    print("V", L.V()); 
    print("L", L()); 
    print("H", H()); 

    constexpr measurement<second> t_max = 60;                    /// max time to evolve the sistem
    constexpr measurement<second> dt = t_max / N;               /// increment time step 

    print("\nEvolving the system...");
    print("total time", t_max);
    print("step", dt);

    meta::for_<N>([&](auto i) constexpr {

        t += dt; 
        H.rk4(dt);                                              /// evolving the system with rk4
        x_i[i] = val(H.x).value;                                /// extracting the variable value and then extracting the measurement value
        p_i[i] = val(H.p).value; 
        E_i[i] = val(H()).value;
        t_i[i] = val(t).value; 

    }); 

    print("\nFinal values");                                    /// printing the final values
    print("x", H.x);
    print("p", H.p);
    print("t", H.t);
    print("E", H());


    print("\nPlotting the phase space plot...");                /// plotting with matplotlibcpp
    plt::figure(); 
    plt::title("Harmonic oscillator");                          
    plt::named_plot("phase space p-x", x_i, p_i); 
    // plt::xlabel("x [" + units::m::to_string() + "]");
    // plt::ylabel("p [" + (units::kg * units::m_s)::to_string() + "]");
    plt::grid(true);
    plt::tight_layout(); 
    plt::legend();
    plt::show(); 

    plt::figure(); 
    plt::title("Energy - time"); 
    plt::plot(t_i, E_i);
    plt::grid(true);
    plt::tight_layout(); 
    plt::show(); 


    return 0; 

}