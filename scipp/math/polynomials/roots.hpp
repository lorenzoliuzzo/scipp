/**
 * @file    math/polynomials/roots.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-05-03
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    template <typename FUNCTION_TYPE>
    auto bisection(const FUNCTION_TYPE& f, 
                   const curves::curves::interval<typename FUNCTION_TYPE::arg_t>& I, 
                   const typename FUNCTION_TYPE::arg_t eps) {

        if (f(I.start) * f(I.end) >= 0) {

            std::cerr << "Invalid range: f(I.start) and f(I.end) must have opposite signs.\n";
            throw std::invalid_argument("Invalid range: f(I.start) and f(I.end) must have opposite signs.\n");

        }
        
        auto I_ = I;
        auto x0 = I.start;
        auto x1 = I.end; 

        while ((x1 - x0) >= eps) {

            auto x = (x0 + x1) / 2.0;

            if (f(x) == 0.0) 
                return x;

            else    
                if (f(x) * f(x1) < 0.0) 
                x1 = x;

            else 
                x0 = x;

        }

        return x0;

    }


    template <typename FUNCTION_TYPE>
    auto regula_falsi(const FUNCTION_TYPE& f, 
                      const curves::curves::interval<typename FUNCTION_TYPE::arg_t>& I, 
                      const typename FUNCTION_TYPE::arg_t eps) {

        if (f(I.start) * f(I.end) >= 0) {

            std::cerr << "Invalid range: f(I.start) and f(I.end) must have opposite signs.\n";
            throw std::invalid_argument("Invalid range: f(I.start) and f(I.end) must have opposite signs.\n");

        }

        auto I_ = I;
        auto x0 = I.start;
        auto x1 = I.end;

        while ((x1 - x0) >= eps) {

            auto fx0 = f(x0);
            auto fx1 = f(x1);
            auto x2 = (x0 * fx1 - x1 * fx0) / (fx1 - fx0);

            if (f(x2) == 0.0)
                return x2;

            else if (f(x2) * fx0 < 0.0)
                x1 = x2;

            else
                x0 = x2;

        }

        return (x0 + x1) / 2.0;

    }


    template <typename FUNCTION_TYPE>
    auto secant(const FUNCTION_TYPE& f, 
                const curves::curves::interval<typename FUNCTION_TYPE::arg_t>& I, 
                const typename FUNCTION_TYPE::result_t eps) {
        
        auto x0 = I.start;
        auto x1 = I.end;
        auto x2 = x1;
        auto x3 = x0;

        while (std::abs(x2 - x3) >= eps * std::max(std::abs(x2), std::abs(x3))) {

            auto f1 = f(x1);
            auto f0 = f(x0);
            if (f1 == f0) {

                std::cerr << "Division by zero error: f(x1) and f(x0) must not be equal.\n";
                throw std::runtime_error("Division by zero error: f(x1) and f(x0) must not be equal.\n");

            }

            auto x4 = x1 - f1 * (x1 - x0) / (f1 - f0);
            x0 = x1;
            x1 = x4;
            x2 = x1;
            x3 = x0;

        }

        return x1;

    }


    template <size_t ITER_MAX = 100, size_t N>
    auto durand_kerner(const geometry::vector<double, N>& coeffs, const double eps = 1e-6)
        -> geometry::vector<std::complex<double>, N - 1> {

        const size_t n = N - 1; // degree of the polynomial
        std::array<std::complex<double>, n> roots; // initial guesses for roots

        const double theta = 2.0 * M_PI / n; // angle between roots

        // initialize the roots as equally spaced points on a circle
        for (size_t i = 0; i < n; ++i) 
            roots[i] = std::polar(1., i * theta);

        // perform iterations until convergence or maximum iterations reached
        for (size_t k = 0; k < ITER_MAX; ++k) {

            std::array<std::complex<double>, n> new_roots;
            bool converged = true;
            for (size_t i = 0; i < n; ++i) {

                std::complex<double> f_i = coeffs.data[n];
                for (size_t j = 0; j < n; ++j) 
                    if (i != j) 
                        f_i *= (roots[i] - roots[j]);

                new_roots[i] = roots[i] - f_i / std::pow(static_cast<double>(n), static_cast<double>(n - 1));
                if (std::abs(new_roots[i] - roots[i]) > eps) 
                    converged = false;
                
            }
            roots = new_roots;
            if (converged) 
                break;

        }

        return roots;

    }


    template <size_t ITER_MAX = 100, size_t N>
    auto roots_newton(const geometry::vector<double, N>& coeffs, const double eps = 1e-6)
        -> geometry::vector<std::complex<double>, N - 1> {

            std::cout << "andrea\n"; 

        const size_t n = N - 1; // degree of the polynomial
        std::array<std::complex<double>, n> roots; // initial guesses for roots

        std::complex<double> z(0.0, 1.0); 
        std::vector<std::complex<double>> sub(n);
        std::copy(coeffs.data.begin(), coeffs.data.end(), sub.begin());
        
        for (size_t i{0}; i < n; ++i) {
            std::cout << "andreaa\n"; 
            roots[i] = newton_method<ITER_MAX>(sub, z, eps);
            std::cout << "andrea\n"; 
            auto ruff = ruffini(sub, roots[i]).first; // geometry::vector<std::complex<double>, N - 1>
            std::cout << "andrea\n"; 
            std::copy(ruff.begin(), ruff.end(), sub.begin());
            sub.pop_back();

        }

        return roots;

    }


    //     std::complex<double> z(0.4, 0.9);
        // std::array<std::complex<double>, ITER_MAX> P; 
        // Matrix P(iterations, vec(n, 0));
        // Complex w;
        
        // //Creating Matrix with initial starting values
        
        // for (int i = 0; i < N - 1; i++) {
        //     P[0][i] = std::pow(z, i);
        // }

        // //Durand Kerner Algorithm

        // for (int col = 0; col < iterations; col++) {

        //     for (int row = 0; row < n; row++) {
        //         Complex g = Polynomial(Z, n, P[col][row]);
        //         for (int k = 0; k < n; k++) {
        //             if (k != row) {
        //                 g = g / (P[col][row] - P[col][k]);
        //             }

        //         }
                    
        //         P[col + 1][row] -= g;

        //     }
                
        //     return P;
    // }   


    template <size_t N>
    constexpr auto find_roots(const geometry::vector<double, N>& a, const double tolerance) 
        -> geometry::vector<std::complex<double>, N - 1> {

        std::array<std::complex<double>, N - 1> roots{};

        std::complex<double> z = std::rand() / static_cast<double>(RAND_MAX);

        auto root = newton_raphson(a, z, tolerance);
        auto a_new = ruffini(a, root);



        for (size_t count{}; count < N - 1; ++count) {

            roots[count] = root;

        }

        // find a first root using newton raphson

        // then apply ruffini factorization to find the coefficients of the polynomial of degree N - 1

        // iterate until the polynomial is of degree 1    


        return roots;

    }

    
    
} // namespace scipp::math