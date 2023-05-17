/**
 * @file    math/meta/function.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-05
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        template <typename ARG_TYPE, typename RESULT_TYPE>
        struct unary_function {


            using arg_t = ARG_TYPE;

            using result_t = RESULT_TYPE;

            using _t = unary_function<arg_t, result_t>; 


            inline static constexpr result_t f(const arg_t& x);


            constexpr result_t operator()(const arg_t& x) const { 

                return f(x); 
            
            }


        };


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


        };


    } // namespace functions


} // namespace scipp::math