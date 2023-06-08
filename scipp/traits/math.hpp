/**
 * @file    traits/math.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the type traits for the scipp::math namespace
 * @date    2023-05-28
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
        struct is_number<long unsigned int> : std::true_type {};

        template <>
        struct is_number<unsigned long long> : std::true_type {};


        template <typename T>
        inline static constexpr bool is_number_v = is_number<T>::value; 

        template <typename... Ts>
        struct are_numbers : std::conjunction<is_number<Ts>...> {}; 

        template <typename... Ts>
        inline static constexpr bool are_numbers_v = are_numbers<Ts...>::value; 


        template <typename T>
            requires (is_number_v<T>)
        inline static constexpr bool is_finite(const T& x) {
            
            return std::isfinite(x);

        }


        template <typename T>
        inline static constexpr bool is_finite(const T& x) {

            return std::isfinite(x.value);
            
        }




    /// =============================================
    /// @brief complex traits
    /// =============================================

        template <typename T> 
        struct complex {};


        /// @brief Type trait to check if a type is a measurement
        template <typename T>
        struct is_complex : std::false_type {};

        template <typename T>
        struct is_complex<complex<T>> : std::true_type {};

        template <typename CMEAS_TYPE>
        inline static constexpr bool is_complex_v = is_complex<CMEAS_TYPE>::value;

        template <typename... CMEAS_TYPES>
        struct are_complex : std::conjunction<is_complex<CMEAS_TYPES>...> {};

        template <typename... CMEAS_TYPES>
        inline static constexpr bool are_complex_v = are_complex<CMEAS_TYPES...>::value;



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

        template <typename T>
        inline static constexpr bool is_unary_function_v = is_unary_function<T>::value; 
        
        template <typename... Ts>
        inline static constexpr bool are_unary_functions_v = std::conjunction_v<is_unary_function<Ts>...>;



        template <typename ARG_TYPE1, typename ARG_TYPE2, typename RESULT_TYPE>
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


    
        template <typename T>
        struct negate;


        template <typename T>
        struct invert;

        template <typename T>
        using invert_t = typename invert<T>::function_t::result_t;  


        template <typename T>
        struct modulo; 

        template <typename T>
        using modulo_t = typename modulo<T>::result_t;


        template <typename ARG_TYPE1, typename ARG_TYPE2 = ARG_TYPE1>
        struct add;

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        using add_t = typename add<ARG_TYPE1, ARG_TYPE2>::function_t::result_t;


        template <typename ARG_TYPE1, typename ARG_TYPE2>
        struct multiply; 

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        using multiply_t = typename multiply<ARG_TYPE1, ARG_TYPE2>::function_t::result_t;
    

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        struct divide : multiply<ARG_TYPE1, invert_t<ARG_TYPE2>> {};

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        using divide_t = typename divide<ARG_TYPE1, ARG_TYPE2>::function_t::result_t;
    

        template <size_t POWER, typename T>
        struct power; 

        template <typename T>
        using square = power<2, T>;

        template <typename T>
        using cube = power<3, T>;

        template <size_t POWER, typename T>
        using power_t = typename power<POWER, T>::function_t::result_t; 

        template <typename T>
        using square_t = square<T>;

        template <typename T>
        using cube_t = cube<T>;


        template <size_t POWER, typename T>
        struct root; 

        template <size_t POWER, typename T>
        using root_t = typename root<POWER, T>::result_t; 


        template <typename T>
        using sqrt_t = root_t<2, T>;

        template <typename T>
        using cbrt_t = root_t<3, T>;


        template <typename T>
        struct exponential;

        template <typename T>
        struct logarithm;


        template <typename T>
        struct sine;

        template <typename T>
        struct cosine;

        template <typename T>
        struct tangent;


        template <typename T>
        struct cosecant;
        
        template <typename T>
        struct secant;
                
        template <typename T>
        struct cotangent;
                

        template <typename T>
        struct arcsine;

        template <typename T>
        struct arccosine;

        template <typename T>
        struct arctangent;


        template <typename T>
        struct arccosecant;
        
        template <typename T>
        struct arcsecant;
                
        template <typename T>
        struct arccotangent;
        

        template <typename T>
        struct hyperbolic_sine;

        template <typename T>
        struct hyperbolic_cosine; 

        template <typename T>
        struct hyperbolic_tangent;


        template <typename T>
        struct hyperbolic_cosecant;

        template <typename T>
        struct hyperbolic_secant;
        
        template <typename T>
        struct hyperbolic_cotangent;
        


        template <typename ARG_TYPE>
        struct round;


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