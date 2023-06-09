/**
 * @file    math/functions/types/nary.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-08
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {
    
    
    namespace functions {


        template <typename RESULT_TYPE, size_t DIM, typename... ARG_TYPEs> 
        struct nary_function {


            using _t = nary_function<RESULT_TYPE, DIM, ARG_TYPEs...>; 

            using result_t = RESULT_TYPE;

            using param_t = std::tuple<ARG_TYPEs...>;


            inline static constexpr result_t f(const ARG_TYPEs&... x);


            inline constexpr result_t operator()(const ARG_TYPEs&... params) const  
                requires (sizeof...(params) == DIM) {

                return f(params...); 
            
            }


        }; /// struct nary_function
  

    } /// namespace functions


} /// namespace scipp::math