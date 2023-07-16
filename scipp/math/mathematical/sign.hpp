/**
 * @file    math/functions/mathematical/sign.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the sign function
 * @date    2023-07-16
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T> 
        struct sign_impl<calculus::expr_ptr<T>> {
            
            static constexpr auto f(const calculus::expr_ptr<T>& x) noexcept {

                return condition(x < 0, -1.0, condition(x > 0, 1.0, 0.0)); 
            
            }
        

        };

        
        template <typename T> 
        struct sign_impl<calculus::variable<T>> {
            
            static constexpr auto f(const calculus::variable<T>& x) noexcept {

                return condition(x.expr < 0, -1.0, condition(x.expr > 0, 1.0, 0.0)); 
                
            }

        }; 


        template <typename T>
            requires (is_number_v<T> || physics::is_measurement_v<T>)
        struct sign_impl<T> {

            static constexpr int f(const T& x) noexcept {
                
                constexpr auto zero = T{};
                return (x > zero) ? 1 : (x < zero) ? -1 : 0;

            }       

        };


    } /// namespace functions


} /// namespace scipp::math