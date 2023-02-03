/**
 * @file    measurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::physics {


    /// @brief Multiply two measurements
    template <typename MEAS1, typename MEAS2, typename = std::enable_if_t<is_measurement_v<MEAS1> && is_measurement_v<MEAS2>>>
    inline constexpr auto operator*(const MEAS1& meas1, const MEAS2& meas2) noexcept -> measurement<units::base_prod_t<typename MEAS1::base, typename MEAS2::base>> { 
        
        return meas1.value * meas2.value; 
        
    }


    /// @brief Divide two measurements
    template <typename MEAS1, typename MEAS2, typename = std::enable_if_t<is_measurement_v<MEAS1> && is_measurement_v<MEAS2>>>
    inline constexpr auto operator/(const MEAS1& meas1, const MEAS2& meas2) -> measurement<units::base_div_t<typename MEAS1::base, typename MEAS2::base>> { 

        if (meas2.value == 0.0) 
            throw std::runtime_error("Cannot divide a measurement by a zero measurement");

        return meas1.value / meas2.value; 
        
    }
   

    template <typename MEAS, typename = std::enable_if_t<is_measurement_v<MEAS>>>
    inline constexpr auto operator*(const MEAS& meas, const scalar& val) noexcept -> MEAS {

        return meas.value * val; 

    }


    template <typename MEAS, typename = std::enable_if_t<is_measurement_v<MEAS>>>
    inline constexpr auto operator*(const scalar& val, const MEAS& meas) noexcept -> MEAS {

        return val * meas.value; 
        
    }


    template <typename MEAS, typename = std::enable_if_t<is_measurement_v<MEAS>>>
    inline constexpr auto operator/(const MEAS& meas, const scalar& val) -> MEAS {

        if (val == 0.0) 
            throw std::runtime_error("Cannot divide a measurement by zero");

        return meas.value / val; 

    }


    template <typename MEAS, typename = std::enable_if_t<is_measurement_v<MEAS>>>
    inline constexpr auto operator/(const scalar& val, const MEAS& meas) -> measurement<units::base_inv_t<typename MEAS::base>> {

        if (val == 0.0) 
            throw std::runtime_error("Cannot divide a scalar by a zero measurement");

        return val / meas.value; 
        
    }


} // namespace scipp::physics


namespace scipp::math {
    
    
    namespace op {


        // ====================================================================================================
        // Utility operations
        // ====================================================================================================
            
            /// @brief Get the inverse of a measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS>>>
            inline constexpr auto inv(const MEAS& meas) noexcept -> physics::measurement<physics::units::base_inv_t<typename MEAS::base>> { 
                
                return 1.0 / meas.value; 
            
            }


            /// @brief Get the absolute of a measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS>>>
            inline constexpr auto abs(const MEAS& meas) noexcept -> MEAS { 
                
                return (meas.value < 0.0) ? -meas : meas; 
            
            }


            /// @brief Get the sign of a measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS>>>
            inline constexpr auto sign(const MEAS& meas) noexcept -> MEAS { 
                
                return (meas.value < 0.0) ? -1.0 : 1.0; 
            
            }


            /// @brief Get the minimum of two measurements
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS>>>
            inline constexpr auto min(const MEAS& meas1, const MEAS& meas2) noexcept -> MEAS { 
                
                return (meas1.value < meas2.value) ? meas1 : meas2; 
            
            }


            /// @brief Get the maximum of two measurements
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS>>>
            inline constexpr auto max(const MEAS& meas1, const MEAS& meas2) noexcept -> MEAS { 
                
                return (meas1.value > meas2.value) ? meas1 : meas2; 
            
            }


        // ====================================================================================================
        // Arithmetic operations
        // ====================================================================================================

            /// @brief Get the square of a measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS>>>
            inline constexpr auto square(const MEAS& meas) noexcept -> physics::measurement<physics::units::base_square_t<typename MEAS::base>> { 
                
                return std::pow(meas.value, 2); 
            
            }


            /// @brief Get the cube of a measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS>>>
            inline constexpr auto cube(const MEAS& meas) noexcept -> physics::measurement<physics::units::base_cube_t<typename MEAS::base>> { 
                
                return std::pow(meas.value, 3); 
            
            }


            /// @brief Get the square root of a measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS>>>
            inline constexpr auto sqrt(const MEAS& meas) noexcept -> physics::measurement<physics::units::base_sqrt_t<typename MEAS::base>> { 
                
                return std::sqrt(meas.value); 
            
            }


            /// @brief Get the cubic root of a measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS>>>
            inline constexpr auto cbrt(const MEAS& meas) noexcept -> physics::measurement<physics::units::base_cbrt_t<typename MEAS::base>> { 
                
                return std::cbrt(meas.value); 
            
            }


            /// @brief Get the exponential of a measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::unitless, typename MEAS::base>>>
            inline constexpr auto exp(const MEAS& meas) noexcept -> MEAS { 
                
                return std::exp(meas.value); 
            
            }


            /// @brief Get the natural logarithm of a measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::unitless, typename MEAS::base>>>
            inline constexpr auto log(const MEAS& meas) noexcept -> MEAS { 
                
                return std::log(meas.value); 
            
            }


            /// @brief Get the base-10 logarithm of a measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::unitless, typename MEAS::base>>>
            inline constexpr auto log10(const MEAS& meas) noexcept -> MEAS { 
                
                return std::log10(meas.value); 
            
            }


        // ====================================================================================================
        // Trigonometric functions
        // ====================================================================================================

            /// @brief Get the sine of an angle_measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::radian, typename MEAS::base>>>
            inline constexpr auto sin(const MEAS& meas) noexcept -> physics::measurement<physics::units::unitless> { 
                            
                return std::sin(meas.value);
            
            }


            /// @brief Get the cosine of an angle_measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::radian, typename MEAS::base>>>
            inline constexpr auto cos(const MEAS& meas) noexcept -> physics::measurement<physics::units::unitless> { 
                            
                return std::cos(meas.value);
            
            }


            /// @brief Get the tangent of an angle_measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::radian, typename MEAS::base>>>
            inline constexpr auto tan(const MEAS& meas) noexcept -> physics::measurement<physics::units::unitless> { 
                            
                return std::tan(meas.value);
            
            }


            /// @brief Get the arcsine of a unitless_measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::unitless, typename MEAS::base>>>
            inline constexpr auto asin(const MEAS& meas) noexcept -> physics::measurement<physics::units::radian> { 
                            
                return std::asin(meas.value);
            
            }


            /// @brief Get the arccosine of a unitless_measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::unitless, typename MEAS::base>>>
            inline constexpr auto acos(const MEAS& meas) noexcept -> physics::measurement<physics::units::radian> { 
                            
                return std::acos(meas.value);
            
            }


            /// @brief Get the arctangent of a unitless_measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::unitless, typename MEAS::base>>>
            inline constexpr auto atan(const MEAS& meas) noexcept -> physics::measurement<physics::units::radian> { 
                            
                return std::atan(meas.value);
            
            }


            /// @brief Get the hyperbolic sine of a unitless_measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::unitless, typename MEAS::base>>>
            inline constexpr auto sinh(const MEAS& meas) noexcept -> physics::measurement<physics::units::unitless> { 
                            
                return std::sinh(meas.value);

            }


            /// @brief Get the hyperbolic cosine of a unitless_measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::unitless, typename MEAS::base>>>
            inline constexpr auto cosh(const MEAS& meas) noexcept -> physics::measurement<physics::units::unitless> { 
                            
                return std::cosh(meas.value);

            }


            /// @brief Get the hyperbolic tangent of a unitless_measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::unitless, typename MEAS::base>>>
            inline constexpr auto tanh(const MEAS& meas) noexcept -> physics::measurement<physics::units::unitless> { 
                            
                return std::tanh(meas.value);

            }

            /// @brief Get the hyperbolic arcsine of a radian_measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::unitless, typename MEAS::base>>>
            inline constexpr auto asinh(const MEAS& meas) noexcept -> physics::measurement<physics::units::radian> { 
                            
                return std::asinh(meas.value);

            }


            /// @brief Get the hyperbolic arccosine of a radian_measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::unitless, typename MEAS::base>>>
            inline constexpr auto acosh(const MEAS& meas) noexcept -> physics::measurement<physics::units::radian> { 
                            
                return std::acosh(meas.value);

            }


            /// @brief Get the hyperbolic arctangent of a radian_measurement
            template <typename MEAS, typename = std::enable_if_t<physics::is_measurement_v<MEAS> && physics::units::is_same_base_v<physics::units::unitless, typename MEAS::base>>>
            inline constexpr auto atanh(const MEAS& meas) noexcept -> physics::measurement<physics::units::radian> { 
                            
                return std::atanh(meas.value);

            }


    } // namespace op


} // namespace scipp::math