/**
 * @file    math/ops/dual.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    
    
    namespace op {


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr MEAS_TYPE ceil(const MEAS_TYPE& other) noexcept {

            return {op::ceil(other.val), op::ceil(other.eps)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr MEAS_TYPE floor(const MEAS_TYPE& other) noexcept {

            return {op::floor(other.val), op::floor(other.eps)}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr MEAS_TYPE abs(const MEAS_TYPE& other) noexcept {

            return {op::abs(other.val), other.eps * op::sign(other.val)}; 

        }


        template <typename MEAS_TYPE, std::size_t POWER>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr auto pow(const MEAS_TYPE& other) noexcept 
            -> dual<meta::pow_t<typename MEAS_TYPE::measurement_t, POWER>> {

            const auto pow = op::pow<POWER - 1>(other.val);
            return {other.val * pow, other.eps * static_cast<double>(POWER) * pow}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr auto square(const MEAS_TYPE& other) noexcept 
            -> dual<meta::square_t<typename MEAS_TYPE::measurement_t>> {

            const auto pow = op::square(other.val);
            return {other.val * pow, 2.0 * other.eps * pow}; 

        }


        /// @todo pow(MEAS_TYPE, MEAS_TYPE)
        // template<class T1, class T2>
        // inline auto
        // pow(const dual<T1> b, const dual<T2>& e)
        // {
        //     using std::pow;
        //     using std::log;

        //     using T = common_numeric_t<T1,T2>;

        //     const auto ba_ea_1 = T(pow(b.val(), e.val()-1));

        //     return dual<T>{
        //         T(b.val()) * ba_ea_1 * (T(1) + (T(e.eps()) * T(log(b.val()))) ),
        //         T(b.eps()) * T(e.val()) * ba_ea_1 };
        // }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr auto sqrt(const MEAS_TYPE& other) noexcept 
            -> dual<meta::sqrt_t<typename MEAS_TYPE::measurement_t>> {

            const auto sqrt = op::sqrt(other.val);
            return {sqrt, other.eps / (2.0 * sqrt)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE>)
        static inline constexpr auto cbrt(const MEAS_TYPE& other) noexcept 
            -> dual<meta::cbrt_t<typename MEAS_TYPE::measurement_t>> {

            const auto cbrt = op::cbrt(other.val);
            return {cbrt, other.eps / (3.0 * op::square(cbrt))}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE sin(const MEAS_TYPE& other) noexcept {

            return {op::sin(other.val), other.eps * op::cos(other.val)}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE cos(const MEAS_TYPE& other) noexcept {

            return {op::cos(other.val), - other.eps * op::sin(other.val)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE tan(const MEAS_TYPE& other) noexcept {

            return {op::tan(other.val), other.eps * op::square(op::cos(other.val))}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE asin(const MEAS_TYPE& other) noexcept {

            return {op::asin(other.val), other.eps / op::sqrt(1.0 - op::square(other.val))}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE acos(const MEAS_TYPE& other) noexcept {

            return {op::acos(other.val), -other.eps / op::sqrt(1.0 - op::square(other.val))}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE atan(const MEAS_TYPE& other) noexcept {

            return {op::atan(other.val), other.eps / (1.0 + op::square(other.val))}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE sinh(const MEAS_TYPE& other) noexcept {

            return {op::sinh(other.val), other.eps * op::cosh(other.val)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE cosh(const MEAS_TYPE& other) noexcept {

            return {op::cosh(other.val), other.eps * op::sinh(other.val)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE tanh(const MEAS_TYPE& other) noexcept {

            return {op::tanh(other.val), other.eps / op::square(op::cosh(other.val))}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE asinh(const MEAS_TYPE& other) noexcept {

            return {op::asinh(other.val), other.eps / op::sqrt(op::square(other.val) + 1.0)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE acosh(const MEAS_TYPE& other) noexcept {

            return {op::acosh(other.val), other.eps / op::sqrt(op::square(other.val) - 1.0)}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE atanh(const MEAS_TYPE& other) noexcept {

            return {op::atanh(other.val), other.eps / (1.0 - op::square(other.val))}; 

        }


        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE exp(const MEAS_TYPE& other) noexcept {

            const auto exp = op::exp(other.val); 
            return {exp, other.eps * exp}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE exp10(const MEAS_TYPE& other) noexcept {

            const auto exp10 = op::exp10(other.val); 
            return {exp10, other.eps * std::exp(10.0) * exp10}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE log(const MEAS_TYPE& other) noexcept {

            return {op::log(other.val), other.eps / other.val}; 

        }

        template <typename MEAS_TYPE>
            requires (is_dual_measurement_v<MEAS_TYPE> && physics::is_scalar_v<typename MEAS_TYPE::measurement_t>)
        static inline constexpr MEAS_TYPE log10(const MEAS_TYPE& other) noexcept {

            return {op::log10(other.val), other.eps / (other.val * std::log(10.0))}; 

        }


    } /// namespace op


} /// namespace scipp::math