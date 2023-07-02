/**
 * @file    test/physics/hamiltonian.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06/25
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



inline variable<measurement<joule>> hamiltonian(const measurement<kilogram>& mass, 
                                                const measurement<newton_per_metre>& spring_constant, 
                                                const variable<measurement<metre>>& position, 
                                                const variable<measurement<kilogram_metre_per_second>>& momentum) {
    
    return kinetic_energy(mass, momentum).value + spring_potential(spring_constant, 1.0 * units::m, position).value; 

}


int main() { 

    constexpr size_t N = 200;                                   /// number of points to plot
    std::vector<double> x_i(N), p_i(N);                         /// value containers for plotting


    constexpr measurement<kilogram> m = 20;                     /// mass
    constexpr measurement<newton_per_metre> k = 50.0;           /// spring_constant

    variable<measurement<metre>> x = 2.0;                       /// initial position
    variable<measurement<kilogram_metre_per_second>> p = 0.0;   /// initial momentum 

    print("Simulating the harmonic oscillator...");             /// print messages
    print("Initial conditions:");
    print("m", m);
    print("k", k);
    print("x", val(x)); 
    print("p", val(p));


    constexpr measurement<second> t_max = 5;                    /// max time to evolve the sistem
    constexpr measurement<second> dt = t_max / N;               /// increment time step 

    print("\nEvolving the system...");
    print("total time", t_max);
    print("step", dt);

    meta::for_<N>([&](auto i) constexpr {

        auto H = hamiltonian(m, k, x, p);                       /// calling the hamiltonian
        auto [dHdx, dHdp] = derivatives(H, wrt(x, p));          /// extracting the derivatives of H 

        x -= dt * dHdp;                                         /// solution for x of hamilton's first order differential equation 
        p += dt * dHdx;                                         /// solution for p of hamilton's first order differential equation 

        x_i[i] = val(x).value;                                  /// extracting the variable value and then extracting the measurement value
        p_i[i] = val(p).value; 

    }); 

    print("\nFinal values:");                                   /// printing the final values
    print("x", val(x)); 
    print("p", val(p));


    print("\nPlotting the phase plot..."); 
    plt::title("Oscillatore armonico");                         /// plotting with matplotlibcpp
    plt::named_plot("ritratto in fase", x_i, p_i); 
    plt::grid(true);
    plt::tight_layout(); 
    plt::legend();
    plt::show(); 


    return 0; 

}