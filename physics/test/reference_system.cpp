/**
 * @file reference_system.cpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2022-12-20
 * 
 * @copyright Copyright (c) 2023
 */


#include "physics.hpp"
#include "matplotlibcpp.h"


using namespace physics;

namespace plt = matplotlibcpp;  


int main(int argc, char **argv) {


    tools::random_generator rg;
    reference_system<3> RS(position(0 * m, 0 * m, 0 * m));

    std::size_t n = std::atoi(argv[1]);
    std::vector<double> x(n), y(n), z(n);
    
    for (std::size_t i{}; i < n; i++) {

        RS.add(position<3>(rg.unif(-10, 10) * m, rg.unif(-10, 10) * m, rg.unif(-10, 10) * m)); 
        x[i] = (RS[i].x().value()); 
        y[i] = (RS[i].y().value()); 
        z[i] = (RS[i].z().value()); 

    }

    plt::scatter(x, y, z, 0.5, {{"color", "red"}});    
    plt::title("A REFERENCE SYSTEM");
    plt::xlabel("x");
    plt::ylabel("y");
    plt::set_zlabel("z");
    // plt::legend(); 
    plt::tight_layout(); 
    plt::show(); 
    plt::clf(); 


    return 0;

}