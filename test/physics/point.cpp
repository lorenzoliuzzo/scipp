/**
 * @file    test/physics/point.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-07-08
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"


using namespace scipp;
using tools::print; 
using namespace physics;
using namespace physics::units::literals; 

int main() {


    material_point<2> p1{1.0, {1.0m, 2.0m}};

    print("mass = ", p1.m);
    print("x = ", p1.x[0]); 
    print("y = ", p1.x[1]);
    print("vx = ", p1.v[0]); 
    print("vy = ", p1.v[1]);

    return 0;

}