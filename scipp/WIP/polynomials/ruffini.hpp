/**
 * @file    math/polynomials/ruffini.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-04
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    /// @brief Performs Ruffini's rule division on a column vector.
    /// @tparam POLYNOMIAL_TYPE The type of the polynomial vector.
    /// @param a The column vector to be divided (in ascending order)
    /// @param r The scalar value to divide `a` by.
    /// @return A pair containing the resulting column vector and the remainder.
    /// @note The returned column vector has a dimension of `VECTOR_TYPE::dim - 1`.
    template <typename T>
    constexpr auto ruffini(const std::vector<T>& v, const T& r) noexcept {

        const size_t degree = v.size() - 1;
        std::vector<T> result(degree);
        result[0] = v[0];
        for (size_t i = 1; i < degree; ++i) 
            result[i] = v[i] + result[i - 1] * r;
        
        auto remainder = v[degree] + r * result[degree - 1];
        
        return std::make_pair(result, remainder);   

    }


} // namespace scipp::math