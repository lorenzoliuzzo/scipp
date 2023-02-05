/**
 * @file earth_sun_mars.cpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2022-12-25
 * 
 * @copyright Copyright (c) 2023
 */


#include "physics.hpp"
#include "solar_system.hpp"

using namespace physics;


int main(int argc, char** argv) {


    mass_system<2> solar_sys2D;

    Earth.set_at_aphelion();
    // Mars.set_at_perihelion();

    solar_sys2D.add_mass(Sun.as_mass_object(),
                         Earth.as_mass_object()); 
                        //  ,                         Mars.as_mass_object()); 

    solar_sys2D.print(); 

    time_measurement time_step = 12. * 3600. * s; 
    for (time_measurement t{}; t < 365.25 * 24. * 3600. * s; t += time_step)
        solar_sys2D.evolve(time_step); 


    // solar_sys2D.animate(365.25 * 24. * 3600. * s, time_step, km);

    solar_sys2D.print();

    return 0; 

}