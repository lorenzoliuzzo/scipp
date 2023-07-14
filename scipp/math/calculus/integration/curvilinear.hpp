/**
 * @file    math/integrals/curvilinear.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 *
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        namespace integrals {


            template <size_t N, typename CURVE_T, typename RANGE, typename... DOMAIN> 
                requires is_curve_v<CURVE_T> && (sizeof...(DOMAIN) == std::tuple_size_v<typename CURVE_T::parametrization_t::variable_t> == 1)
            static constexpr auto curvilinear(CURVE_T gamma, function<RANGE, DOMAIN...> f) {

                variable<op::multiply_t<RANGE, std::tuple_element_t<0, std::tuple<DOMAIN...>>>> result{}; 

                const auto I = std::get<0>(gamma.intervals); 
                const auto step = I.step(N);
                auto& x = std::get<0>(gamma.parametrization.variables);
                x = I.start;
                f.variables = gamma.parametrization.variables;

                meta::for_<N>([&](auto) constexpr {
                    x += step;
                    result += f() * norm(gamma.gradient()) * step;
                });

                return result; 

            }


            template <size_t N, typename CURVE_T>
            static constexpr auto curvilinear(CURVE_T gamma) {

                variable<typename CURVE_T::value_t> result{}; 

                const auto I = std::get<0>(gamma.intervals); 
                const auto step = I.step(N);
                auto& x = std::get<0>(gamma.parametrization.variables);
                x = I.start;

                meta::for_<N>([&](auto) constexpr {
                    x += step;
                    result += norm(gamma.gradient()) * step;
                });

                return result; 
            }


        } // namespace integrals


    } // namespace integrals
    

} // namespace scipp::math