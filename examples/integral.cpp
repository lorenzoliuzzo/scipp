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

using namespace physics;
using namespace units;

using namespace math;
using namespace op; 
using namespace calculus;

using tools::print; 

using namespace std::numbers; 


int main() {

    constexpr auto a = 0.2 * m;                     /// apertura del reticolo
    constexpr auto d = 10.0 * um;                   /// passo del reticolo
    constexpr auto lambda = 589.0 * nm;             /// lunghezza d'onda
    constexpr auto L = 1.0 * m;                     /// distanza sorgente-reticolo

    measurement<base::length> x_ = -a;              /// posizione sull'asse x
    constexpr auto I_ = interval(-a, a);            /// intervallo di campionamento
    constexpr auto dx = 1.0 * mm;                   /// passo di campionamento
    constexpr size_t N = I_.steps(dx);              /// numero di campioni

    variable<measurement<base::length>> x;          /// variabile di integrazione
    constexpr auto I = interval(-0.5 * d, 0.5 * d); /// intervallo di integrazione
    constexpr auto interval_length = I.length();    /// lunghezza dell'intervallo di integrazione    

    auto f = unary_function<measurement<base::scalar>, measurement<base::length>>(
        [lambda, L, &x_](variable<measurement<base::length>>& t) { 
            constexpr auto k = 2.0 * pi / lambda;
            auto delta = hypot(L, x_ - t) - hypot(L, x_);
            return cos(k * delta); 
        }, x);                                      /// funzione dell'ampiezza sullo schermo

    print<micrometre>("d = ", d);
    print<nanometre>("lambda = ", lambda);
    print("L = ", L);
    print("interval = ", I); 

    std::vector<double> integral_values(N), x_values(N); 
    meta::for_<N>([&](auto i) {

        x_values[i] = x_.value;
        integral_values[i] = midpoint<std::ratio<1, 10000>>(f, I) / interval_length;
        x_ += dx;

    });

    plt::figure();
    plt::title("Diffracted intensity");
    plt::plot(x_values, integral_values);
    plt::xlabel("x [m]");
    plt::ylabel("I / I_0");
    plt::grid(true);
    plt::tight_layout();
    plt::save("images/diffracted_intensity.png");
    plt::show();

    return 0; 

}