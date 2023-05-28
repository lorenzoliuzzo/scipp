/**
 * @file    math/calculus/integrals/gauss.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace integrals {


        enum weight_function_type {

            legendre,
            laguerre,
            hermite,
            chebyshev1, 
            chebyshev2,

        };


        template <weight_function_type TYPE>
        struct weight_function : functions::unary_function<double, double> {

            
            inline static constexpr result_t f([[maybe_unused]] const arg_t& x) noexcept { 

                switch (TYPE) {

                    case legendre: 
                        return 1.0;
                        break;

                    case laguerre:
                        return std::exp(-x);
                        break;

                    case hermite:
                        return std::exp(-std::pow(x, 2));
                        break;

                    case chebyshev1:
                        return 1.0 / std::sqrt(1.0 - std::pow(x, 2));
                        break; 

                    case chebyshev2: 
                        return std::sqrt(1.0 - std::pow(x, 2));
                        break;
                    
                    default:    
                        break;

                }

                throw std::runtime_error("Weight function not implemented");

            }


            template <typename INTERVAL_TYPE>
                requires (is_interval_v<INTERVAL_TYPE>)
            inline static constexpr auto weighted_nodes(const INTERVAL_TYPE& I, size_t steps) {
                
                std::vector<double> weights(steps); 
                std::vector<typename INTERVAL_TYPE::arg_t> nodes(steps);

        switch (TYPE) {
            case chebyshev1:
                for (size_t i = 0; i < steps; ++i) {
                    weights[i] = constants::pi / static_cast<double>(steps);
                    nodes[i] = I.start + (I.end - I.start) * 0.5 * (1.0 + op::cos((2.0 * i - 1.0) * constants::pi / (2.0 * steps)));
                }
                break;

            case chebyshev2:
                for (size_t i = 0; i < steps; ++i) {
                    const double x = constants::pi / (steps + 1);
                    nodes[i] = I.start + (I.end - I.start) * 0.5 * (1.0 + op::cos(i * x));
                    weights[i] = x * op::square(op::sin(i * x));
                }
                break;

            case legendre:
                for (size_t i = 0; i < steps; ++i) {
                    double point = std::cos((2 * i + 1) * M_PI / (2 * steps + 2));
                    nodes[i] = I.start + (I.end - I.start) * 0.5 * (1.0 + point);
                    weights[i] = (I.end - I.start) * 0.5 * (1.0 - point * point) / steps;
                }
                break;

            case laguerre:
                for (size_t i = 0; i < steps; ++i) {
                    double point = std::exp(std::lgamma(steps + 1) - std::lgamma(steps - i) - i * std::log(2));
                    nodes[i] = I.start + (I.end - I.start) * point;
                    weights[i] = (I.end - I.start) * point / ((steps + 1) * point * point);
                }
                break;

            case hermite:
                for (size_t i = 0; i < steps; ++i) {
                    double point = std::sqrt(2 * (steps + 1)) * std::cos((2 * i + 1) * M_PI / (2 * steps + 2));
                    nodes[i] = I.start + (I.end - I.start) * 0.5 * (1.0 + point);
                    weights[i] = (I.end - I.start) * std::pow(std::sin((i + 0.5) * M_PI / (steps + 1)), 2) / ((steps + 1) * M_PI);
                }
                break;
                
            default:
                break;
                }

                return std::make_pair(nodes, weights);
            }

        };


        template <typename T>
        struct is_weight_function : std::false_type {}; 

        template <weight_function_type TYPE>
        struct is_weight_function<weight_function<TYPE>> : std::true_type{}; 

        template <typename T>
        inline static constexpr bool is_weight_function_v = is_weight_function<T>::value; 


        template <typename FUNCTION_TYPE, typename WEIGHT_FUNCTION_TYPE>
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t> && is_weight_function_v<WEIGHT_FUNCTION_TYPE>)
        static constexpr auto gauss(const interval<typename FUNCTION_TYPE::arg_t>& I, size_t steps) {
            
            if (steps % 2 != 0) 
                throw std::runtime_error("Number of steps for Gauss Quadrature must be even.");

            const auto [x, w] = WEIGHT_FUNCTION_TYPE::weighted_nodes(I, steps);
            const auto fx = std::views::iota(0u, steps) | std::views::transform(
                [&](size_t i) {
                    return FUNCTION_TYPE::f(x[i]) * w[i]; 
                }
            );
            
            auto result = functions::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t>{};
            std::ranges::for_each(fx, 
                [&](auto fx_i) {
                    result += fx_i; 
                }
            );

            return result; 

        }


// template <typename FUNCTION_TYPE>
//     requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
// static constexpr auto weighted_nodes(size_t n) {

//     std::vector<typename FUNCTION_TYPE::arg_t> x(n);
//     std::vector<double> w(n);

//     for (size_t i = 0; i < n; ++i) {
//         x[i] = gauss_point<FUNCTION_TYPE>(n, i);
//         w[i] = gauss_weight<FUNCTION_TYPE>(n, i);
//     }

//     return std::make_pair(x, w);

// }

template <typename FUNCTION_TYPE>
    requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
static constexpr auto gauss_point(size_t n, size_t i) {
    const auto h = 1.0 / static_cast<double>(n);
    return std::cos((2 * i + 1) * M_PI / (2 * n + 2)) * h;
}

template <typename FUNCTION_TYPE>
    requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
static constexpr auto gauss_weight(size_t n, size_t i) {
    const auto h = 1.0 / static_cast<double>(n);
    return (h * M_PI) / (n + 1) * std::sin((2 * i + 1) * M_PI / (2 * n + 2));
}

    }

    // namespace integrals {



    //     template <weight_function_type WEIGHT_FUNC, size_t N>
    //     inline static constexpr auto weighted_points(const interval<auto>& I) {

    //         std::array<double, N> weights, points; 

    //         double t = I.start; 
    //         const double h = (I.end - I.start) / (N - 1.);

    //         switch (WEIGHT_FUNC) {

    //             case legendre: 

    //                 if constexpr (N == 1) {
    //                     points[0] = 0.0;
    //                     weights[0] = 2.0;

    //                 } else if constexpr (N == 2) {
    //                     auto x = std::sqrt(1.0 / 3.0);
    //                     points[0] = -x; 
    //                     points[1] = x;
    //                     weights[0] = weights[1] = 1.0;

    //                 } else if constexpr (N == 3) {
    //                     auto x = std::sqrt(3.0 / 5.0);
    //                     points[0] = -x; 
    //                     points[1] = 0.0; 
    //                     points[2] = x;
    //                     weights[0] = weights[2] = 5.0 / 9.0;
    //                     weights[1] = 8.0 / 9.0;

    //                 } else if constexpr (N == 4) {
    //                     auto a = 2.0 / 7.0 * std::sqrt(6.0 / 5.0);
    //                     points[0] = -std::sqrt(3.0 / 7.0 + a);
    //                     points[1] = -std::sqrt(3.0 / 7.0 - a);
    //                     points[2] = std::sqrt(3.0 / 7.0 - a);
    //                     points[3] = std::sqrt(3.0 / 7.0 + a);
    //                     weights[0] = weights[3] = (18.0 - std::sqrt(30.0)) / 36.0;
    //                     weights[1] = weights[2] = (18.0 + std::sqrt(30.0)) / 36.0;

    //                 } else if constexpr (N == 5) {
    //                     auto b = 2.0 * std::sqrt(10.0 / 7.0);
    //                     points[0] = -std::sqrt(5.0 + b) / 3.0;
    //                     points[1] = -std::sqrt(5.0 - b) / 3.0;
    //                     points[2] = 0.0;
    //                     points[3] = std::sqrt(5.0 - b) / 3.0;
    //                     points[4] = std::sqrt(5.0 + b) / 3.0;
    //                     weights[0] = weights[4] = (322.0 - 13.0 * std::sqrt(70.0)) / 900.0;
    //                     weights[1] = weights[3] = (322.0 + 13.0 * std::sqrt(70.0)) / 900.0;
    //                     weights[2] = 128.0 / 225.0;

    //                 } else if constexpr (N == 6) {
    //                     auto a = std::sqrt(5.0 / 3.0);
    //                     auto b = std::sqrt(5.0 / 6.0);
    //                     points[0] = -a;
    //                     points[1] = -b;
    //                     points[2] = 0.0;
    //                     points[3] = b;
    //                     points[4] = a;
    //                     weights[0] = weights[4] = (2665 - 14 * std::sqrt(70)) / 18000;
    //                     weights[1] = weights[3] = (2665 + 14 * std::sqrt(70)) / 18000;
    //                     weights[2] = 133 / 225.0;
    //                 }
    //                 break;


    //             case chebyshev1:    
    //                 break; 

    //             case chebyshev2:   
    //                 break; 

    //             case hermite: 
    //                 break; 

    //             // elseif kind == 2
    //             //     # Gauss-ChebyshevU quadrature, i.e., w(x) = sqrt(1-x^2)
    //             //     return ([ for k = n:-1:1],
    //             //             [ for k = n:-1:1])
    //             // elseif kind == 3
    //             //     # Gauss-ChebyshevV quadrature, i.e., w(x) = sqrt((1+x)/(1-x))
    //             //     return ([cos((k - .5) * π / (n + .5)) for k = n:-1:1],
    //             //             [2π / (n + .5) * cos((k - .5) * π / (2 * (n + .5)))^2 for k = n:-1:1])
    //             // elseif kind == 4
    //             //     # Gauss-ChebyshevW quadrature, i.e., w(x) = sqrt((1-x)/(1+x))
    //             //     return ([cos(k * π / (n + .5)) for k = n:-1:1],
    //             //             [2π / (n + .5) * sin(k * π / (2 * (n + .5)))^2 for k = n:-1:1])
    //             //                 break;
                            
    //             default:
    //                 break;

    //         }

    //         return std::make_pair(points, weights);

    //     }


    //     template <weight_function_type WEIGHT_FUNC, size_t N = 100, typename FUNC_TYPE>
//         requires (is_unary_function_v<FUNC_TYPE>)
    //     inline static constexpr auto gauss(const FUNC_TYPE& func, const interval<typename FUNC_TYPE::arg_t>& I) {

    //         typename FUNC_TYPE::result_t result{};
    //         const auto [points, weights] = weighted_points<WEIGHT_FUNC, N>(I);
    //         for (size_t i{}; i < N; ++i) 
    //             result += weights[i] * func(points[i]);

    //         return result;          

    //     } 


    //     template <typename POLYNOMIAL_TYPE, typename FUNC_TYPE>
    //         requires (is_unary_function_v<FUNC_TYPE>)
    //     inline static constexpr auto gauss(const FUNC_TYPE& func) {

    //         constexpr auto poly = POLYNOMIAL_TYPE();
    //         typename FUNC_TYPE::result_t result{};
    //         const auto [nodes, weights] = poly.weighted_nodes();
            
    //         for (size_t i{}; i < poly.order; ++i) 
    //             result += weights[i] * func(nodes[i]);

    //         return result;       

    //     } 


    //     template <typename POLYNOMIAL_TYPE, typename FUNC_TYPE>
    //         requires (is_unary_function_v<FUNC_TYPE>)
    //     inline static constexpr auto gauss(const FUNC_TYPE& func, const interval<typename FUNC_TYPE::arg_t>& I) {

    //         constexpr auto poly = POLYNOMIAL_TYPE();
    //         typename FUNC_TYPE::result_t result{};
    //         auto [nodes, weights] = poly.weighted_nodes();

    //         std::transform(weights.data.begin(), weights.data.end(), weights.data.begin(), 
    //             [&I](auto w_k) { return 0.5 * (I.end - I.start) *  w_k; });

    //         std::transform(nodes.data.begin(), nodes.data.end(), nodes.data.begin(), 
    //             [&I](auto x_k) { return 0.5 * (I.start + I.end) + 0.5 * (I.end - I.start) * x_k; });

    //         for (size_t i{}; i < poly.order; ++i) 
    //             result += weights.data[i] * func(nodes.data[i]);

    //         return result;       

    //     } 


    //     template <typename FUNC_TYPE>
    //         requires (is_unary_function_v<FUNC_TYPE>)
    //     inline static constexpr auto gauss_legendre(const FUNC_TYPE& func, const interval<typename FUNC_TYPE::arg_t>& I) {

    //         typename FUNC_TYPE::result_t result{};

    //         for (size_t i{}; i < 512; ++i) 
    //             result += 0.5 * (I.end - I.start) * polynomials::legendre_weights_right[i] * func(0.5 * (I.start + I.end) + 0.5 * polynomials::legendre_roots_right[i] * (I.end - I.start));

    //         for (size_t i{}; i < 512; ++i) 
    //             result += 0.5 * (I.end - I.start) * polynomials::legendre_weights_right[i] * func(-0.5 * (I.start + I.end) - 0.5 * polynomials::legendre_roots_right[i] * (I.end - I.start));

    //         return result;       

    //     } 

    //     template <typename FUNC_TYPE>
    //         requires (is_unary_function_v<FUNC_TYPE>)
    //     inline static constexpr auto gauss_legendre(const FUNC_TYPE& func) {

    //         typename FUNC_TYPE::result_t result{};
            
    //         for (size_t i{}; i < 512; ++i) 
    //             result += polynomials::legendre_weights_right[i] * func(polynomials::legendre_roots_right[i]);

    //         for (size_t i{}; i < 512; ++i) 
    //             result += polynomials::legendre_weights_right[i] * func(-polynomials::legendre_roots_right[i]);

    //         return result;       

    //     } 


    // } /// namespace integrals


} /// namespace scipp::math