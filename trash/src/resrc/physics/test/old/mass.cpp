/**
 * @file mass.cpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief Test file for mass.hpp
 * @date 2022-12-24
 * 
 * @copyright Copyright (c) 2023
 */


#include "physics.hpp"

using namespace physics;


int main(int argc, char** argv) {


    mass_system sys2D(position(10 * m, 10 * m));
    tools::random_generator rg; 

    size_t N = std::atoi(argv[1]);

    for (size_t i{}; i < N; i++) 
        sys2D.add_mass(mass(rg.unif(100000., 10000000) * kg, 
                       position(rg.unif(-1000, 1000) * km, rg.unif(-1000, 1000) * km), 
                       linear_velocity(rg.unif(-5, 5) * km_s, rg.unif(-5, 5) * km_s))); 

    sys2D.print(); 

    sys2D.animate(15 * s, km);


    // for (time_measurement t; t < 100 * s; t += 1 * s) {

    //     sys2D.evolve(1 * s);
    //     sys2D.plot(); 

    // }

    // mass_system<3> sys3D; 
    // for (size_t i{}; i < N; i++) 
    //     sys3D.add_mass(mass(rg.unif(100., 10000) * kg, position(rg.unif(-10, 10) * km, rg.unif(-10, 10) * km, rg.unif(-10, 10) * km))); 

    // sys3D.baricenter().print(); 
    // sys3D.plot(km); 


    return 0; 

}