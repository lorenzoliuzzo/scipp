/**
 * @file    math/functions/types/binary.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-08
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {
    
    
    namespace functions {


        template <typename ARG_TYPE1, typename ARG_TYPE2, typename RESULT_TYPE>
        struct binary_function {


            using _t = binary_function<ARG_TYPE1, ARG_TYPE2, RESULT_TYPE>; 

            using result_t = RESULT_TYPE;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t&, const second_arg_t&);


            constexpr result_t operator()(const first_arg_t& x, const second_arg_t& y) const { 

                return f(x, y); 
            
            }


        };


    } // namespace functions


} // namespace scipp::math