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
            // laguerre,
            hermite,
            chebyshev1, 
            chebyshev2

        };


        template <weight_function_type TYPE>
        struct weight_function : meta::unary_function<double, double> {

            
            constexpr double f([[maybe_unused]] const double& x) const override {

                switch (TYPE) {

                    case legendre: 
                        return 1.0;
                        break;

                    // case laguerre:
                    //     return op::exp(-x);
                    //     break;

                    case hermite:
                        return op::exp(-op::square(x));
                        break;

                    case chebyshev1:
                        return 1.0 / std::sqrt(1.0 - op::square(x));
                        break;

                    case chebyshev2:
                        return std::sqrt(1.0 - op::square(x));
                        break;
                
                    
                    default:    
                        break;
                }

                throw std::runtime_error("Weight function not implemented");

            }

        };


        template <std::size_t N, weight_function_type WEIGHT_FUNC>
        inline static constexpr auto gauss_weighted_points() {

            geometry::vector<double, N> weights, points; 
            return {points, weights};

        }


        template <std::size_t N, typename FUNC_TYPE, weight_function_type WEIGHT_FUNC>
            requires (meta::is_unary_function_v<FUNC_TYPE>)
        inline static constexpr auto gauss(const FUNC_TYPE& func, const curve<typename FUNC_TYPE::arg_t>& curve) {

            typename FUNC_TYPE::result_t result;
            const auto [points, weights] = gauss_weighted_points<N, WEIGHT_FUNC>();
            for (std::size_t i{}; i < N; ++i) 
                result += weights.data[i] * func(points.data[i]);

            return result;          

        } 



    } /// namespace integrals


} /// namespace scipp::math