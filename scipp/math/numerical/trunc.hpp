/**
 * @file    math/numerical/trunc.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the trunc function.
 * @date    2023-07-16
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
            requires is_number_v<T>
        struct trunc_impl<T> {

            static constexpr T f(const T& x) noexcept {

                return std::trunc(x);

            }
        
        };


        template <typename T>
            requires physics::is_measurement_v<T>
        struct trunc_impl<T> {

            static constexpr T f(const T& x) noexcept {

                return std::trunc(x.value);

            }
        
        };


    } // namespace op


} // namespace scipp::math