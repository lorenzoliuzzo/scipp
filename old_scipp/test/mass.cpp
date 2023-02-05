/**
 * @file    mamss.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-21
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp;
using namespace scipp::physics;


int main() {

    tools::cpu_timer timer;

    timer.start();
        mass<2> obj(std::sqrt(2894) * kg, position2(1.0 * m, 2.0 * m), lin_velocity2(123.431 * (m / s), -45.0 * (m / s)));
    timer.stop();
    std::cout << "time: " << timer.elapsed() << '\n';


    math::equations::ode_solver solver; 

    std::cout << solver.RK4(potentials::gravitational_field<2>(), obj.as_position(), 3 * s, obj.as_mass_m(), 34564234 * kg, position2(-35 * m, -235 * m)); 

    

    // obj.print(); 
    // std::cout << "kinetic energy: " << obj.kinetic_energy() << '\n';
    





    return 0;

}