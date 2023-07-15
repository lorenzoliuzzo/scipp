/**
 * @file    examples/physics/integral.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Integrale per mi fratello polletto
 * @date    2023-07-12
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"

using namespace scipp;

using namespace physics;            // for measurements 
using namespace units;              // for the units
using namespace units::literals;    // for the units literals

using namespace math; 
using namespace op;                 // for the operators and the functions
using namespace calculus;           // for the integral function and the interval struct

using tools::print;                 // for the print function


int main() {

    /// parameters of the experiment
    constexpr auto d = 10.0um;                      /// slit width
    constexpr auto lambda = 589.0nm;                /// wavelength
    constexpr auto L = 0.5m;                        /// distance from the slit to the screen


    measurement<base::length> x = -0.2m;            /// variable for the function I(x)
    constexpr auto I = interval(-0.2m, 0.2m);       /// interval of points where we want to evaluate I(x)
    constexpr auto dx = 1.0mm;                      /// distance between two points
    constexpr size_t N = I.steps(dx);               /// numer of points with the math::calculus::interval function

    measurement<base::length> x_;                   /// variable for the integral function     
    auto I_ = interval(-0.5 * d, 0.5 * d);          /// interval of integration

    print<micrometre>("d = ", d);                   /// we can specify the unit of measurement as a template parameter (type)
    print("lambda = ", lambda, nm);                 /// or we can specify the unit of measurement as a function parameter (value)
    print("interval of x_ = ", I_);                 /// we can print the interval too
    print("interval of x = ", I);          


    /// we define the integral function of I(x) as a math::calculus::unary_function 
    /// we can construct the unary_function by simply using a lambda function and passing the variable as a reference
    /// the unary_function takes a math::calculus::variable and returns a measurement
    auto f = unary_function<measurement<base::scalar>, measurement<base::length>>(
        
        /// we pass by value the parameters and by reference the x variable
        /// note that the lambda function only *has* to take a variable.
        [lambda, L, &x](variable<measurement<base::length>>& t) {   

            constexpr auto k = 2.0 * std::numbers::pi / lambda;     /// wave number
            return cos(k * (hypot(L, x - t) - hypot(L, x)));        /// using the math::op::hypot function     

        }, x_ /// we pass the x variable to the unary_function constructor to bind with its variable member

    ); /// please note that the function f is a cosine, so it is a scalar function, in the sense that it returns measurement with base::scalar


    std::vector<double> integral_values(N), x_values(N); /// to store the values for the plot

    /// we iterate over the interval using the meta::for_ function
    meta::for_<N>([&](auto i) { 

        /// we store the value of x, not the measurement
        x_values[i] = x.value; 

        /// we evaluate the integral using i.e. the midpoint rule from the math::calculus namespace
        /// the precision of the calculation could be specified using an std::ratio as a template parameter
        /// the result of the integral is the width of the diffraction pattern
        integral_values[i] = midpoint<std::ratio<1, 10000>>(f, I_).value_as(um); /// we extract the value of the integral in micrometres

        /// we increment the x variable by dx
        x += dx; 

    });

    /// The integration here is correct from the dimensional point of view!
    /// the result of the integral is a measurement with base::length
    auto integral = midpoint<std::ratio<1, 10000>>(f, I_);
    print("integral = ", integral); 
    static_assert(are_same_measurement_v<decltype(integral), measurement<base::length>>); 


    /// we plot the results using the matplotlib-cpp library
    plt::figure();
    plt::title("Diffracted intensity");
    plt::plot(x_values, integral_values);
    plt::xlabel("x [m]");  // we can specify the unit of measurement
    plt::ylabel("I [um]"); // we can specify the unit of measurement
    plt::grid(true);
    plt::tight_layout();
    plt::save("images/diffracted_intensity.png");
    plt::show();

    return 0; 

}