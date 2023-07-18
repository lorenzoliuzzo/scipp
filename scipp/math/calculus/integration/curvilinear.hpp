/**
 * @file    scipp/math/calculus/integration/curvilinear.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the definition of the curvilinear integral.
 * @date    2023-07-16
 *
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        namespace integrals {


            template <size_t N, typename FUNCTION, typename CURVE> 
                requires is_curve_v<CURVE>
            static constexpr auto curvilinear(const FUNCTION& f, const CURVE& gamma) {

                using DOMAIN = typename CURVE::value_t;
                op::multiply_t<std::invoke_result_t<FUNCTION, DOMAIN>, DOMAIN> result{}; 

                const auto step = gamma.interval.step(N);
                variable<DOMAIN> t = gamma.interval.start;

                meta::for_<N>([&](auto) constexpr {

                    auto point = gamma(t); 
                    result += f(point) * op::norm(gradient(point, t)) * step;
                    t += step;

                });

                return result; 

            }


            template <size_t N, typename CURVE>
                requires is_curve_v<CURVE>
            static constexpr auto length(const CURVE& gamma) {

                const auto step = gamma.domain.step(N);
                variable<typename CURVE::interval_t::value_t> t = gamma.domain.start;

                using result_t = decltype(op::norm(gradient(gamma(t), t)) * step); 
                result_t result{};

                meta::for_<N>([&](auto) constexpr {

                    result += op::norm(gradient(gamma(t), t)) * step;
                    t += step;

                });
                    
                return result; 

            }


        } // namespace integrals


    } // namespace integrals
    

} // namespace scipp::math