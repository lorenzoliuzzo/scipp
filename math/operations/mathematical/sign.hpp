/**
 * @file    math/functions/mathematical/sign.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-12
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        /// @brief Get the sign of a number or a measurement
        template <typename T>
            requires (is_number_v<T> || physics::is_generic_measurement_v<T>)
        struct sign<T> {

            using function_t = unary_function<T, int>;                                          

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) noexcept {
                
                auto zero = typename function_t::arg_t{};
                return (x == zero) ? 0 : ((x > zero) ? 1 : -1);

            }       

        };


    } /// namespace functions


} /// namespace scipp::math