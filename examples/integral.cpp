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

using namespace physics;             // for measurements 
using namespace units;               // for the units
using namespace units::literals;     // for the units literals

using namespace math; 
using namespace op;                  // for the operators and the functions
using namespace calculus::integral;  // for the integral function
using calculus::interval;            // for the interval struct

using tools::print;                  // for the print function


int main() {

    /// parameters of the experiment
    constexpr auto d = 10.0um;                          /// slit width
    constexpr auto lambda = 589.0nm;                    /// wavelength
    constexpr auto L = 0.5m;                            /// distance from the slit to the screen

    constexpr auto I_int = interval(-0.5 * d, 0.5 * d); /// interval of integration

    measurement<base::length> x = -0.2m;                /// variable for the function I(x)
    constexpr auto I = interval(-0.2m, 0.2m);           /// interval of points where we want to evaluate I(x)
    constexpr auto dx = 1.0mm;                          /// distance between two points
    constexpr size_t N = I.steps(dx);                   /// numer of points with the math::calculus::interval function


    /// we define the integral function of I(x) as an std::function 
    /// we use a lambda function and we pass by value the parameters and by reference the integral variable
    /// the function is a scalar function, so it returns a measurement with base::scalar
    std::function f = [lambda, L, &x](measurement<base::length> t) -> measurement<base::scalar> {   

        constexpr auto k = 2.0 * std::numbers::pi / lambda;     /// wave number
        return cos(k * (hypot(L, x - t) - hypot(L, x)));        /// using the math::op::hypot function     

    }; 


    print<micrometre>("d = ", d);                       /// we can specify the unit of measurement as a template parameter (type)
    print("lambda = ", lambda, nm);                     /// or we can specify the unit of measurement as a function parameter (value)
    print("interval of integration: ", I_int);          /// we can print the interval too
    print("f(0.0m) = ", f(0.0m));                       /// we can evaluate the function at a point


    std::vector<double> integral_values(N), x_values(N); /// to store the values for the plot

    /// we iterate over the interval using the meta::for_ function
    meta::for_<N>([&](auto i) { 

        /// we store the value of x, not the measurement
        x_values[i] = x.value; 

        /// we evaluate the integral using i.e. the midpoint rule from the math::calculus namespace
        /// the result of the integral is the width of the diffraction pattern
        /// the integration is correct from a dimensional point of view: the result is a measurement with base::length
        /// the precision of the calculation could be specified using an std::ratio as a template parameter
        /// you can also just fix a number of steps as a function parameter or template parameter, as you prefer
        integral_values[i] = midpoint<std::micro>(f, I_int).value_as(um); /// we extract the value of the integral in micrometres

        /// we increment the x variable by dx
        x += dx; 

    });

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


void test_integral() {


    auto f = [](auto x) { return op::sin(x); };
    auto I = interval(0.0, 2.3 * std::numbers::pi);

    auto simpson_result = simpson<100000>(f, I);
    auto midpoint_result = midpoint<100000>(f, I);
    auto midpoint_result_fixed = midpoint<std::femto>(f, I);

    print("Interval = ", I);
    print<std::femto>("simpson = ", simpson_result);
    print<std::femto>("midpoint = ", midpoint_result);
    print<std::femto>("midpoint (fixed) = ", midpoint_result_fixed);
    print<std::femto>("difference = ", simpson_result - midpoint_result);
    print<std::femto>("difference (fixed) = ", simpson_result - midpoint_result_fixed);
    print<std::femto>("difference (fixed) = ", midpoint_result - midpoint_result_fixed);

}