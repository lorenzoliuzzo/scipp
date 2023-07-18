/**
 * @file    examples/curves.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Example of applied automatic differentiation in calculus: curves and surfaces
 * @date    2023-07-18
 * 
 * @copyright Copyright (c) 2023
 */


#include "scipp" // Include the scipp library header

// Import the necessary namespaces from the scipp library
using namespace scipp;

using namespace physics; // for measurement
using namespace units::literals; // for units and literals

using namespace math;
using namespace math::calculus; // for curve and interval

using namespace geometry; // for vector

using namespace tools; // for plot and print


int main() {

    // Define a circle in the origin with a radius of 3 meters using the 'curves::circle' class
    curves::circle<measurement<base::length>> circle(3.0m, make_vector(0.0m, 0.0m)); 

    // Define an angle 'theta' as pi / 2.0 radians
    double theta = std::numbers::pi / 2.0; 
    print("theta: ", theta); 

    // Evaluate and print the point on the circle at the given 'theta'
    print("point at theta: ", circle(theta));

    // Compute and print the gradient of the circle at the given 'theta'
    print("gradient at theta: ", circle.gamma.gradient(theta));

    // Print the circle's radius and center
    print("radius: ", circle.radius); 
    print("center: ", circle.center);

    // Compute and print the length of the circle's curve using numerical integration
    auto length = integrals::length<1000>(circle.gamma); 
    print("length of the circle: ", length);

    // Plot the circle's curve and save the plot as "images/circle.png"
    plot(1000, circle.gamma, "x [m]", "y [m]", "Circle", "images/circle.png"); 

    // Modify the circle's center and radius
    circle.center = make_vector(1.0m, 1.0m);
    circle.radius = 2.0m;

    // Print the updated circle's radius and center
    print("radius: ", circle.radius); 
    print("center: ", circle.center);

    // Re-compute the length of the circle's curve with the updated parameters
    length = integrals::length<1000>(circle.gamma); 
    print("length of the circle: ", length);

    // Plot the updated circle's curve and save the plot as "images/circle2.png"
    plot(1000, circle.gamma, "x [m]", "y [m]", "Circle with center translated", "images/circle2.png");

    return 0;

}