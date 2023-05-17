/**
 * @file    traits/math.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the type traits for the scipp::math namespace
 * @date    2023-05-17
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {


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


    // =============================================
    // functions traits
    // =============================================

    namespace functions {


        template <typename ARG_TYPE, typename RESULT_TYPE>
        struct unary_function; 

        template <typename T>
        struct is_unary_function : std::false_type {};

        template <typename ARG_TYPE, typename RESULT_TYPE>
        struct is_unary_function<unary_function<ARG_TYPE, RESULT_TYPE>> : std::true_type {};

        template <typename FUNC>
        inline static constexpr bool is_unary_function_v = is_unary_function<typename FUNC::_t>::value; 


        template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2>
        struct binary_function; 

        template <typename T>
        struct is_binary_function : std::false_type {};

        template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2>
        struct is_binary_function<binary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_binary_function_v = is_binary_function<T>::value; 


        template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2, typename ARG_TYPE3>
        struct ternary_function; 
        
        template <typename T>
        struct is_ternary_function : std::false_type {};

        template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2, typename ARG_TYPE3>
        struct is_ternary_function<ternary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2, ARG_TYPE3>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_ternary_function_v = is_ternary_function<T>::value; 


        template <typename RESULT_TYPE, size_t DIM, typename... ARG_TYPEs> 
            requires (sizeof...(ARG_TYPEs) == DIM)
        struct nary_function;

        template <typename T>
        struct is_nary_function : std::false_type {};

        template <typename RESULT_TYPE, size_t DIM, typename... ARG_TYPEs>
        struct is_nary_function<nary_function<RESULT_TYPE, DIM, ARG_TYPEs...>> : std::true_type {};
        
        template <typename T>
        inline static constexpr bool is_nary_function_v = is_nary_function<T>::value; 



        template <typename ARG_TYPE1, typename ARG_TYPE2 = ARG_TYPE1>
        struct add; 

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        using add_t = typename add<ARG_TYPE1, ARG_TYPE2>::result_t;


        template <typename ARG_TYPE1, typename ARG_TYPE2 = ARG_TYPE1>
        struct subtract; 

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        using subtract_t = typename subtract<ARG_TYPE1, ARG_TYPE2>::result_t;


        template <typename ARG_TYPE>
        struct negate; 

        template <typename ARG_TYPE>
        using negate_t = ARG_TYPE;


        template <typename ARG_TYPE1, typename ARG_TYPE2>
        struct multiply; 

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        using multiply_t = typename multiply<ARG_TYPE1, ARG_TYPE2>::result_t;
    

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        struct divide; 

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        using divide_t = typename divide<ARG_TYPE1, ARG_TYPE2>::result_t;
    
    
        template <typename T>
        struct invert;

        template <typename T>
        using invert_t = typename invert<T>::result_t;  


        template <size_t POWER, typename T>
        struct power; 

        template <size_t POWER, typename T>
        using power_t = typename power<POWER, T>::result_t; 


        template <typename T>
        using square_t = power_t<2, T>;

        template <typename T>
        using cube_t = power_t<3, T>;

        
        template <size_t POWER, typename T>
        struct root; 

        template <size_t POWER, typename T>
        using root_t = typename root<POWER, T>::result_t; 


        template <typename T>
        using sqrt_t = root_t<2, T>;

        template <typename T>
        using cbrt_t = root_t<3, T>;


    }


    // =============================================
    // calculus traits
    // =============================================

        template <typename T>
        struct interval; 

        template <typename T>
        struct is_interval : std::false_type {};

        template <typename T>
        struct is_interval<interval<T>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_interval_v = is_interval<T>::value;


} /// namespace scipp::math