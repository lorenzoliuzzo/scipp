/**
 * @file    math/calculus/function.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        template <typename RESULT_TYPE, typename ARG_TYPE>
        struct unary_function {


            using _t = unary_function<RESULT_TYPE, ARG_TYPE>; 

            using result_t = RESULT_TYPE;

            using arg_t = ARG_TYPE;


            virtual ~unary_function() = default;

            virtual constexpr result_t operator()(const arg_t& x) const = 0; 


        };


        template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2 = ARG_TYPE1>
        struct binary_function {


            using _t = binary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2>; 

            using result_t = RESULT_TYPE;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            virtual ~binary_function() = default;

            virtual constexpr result_t operator()(const first_arg_t& x, const second_arg_t& y) const = 0; 


        };


        template <typename RESULT_TYPE, typename ARG_TYPE, std::size_t DIM> 
        struct nary_function {


            using _t = nary_function<RESULT_TYPE, ARG_TYPE, DIM>; 

            using result_t = RESULT_TYPE;

            using arg_t = geometry::vector<ARG_TYPE, DIM>;


            virtual ~nary_function() = default;

            constexpr result_t operator()(const geometry::vector<ARG_TYPE, DIM>& x) const {} 


        };


        template <typename RESULT_TYPE, typename... ARG_TYPES>
        struct variadic_function {


            using _t = variadic_function<RESULT_TYPE, ARG_TYPES...>; 

            using result_t = RESULT_TYPE;

            using args_t = std::tuple<ARG_TYPES...>;


            virtual ~variadic_function() = default;

            virtual constexpr result_t operator()(const args_t& args) const = 0; 


        };


        template <typename T>
        struct identity : public unary_function<T, T> {

            using result_t = T;

            using arg_t = T;

            constexpr T operator()(const T& x) const noexcept override { 
                
                return x; 
                
            }

        };


    } // namespace functions


} // namespace scipp::math