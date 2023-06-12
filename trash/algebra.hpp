/**
 * @file    math/calculus/curve.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-05-02
 * 
 * @copyright Copyright (c) 2023
 */


template <typename T>
std::vector<T> slice(const std::vector<T>& vec, size_t start, size_t end, size_t step=1) noexcept {
    std::vector<T> result;
    for (size_t i = start; i < end; i += step) 
        result.push_back(vec[i]);
    
    return result;
}


namespace scipp::math {
    
    
    // function to calculate the value of a polynomial at a given point x
    template <size_t N, typename SCALAR_CMEAS_TYPE, typename CMEAS_TYPE>
        requires (physics::is_scalar_complex_v<SCALAR_CMEAS_TYPE> && math::is_complex_v<CMEAS_TYPE>)
    constexpr CMEAS_TYPE eval_poly(const std::vector<SCALAR_CMEAS_TYPE>& coeffs, CMEAS_TYPE x) {

        CMEAS_TYPE result = 0.0;
        CMEAS_TYPE power = 1.0;
        for (const auto& c : coeffs) {
            result += c * power;
            power *= x;
        }
        return result;

    }

    // function to find all roots of a polynomial of order n using the Fundamental Theorem of Algebra
    template <size_t N, typename SCALAR_CMEAS_TYPE>
    requires (physics::is_scalar_complex_v<SCALAR_CMEAS_TYPE>)
    constexpr geometry::vector<SCALAR_CMEAS_TYPE, N> find_roots(const std::vector<SCALAR_CMEAS_TYPE>& coeffs) {

        geometry::vector<SCALAR_CMEAS_TYPE, N> roots;
        geometry::vector<SCALAR_CMEAS_TYPE, N> poly_coeffs;
        poly_coeffs.data[0] = 1.0;

        if (coeffs[1] != SCALAR_CMEAS_TYPE::zero) 
            poly_coeffs[1] = -coeffs[0] / coeffs[1];
        
        else {

            if (N == 1) 
                return roots; // polynomial is a constant, no roots
            else 
                return find_roots<N - 1>(std::vector<SCALAR_CMEAS_TYPE>{coeffs.begin() + 1, coeffs.begin() + N}); // find roots of derivative polynomial
            
        }

        for (size_t i{2}; i < N; ++i) {

            // form the ith polynomial using the previous polynomial and the original polynomial
            poly_coeffs.data[i] = 0.0;
            for (size_t j{i}; j >= 1; --j) {
                poly_coeffs.data[j] = poly_coeffs.data[j - 1] - poly_coeffs.data[j] * coeffs[i - 1] / coeffs[i];
            }

            poly_coeffs.data[0] = -poly_coeffs.data[0] * coeffs[i - 1] / coeffs[i];
        }

        // find the roots of the polynomial using the QR algorithm
        for (int i{}; i < static_cast<int>(N) - 1; ++i) {

            SCALAR_CMEAS_TYPE x = 0.0;
            SCALAR_CMEAS_TYPE y = 0.0;
            SCALAR_CMEAS_TYPE b = poly_coeffs[N - i - 2];

            if (eval_poly(slice(poly_coeffs, 0, N - i - 1), SCALAR_CMEAS_TYPE::zero) == 0.0) {
                // if the remaining polynomial is constant, all roots are zero
                for (size_t j{0}; j < N - i - 1; ++j) 
                    roots.data[i + j] = SCALAR_CMEAS_TYPE::zero;
                break;
            }

            for (int j{static_cast<int>(N) - i - 3}; j >= 0; --j) {
                y = x + y * roots.data[i];
                x = x * roots.data[i] + poly_coeffs.data[j];
            }

            roots.data[i] = (-b - x) / y;

        }

        return roots;

    }



    // // function to find all roots of a polynomial of order n using the Fundamental Theorem of Algebra
    // template <size_t N, typename SCALAR_CMEAS_TYPE>
    //     requires (physics::is_scalar_complex_v<SCALAR_CMEAS_TYPE>)
    // constexpr geometry::vector<SCALAR_CMEAS_TYPE, N> find_roots(const geometry::vector<SCALAR_CMEAS_TYPE, N>& coeffs) {

    //     geometry::vector<SCALAR_CMEAS_TYPE, N> roots;
    //     geometry::vector<SCALAR_CMEAS_TYPE, N> poly_coeffs;
    //     poly_coeffs.data[0] = 1.0;

    //     if (coeffs[1] != SCALAR_CMEAS_TYPE::zero) 
    //         poly_coeffs[1] = -coeffs[0] / coeffs[1];
    //     else
    //         poly_coeffs[1] = 0;

    //     for (size_t i{2}; i < N; ++i) {

    //         // form the ith polynomial using the previous polynomial and the original polynomial
    //         poly_coeffs.data[i] = 0.0;
    //         for (size_t j{i}; j >= 1; --j) 
    //             poly_coeffs.data[j] = poly_coeffs.data[j - 1] - poly_coeffs.data[j] * coeffs.data[i - 1] / coeffs.data[i];
            
    //         poly_coeffs.data[0] = -poly_coeffs.data[0] * coeffs.data[i - 1] / coeffs.data[i];
    //     }

    //     // find the roots of the polynomial using the QR algorithm
    //     for (int i{}; i < static_cast<int>(N) - 1; ++i) {
    //         SCALAR_CMEAS_TYPE x = 0.0;
    //         SCALAR_CMEAS_TYPE y = 0.0;
    //         SCALAR_CMEAS_TYPE b = poly_coeffs[N - i - 2];
    //         for (int j{static_cast<int>(N) - i - 3}; j >= 0; --j) {
    //             y = x + y * roots.data[i];
    //             x = x * roots.data[i] + poly_coeffs.data[j];
    //         }
    //         roots.data[i] = (-b - x / y) / static_cast<double>(N);
    //     }

    //     return roots;

    // }


} // namespace scipp::math