/**
 * @file    math/functions/types/ternary.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-08
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {
    
    
    namespace functions {



        template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2 = ARG_TYPE1, typename ARG_TYPE3 = ARG_TYPE1>
        struct ternary_function {


            using _t = ternary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2>; 

            using result_t = RESULT_TYPE;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;

            using third_arg_t = ARG_TYPE3;


            virtual ~ternary_function() = default;


            inline static constexpr result_t f(const first_arg_t&, const second_arg_t&, const third_arg_t&);


            constexpr result_t operator()(const first_arg_t& x, const second_arg_t& y, const third_arg_t& z) const { 

                return f(x, y, z); 
            
            }


        };
  
    
    } /// namespace functions


} /// namespace scipp::math