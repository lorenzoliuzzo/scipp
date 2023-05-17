/**
 * @file    math/functions/negate.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-06
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        template <typename T>
            requires (is_number_v<T>)
        struct negate<T> : unary_function<T, T> {


            using result_t = T; 

            using arg_t = T;


            inline static constexpr result_t f(const arg_t& x) noexcept {

                return -x;

            }


        };


        template <typename T>
            requires (physics::is_measurement_v<T>)
        struct negate<T> : unary_function<T, T> {


            using result_t = T; 

            using arg_t = T;


            inline static constexpr result_t f(const arg_t& x) noexcept {

                return -x.value;

            }
            

        };



    } // namespace functions


} // namespace scipp::math