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
            requires (sizeof...(ARG_TYPEs) == DIM)
        struct nary_function {


            using _t = nary_function<RESULT_TYPE, DIM, ARG_TYPEs...>; 

            using result_t = RESULT_TYPE;

            using arg_t = std::tuple<ARG_TYPEs...>;


            virtual ~nary_function() = default;


            inline static constexpr result_t f(const ARG_TYPEs&... x);


            constexpr result_t operator()(const ARG_TYPEs&... x) const { 

                return f(x...); 
            
            }


        }; /// struct nary_function
  

        template <typename T>
        struct is_nary_function : std::false_type {};

        template <typename RESULT_TYPE, size_t DIM, typename... ARG_TYPEs>
        struct is_nary_function<nary_function<RESULT_TYPE, DIM, ARG_TYPEs...>> : std::true_type {};
        
        template <typename T>
        inline static constexpr bool is_nary_function_v = is_nary_function<T>::value; 

    
    } /// namespace functions


} /// namespace scipp::math