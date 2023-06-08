/**
 * @file    math/functions/types/unary.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-08
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {
    
    
    namespace functions {


        template <typename ARG_TYPE, typename RESULT_TYPE>
        struct unary_function {

            using arg_t = ARG_TYPE;

            using result_t = RESULT_TYPE;

            using function_t = unary_function<arg_t, result_t>;


            static inline constexpr result_t f(const arg_t& x);

            constexpr result_t operator()(const arg_t& x) const { 

                return f(x); 
            
            }

        };


    } // namespace functions


} // namespace scipp::math