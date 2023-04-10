/**
 * @file    math/calculus/function_traits.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {


    namespace functions {

        
        template <typename T>
        struct is_function : public std::false_type {};

        template <typename RESULT_TYPE, typename ARG_TYPE>
        struct is_function<unary_function<RESULT_TYPE, ARG_TYPE>> : public std::true_type {};

        template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2>
        struct is_function<binary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2>> : public std::true_type {};

        template <typename RESULT_TYPE, typename ARG_TYPE, std::size_t DIM>
        struct is_function<nary_function<RESULT_TYPE, ARG_TYPE, DIM>> : public std::true_type {};

        template <typename RESULT_TYPE, typename... ARG_TYPEs>
        struct is_function<variadic_function<RESULT_TYPE, ARG_TYPEs...>> : public std::true_type {};

        template <typename T>
        inline static constexpr bool is_function_v = is_function<T>::value;

        
        template <typename T>
        struct is_unary_function : public std::false_type {};

        template <typename RESULT_TYPE, typename ARG_TYPE>
        struct is_unary_function<unary_function<RESULT_TYPE, ARG_TYPE>> : public std::true_type {};

        template <typename T>
        inline static constexpr bool is_unary_function_v = is_unary_function<T>::value; 


        template <typename T>
        struct is_binary_function : public std::false_type {};

        template <typename RESULT_TYPE, typename ARG_TYPE>
        struct is_binary_function<binary_function<RESULT_TYPE, ARG_TYPE>> : public std::true_type {};

        template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2>
        struct is_binary_function<binary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2>> : public std::true_type {};

        template <typename T>
        inline static constexpr bool is_binary_function_v = is_binary_function<T>::value; 


        template <typename T>
        struct is_nary_function : public std::false_type {};

        template <typename RESULT_TYPE, typename ARG_TYPE, std::size_t DIM>
        struct is_nary_function<nary_function<RESULT_TYPE, ARG_TYPE, DIM>> : public std::true_type {};
        
        template <typename T>
        inline static constexpr bool is_nary_function_v = is_nary_function<T>::value; 


        template <typename T>
        struct is_variadic_function : public std::false_type {};

        template <typename RESULT_TYPE, typename... ARG_TYPEs>
        struct is_variadic_function<nary_function<RESULT_TYPE, ARG_TYPEs...>> : public std::true_type {};

        template <typename T>
        inline static constexpr bool is_variadic_function_v = is_variadic_function<T>::value; 


    } // namespace functions
    

} // namespace scipp::math