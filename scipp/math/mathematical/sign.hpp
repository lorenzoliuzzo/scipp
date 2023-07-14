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
            requires (is_number_v<T> || physics::is_measurement_v<T>)
        struct sign_impl {

            static constexpr int f(const T& x) noexcept {
                
                constexpr auto zero = T{};
                return (x > zero) ? 1 : (x < zero) ? -1 : 0;

            }       

        };


    } /// namespace functions


} /// namespace scipp::math