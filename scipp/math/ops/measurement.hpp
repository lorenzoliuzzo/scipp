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
        // operations on types
        // ====================================================================================================

            template <typename MEAS_TYPE>   
                requires (physics::is_measurement_v<MEAS_TYPE>)
            struct invert<MEAS_TYPE> : physics::measurement<op::base_invert_t<typename MEAS_TYPE::base_t>> {};

            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (physics::are_measurements_v<MEAS_TYPE1, MEAS_TYPE2>)
            struct multiply<MEAS_TYPE1, MEAS_TYPE2> : physics::measurement<op::base_product_t<typename MEAS_TYPE1::base_t, typename MEAS_TYPE2::base_t>> {};

            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (physics::are_measurements_v<MEAS_TYPE1, MEAS_TYPE2>)
            struct divide<MEAS_TYPE1, MEAS_TYPE2> : physics::measurement<op::base_division_t<typename MEAS_TYPE1::base_t, typename MEAS_TYPE2::base_t>> {};

            template <typename MEAS_TYPE, std::size_t POWER>    
                requires (physics::is_measurement_v<MEAS_TYPE>)
            struct power<MEAS_TYPE, POWER> : physics::measurement<op::base_pow_t<typename MEAS_TYPE::base_t, POWER>> {};

            template <typename MEAS_TYPE, std::size_t POWER>    
                requires (physics::is_measurement_v<MEAS_TYPE>)
            struct root_power<MEAS_TYPE, POWER> : physics::measurement<op::base_root_t<typename MEAS_TYPE::base_t, POWER>> {};

        
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
                -> op::invert_t<MEAS_TYPE> {            

                if (other.value == 0.0) 
                    throw std::runtime_error("Cannot invert a zero measurement");

                return 1.0 / other.value; 
            
            }


            /// @brief Get the power of a measurement
            template <int POWER, typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto pow(const MEAS_TYPE& other) noexcept
                -> op::power_t<MEAS_TYPE, POWER> { 
                                
                return std::pow(other.value, POWER); 

            }       

            /// @brief Get the square of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto square(const MEAS_TYPE& other) noexcept 
                -> op::square_t<MEAS_TYPE> {

                return std::pow(other.value, 2); 
            
            }

            /// @brief Get the cube of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto cube(const MEAS_TYPE& other) noexcept 
                -> op::cube_t<MEAS_TYPE> {
                
                return std::pow(other.value, 3); 
            
            }


            /// @brief Get the power of a measurement
            template <int POWER, typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto root(const MEAS_TYPE& other)
                -> op::root_power_t<MEAS_TYPE, POWER> { 

                if (POWER % 2 == 0 && other.value < 0.0) 
                    throw std::runtime_error("Cannot get the root of a negative measurement");
                                
                return std::pow(other.value, 1.0 / POWER); 

            }            
            
            /// @brief Get the square root of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto sqrt(const MEAS_TYPE& other) 
                -> op::sqrt_t<MEAS_TYPE> {
                
                if (other.value < 0.0)  
                    throw std::runtime_error("Cannot take the square root of a negative measurement"); 

                return std::sqrt(other.value); 
            
            }

            /// @brief Get the square root of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto cbrt(const MEAS_TYPE& other) noexcept 
                -> op::cbrt_t<MEAS_TYPE> {
                
                return std::cbrt(other.value); 
            
            }


            /// @brief Get the exponential of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto exp(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::exp(other.value); 
            
            }

            /// @brief Get the natural logarithm of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto log(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {
                
                return std::log(other.value); 
            
            }


            /// @brief Get the base-10 exponential of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto exp10(const MEAS_TYPE& other) noexcept
                -> physics::measurement<physics::units::scalar> {
                
                return std::pow(10.0, other.value); 

            }

            /// @brief Get the base-10 logarithm of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            inline constexpr auto log10(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {
                                    
                return std::log10(other.value); 

            }


        // ====================================================================================================
        // Trigonometric functions
        // ====================================================================================================

            /// @brief Get the sine of an angle_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
            inline constexpr auto sin(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::sin(static_cast<double>(other)); 
            
            }


            /// @brief Get the cosine of an angle_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
            inline constexpr auto cos(const MEAS_TYPE& other) noexcept
                -> physics::measurement<physics::units::scalar> {

                return std::cos(static_cast<double>(other)); 

            }


            /// @brief Get the tangent of an angle_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
            inline constexpr auto tan(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::tan(static_cast<double>(other)); 
            
            }


            /// @brief Get the arcsine of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
            inline constexpr auto asin(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::asin(other.value); 
            
            }


            /// @brief Get the arccosine of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
            inline constexpr auto acos(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::acos(other.value); 
            
            }


            /// @brief Get the arctangent of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
            inline constexpr auto atan(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::atan(other.value); 
            
            }


            /// @brief Get the hyperbolic sine of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
            inline constexpr auto sinh(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::sinh(other.value); 

            }


            /// @brief Get the hyperbolic cosine of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
            inline constexpr auto cosh(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::cosh(other.value); 

            }


            /// @brief Get the hyperbolic tangent of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
            inline constexpr auto tanh(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::tanh(other.value); 

            }


            /// @brief Get the hyperbolic arcsine of a radian_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
            inline constexpr auto asinh(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::asinh(other.value);

            }


            /// @brief Get the hyperbolic arccosine of a radian_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
            inline constexpr auto acosh(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::acosh(other.value);

            }


            /// @brief Get the hyperbolic arctangent of a radian_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_scalar_measurement_v<MEAS_TYPE>)
            inline constexpr auto atanh(const MEAS_TYPE& other) noexcept 
                -> physics::measurement<physics::units::scalar> {

                return std::atanh(other.value);

            }


    } // namespace op


} // namespace scipp::math