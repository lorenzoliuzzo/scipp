/**
 * @file    math/ops/dual.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {
    
    
    namespace op {


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr MEAS_TYPE ceil(const MEAS_TYPE& other) noexcept {

            return {op::ceil(other.real), op::ceil(other.imag)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr MEAS_TYPE floor(const MEAS_TYPE& other) noexcept {

            return {op::floor(other.real), op::floor(other.imag)}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr MEAS_TYPE abs(const MEAS_TYPE& other) noexcept {

            return {op::abs(other.real), other.imag * op::sign(other.real)}; 

        }


        template <typename MEAS_TYPE, std::size_t POWER>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr auto pow(const MEAS_TYPE& other) noexcept 
            -> dual<op::measurement_pow_t<typename MEAS_TYPE::measurement_t, POWER>> {

            constexpr auto pow = op::pow<POWER - 1>(other.real);
            return {other.real * pow, other.imag * static_cast<physics::scalar_m>(POWER) * pow}; 

        }


        /// @todo pow(MEAS_TYPE, MEAS_TYPE)
        // template<class T1, class T2>
        // inline auto
        // pow(const dual<T1> b, const dual<T2>& e)
        // {
        //     using std::pow;
        //     using std::log;

        //     using T = common_numeric_t<T1,T2>;

        //     const auto ba_ea_1 = T(pow(b.real(), e.real()-1));

        //     return dual<T>{
        //         T(b.real()) * ba_ea_1 * (T(1) + (T(e.imag()) * T(log(b.real()))) ),
        //         T(b.imag()) * T(e.real()) * ba_ea_1 };
        // }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr auto sqrt(const MEAS_TYPE& other) noexcept 
            -> dual<op::measurement_sqrt_t<typename MEAS_TYPE::measurement_t>> {

            constexpr auto sqrt = op::sqrt(other.real);
            return {sqrt, other.imag / (2.0 * sqrt)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr auto cbrt(const MEAS_TYPE& other) noexcept 
            -> dual<op::measurement_cbrt_t<typename MEAS_TYPE::measurement_t>> {

            constexpr auto cbrt = op::cbrt(other.real);
            return {cbrt, other.imag / (3.0 * op::square(cbrt))}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE sin(const MEAS_TYPE& other) noexcept {

            return {op::sin(other.real), other.imag * op::cos(other.real)}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE cos(const MEAS_TYPE& other) noexcept {

            return {op::cos(other.real), - other.imag * op::sin(other.real)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE tan(const MEAS_TYPE& other) noexcept {

            return {op::tan(other.real), other.imag * op::square(op::cos(other.real))}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE asin(const MEAS_TYPE& other) noexcept {

            return {op::asin(other.real), other.imag / op::sqrt(1.0 - op::square(other.real))}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE acos(const MEAS_TYPE& other) noexcept {

            return {op::acos(other.real), -other.imag / op::sqrt(1.0 - op::square(other.real))}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE atan(const MEAS_TYPE& other) noexcept {

            return {op::atan(other.real), other.imag / (1.0 + op::square(other.real))}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE sinh(const MEAS_TYPE& other) noexcept {

            return {op::sinh(other.real), other.imag * op::cosh(other.real)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE cosh(const MEAS_TYPE& other) noexcept {

            return {op::cosh(other.real), other.imag * op::sinh(other.real)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE tanh(const MEAS_TYPE& other) noexcept {

            return {op::tanh(other.real), other.imag / op::square(op::cosh(other.real))}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE asinh(const MEAS_TYPE& other) noexcept {

            return {op::asinh(other.real), other.imag / op::sqrt(op::square(other.real) + 1.0)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE acosh(const MEAS_TYPE& other) noexcept {

            return {op::acosh(other.real), other.imag / op::sqrt(op::square(other.real) - 1.0)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE atanh(const MEAS_TYPE& other) noexcept {

            return {op::atanh(other.real), other.imag / (1.0 - op::square(other.real))}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE exp(const MEAS_TYPE& other) noexcept {

            constexpr auto exp = op::exp(other.real); 
            return {exp, other.imag * exp}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE exp10(const MEAS_TYPE& other) noexcept {

            constexpr auto exp10 = op::exp10(other.real); 
            return {exp10, other.imag * std::exp(10.0) * exp10}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE log(const MEAS_TYPE& other) noexcept {

            return {op::log(other.real), other.imag / other.real}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE log10(const MEAS_TYPE& other) noexcept {

            return {op::log10(other.real), other.imag / (other.real * std::log(10.0))}; 

        }


    } /// namespace op


} /// namespace scipp::math