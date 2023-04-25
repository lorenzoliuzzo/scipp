/**
 * @file    math/ops/measurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-24
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    
    
    namespace op {


        // ====================================================================================================
        // operations on values
        // ====================================================================================================

            /// @brief Get the absolute of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr MEAS_TYPE abs(const MEAS_TYPE& other) noexcept {

                return (other.value < 0.0) ? -other : other; 
            
            }

            /// @brief Get the sign of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr bool sign(const MEAS_TYPE& other) noexcept {

                return (other.value > 0.0) ? 0 : 1; 
            
            }


            /// @brief Get the minimum of two measurements
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr MEAS_TYPE min(const MEAS_TYPE& meas1, const MEAS_TYPE& meas2) noexcept {

                return (meas1.value < meas2.value) ? meas1 : meas2; 
            
            }

            /// @brief Get the maximum of two measurements
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr MEAS_TYPE max(const MEAS_TYPE& meas1, const MEAS_TYPE& meas2) noexcept {

                return (meas1.value > meas2.value) ? meas1 : meas2; 
            
            }


            /// @brief Get the inverse of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto inv(const MEAS_TYPE& other) 
                -> meta::invert_t<MEAS_TYPE> {            

                if (other.value == 0.0) 
                    throw std::runtime_error("Cannot invert a zero measurement");

                return 1.0 / other.value; 
            
            }


            /// @brief Get the power of a measurement
            template <int POWER, typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto pow(const MEAS_TYPE& other) noexcept
                -> meta::power_t<MEAS_TYPE, POWER> { 
                                
                return std::pow(other.value, POWER); 

            }       

            /// @brief Get the square of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto square(const MEAS_TYPE& other) noexcept 
                -> meta::square_t<MEAS_TYPE> {

                return std::pow(other.value, 2); 
            
            }

            /// @brief Get the cube of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto cube(const MEAS_TYPE& other) noexcept 
                -> meta::cube_t<MEAS_TYPE> {
                
                return std::pow(other.value, 3); 
            
            }


            /// @brief Get the power of a measurement
            template <int POWER, typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto root(const MEAS_TYPE& other)
                -> meta::root_t<MEAS_TYPE, POWER> { 

                if (POWER % 2 == 0 && other.value < 0.0) 
                    throw std::runtime_error("Cannot get the root of a negative measurement");
                                
                return std::pow(other.value, 1.0 / POWER); 

            }            
            
            /// @brief Get the square root of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto sqrt(const MEAS_TYPE& other) 
                -> meta::sqrt_t<MEAS_TYPE> {
                
                if (other.value < 0.0)  
                    throw std::runtime_error("Cannot take the square root of a negative measurement"); 

                return std::sqrt(other.value); 
            
            }

            /// @brief Get the square root of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto cbrt(const MEAS_TYPE& other) noexcept 
                -> meta::cbrt_t<MEAS_TYPE> {
                
                return std::cbrt(other.value); 
            
            }


            /// @brief Get the exponential of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_v<MEAS_TYPE>)
            inline constexpr MEAS_TYPE exp(const MEAS_TYPE& other) noexcept {

                return std::exp(other.value); 
            
            }

            /// @brief Get the natural logarithm of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_v<MEAS_TYPE>)
            inline constexpr MEAS_TYPE log(const MEAS_TYPE& other) noexcept {
                
                return std::log(other.value); 
            
            }


            /// @brief Get the base-10 exponential of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_v<MEAS_TYPE>)
            inline constexpr MEAS_TYPE exp10(const MEAS_TYPE& other) noexcept {
                
                return std::pow(10.0, other.value); 

            }

            /// @brief Get the base-10 logarithm of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_v<MEAS_TYPE>)
            inline constexpr MEAS_TYPE log10(const MEAS_TYPE& other) noexcept {
                                    
                return std::log10(other.value); 

            }


        // ====================================================================================================
        // Trigonometric functions
        // ====================================================================================================

            /// @brief Get the sine of an angle_measurement
            template <typename T>
                requires (physics::is_scalar_v<T>)
            inline constexpr T sin(const T& other) noexcept {

                return std::sin(static_cast<double>(other)); 
            
            }


            /// @brief Get the cosine of an angle_measurement
            template <typename T>
                requires (physics::is_scalar_v<T>)
            inline constexpr T cos(const T& other) noexcept{

                return std::cos(static_cast<double>(other)); 

            }


            /// @brief Get the tangent of an angle_measurement
            template <typename T>
                requires (physics::is_scalar_v<T>)
            inline constexpr T tan(const T& other) noexcept {

                return std::tan(static_cast<double>(other)); 
            
            }


            /// @brief Get the arcsine of a unitless_measurement
            template <typename T>
                requires (physics::is_scalar_v<T>)
            inline constexpr T asin(const T& other) noexcept {

                return std::asin(other.value); 
            
            }


            /// @brief Get the arccosine of a unitless_measurement
            template <typename T>
                requires (physics::is_scalar_v<T>)
            inline constexpr T acos(const T& other) noexcept {

                return std::acos(other.value); 
            
            }


            /// @brief Get the arctangent of a unitless_measurement
            template <typename T>
                requires (physics::is_scalar_v<T>)
            inline constexpr T atan(const T& other) noexcept {

                return std::atan(other.value); 
            
            }


            /// @brief Get the hyperbolic sine of a unitless_measurement
            template <typename T>
                requires (physics::is_scalar_v<T>)
            inline constexpr T sinh(const T& other) noexcept {

                return std::sinh(other.value); 

            }


            /// @brief Get the hyperbolic cosine of a unitless_measurement
            template <typename T>
                requires (physics::is_scalar_v<T>)
            inline constexpr T cosh(const T& other) noexcept {

                return std::cosh(other.value); 

            }


            /// @brief Get the hyperbolic tangent of a unitless_measurement
            template <typename T>
                requires (physics::is_scalar_v<T>)
            inline constexpr T tanh(const T& other) noexcept {

                return std::tanh(other.value); 

            }


            /// @brief Get the hyperbolic arcsine of a radian_measurement
            template <typename T>
                requires (physics::is_scalar_v<T>)
            inline constexpr T asinh(const T& other) noexcept {

                return std::asinh(other.value);

            }


            /// @brief Get the hyperbolic arccosine of a radian_measurement
            template <typename T>
                requires (physics::is_scalar_v<T>)
            inline constexpr T acosh(const T& other) noexcept {

                return std::acosh(other.value);

            }


            /// @brief Get the hyperbolic arctangent of a radian_measurement
            template <typename T>
                requires (physics::is_scalar_v<T>)
            inline constexpr T atanh(const T& other) noexcept {

                return std::atanh(other.value);

            }


    } // namespace op


} // namespace scipp::math