/**
 * @file    sizes.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-20
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp; 


int main() {


    physics::position3 x(47 * m, -40 * m, 42 * m);
    physics::position3 y(23 * m, 24 * m, -30 * m);
    physics::position3 z = math::op::sqrt(math::op::cross(x, y));

    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
    std::cout << "z: " << z << '\n';

    
    std::vector<time_m> time; 
    time.emplace_back(0.2 * s); 
    time.emplace_back(0.4 * s); 
    time.emplace_back(0.6 * s); 

    std::vector<length_m> space; 
    space.emplace_back(1.2 * m); 
    space.emplace_back(1.4 * m); 
    space.emplace_back(1.6 * m); 
    
    // tools::plotter plt; 
    // plt.plot(time, space, "space-time"); 
    // plt.plot3d(x.as_std_vector(), y.as_std_vector(), z.as_std_vector(), "R^3"); 

    
 

    return 0; 

}