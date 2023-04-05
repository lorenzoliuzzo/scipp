/**
 * @file    math/function.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-05
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {



    /// @brief Tuple constructed from a fixed size and a list of types 
    template <size_t N, typename... Ts>
    struct types_tuple {

        using type = std::tuple<Ts...>;
        using size = std::integral_constant<std::size_t, N>;

    };


    /// @brief Tuple constructed from a fixed size and single type
    template <size_t N, typename T>
    struct types_tuple<N, T> {

        template <std::size_t... Is>
        static auto create_tuple(std::index_sequence<Is...>) {

            // Create a tuple with N copies of T
            return std::make_tuple((static_cast<void>(Is), T{})...);

        }

        using type = decltype(create_tuple(std::make_index_sequence<N>{}));
        using size = std::integral_constant<std::size_t, N>;

    };


    template <size_t N, typename... Ts>
    using types_tuple_t = typename types_tuple<N, Ts...>::type;



    template <typename RESULT_TYPE, typename ARG_TYPE>
    struct unary_function {

        using type = unary_function<RESULT_TYPE, ARG_TYPE>; 

        using result_t = RESULT_TYPE;

        using arg_t = ARG_TYPE;

        virtual ~unary_function() = default;

        virtual constexpr result_t operator()(const arg_t& x) const = 0; 

    };


    template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2 = ARG_TYPE1>
    struct binary_function {

        using type = binary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2>; 

        using result_t = RESULT_TYPE;

        using first_arg_t = ARG_TYPE1;

        using second_arg_t = ARG_TYPE2;

        virtual ~binary_function() = default;

        virtual constexpr result_t operator()(const first_arg_t& x, const second_arg_t& y) const = 0; 

    };


    template <typename RESULT_TYPE, typename ARG_TYPE, std::size_t DIM> 
    struct nary_function {


        using type = nary_function<RESULT_TYPE, ARG_TYPE, DIM>; 

        using result_t = RESULT_TYPE;

        using arg_t = geometry::vector<ARG_TYPE, DIM>;

        using args_t = ARG_TYPE;


        inline static constexpr std::size_t dimension = DIM; 


        virtual ~nary_function() = default;

        constexpr result_t operator()(const geometry::vector<ARG_TYPE, DIM>& x) const {} 


    };


    // template <typename RESULT_TYPE, typename SINGLE_ARG_TYPE, std::size_t N>
    // struct nary_function<RESULT_TYPE, SINGLE_ARG_TYPE> {

    //     using type = nary_function<RESULT_TYPE, SINGLE_ARG_TYPE, N>; 

    //     using result_t = RESULT_TYPE;

    //     using args_t = std::array<SINGLE_ARG_TYPE, N>;

    // }; 



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

    template <typename RESULT_TYPE, typename... ARG_TYPEs>
    struct is_nary_function<nary_function<RESULT_TYPE, ARG_TYPEs...>> : public std::true_type {};

    template <typename T>
    inline static constexpr bool is_nary_function_v = is_nary_function<T>::value; 



    // template <typename MEAS_TYPE>
    // struct binary_operator : public binary_function<MEAS_TYPE, MEAS_TYPE> {

    //     using result_t = MEAS_TYPE;

    //     using first_arg_t = MEAS_TYPE;

    //     using second_arg_t = MEAS_TYPE;

    //     virtual ~binary_operator() = default;

    //     virtual constexpr MEAS_TYPE operator()(const MEAS_TYPE& x, const MEAS_TYPE& y) const noexcept = 0;

    // };


    // template <typename MEAS_TYPE>
    // struct binary_predicate : public binary_function<bool, MEAS_TYPE> {

    //     using result_t = bool;

    //     using first_arg_t = MEAS_TYPE;

    //     using second_arg_t = MEAS_TYPE;

    //     virtual ~binary_predicate() = default;

    //     virtual constexpr bool operator()(const MEAS_TYPE& x, const MEAS_TYPE& y) const noexcept = 0;

    // };


    // template <typename MEAS_TYPE>
    // struct unary_operator : public unary_function<MEAS_TYPE, MEAS_TYPE> {

    //     using result_t = MEAS_TYPE;

    //     using arg_t = MEAS_TYPE;

    //     virtual ~unary_operator() = default;

    //     virtual constexpr MEAS_TYPE operator()(const MEAS_TYPE& x) const noexcept = 0;

    // };


    // template <typename MEAS_TYPE>
    // struct unary_predicate : public unary_function<bool, MEAS_TYPE> {

    //     using result_t = bool;

    //     using arg_t = MEAS_TYPE;

    //     virtual ~unary_predicate() = default;

    //     virtual constexpr bool operator()(const MEAS_TYPE& x) const noexcept = 0;

    // };


} // namespace scipp::math