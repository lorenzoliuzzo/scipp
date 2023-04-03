/**
 * @file    math/ops/complex.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-03
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {
    
    
    namespace op {


        template <typename MEAS_TYPE>
            requires (physics::is_complex_measurement_v<MEAS_TYPE>)
        inline constexpr MEAS_TYPE::measurement_type abs(const MEAS_TYPE& other) noexcept {
            
            return op::sqrt(op::square(other.real) + op::square(other.imag));

        }


        template <typename MEAS_TYPE>
            requires (physics::is_complex_measurement_v<MEAS_TYPE>)
        inline constexpr auto arg(const MEAS_TYPE& other) noexcept {
            
            return op::atan(other.imag / other.real);

        }

        template <typename MEAS_TYPE>
            requires (physics::is_complex_measurement_v<MEAS_TYPE>)
        inline constexpr auto norm(const MEAS_TYPE& other) noexcept {
            
            return op::square(other.real) + op::square(other.imag);

        }


        template <typename MEAS_TYPE>
            requires (physics::is_complex_measurement_v<MEAS_TYPE>)
        inline constexpr auto conj(const MEAS_TYPE& other) noexcept {
            
            return MEAS_TYPE{other.real, -other.imag};

        }


        template <typename MEAS_TYPE1, typename MEAS_TYPE2>
            requires (physics::are_generic_measurements_v<MEAS_TYPE1, MEAS_TYPE2> && physics::is_scalar_v<MEAS_TYPE2>)
        inline constexpr physics::complex<MEAS_TYPE1> polar(const MEAS_TYPE1& rho, const MEAS_TYPE2& theta) noexcept {
            
            return physics::complex<MEAS_TYPE1>(rho * op::cos(theta), rho * op::sin(theta));

        }


        /// @brief Get the cosine of an angle_measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto cos(const physics::complex<MEAS_TYPE>& other) noexcept 
            -> physics::complex<math::op::measurements_div_t<MEAS_TYPE, MEAS_TYPE>> {
            
            return { op::cos(other.real) * op::cosh(other.imag), -op::sin(other.real) * op::sinh(other.imag) };

        }


    } // namespace op


} // namespace scipp::math