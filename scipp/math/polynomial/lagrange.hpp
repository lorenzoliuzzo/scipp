/**
 * @file    math/polynomials/lagrange.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    template <typename T>
    static inline constexpr T lagrange_polynomial(const T& x, const T& A, const T& B, const T& C) noexcept {

        return (x - A) * (x - B) / (C - A) / (C - B);

    }

    
} // namespace scipp::math