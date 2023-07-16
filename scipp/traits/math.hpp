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


        template <typename T> 
        struct constant_expr; 

        template <typename T> 
        inline constexpr expr_ptr<T> constant(const T& val) { 
            
            return std::make_shared<constant_expr<T>>(val); 
            
        }


        template <typename T> 
        struct variable_expr; 

        template <typename T> 
        struct independent_variable_expr; 

        template <typename T> 
        struct dependent_variable_expr; 


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


        template <typename T>
            requires std::is_arithmetic_v<T>
        constexpr T expr_value(const T &t) {

            return t;

        }

        template <typename T>
        constexpr T expr_value(const expr_ptr<T> &t) {

            return t->val;

        }

        template <typename T>
        constexpr T expr_value(const variable<T> &t) {

            return t.expr->val;
            
        }

        template <typename T>
        inline constexpr auto val(const T &t) {

            return expr_value(t);

        }
        

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


        template <typename X, typename Y>
        struct curve; 

        template <typename T>
        struct is_curve : std::false_type {};

        template <typename X, typename Y>
        struct is_curve<curve<X, Y>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_curve_v = is_curve<typename T::curve_t>::value;


    } // namespace calculus


    namespace op {


        template <typename T1, typename T2>
        struct equal_impl;

        template <typename T1, typename T2>
        inline static constexpr bool equal(const T1& x, const T2& y) noexcept {
            
            return equal_impl<T1, T2>::f(x, y); 

        }


        template <typename T1, typename T2>
        struct greater_impl;

        template <typename T1, typename T2>
        inline static constexpr bool greater(const T1& x, const T2& y) noexcept {
            
            return greater_impl<T1, T2>::f(x, y); 

        }


        template <typename T1, typename T2>
        struct less_impl;

        template <typename T1, typename T2>
        inline static constexpr bool less(const T1& x, const T2& y) noexcept {
            
            return less_impl<T1, T2>::f(x, y); 

        }


        template <typename T1, typename T2>
        struct greater_equal_impl;

        template <typename T1, typename T2>
        inline static constexpr bool greater_equal(const T1& x, const T2& y) noexcept {
            
            return greater_equal_impl<T1, T2>::f(x, y); 

        }


        template <typename T1, typename T2>
        struct less_equal_impl;

        template <typename T1, typename T2>
        inline static constexpr bool less_equal(const T1& x, const T2& y) noexcept {
            
            return less_equal_impl<T1, T2>::f(x, y); 

        }


        template <typename T>
        struct negate_impl; 

        template <typename T>
        inline static constexpr auto neg(const T& x) noexcept {
            
            return negate_impl<T>::f(x); 

        }


        template <typename T1, typename T2>
        struct add_impl;

        template <typename T1, typename T2>
        using add_t = typename add_impl<T1, T2>::result_t;

        template <typename T1, typename T2>
        inline static constexpr auto add(const T1& x, const T2& y) noexcept {
            
            return add_impl<T1, T2>::f(x, y); 

        }


        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto sub(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {
            
            return add_impl<ARG_TYPE1, ARG_TYPE2>::f(x, negate_impl<ARG_TYPE2>::f(y)); 

        }


        template <typename T>
        struct invert_impl;

        template <typename T>
        using invert_t = typename invert_impl<T>::result_t;  

        template <typename T>
        inline static constexpr auto inv(const T& x) {
            
            return invert_impl<T>::f(x); 

        }


        template <typename T1, typename T2>
        struct multiply_impl;       

        template <typename T1, typename T2>
        using multiply_t = typename multiply_impl<T1, T2>::result_t;
    
        template <typename T1, typename T2>
        inline static constexpr auto mult(const T1& x, const T2& y) noexcept {
            
            return multiply_impl<T1, T2>::f(x, y); 

        }


        template <typename T1, typename T2>
        using divide_t = typename multiply_impl<T1, invert_t<T2>>::result_t;
    
        template <typename T1, typename T2>
        inline static constexpr auto div(const T1& x, const T2& y) {
            
            return multiply_impl<T1, invert_t<T2>>::f(x, invert_impl<T2>::f(y)); 

        }


        template <int T1, typename T2>
        struct power_impl; 

        template <int T1, typename T2>
        using power_t = typename power_impl<T1, T2>::result_t;

        template <int T1, typename T2>
        inline static constexpr auto pow(const T2& x) noexcept {
            
            return power_impl<T1, T2>::f(x); 

        }

        inline static constexpr auto square(const auto& x) noexcept {
            
            return pow<2>(x); 

        }

        inline static constexpr auto cube(const auto& x) noexcept {
            
            return pow<3>(x); 

        }


        template <size_t T1, typename T2>
        struct root_impl; 

        template <size_t T1, typename T2>
        using root_t = typename root_impl<T1, T2>::result_t;

        template <size_t T1, typename T2>
        inline static constexpr auto root(const T2& x) {
            
            return root_impl<T1, T2>::f(x); 

        }

        inline static constexpr auto sqrt(const auto& x) {
            
            return root<2>(x); 

        }

        inline static constexpr auto cbrt(const auto& x) {
            
            return root<3>(x); 

        }


        inline static constexpr auto hypot(const auto& x, const auto& y) noexcept {
            
            return sqrt(square(x) + square(y)); 

        }


        template <typename T>
        struct sign_impl; 

        template <typename T>
        inline static constexpr auto sign(const T& x) noexcept {
            
            return sign_impl<T>::f(x); 

        }


        template <typename T>
        struct absolute_impl; 

        template <typename T>
        using absolute_t = typename absolute_impl<T>::result_t;

        template <typename T>
        inline static constexpr auto abs(const T& x) noexcept {
            
            return absolute_impl<T>::f(x); 

        }


        template <typename T>
        struct norm_impl; 

        template <typename T>
        using norm_t = typename norm_impl<T>::result_t;

        template <typename T>
        inline static constexpr auto norm(const T& x) noexcept {
            
            return norm_impl<T>::f(x); 

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
        inline static constexpr auto sin(const T& x) noexcept {
            
            return sine_impl<T>::f(x); 

        }
        template <typename T>
        inline static constexpr auto csc(const T& x) noexcept {
            
            return invert_impl<T>::f(sine_impl<T>::f(x));

        }


        template <typename T>
        struct cosine_impl;

        template <typename T>
        inline static constexpr auto cos(const T& x) noexcept {
            
            return cosine_impl<T>::f(x); 

        }
        template <typename T>
        inline static constexpr auto sec(const T& x) noexcept {
            
            return invert_impl<T>::f(cosine_impl<T>::f(x));

        }


        template <typename T>
        struct tangent_impl; 
        
        template <typename T>
        inline static constexpr auto tan(const T& x) noexcept {
            
            return tangent_impl<T>::f(x); 

        }

        template <typename T>
        inline static constexpr auto cot(const T& x) noexcept {
            
            return invert_impl<T>::f(tangent_impl<T>::f(x));

        }


        template <typename T>
        struct arcsine_impl;

        template <typename T>
        inline static constexpr auto asin(const T& x) noexcept {
            
            return arcsine_impl<T>::f(x); 

        }


        template <typename T>
        struct arccosine_impl;

        template <typename T>
        inline static constexpr auto acos(const T& x) noexcept {
            
            return arccosine_impl<T>::f(x); 

        }


        template <typename T>
        struct arctangent_impl;

        template <typename T>
        inline static constexpr auto atan(const T& x) noexcept {
            
            return arctangent_impl<T>::f(x); 

        }


        template <typename T>
        struct hyperbolic_sine_impl;

        template <typename T>
        inline static constexpr auto sinh(const T& x) noexcept {
            
            return hyperbolic_sine_impl<T>::f(x); 

        }

        template <typename T>
        inline static constexpr auto csch(const T& x) noexcept {
            
            return invert_impl<T>::f(hyperbolic_sine_impl<T>::f(x));

        }


        template <typename T>
        struct hyperbolic_cosine_impl;

        template <typename T>
        inline static constexpr auto cosh(const T& x) noexcept {
            
            return hyperbolic_cosine_impl<T>::f(x); 

        }

        template <typename T>
        inline static constexpr auto sech(const T& x) noexcept {
            
            return invert_impl<T>::f(hyperbolic_cosine_impl<T>::f(x));

        }


        template <typename T>
        struct hyperbolic_tangent_impl;

        template <typename T>
        inline static constexpr auto tanh(const T& x) noexcept {
            
            return hyperbolic_tangent_impl<T>::f(x); 

        }

        template <typename T>
        inline static constexpr auto coth(const T& x) noexcept {
            
            return invert_impl<T>::f(hyperbolic_tangent_impl<T>::f(x));

        }


        template <typename T>
        struct hyperbolic_arcsine_impl;

        template <typename T>
        inline static constexpr auto asinh(const T& x) noexcept {
            
            return hyperbolic_arcsine_impl<T>::f(x); 

        }


        template <typename T>
        struct hyperbolic_arccosine_impl;

        template <typename T>
        inline static constexpr auto acosh(const T& x) noexcept {
            
            return hyperbolic_arccosine_impl<T>::f(x); 

        }


        template <typename T>
        struct hyperbolic_arctangent_impl;

        template <typename T>
        inline static constexpr auto atanh(const T& x) noexcept {
            
            return hyperbolic_arctangent_impl<T>::f(x); 

        }

        template <typename T>
        inline static constexpr auto acoth(const T& x) noexcept {
            
            return 0.5 * log((x + static_cast<T>(1.0)) / (x - static_cast<T>(1.0)));

        }


        template <typename T>
        inline static constexpr auto asech(const T& x) noexcept {
            
            return log((static_cast<T>(1.0) + sqrt(static_cast<T>(1.0) - square(x))) / x);

        }

        template <typename T>
        inline static constexpr auto acsch(const T& x) noexcept {
            
            return log((static_cast<T>(1.0) + hypot(static_cast<T>(1.0), x)) / x);

        }


        template <typename T>
        struct erf_impl;

        template <typename T>
        inline static constexpr auto erf(const T& x) noexcept {
            
            return erf_impl<T>::f(x); 

        }


        template <typename T>
        struct erfc_impl;

        template <typename T>
        inline static constexpr auto erfc(const T& x) noexcept {
            
            return erfc_impl<T>::f(x); 

        }


        template <typename T>
        struct gamma_impl;

        template <typename T>
        inline static constexpr auto gamma(const T& x) noexcept {
            
            return gamma_impl<T>::f(x); 

        }


        // template <typename T>
        // struct lgamma_impl;

        // template <typename T>
        // inline static constexpr auto lgamma(const T& x) {
            
        //     return lgamma_impl<T>::f(x); 

        // }


        // template <typename T>
        // struct digamma_impl;

        // template <typename T>
        // inline static constexpr auto digamma(const T& x) {
            
        //     return digamma_impl<T>::f(x); 

        // }


        // template <typename T>
        // struct trigamma_impl;

        // template <typename T>
        // inline static constexpr auto trigamma(const T& x) {
            
        //     return trigamma_impl<T>::f(x); 

        // }


        // template <typename T>
        // struct beta_impl;

        // template <typename T>
        // inline static constexpr auto beta(const T& x, const T& y) {
            
        //     return beta_impl<T>::f(x, y); 

        // }


        // template <typename T>
        // struct zeta_impl;

        // template <typename T>
        // inline static constexpr auto zeta(const T& x, const T& y) {
            
        //     return zeta_impl<T>::f(x, y); 

        // }


        // template <typename T>
        // struct polygamma_impl;

        // template <typename T>
        // inline static constexpr auto polygamma(const T& x, const T& y) {
            
        //     return polygamma_impl<T>::f(x, y); 

        // }


        // template <typename T>
        // struct binomial_impl;

        // template <typename T>
        // inline static constexpr auto binomial(const T& x, const T& y) {
            
        //     return binomial_impl<T>::f(x, y); 

        // }


        // template <typename T>
        // struct bernoulli_impl;

        // template <typename T>
        // inline static constexpr auto bernoulli(const T& x) {
            
        //     return bernoulli_impl<T>::f(x); 

        // }


        // template <typename T>
        // struct harmonic_impl;

        // template <typename T>
        // inline static constexpr auto harmonic(const T& x) {
            
        //     return harmonic_impl<T>::f(x); 

        // }


        // template <typename T>
        // struct euler_impl;

        // template <typename T>
        // inline static constexpr auto euler(const T& x) {
            
        //     return euler_impl<T>::f(x); 

        // }


        // template <typename T>
        // struct catalan_impl;

        // template <typename T>
        // inline static constexpr auto catalan(const T& x) {
            
        //     return catalan_impl<T>::f(x); 

        // }


        // template <typename T>
        // struct riemann_zeta_impl;

        // template <typename T>
        // inline static constexpr auto riemann_zeta(const T& x) {
            
        //     return riemann_zeta_impl<T>::f(x); 

        // }


        // template <typename T>
        // struct dirichlet_eta_impl;

        // template <typename T>
        // inline static constexpr auto dirichlet_eta(const T& x) {
            
        //     return dirichlet_eta_impl<T>::f(x); 

        // }
     
        // template <typename T>
        // struct bessel_j0_impl;

        // template <typename T>
        // inline static constexpr auto bessel_j0(const T& x) {
            
        //     return bessel_j0_impl<T>::f(x); 

        // }


        // template <typename T>
        // struct bessel_j1_impl;

        // template <typename T>
        // inline static constexpr auto bessel_j1(const T& x) {
            
        //     return bessel_j1_impl<T>::f(x); 

        // }


        template <typename T>
        struct round_impl;

        template <typename T>
        inline static constexpr T round(const T& x) noexcept {

            return round_impl<T>::f(x);
            
        }
        

        template <typename T>
        struct floor_impl;

        template <typename T>
        inline static constexpr T floor(const T& x) noexcept {

            return floor_impl<T>::f(x);
            
        }
        

        template <typename T>
        struct ceil_impl;

        template <typename T>
        inline static constexpr T ceil(const T& x) noexcept {

            return ceil_impl<T>::f(x);
            
        }


        template <typename T>
        struct trunc_impl;

        template <typename T>
        inline static constexpr T trunc(const T& x) noexcept {

            return trunc_impl<T>::f(x);
            
        }

        // /// @brief Truncation function
        // /// @tparam precision of the truncation
        // /// @param value to truncate
        // template <class PRECISION, typename T>
        //     requires physics::is_prefix_v<PRECISION>
        // inline static constexpr auto trunc(const T& x) noexcept {
    
        //     /// truct up to the precision of the type
        //     constexpr double relative_precision = static_cast<double>(PRECISION::num) / static_cast<double>(PRECISION::den);

        //     if (op::abs(x) > T{1.0}) 
        //         return trunc_impl<T>::f(x / relative_precision, PRECISION) * relative_precision;

        //     else 
        //         return trunc_impl<T>::f(x * relative_precision, PRECISION) / relative_precision;
    
        // }


        // /// @brief Truncation function
        // /// @tparam precision of the truncation
        // /// @param value to truncate
        // template <typename T, typename PRECISION>
        //     requires physics::is_prefix_v<PRECISION>
        // inline static constexpr auto trunc(const T& x, const PRECISION&) noexcept {
    
        //     /// truct up to the precision of the type
        //     constexpr double relative_precision = static_cast<double>(PRECISION::num) / static_cast<double>(PRECISION::den);

        //     if (op::abs(x) > T{1.0}) 
        //         return trunc_impl<T>::f(x / relative_precision, PRECISION) * relative_precision;

        //     else 
        //         return trunc_impl<T>::f(x * relative_precision, PRECISION) / relative_precision;
    
        // }


        template <typename T>
        struct frac_impl;

        template <typename T>
        inline static constexpr T frac(const T& x) noexcept {

            return frac_impl<T>::f(x);
            
        }


        template <typename T>
        struct fmod_impl;

        template <typename T>
        inline static constexpr T fmod(const T& x, const T& y) noexcept {

            return fmod_impl<T>::f(x, y);
            
        }


        template <typename T>
        struct mod_impl;

        template <typename T>
        inline static constexpr T mod(const T& x, const T& y) noexcept {

            return mod_impl<T>::f(x, y);
            
        }


        template <typename T>
        struct min_impl;

        template <typename T>
        inline static constexpr T min(const T& x, const T& y) noexcept {

            return min_impl<T>::f(x, y);
            
        }


        template <typename T>
        struct max_impl;

        template <typename T>
        inline static constexpr T max(const T& x, const T& y) noexcept {

            return max_impl<T>::f(x, y);
            
        }


        template <typename T>
        struct clip_impl;

        template <typename T>
        inline static constexpr T clip(const T& x, const T& y, const T& z) noexcept {

            return clip_impl<T>::f(x, y, z);
            
        }
        


    } // namespace op


    // namespace functions {


    //     template <typename T, typename RESULT_TYPE, typename BACK_TYPE>
    //     struct unary_function;

    //     template <typename T>
    //     struct is_unary_function : std::false_type {};

    //     template <typename T, typename RESULT_TYPE, typename BACK_TYPE>
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