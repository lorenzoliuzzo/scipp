/**
 * @file    math/calculus/möbius_map.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-03
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    

    namespace calculus {


        struct möbius_map {

            std::complex<double> a, b, c, d;

            // Constructor
            möbius_map(std::complex<double> a_, std::complex<double> b_, std::complex<double> c_, std::complex<double> d_)
                : a(a_), b(b_), c(c_), d(d_) {}

            // Apply the Möbius map to a complex number z
            std::complex<double> operator()(std::complex<double> z) const {
                return (a * z + b) / (c * z + d);
            }

            // Get the inverse of the current Möbius map
            möbius_map inverse() const {
                return möbius_map(d, -b, -c, a);
            }

        };


        auto identity_map = möbius_map(1.0, 0.0, 0.0, 1.0);
        auto inversion_map = möbius_map(0.0, 1.0, 1.0, 0.0);
        auto zero_map = möbius_map(0.0, 0.0, 0.0, 0.0);

        auto linear_map(std::complex<double> a, std::complex<double> b) {
            return möbius_map(a, b, 0.0, 1.0);
        }


        // std::array<std::complex<double>, 4> calculate_jacobian(const möbius_map& map, std::complex<double> z) {
        //     std::array<std::complex<double>, 4> jacobian;

        //     std::complex<double> denom = (map.c * z + map.d);
        //     std::complex<double> denom_squared = denom * denom;

        //     jacobian[0] = z / denom;
        //     jacobian[1] = 1.0 / denom;
        //     jacobian[2] = -map.a * z / denom_squared;
        //     jacobian[3] = -map.a / denom_squared;

        //     return jacobian;
        // }


        // std::array<std::complex<double>, 4> find_mobius_map_coefficients(const std::array<std::complex<double>, 3>& inputs, const std::array<std::complex<double>, 3>& mapped_values) {
        //     std::array<std::complex<double>, 4> coefficients;

        //     // Initialize the coefficients with initial guesses
        //     coefficients[0] = 1.0;
        //     coefficients[1] = 0.0;
        //     coefficients[2] = 0.0;
        //     coefficients[3] = 1.0;

        //     const int max_iterations = 10000;
        //     const double tolerance = 1e-6;

        //     for (int iteration = 0; iteration < max_iterations; ++iteration) {
        //         std::array<std::complex<double>, 4> delta;

        //         // Calculate the residuals
        //         std::array<std::complex<double>, 3> residuals;
        //         for (int i = 0; i < 3; ++i) {
        //             auto map = möbius_map(coefficients[0], coefficients[1], coefficients[2], coefficients[3]);
        //             residuals[i] = mapped_values[i] - map(inputs[i]);
        //         }

        //         // Calculate the Jacobian matrix
        //         std::array<std::array<std::complex<double>, 4>, 3> jacobian;
        //         for (int i = 0; i < 3; ++i) {
        //             jacobian[i] = calculate_jacobian({ coefficients[0], coefficients[1], coefficients[2], coefficients[3] }, inputs[i]);
        //         }

        //         // Solve for the delta coefficients using matrix operations
        //         for (int j = 0; j < 4; ++j) {
        //             delta[j] = 0.0;
        //             for (int i = 0; i < 3; ++i) {
        //                 delta[j] += jacobian[i][j] * residuals[i];
        //             }
        //         }

        //         // Update the coefficients
        //         for (int j = 0; j < 4; ++j) {
        //             coefficients[j] += delta[j];
        //         }

        //         // Check for convergence
        //         if (std::abs(delta[0]) < tolerance && std::abs(delta[1]) < tolerance && std::abs(delta[2]) < tolerance && std::abs(delta[3]) < tolerance) {
        //             break;
        //         }
        //     }

        //     return coefficients;
        // }


    } // namespace calculus


} // namespace scipp::math