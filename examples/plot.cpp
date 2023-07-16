/**
 * @file    examples/plot.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Basic example of the plot function.
 * @date    2023-07-16
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"


using namespace scipp;

using namespace math::op; 

using namespace physics;  
using namespace physics::units;
using namespace physics::units::literals;

using math::calculus::interval;     
using namespace math::calculus::integral;

using tools::plot;             
using tools::print;             


int main() {


    plot<1000>(                                 // Number of points: 1000
        interval(0.0, 4.0 * std::numbers::pi),  // Interval: [0, 4pi]
        [&](auto x) {                           // Lambda function: x -> sin(x)
            return op::sin(x); 
        },
        "x", "y",                               // Axis labels         
        "Sin function",                         // Title       (optional)
        "images/plots/sine.png"                 // Output file (optional)    
    );


    plot(
        1000, // the number of points can be specified as a function parameter too
        interval(10.0m, 20.0m), 
        [&](measurement<base::length> x) -> measurement<base::area> { 
            return 2.0 * op::square(x); 
        },
        "x", // the unit of measurement will be added automatically
        "y", 
        "Square function",
        "images/plots/square.png"
    );


    return 0; 
    
}