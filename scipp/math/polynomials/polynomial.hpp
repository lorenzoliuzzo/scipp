/**
 * @file    math/polynomials/polynomial.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-28
 * 
 * @copyright Copyright (c) 2023
 */


#include <vector>


namespace scipp::math {


    template <size_t N, typename T>
    struct polynomial {


        using _t = polynomial<N, T>;

        using value_t = T;

        inline static constexpr size_t degree = N;


        std::array<T, N + 1> coeff;


        template <typename... Ts>
        constexpr polynomial(const Ts&&... ts) noexcept 
            requires (sizeof...(Ts) == N + 1) : 
                
                coeff{ts...} {}


        constexpr polynomial(const std::array<T, N + 1>& arr) noexcept : 

            coeff{arr} {}

        constexpr polynomial(const std::vector<T>& vec) noexcept 
            requires (vec.size() == N + 1) : 

            coeff{vec.begin(), vec.end()} {}


        constexpr polynomial(const polynomial<N, T>& p) noexcept :

            coeff{p.coeff} {}

        
        constexpr auto eval(const T& x) const noexcept {

            const auto s = op::abs(x);

            std::array<T, N + 1> a, b;
            a[0] = this->coeff[N];
            b[0] = this->coeff[N - 1];
            for (size_t j = 1; j < N; ++j) {
                a[j] = b[j - 1] + a[j - 1] * x.real * 2.0;
                b[j] = this->coeff[j + 1] - a[j - 1] * s;
            }

            return x * a[N - 1] + b[N - 1];

        }


        constexpr auto eval_derivative(const T& x) const noexcept {

            const auto s = op::abs(x);

            std::array<T, N + 1> a, b;
            a[0] = T{0.0};
            b[0] = this->coeff[0] * N;
            for (std::size_t j = 1; j < N; ++j) {
                a[j] = b[j - 1] + a[j - 1] * x.real * 2.0;
                b[j] = this->coeff[j] * (N - j) - a[j - 1] * s;
            }

            return a[N - 1] + x * b[N - 1];

        }


    };


    // template <typename VECTOR_TYPE>
    //     requires (geometry::is_column_vector_v<VECTOR_TYPE> && math::is_complex_v<typename VECTOR_TYPE::value_t> && VECTOR_TYPE::dim > 1)
    // constexpr auto eval_polynomial(const VECTOR_TYPE& u, typename VECTOR_TYPE::value_t z) {

    //     const auto s = op::abs(z);
    //     constexpr std::size_t n = VECTOR_TYPE::dim - 1;

    //     VECTOR_TYPE a, b;
    //     a.data[0] = u.data[n];
    //     b.data[0] = u.data[n - 1];
    //     for (size_t j = 1; j < u.dim - 1; ++j) {

    //         a.data[j] = b.data[j - 1] + a.data[j - 1] * z.real * 2.0;
    //         b.data[j] = u.data[j + 1] - a.data[j - 1] * s;

    //     }

    //     return z * a.data[n - 1] + b.data[n - 1];

    // }


    // template <typename VECTOR_TYPE>
    //     requires (geometry::is_column_vector_v<VECTOR_TYPE> && math::is_complex_v<typename VECTOR_TYPE::value_t> && VECTOR_TYPE::dim > 1)
    // constexpr auto eval_polynomial_derivative(const VECTOR_TYPE& u, typename VECTOR_TYPE::value_t z) {

    //     const auto s = op::abs(z);
    //     constexpr std::size_t n = VECTOR_TYPE::dim - 1;

    //     VECTOR_TYPE a, b;
    //     a.data[0] = typename VECTOR_TYPE::value_t{0.0};
    //     b.data[0] = u.data[0] * n;
    //     for (std::size_t j = 1; j < u.dim - 1; ++j) {
    //         a.data[j] = b.data[j - 1] + a.data[j - 1] * z.real * 2.0;
    //         b.data[j] = u.data[j] * (n - j) - a.data[j - 1] * s;
    //     }

    //     return z * a.data[n - 1] + b.data[n - 1];

    // }




template <typename T>
constexpr auto eval_polynomial(const std::vector<T>& u, T z) {

    const auto s = op::abs(z);
    const size_t n = u.size() - 1;

    std::vector<T> a(n), b(n);
    a[0] = u[n];
    b[0] = u[n - 1];
    for (size_t j = 1; j < n; ++j) {
        a[j] = b[j - 1] + a[j - 1] * z * 2.0;
        b[j] = u[j + 1] - a[j - 1] * s;
    }

    return z * a[n - 1] + b[n - 1] / s;

}

template <typename T>
constexpr auto eval_polynomial_derivative(const std::vector<T>& u, T z) {

    const auto s = op::abs(z);
    const size_t n = u.size() - 1;

    std::vector<T> a(n), b(n);
    a[0] = T{0.0};
    b[0] = u[0] * n;
    for (std::size_t j = 1; j < n; ++j) {
        a[j] = b[j - 1] + a[j - 1] * z * 2.0;
        b[j] = u[j] * (n - j) - a[j - 1] * s;
    }

    return z * a[n - 1] + b[n - 1] / s;
    
}


} // namespace scipp::math