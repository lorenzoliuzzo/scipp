/**
 * @file    math/polynomials/newton_raphson.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-05-03
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    

    std::complex<double> eval_polynomial(const std::vector<std::complex<double>>& u, std::complex<double> z) {

        const double s = std::abs(z);
        auto n = u.size();

        std::vector<std::complex<double>> a(n);
        std::vector<std::complex<double>> b(n);
        a[0] = u[n];
        b[0] = u[n - 1];
        for (size_t j = 1; j < u.size(); ++j) {

            a[j] = b[j - 1] + a[j - 1] * 2. * z.real();
            b[j] = u[n - j] - a[j - 1] * s;

        }

        return z * a[n - 1] + b[n - 1];

    }


    // Evaluate a polynomial with coefficients a at x
    // template <size_t N>
    // constexpr std::complex<double> eval_polynomial(const geometry::vector<std::complex<double>, N>& a, std::complex<double> x) noexcept {
        
    //     std::complex<double> result{};

    //     for (int i = static_cast<int>(N) - 1; i >= 0; i--) 
    //         result = result * x + a[i];
        
    //     return result;

    // }

    // Evaluate the derivative of a polynomial with coefficients a at x
    std::complex<double> eval_polynomial_derivative(const std::vector<std::complex<double>>& a, std::complex<double> x) noexcept {
        
        std::complex<double> result = 0.0;

        for (int i = a.size() - 1; i >= 0; i--) 
            result = result * x + a[i + 1] * (i + 1.);

        return result;

    }

    // Find a root of a polynomial with coefficients a using the Newton-Raphson method
    template <size_t ITER_MAX>
    std::complex<double> newton_method(const std::vector<std::complex<double>>& a, std::complex<double> x0, double tolerance = std::numeric_limits<double>::epsilon()) {
        
        std::complex<double> x = x0;
        std::complex<double> fx;
        size_t iteration = 0;

        while (iteration < ITER_MAX) {

            fx = eval_polynomial(a, x);
            std::cout << "lorenzo\n";
            
            if (std::abs(fx) < tolerance) 
                break;
            
            x -= fx / eval_polynomial_derivative(a, x);
            std::cout << "lorenz0o\n";
            ++iteration;
            
        }

        if (iteration == ITER_MAX) {
            std::cerr << "Maximum iterations reached!\n";
            return std::numeric_limits<double>::quiet_NaN();
        }
        else 
            return x;

    }


} // namespace scipp::math