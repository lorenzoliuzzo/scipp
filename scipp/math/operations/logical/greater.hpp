/**
 * @file    math/functions/logical/greater.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * 
 * @brief   greater function implementation
 * 
 * @date    2023-06-09
 * @copyright Copyright (c) 2023
 */

    

namespace scipp::math {


    namespace functions {


        template <typename T>
            requires (is_number_v<T>)
        struct greater<T> {

            using function_t = binary_function<T, T, T>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return x > y;   
            
            }

        };


        template <typename T>
            requires (is_number_v<T>)
        struct greater_equal<T> {

            using function_t = binary_function<T, T, T>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return x >= y;   
            
            }

        };
        

    } // namespace functions


} // namespace scipp::math