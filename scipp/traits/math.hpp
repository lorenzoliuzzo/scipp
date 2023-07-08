/**
 * @file    traits/math.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the type traits for the scipp::math namespace
 * @date    2023-07-03
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


    /// =============================================
    /// @brief complex numbers traits
    /// =============================================

        template <typename T> 
        struct complex;

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


    /// =============================================
    /// @brief dual numbers traits
    /// =============================================

        template <typename T> 
        struct dual;

        template <typename T>
        dual(T) -> dual<T>;

        template <typename T>
        dual(T, T) -> dual<T>;


        /// @brief Type trait to check if a type is a dual number
        template <typename T>
        struct is_dual : std::false_type {};

        template <typename MEAS_TYPE>
        struct is_dual<dual<MEAS_TYPE>> : std::true_type {};

        template <typename T>
        inline constexpr bool is_dual_v = is_dual<T>::value;


        /// @brief Type trait to check if a set of types are all dual numbers
        template <typename... MEAS_TYPES>
        struct are_duals : std::conjunction<is_dual<MEAS_TYPES>...>{};

        template <typename... MEAS_TYPES>
        inline constexpr bool are_duals_v = are_duals<MEAS_TYPES...>::value;



    /// =============================================
    /// @brief generic numbers traits
    /// =============================================

        /// @brief Type trait to check if a type is a generic number
        template <typename T>
        struct is_generic_number : std::conditional_t<is_number_v<T> || is_complex_v<T> || is_dual_v<T>, 
                                                      std::true_type, 
                                                      std::false_type> {};

        template <typename T>
        inline static constexpr bool is_generic_number_v = is_generic_number<T>::value;

        template <typename... MEAS_TYPES>
        struct are_generic_numbers : std::conjunction<is_generic_number<MEAS_TYPES>...> {};

        template <typename... Ts>
        inline static constexpr bool are_generic_number_v = are_generic_numbers<Ts...>::value;


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
    /// @brief functions traits
    /// =============================================


    namespace calculus {
                

        template <typename T>
        struct expr;
        
        template <typename T>
        using expr_ptr = std::shared_ptr<expr<T>>;


        template <typename T>
        struct is_expr : std::false_type {}; 

        template <typename T>
        struct is_expr<expr<T>> : std::true_type {}; 

        template <typename T>
        inline static constexpr bool is_expr_v = is_expr<T>::value; 


        template <typename T>
        struct is_expr_ptr : std::false_type {}; 

        template <typename T>
        struct is_expr_ptr<expr_ptr<T>> : std::true_type {}; 

        template <typename T>
        inline static constexpr bool is_expr_ptr_v = is_expr_ptr<T>::value; 


        template <typename VALUE_T>
        struct variable; 

        template <typename T>
        struct is_variable : std::false_type {};

        template <typename T>
        struct is_variable<variable<T>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_variable_v = is_variable<T>::value; 

        template <typename... Ts>
        inline static constexpr bool are_variables_v = std::conjunction_v<is_variable<Ts>...>;


        // template <typename T>
        // struct variable_value_t; 

        // template <typename VALUE_T>
        // struct variable_value_t<variable<VALUE_T>> { 
            
        //     using type = VALUE_T; 
                    
        // };

        // template <typename T>
        // struct variable_value_t<expr_ptr<T>> { 
            
        //     using type = typename variable_value_t<T>::type; 
        
        // };

        template <typename T>
        struct variable_order { 
            
            constexpr static auto value = 0; 
        
        };

        template <typename VALUE_T>
        struct variable_order<variable<VALUE_T>> { 
            
            constexpr static auto value = 1 + variable_order<VALUE_T>::value; 
        
        };



        template <typename RANGE, typename... DOMAIN>
        struct function;

        template <typename T>
        struct is_function : std::false_type {};

        template <typename RANGE, typename... DOMAIN>
        struct is_function<function<RANGE, DOMAIN...>> : std::true_type {};

        template <typename RANGE, typename... DOMAIN>
        struct is_function<function<RANGE, DOMAIN...>&> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_function_v = is_function<T>::value;


        template <typename T>
        struct interval; 

        template <typename T>
        struct is_interval : std::false_type {};

        template <typename T>
        struct is_interval<interval<T>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_interval_v = is_interval<T>::value;


        template <typename T, typename... ARGs>
        struct curve; 

        template <typename T>
        struct is_curve : std::false_type {};

        template <typename T, typename... ARGs>
        struct is_curve<curve<T, ARGs...>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_curve_v = is_curve<typename T::curve_t>::value;


    } // namespace calculus


    namespace op {


        template <typename ARG_TYPE1, typename ARG_TYPE2>
        struct add_impl;

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        using add_t = typename add_impl<ARG_TYPE1, ARG_TYPE2>::result_t;

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto add(const ARG_TYPE1& x, const ARG_TYPE2& y) {
            
            return add_impl<ARG_TYPE1, ARG_TYPE2>::f(x, y); 

        }


        template <typename T>
        struct negate_impl;

        template <typename T>
        using negate_t = typename negate_impl<T>::result_t;  

        template <typename ARG_TYPE>
        inline static constexpr auto neg(const ARG_TYPE& x) noexcept {
            
            return negate_impl<ARG_TYPE>::f(x); 

        }


        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto sub(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {
            
            return add_impl<ARG_TYPE1, ARG_TYPE2>::f(x, negate_impl<ARG_TYPE2>::f(y)); 

        }


        template <typename ARG_TYPE1, typename ARG_TYPE2>
        struct multiply_impl;       

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        using multiply_t = typename multiply_impl<std::decay_t<ARG_TYPE1>, std::decay_t<ARG_TYPE2>>::result_t;
    
        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto mult(const ARG_TYPE1& x, const ARG_TYPE2& y) {
            
            return multiply_impl<ARG_TYPE1, ARG_TYPE2>::f(x, y); 

        }


        template <int ARG_TYPE1, typename ARG_TYPE2>
        struct power_impl; 

        template <int ARG_TYPE1, typename ARG_TYPE2>
        using power_t = typename power_impl<ARG_TYPE1, ARG_TYPE2>::result_t;

        template <int ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto pow(const ARG_TYPE2& x) {
            
            return power_impl<ARG_TYPE1, ARG_TYPE2>::f(x); 

        }

        template <typename ARG_TYPE>
        inline static constexpr auto square(const ARG_TYPE& x) {
            
            return pow<2>(x); 

        }

        template <typename ARG_TYPE>
        inline static constexpr auto cube(const ARG_TYPE& x) {
            
            return pow<3>(x); 

        }


        template <typename T>
        struct modulo_impl; 

        template <typename T>
        using modulo_t = typename modulo_impl<T>::result_t;

        template <typename ARG_TYPE>
        inline static constexpr auto abs(const ARG_TYPE& x) {
            
            return modulo_impl<ARG_TYPE>::f(x); 

        }


        template <typename T>
        struct invert_impl;

        template <typename T>
        using invert_t = typename invert_impl<T>::result_t;  

        template <typename ARG_TYPE>
        inline static constexpr auto inv(const ARG_TYPE& x) {
            
            return invert_impl<ARG_TYPE>::f(x); 

        }


        template <typename ARG_TYPE1, typename ARG_TYPE2>
        using divide_t = typename multiply_impl<ARG_TYPE1, invert_t<ARG_TYPE2>>::result_t;
    
        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto div(const ARG_TYPE1& x, const ARG_TYPE2& y) {
            
            return multiply_impl<ARG_TYPE1, invert_t<ARG_TYPE2>>::f(x, invert_impl<ARG_TYPE2>::f(y)); 

        }


        template <size_t ARG_TYPE1, typename ARG_TYPE2>
        struct root_impl; 

        template <size_t ARG_TYPE1, typename ARG_TYPE2>
        using root_t = typename root_impl<ARG_TYPE1, ARG_TYPE2>::result_t;

        template <size_t ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto root(const ARG_TYPE2& x) {
            
            return root_impl<ARG_TYPE1, ARG_TYPE2>::f(x); 

        }

        template <typename T> 
        inline static constexpr auto sqrt(const T& x) {
            
            return root<2>(x); 

        }

        template <typename T>
        inline static constexpr auto cbrt(const T& x) {
            
            return root<3>(x); 

        }

        
        template <typename T>
        struct exponential_impl;

        template <typename T>
        inline static constexpr auto exp(const T& x) noexcept {  

            return exponential_impl<T>::f(x);

        }


        template <typename T>
        struct logarithm_impl;
        
        template <typename T>
        inline static constexpr auto log(const T& x) {

            return logarithm_impl<T>::f(x);

        }


        template <typename T>
        struct sine_impl;

        template <typename T>   
        inline static constexpr auto sin(const T& x) {

            return sine_impl<T>::f(x); 

        }

        template <typename T>
        struct arcsine_impl;

        template <typename T>   
        inline static constexpr auto asin(const T& x) {

            return arcsine_impl<T>::f(x); 

        }


        template <typename T>
        struct cosine_impl;

        template <typename T>   
        inline static constexpr auto cos(const T& x) {

            return cosine_impl<T>::f(x); 

        }

        template <typename T>
        struct arccosine_impl;

        template <typename T>   
        inline static constexpr auto acos(const T& x) {

            return arccosine_impl<T>::f(x); 

        }


        template <typename T>
        struct tangent_impl;

        template <typename T>   
        inline static constexpr auto tan(const T& x) {

            return tangent_impl<T>::f(x); 

        }

        template <typename T>
        struct arctangent_impl;

        template <typename T>   
        inline static constexpr auto atan(const T& x) {

            return arctangent_impl<T>::f(x); 

        }

        template <typename T>
        struct arctangent2_impl;

        template <typename T>   
        inline static constexpr auto atan(const T& x, const T& y) {

            return arctangent2_impl<T>::f(x, y); 

        }


        template <typename T>
        struct sine_hyp_impl;

        template <typename T>
        inline static constexpr T sinh(const T& x) noexcept {
            
            return sine_hyp_impl<T>::f(x);

        }

        template <typename T>
        struct arcsine_hyp_impl;

        template <typename T>
        inline static constexpr T asinh(const T& x) noexcept {

            return arcsine_hyp_impl<T>::f(x);

        }


        template <typename T>
        struct cosine_hyp_impl; 

        template <typename T>
        inline static constexpr T cosh(const T& x) noexcept {
            
            return cosine_hyp_impl<T>::f(x);

        }

        template <typename T>
        struct arccosine_hyp_impl; 

        template <typename T>
        inline static constexpr T acosh(const T& x) noexcept {
            
            return arccosine_hyp_impl<T>::f(x);

        }


        template <typename T>
        struct tangent_hyp_impl;

        template <typename T>
        inline static constexpr T tanh(const T& x) noexcept {
            
            return tangent_hyp_impl<T>::f(x);

        }

        template <typename T>
        struct arctangent_hyp_impl;

        template <typename T>
        inline static constexpr T atanh(const T& x) noexcept {
            
            return arctangent_hyp_impl<T>::f(x);

        }


        template <typename T>
        struct cosecant_impl;

        template <typename T>
        inline static constexpr auto csc(const T& x) noexcept {

            return cosecant_impl<T>::f(x);

        }


        template <typename T>
        struct secant_impl;
                
        template <typename T>
        inline static constexpr auto sec(const T& x) noexcept {

            return secant_impl<T>::f(x);

        }


        template <typename T>
        struct cotangent_impl;

        template <typename T>
        inline static constexpr auto cot(const T& x) noexcept {

            return cotangent_impl<T>::f(x);

        }


        template <typename T>
        struct arccosecant_impl;
        
        template <typename T>
        inline static constexpr auto acsc(const T& x) noexcept {

            return arccosecant_impl<T>::f(x);

        }


        template <typename T>
        struct arcsecant_impl;

        template <typename T>
        inline static constexpr auto asec(const T& x) noexcept {

            return arcsecant_impl<T>::f(x);

        }


        template <typename T>
        struct arccotangent_impl;
        
        template <typename T>
        inline static constexpr auto acot(const T& x) noexcept {

            return arccotangent_impl<T>::f(x);

        }


        template <typename T>
        struct cosecant_hyp_impl;

        template <typename T>
        struct secant_hyp_impl;
        
        template <typename T>
        struct cotangent_hyp_impl;


    } // namespace op


    // namespace functions {


    //     template <typename ARG_TYPE, typename RESULT_TYPE, typename BACK_TYPE>
    //     struct unary_function;

    //     template <typename T>
    //     struct is_unary_function : std::false_type {};

    //     template <typename ARG_TYPE, typename RESULT_TYPE, typename BACK_TYPE>
    //     struct is_unary_function<unary_function<ARG_TYPE, RESULT_TYPE, BACK_TYPE>> : std::true_type {};

    //     template <typename T>
    //     inline static constexpr bool is_unary_function_v = is_unary_function<T>::value; 
        
    //     template <typename... Ts>
    //     inline static constexpr bool are_unary_functions_v = std::conjunction_v<is_unary_function<Ts>...>;



    //     template <typename ARG_TYPE1, typename ARG_TYPE2, typename RESULT_TYPE>
    //     struct binary_function;

    //     template <typename T>
    //     struct is_binary_function : std::false_type {};

    //     template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2>
    //     struct is_binary_function<binary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2>> : std::true_type {};

    //     template <typename T>
    //     inline static constexpr bool is_binary_function_v = is_binary_function<T>::value; 



    //     template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2, typename ARG_TYPE3>
    //     struct ternary_function;
        
    //     template <typename T>
    //     struct is_ternary_function : std::false_type {};

    //     template <typename RESULT_TYPE, typename ARG_TYPE1, typename ARG_TYPE2, typename ARG_TYPE3>
    //     struct is_ternary_function<ternary_function<RESULT_TYPE, ARG_TYPE1, ARG_TYPE2, ARG_TYPE3>> : std::true_type {};

    //     template <typename T>
    //     inline static constexpr bool is_ternary_function_v = is_ternary_function<T>::value; 


    //     template <typename RESULT_TYPE, size_t DIM, typename... ARG_TYPEs> 
    //     struct nary_function;

    //     template <typename T>
    //     struct is_nary_function : std::false_type {};

    //     template <typename RESULT_TYPE, size_t DIM, typename... ARG_TYPEs>
    //     struct is_nary_function<nary_function<RESULT_TYPE, DIM, ARG_TYPEs...>> : std::true_type {};
        
    //     template <typename T>
    //     inline static constexpr bool is_nary_function_v = is_nary_function<T>::value; 


    //     template <typename T1, typename T2>
    //     struct equal;


    //     template <typename T>
    //     struct greater;


    //     template <typename T>
    //     struct less;


    //     template <typename T>
    //     struct greater_equal;


    //     template <typename T>
    //     struct less_equal;


    //     template <typename T>
    //     struct sign; 


    //     template <typename T>
    //     struct exponential;

    //     template <typename T>
    //     struct logarithm;


    //     template <typename T>
    //     struct sine;

    //     template <typename T>
    //     struct cosine;

    //     template <typename T>
    //     struct tangent;    


    //     template <typename ARG_TYPE>
    //     struct round;


    // }


    /// =============================================
    /// @brief calculus traits
    /// =============================================

    // namespace curves {







    //     template <typename T>
    //     struct line; 

    //     template <typename T>
    //     struct is_line : std::false_type {};

    //     template <typename T>
    //     struct is_line<line<T>> : std::true_type {};

    //     template <typename T>
    //     inline static constexpr bool is_line_v = is_line<T>::value;


    //     template <typename T>
    //     struct circumference; 

    //     template <typename T>
    //     struct is_circumference : std::false_type {};

    //     template <typename T>
    //     struct is_circumference<circumference<T>> : std::true_type {};

    //     template <typename T>
    //     inline static constexpr bool is_circumference_v = is_circumference<T>::value;



    // } // namespace curves


} /// namespace scipp::math