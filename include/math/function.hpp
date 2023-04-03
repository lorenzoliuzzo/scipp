/**
 * @file    math/function.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-10
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {


    template <typename RESULT_TYPE, typename ARG_TYPE>
    struct unary_function {

        using type = unary_function<RESULT_TYPE, ARG_TYPE>; 

        using result_t = RESULT_TYPE;

        using argument_t = ARG_TYPE;

        virtual ~unary_function() = default;

        virtual constexpr result_t operator()(const argument_t& x) const noexcept = 0;

    };

    template <typename T>
    struct is_unary_function : public std::false_type {};

    template <typename RESULT_TYPE, typename ARG_TYPE>
    struct is_unary_function<unary_function<RESULT_TYPE, ARG_TYPE>> : public std::true_type {};

    template <typename T>
    inline static constexpr bool is_unary_function_v = is_unary_function<T>::value; 



    template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2 = ARG_TYPE1>
    struct binary_function {

        using type = binary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2>; 

        using result_t = RESULT_TYPE;

        using first_argument_t = ARG_TYPE1;

        using second_argument_t = ARG_TYPE2;

        virtual ~binary_function() = default;

        virtual constexpr result_t operator()(const first_argument_t& x, const second_argument_t& y) const noexcept = 0;

    };

    template <typename T>
    struct is_binary_function : public std::false_type {};

    template <typename RESULT_TYPE, typename ARG_TYPE>
    struct is_binary_function<binary_function<RESULT_TYPE, ARG_TYPE>> : public std::true_type {};

    template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2>
    struct is_binary_function<binary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2>> : public std::true_type {};

    template <typename T>
    inline static constexpr bool is_binary_function_v = is_binary_function<T>::value; 


    // template <typename MEAS_TYPE>
    // struct binary_operator : public binary_function<MEAS_TYPE, MEAS_TYPE> {

    //     using result_t = MEAS_TYPE;

    //     using first_argument_t = MEAS_TYPE;

    //     using second_argument_t = MEAS_TYPE;

    //     virtual ~binary_operator() = default;

    //     virtual constexpr MEAS_TYPE operator()(const MEAS_TYPE& x, const MEAS_TYPE& y) const noexcept = 0;

    // };


    // template <typename MEAS_TYPE>
    // struct binary_predicate : public binary_function<bool, MEAS_TYPE> {

    //     using result_t = bool;

    //     using first_argument_t = MEAS_TYPE;

    //     using second_argument_t = MEAS_TYPE;

    //     virtual ~binary_predicate() = default;

    //     virtual constexpr bool operator()(const MEAS_TYPE& x, const MEAS_TYPE& y) const noexcept = 0;

    // };


    // template <typename MEAS_TYPE>
    // struct unary_operator : public unary_function<MEAS_TYPE, MEAS_TYPE> {

    //     using result_t = MEAS_TYPE;

    //     using argument_t = MEAS_TYPE;

    //     virtual ~unary_operator() = default;

    //     virtual constexpr MEAS_TYPE operator()(const MEAS_TYPE& x) const noexcept = 0;

    // };


    // template <typename MEAS_TYPE>
    // struct unary_predicate : public unary_function<bool, MEAS_TYPE> {

    //     using result_t = bool;

    //     using argument_t = MEAS_TYPE;

    //     virtual ~unary_predicate() = default;

    //     virtual constexpr bool operator()(const MEAS_TYPE& x) const noexcept = 0;

    // };


} // namespace scipp::math