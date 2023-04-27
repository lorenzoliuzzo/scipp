/**
 * @file    math/calculus/function.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-25
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace meta {


        template <typename RESULT_TYPE, typename ARG_TYPE>
        struct unary_function {


            using _t = unary_function<RESULT_TYPE, ARG_TYPE>; 

            using result_t = RESULT_TYPE;

            using arg_t = ARG_TYPE;


            virtual constexpr result_t f(const arg_t& x) const = 0;


            inline constexpr result_t operator()(const arg_t& x) const { 

                return f(x); 
            
            }


        };


        template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2 = ARG_TYPE1>
        struct binary_function {


            using _t = binary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2>; 

            using result_t = RESULT_TYPE;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            virtual constexpr result_t f(const first_arg_t&, const second_arg_t&) const = 0;



            inline constexpr result_t operator()(const first_arg_t& x, const second_arg_t& y) const { 

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

            virtual constexpr result_t operator()(const first_arg_t& x, const second_arg_t& y, const third_arg_t& z) const = 0; 


        };


        template <typename RESULT_TYPE, std::size_t DIM, typename... ARG_TYPEs> 
            requires (sizeof...(ARG_TYPEs) == DIM)
        struct nary_function {


            using _t = nary_function<RESULT_TYPE, DIM, ARG_TYPEs...>; 

            using result_t = RESULT_TYPE;

            using arg_t = std::tuple<ARG_TYPEs...>;


            virtual constexpr result_t f(const ARG_TYPEs&... x) const = 0;


            inline constexpr result_t operator()(const ARG_TYPEs&... x) const { 

                return f(x...); 
            
            }


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
        struct identity : unary_function<T, T> {

            using result_t = T;

            using arg_t = T;

            constexpr T f(const T& x) const noexcept override { 
                
                return x; 
                
            }

        };


        template <typename T>
        struct one : unary_function<int, T> {

            using result_t = int;

            using arg_t = T;

            constexpr result_t f([[maybe_unused]] const arg_t&) const noexcept override { 
                
                return 1; 
                
            }

        };


    } // namespace meta


} // namespace scipp::math