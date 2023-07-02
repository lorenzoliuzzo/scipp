/**
 * @file    math/polynomials/chebyshev.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace polynomials {


        template <size_t ITER_MAX = 1000, size_t N>
        auto durand_kerner(const geometry::vector<double, N>& coeffs, const double tolerance = 1e-8) 
            -> geometry::vector<std::complex<double>, N - 1> {

            // Initialize roots
            const int degree = N - 1;
            std::array<std::complex<double>, degree> roots;

            for (size_t i = 0; i < degree; ++i) {
                const double angle = 2.0 * M_PI * i / degree;
                roots[i] = std::complex<double>(std::cos(angle), std::sin(angle));
            }

            // Iterate until convergence
            size_t iteration = 0;
            double max_diff = 2.0 * tolerance;
            while (max_diff > tolerance && iteration < ITER_MAX) {

                max_diff = 0.0;
                for (int i = 0; i < degree; ++i) {
                    
                    std::complex<double> f(0.0);
                    for (int j = 0; j < degree; ++j) 
                        f += coeffs.data[j] * std::pow(roots[i], degree - j);

                    const std::complex<double> delta = -f / (degree * coeffs.data[degree]);
                    roots[i] += delta;
                    max_diff = std::max(max_diff, std::abs(delta));

                }
                ++iteration;

            }

            return roots;

        }

    
    }


}