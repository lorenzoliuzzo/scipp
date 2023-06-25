/**
 * @file    math/polynomials/newton_root.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-04
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    

    template <typename T>
    constexpr auto newton_method(const std::vector<T>& coeff, T x0, double precision = 1e-6) {

        constexpr size_t max_iterations = 100;
        size_t iterations = 0;
        auto x = x0;
        auto f = eval_polynomial(coeff, x);
        auto df = eval_polynomial_derivative(coeff, x);

        while (op::abs(f) > precision && iterations < max_iterations) {
            x -= f / df;
            f = eval_polynomial(coeff, x);
            df = eval_polynomial_derivative(coeff, x);
            iterations++;
        }

        if (iterations == max_iterations)
            throw std::runtime_error("Newton method did not converge");

        return x;

    }

    // template <typename POLYNOMIAL_TYPE>
    //     // requires (geometry::is_column_vector_v<VECTOR_TYPE> && math::is_complex_v<typename VECTOR_TYPE::value_t> && VECTOR_TYPE::dim > 1)
    // constexpr auto newton_method(const POLYNOMIAL_TYPE& poly, typename POLYNOMIAL_TYPE::value_t x0, double precision) {

    //     constexpr size_t max_iterations = 100;
    //     size_t iterations = 0;
    //     auto x = x0;
    //     auto f = poly.eval(x);
    //     auto df = poly.eval_derivative(x);

    //     while (op::abs(f) > precision && iterations < max_iterations) {
    //         x -= f / df;
    //         f = poly.eval(x);
    //         df = poly.eval_derivative(x);
    //         iterations++;
    //     }

    //     if (iterations == max_iterations)
    //         throw std::runtime_error("Newton method did not converge");

    //     return x;

    // }

template <size_t Degree, typename T, size_t... Indices>
constexpr auto find_roots_recursive(const std::vector<T>& coeff, std::array<T, Degree>& roots, std::index_sequence<Indices...>) {
    
    if constexpr (sizeof...(Indices) == Degree) {
        return roots;
    } else {
        constexpr size_t Index = sizeof...(Indices);
        auto root = newton_method(coeff, T(0.30));
        auto ruff_poly = ruffini(coeff, root).first;
        roots[Index] = root;
        return find_roots_recursive(ruff_poly, roots, std::make_index_sequence<Index + 1>());
    }

}

template <size_t Degree, typename T>
constexpr auto find_roots(const std::vector<T>& coeff) {

    std::array<T, Degree> roots{};
    return find_roots_recursive<Degree, T>(coeff, roots, std::make_index_sequence<0>());
    
}




    // template <typename POLYNOMIAL_TYPE>
    //     // requires (geometry::is_column_vector_v<VECTOR_TYPE> && math::is_complex_v<typename VECTOR_TYPE::value_t> && VECTOR_TYPE::dim > 1)
    // constexpr auto find_roots(const POLYNOMIAL_TYPE& poly, double precision) {
        
    //     using value_t = typename POLYNOMIAL_TYPE::value_t;

    //     std::array<value_t, POLYNOMIAL_TYPE::degree> roots;
    //     value_t first_root = newton_method(poly, value_t(0.0), precision);
    //     auto ruff_poly = ruffini(poly, first_root).first;
    //     std::vector<value_t> r(std::begin(ruff_poly), std::end(ruff_poly));
    //     roots[0] = first_root;

    //     for (size_t i = 1; i < POLYNOMIAL_TYPE::degree; ++i) {
    //         polynomial new_poly(r); /// of size r.size() - 1
    //         value_t root = newton_method(new_poly, value_t(0.0), precision);
    //         r.resize(r.size() - 1);
    //         r = ruffini(new_poly, root);
    //         roots[i] = root;
    //     }

    //     return roots;

    // }


    // Evaluate a polynomial with coefficients a at x
    // template <size_t N>
    // constexpr std::complex<double> eval_polynomial(const geometry::vector<std::complex<double>, N>& a, std::complex<double> x) noexcept {
        
    //     std::complex<double> result{};

    //     for (int i = static_cast<int>(N) - 1; i >= 0; i--) 
    //         result = result * x + a[i];
        
    //     return result;

    // }

    // // Evaluate the derivative of a polynomial with coefficients a at x
    // std::complex<double> eval_polynomial_derivative(const std::vector<std::complex<double>>& a, std::complex<double> x) noexcept {
        
    //     std::complex<double> result = 0.0;

    //     for (int i = a.size() - 1; i >= 0; i--) 
    //         result = result * x + a[i + 1] * (i + 1.);

    //     return result;

    // }




} // namespace scipp::math