/**
 * @file    math/ops/measurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-03
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {
    
    
    namespace op {


        // ====================================================================================================
        // Utility operations
        // ====================================================================================================

            /// @brief Get the inverse of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_measurement_v<MEAS_TYPE>
            inline constexpr auto invert(const MEAS_TYPE& meas) 
                -> measurement_inv_t<MEAS_TYPE> {            

                if (meas.value == 0.0) 
                    throw std::runtime_error("Cannot invert a zero measurement");

                return { 1.0 / meas.value }; 
            
            }


            /// @brief Get the power of a measurement
            template <int POWER, typename MEAS_TYPE>
                requires physics::is_measurement_v<MEAS_TYPE>
            inline constexpr auto pow(const MEAS_TYPE& meas) noexcept
                -> measurement_pow_t<MEAS_TYPE, POWER> { 
                                
                return std::pow(meas.value, POWER); 

            }       

            /// @brief Get the square of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_measurement_v<MEAS_TYPE>
            inline constexpr auto square(const MEAS_TYPE& meas) noexcept 
                -> measurement_square_t<MEAS_TYPE> {

                return { std::pow(meas.value, 2) }; 
            
            }

            /// @brief Get the cube of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_measurement_v<MEAS_TYPE>
            inline constexpr auto cube(const MEAS_TYPE& meas) noexcept 
                -> measurement_cube_t<MEAS_TYPE> {
                
                return std::pow(meas.value, 3); 
            
            }


            /// @brief Get the power of a measurement
            template <int POWER, typename MEAS_TYPE>
                requires physics::is_measurement_v<MEAS_TYPE>
            inline constexpr auto root(const MEAS_TYPE& meas)
                -> measurement_root_t<MEAS_TYPE, POWER> {

                if (POWER % 2 == 0 && meas.value < 0.0) 
                    throw std::runtime_error("Cannot get the root of a negative measurement");
                                
                return std::pow(meas.value, 1.0 / POWER); 

            }            
            
            /// @brief Get the square root of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_measurement_v<MEAS_TYPE>
            inline constexpr auto sqrt(const MEAS_TYPE& meas) noexcept 
                -> measurement_sqrt_t<MEAS_TYPE> {
                
                return std::sqrt(meas.value); 
            
            }

            /// @brief Get the square root of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_measurement_v<MEAS_TYPE>
            inline constexpr auto cbrt(const MEAS_TYPE& meas) noexcept 
                -> measurement_cbrt_t<MEAS_TYPE> {
                
                return std::cbrt(meas.value); 
            
            }


            /// @brief Get the absolute of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_measurement_v<MEAS_TYPE>
            inline constexpr MEAS_TYPE abs(const MEAS_TYPE& meas) noexcept {

                return (meas.value < 0.0) ? -meas : meas; 
            
            }


            /// @brief Get the sign of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_measurement_v<MEAS_TYPE>
            inline constexpr MEAS_TYPE sign(const MEAS_TYPE& meas) noexcept {

                return (meas.value < 0.0) ? -1 : 1; 
            
            }


            /// @brief Get the minimum of two measurements
            template <typename MEAS_TYPE>
                requires physics::is_measurement_v<MEAS_TYPE>
            inline constexpr MEAS_TYPE min(const MEAS_TYPE& meas1, const MEAS_TYPE& meas2) noexcept {

                return (meas1.value < meas2.value) ? meas1 : meas2; 
            
            }


            /// @brief Get the maximum of two measurements
            template <typename MEAS_TYPE>
                requires physics::is_measurement_v<MEAS_TYPE>
            inline constexpr MEAS_TYPE max(const MEAS_TYPE& meas1, const MEAS_TYPE& meas2) noexcept {

                return (meas1.value > meas2.value) ? meas1 : meas2; 
            
            }


            /// @brief Get the exponential of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto exp(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::exp(meas.value); 
            
            }

            /// @brief Get the natural logarithm of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto log(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::scalar> {
                
                return std::log(meas.value); 
            
            }


            /// @brief Get the base-10 exponential of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto exp10(const MEAS_TYPE& meas) noexcept
                -> physics::measurement<physics::units::scalar> {
                
                return std::pow(10.0, meas.value); 

            }

            /// @brief Get the base-10 logarithm of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto log10(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::scalar> {
                                    
                return std::log10(meas.value); 

            }


        // ====================================================================================================
        // Trigonometric functions
        // ====================================================================================================

            /// @brief Get the sine of an angle_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            inline constexpr auto sin(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::scalar> {
                
                return std::sin(static_cast<double>(meas)); 
            
            }


            /// @brief Get the cosine of an angle_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            inline constexpr auto cos(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::scalar> {
                
                return std::cos(static_cast<double>(meas)); 

            }


            /// @brief Get the tangent of an angle_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            inline constexpr auto tan(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::scalar> {
                
                return std::tan(static_cast<double>(meas)); 
            
            }


            /// @brief Get the arcsine of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto asin(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::radian> {
                
                return std::asin(meas.value); 
            
            }


            /// @brief Get the arccosine of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto acos(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::radian> {
                
                return std::acos(meas.value); 
            
            }


            /// @brief Get the arctangent of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto atan(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::radian> {
                
                return std::atan(meas.value); 
            
            }


            /// @brief Get the hyperbolic sine of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto sinh(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::scalar> {
                
                return std::sinh(meas.value); 

            }


            /// @brief Get the hyperbolic cosine of a unitless_measurement
            template <typename MEAS_TYPE>
                 requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto cosh(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::scalar> {
                
                return std::cosh(meas.value); 

            }


            /// @brief Get the hyperbolic tangent of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto tanh(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::scalar> {
                
                return std::tanh(meas.value); 

            }


            /// @brief Get the hyperbolic arcsine of a radian_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto asinh(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::asinh(meas.value);

            }


            /// @brief Get the hyperbolic arccosine of a radian_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto acosh(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::acosh(meas.value);

            }


            /// @brief Get the hyperbolic arctangent of a radian_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto atanh(const MEAS_TYPE& meas) noexcept 
                -> physics::measurement<physics::units::scalar> {
                
                return std::atanh(meas.value);

            }


    } // namespace op


} // namespace scipp::math