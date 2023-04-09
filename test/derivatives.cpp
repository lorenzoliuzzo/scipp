#include "sci++.hpp"


using namespace scipp; 

using namespace tools; 
using namespace math; 
using namespace physics;
using namespace units; 
using namespace geometry;


int main() {


    print("Testing the derivatives class...");

    const auto f = functions::log();
    const auto df = functions::total_derivative(f); 
    const auto expected_df = functions::invert();
    print("f(2)", f(2. * rad));
    print("df(2, 0.1)", df(2. * rad, 0.1 * rad));
    print("expected_df(2, 0.1)", expected_df(2. * rad));




    vector<scalar_m, 100> x_values;
    vector<scalar_m, 100> f_values;
    vector<scalar_m, 100> df_values;
    vector<scalar_m, 100> expected_df_values;

    scalar_m increment = 2.0 * math::constants::pi / 100.0;
    std::size_t i{}; 
    for (scalar_m x{increment}; x < 2.0 * math::constants::pi; x += increment, ++i) {

        x_values[i] = x;
        f_values[i] = f(x);
        df_values[i] = df(x, increment);
        expected_df_values[i] = expected_df(x);

    }

    plt::title("f(x) and df(x, dx)");
    plt::xlabel("x");
    plt::grid(true);
    plt::xlim(0, static_cast<int>(2.0 * math::constants::pi));
    plt::named_plot("f", static_cast<std::vector<double>>(x_values), static_cast<std::vector<double>>(f_values));
    plt::named_plot("df", static_cast<std::vector<double>>(x_values), static_cast<std::vector<double>>(df_values));
    plt::named_plot("expected_df", static_cast<std::vector<double>>(x_values), static_cast<std::vector<double>>(expected_df_values));
    plt::tight_layout(); 
    plt::legend();
    plt::save("images/derivatives4.png");
    plt::show();
        




    return 0; 

}