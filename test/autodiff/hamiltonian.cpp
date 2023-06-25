/**
 * @file    test/autodiff/hamiltonian.cpp
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



variable<measurement<joule>> hamiltonian(const measurement<kilogram>& mass, 
                                         const measurement<divide_t<newton, metre>>& spring_constant, 
                                         const variable<measurement<metre>>& position, 
                                         const variable<measurement<multiply_t<metre_per_second, kilogram>>>& momentum) {

    return 0.5 * (momentum * momentum / mass + spring_constant * position * position); 

}

int main() { 

    constexpr measurement<kilogram> m = 20;
    constexpr auto k = 50.0 * (units::N / units::m); 
    variable<measurement<metre>> x = 2.0; 
    variable<measurement<multiply_t<metre_per_second, kilogram>>> p = 0.0;

    constexpr size_t N = 500; 
    constexpr measurement<second> t_max = 10;
    constexpr measurement<second> dt = t_max / N;

    print("Simulating the harmonic oscillator...");
    print("Initial conditions:");
    print("m", m);
    print("k", k);
    print("x", val(x)); 
    print("p", val(p));
    print("t_max", t_max);
    print("dt", dt);

    std::vector<double> x_i(N), p_i(N);
    meta::for_<N>([&](auto i) constexpr {

        auto H = hamiltonian(m, k, x, p);
        auto [dHdx, dHdp] = derivatives(H, wrt(x, p)); 

        x -= dt * dHdp;
        p += dt * dHdx;

        x_i[i] = val(x).value; 
        p_i[i] = val(p).value; 

    }); 

    plt::title("Oscillatore armonico");
    plt::named_plot("ritratto in fase", x_i, p_i); 
    plt::grid(true);
    plt::tight_layout(); 
    plt::legend();
    plt::show(); 

    return 0; 

}