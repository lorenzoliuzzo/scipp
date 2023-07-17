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
                variable<DOMAIN> x = gamma.interval.start;

                meta::for_<N>([&](auto) constexpr {

                    auto [g, g_prime] = gamma(x);
                    result += f(g) * op::norm(g_prime) * step;
                    x += step;

                });

                return result; 

            }


            template <size_t N, typename CURVE>
                requires is_curve_v<CURVE>
            static constexpr auto curvilinear(CURVE gamma) {

                typename CURVE::interval_t::value_t result{};

                const auto step = gamma.domain.step(N);
                variable<typename CURVE::parameter_t> t = gamma.domain.start;

                meta::for_<N>([&](auto) constexpr {

                    result += op::norm(gradient(gamma(t), t)) * step;
                    t += step;

                });

                return result; 

            }


        } // namespace integrals


    } // namespace integrals
    

} // namespace scipp::math