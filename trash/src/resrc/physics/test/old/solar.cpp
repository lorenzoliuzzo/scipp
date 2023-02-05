/**
 * @file solar.cpp
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

    Mercury.set_at_aphelion();
    Venus.set_at_perihelion();
    Earth.set_at_aphelion();
    Mars.set_at_perihelion();
    Jupiter.set_at_aphelion();
    Saturn.set_at_perihelion();
    Uranus.set_at_aphelion();
    Neptune.set_at_perihelion();

    solar_sys2D.add_mass(Sun.as_mass_object(),
                         Mercury.as_mass_object(),
                         Venus.as_mass_object(),
                         Earth.as_mass_object(),
                         Mars.as_mass_object(),
                         Jupiter.as_mass_object(),
                         Saturn.as_mass_object(), 
                         Uranus.as_mass_object(), 
                         Neptune.as_mass_object()); 

    solar_sys2D.print(); 
    solar_sys2D.animate(100. * 24. * 3600. * s, 12 * 3600 * s, km);


    return 0; 

}