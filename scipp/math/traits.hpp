/**
 * @file    math/traits.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the type traits for the scipp::math namespace
 * @date    2023-04-25
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {


    // =============================================
    // common traits
    // =============================================

    namespace meta {

        // =============================================
        // unary function traits
        // =============================================

            template <typename RESULT_TYPE, typename ARG_TYPE>
            struct unary_function; 
            

            template <typename T>
            struct is_unary_function : std::false_type {};

            template <typename RESULT_TYPE, typename ARG_TYPE>
            struct is_unary_function<unary_function<RESULT_TYPE, ARG_TYPE>> : std::true_type {};

            template <typename FUNC>
            inline static constexpr bool is_unary_function_v = is_unary_function<typename FUNC::_t>::value; 


        // =============================================
        // binary function traits
        // =============================================

            template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2>
            struct binary_function; 
            

            template <typename T>
            struct is_binary_function : std::false_type {};

            template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2>
            struct is_binary_function<binary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2>> : std::true_type {};

            template <typename T>
            inline static constexpr bool is_binary_function_v = is_binary_function<T>::value; 


        // =============================================
        // ternary function traits
        // =============================================

            template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2, typename ARG_TYPE3>
            struct ternary_function; 
            

            template <typename T>
            struct is_ternary_function : std::false_type {};

            template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2, typename ARG_TYPE3>
            struct is_ternary_function<ternary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2, ARG_TYPE3>> : std::true_type {};

            template <typename T>
            inline static constexpr bool is_ternary_function_v = is_ternary_function<T>::value; 


        // =============================================
        // nary function traits
        // =============================================

            template <typename RESULT_TYPE, std::size_t DIM, typename... ARG_TYPEs> 
                requires (sizeof...(ARG_TYPEs) == DIM)
            struct nary_function;


            template <typename T>
            struct is_nary_function : std::false_type {};

            template <typename RESULT_TYPE, std::size_t DIM, typename... ARG_TYPEs>
            struct is_nary_function<nary_function<RESULT_TYPE, DIM, ARG_TYPEs...>> : std::true_type {};
            
            template <typename T>
            inline static constexpr bool is_nary_function_v = is_nary_function<T>::value; 


        // =============================================
        // variadic function traits
        // =============================================

            template <typename RESULT_TYPE, typename... ARG_TYPES>
            struct variadic_function;


            template <typename T>
            struct is_variadic_function : std::false_type {};

            template <typename RESULT_TYPE, typename... ARG_TYPEs>
            struct is_variadic_function<variadic_function<RESULT_TYPE, ARG_TYPEs...>> : std::true_type {};

            template <typename T>
            inline static constexpr bool is_variadic_function_v = is_variadic_function<T>::value; 


        // =============================================
        // generic function traits
        // =============================================

            template <typename T>
            struct is_function : std::false_type {};

            template <typename RESULT_TYPE, typename ARG_TYPE>
            struct is_function<unary_function<RESULT_TYPE, ARG_TYPE>> : std::true_type {};

            template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2>
            struct is_function<binary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2>> : std::true_type {};
            
            template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2, typename ARG_TYPE3>
            struct is_function<ternary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2, ARG_TYPE3>> : std::true_type {};

            template <typename RESULT_TYPE, std::size_t DIM, typename... ARG_TYPEs>
            struct is_function<nary_function<RESULT_TYPE, DIM, ARG_TYPEs...>> : std::true_type {};

            template <typename RESULT_TYPE, typename... ARG_TYPEs>
            struct is_function<variadic_function<RESULT_TYPE, ARG_TYPEs...>> : std::true_type {};

            template <typename T>
            inline static constexpr bool is_function_v = is_function<T>::value;


    } // namespace meta


    // =============================================
    // number traits
    // =============================================

        template <typename T>
        struct is_number : std::false_type {}; 

        template <typename T>
        inline static constexpr bool is_number_v = is_number<T>::value; 

        template <typename... Ts>
        struct are_numbers : std::conjunction<is_number<Ts>...> {}; 

        template <typename... Ts>
        inline static constexpr bool are_numbers_v = are_numbers<Ts...>::value; 


        template <>
        struct is_number<int> : std::true_type {};

        template <>
        struct is_number<float> : std::true_type {};

        template <>
        struct is_number<double> : std::true_type {};

        template <>
        struct is_number<long double> : std::true_type {};

        template <>
        struct is_number<unsigned int> : std::true_type {};

        template <>
        struct is_number<unsigned long> : std::true_type {};

        template <>
        struct is_number<unsigned long long> : std::true_type {};


        template <typename T>
        struct is_scalar : std::conditional_t<is_number_v<T> || 
                                              physics::is_scalar_base_v<T> || 
                                              physics::is_scalar_unit_v<T> || 
                                              physics::is_scalar_measurement_v<T> ||
                                              physics::is_scalar_umeasurement_v<T> ||
                                              physics::is_scalar_cmeasurement_v<T>, std::true_type, std::false_type> {}; 

        template <typename T>
        inline static constexpr bool is_scalar_v = is_scalar<T>::value; 


    namespace op {


        template <typename T>
        inline static constexpr auto abs(const T&) noexcept;

        template <typename T>
        inline static constexpr auto inv(const T&);

        template <typename T, typename U>
        inline static constexpr auto pow(const T&, const U&) noexcept;

        template <uint POWER, typename T>
        inline static constexpr auto pow(const T&) noexcept;

        template <typename T>
        inline static constexpr auto square(const T&) noexcept;   

        template <typename T>
        inline static constexpr auto cube(const T&) noexcept;


        template <typename T, typename POWER>
        inline static constexpr auto root(const T&, const POWER&);

        template <typename T>
        inline static constexpr auto sqrt(const T&);

        template <typename T>
        inline static constexpr auto cbrt(const T&);
        

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T exp(const T&) noexcept;

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T log(const T&);


        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T sin(const T&) noexcept;

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T cos(const T&) noexcept;

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T tan(const T&) noexcept;

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T sinh(const T&) noexcept;

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T cosh(const T&) noexcept;

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T tanh(const T&) noexcept;


        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T asin(const T&) noexcept;

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T acos(const T&) noexcept;

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T atan(const T&) noexcept;

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr auto atan(const T&, const T&) noexcept; 

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T asinh(const T&) noexcept;

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T acosh(const T&) noexcept;

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T atanh(const T&) noexcept;


        template <typename T>
        inline static constexpr auto norm(const T&) noexcept; 

        template <typename T>
        inline static constexpr auto norm2(const T&) noexcept; 

        template <typename T>
        inline static constexpr auto normalize(const T&) noexcept; 


    } // namespace op


    template <typename POINT_TYPE>
    struct interval; 


    template <typename T>
    struct is_interval : std::false_type {};

    template <typename ARG_TYPE>
    struct is_interval<interval<ARG_TYPE>> : std::true_type {};

    template <typename T>
    inline static constexpr bool is_interval_v = is_interval<T>::value;


    template <typename POINT_TYPE>
        requires (geometry::is_vector_v<POINT_TYPE> || physics::is_cmeasurement_v<POINT_TYPE>)
    struct curve; 

    template <typename T>
    struct is_curve : std::false_type {};

    template <typename POINT_TYPE>
    struct is_curve<curve<POINT_TYPE>> : std::true_type {};

    template <typename T>
    inline static constexpr bool is_curve_v = is_curve<typename T::_t>::value;


    namespace integrals {


        enum integration_method {

            rectangle = 0,
            trapexoid = 1, 
            midpoint = 2, 
            simpson = 3,
            // MC = 4
            
        }; 


        template <typename FUNCTION_TYPE, std::size_t steps> 
            requires (meta::is_unary_function_v<FUNCTION_TYPE>)
        inline static constexpr auto curvilinear(const FUNCTION_TYPE&, 
                                                 const curve<typename FUNCTION_TYPE::arg_t>&,
                                                 double); 


    } // namespace integrals


} /// namespace scipp::math