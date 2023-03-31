/**
 * @file    math/ops/measurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-23
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {
    
    
    namespace op {


        template <typename MEAS_TYPE, typename... MEAS_TYPES>
            requires (physics::are_generic_measurements_v<MEAS_TYPE, MEAS_TYPES...>)
        struct measurements_prod { 
            
            using type = std::conditional_t<physics::are_umeasurements_v<MEAS_TYPE, MEAS_TYPES...>,    
                                            physics::umeasurement<math::op::base_product_t<typename MEAS_TYPE::base, typename measurements_prod<MEAS_TYPES...>::type::base>>,
                                            physics::measurement<math::op::base_product_t<typename MEAS_TYPE::base, typename measurements_prod<MEAS_TYPES...>::type::base>>>;
        
        };

        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurements_prod<MEAS_TYPE> {

            using type = MEAS_TYPE;

        };


        template <typename... Ts>
        using measurements_prod_t = typename measurements_prod<Ts...>::type;


        template <typename MEAS_TYPE1, typename MEAS_TYPE2>
            requires (physics::are_generic_measurements_v<MEAS_TYPE1, MEAS_TYPE2>)
        struct measurements_div { 
            
            using type = std::conditional_t<physics::are_umeasurements_v<MEAS_TYPE1, MEAS_TYPE2>,    
                                            physics::umeasurement<math::op::base_division_t<typename MEAS_TYPE1::base, typename measurements_prod<MEAS_TYPE2>::type::base>>,
                                            physics::measurement<math::op::base_division_t<typename MEAS_TYPE1::base, typename measurements_prod<MEAS_TYPE2>::type::base>>>;
        
            
        };

        template <typename T1, typename T2>
        using measurements_div_t = typename measurements_div<T1, T2>::type;


        template <typename MEAS_TYPE>
        struct measurement_inv { 
            
            using type = std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                            physics::umeasurement<math::op::base_invert_t<typename MEAS_TYPE::base>>, 
                                            physics::measurement<math::op::base_invert_t<typename MEAS_TYPE::base>>>;


        }; 

        template <typename MEAS_TYPE>
        using measurement_inv_t = typename measurement_inv<MEAS_TYPE>::type;


        template <typename MEAS_TYPE, std::size_t POWER>    
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurement_pow { 
            
            using type = std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                            physics::umeasurement<math::op::base_pow_t<typename MEAS_TYPE::base, POWER>>, 
                                            physics::measurement<math::op::base_pow_t<typename MEAS_TYPE::base, POWER>>>;

        }; 

        template <typename MEAS_TYPE, std::size_t POWER>
        using measurement_pow_t = typename measurement_pow<MEAS_TYPE, POWER>::type;

        template <typename MEAS_TYPE>
        using measurement_square_t = measurement_pow_t<MEAS_TYPE, 2>;

        template <typename MEAS_TYPE>
        using measurement_cube_t = measurement_pow_t<MEAS_TYPE, 3>;


        template <typename MEAS_TYPE, std::size_t POWER>    
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurement_root { 
            
            using type = std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                            physics::umeasurement<math::op::base_root_t<typename MEAS_TYPE::base, POWER>>, 
                                            physics::measurement<math::op::base_root_t<typename MEAS_TYPE::base, POWER>>>;

        }; 

        template <typename MEAS_TYPE, std::size_t POWER>
        using measurement_root_t = typename measurement_root<MEAS_TYPE, POWER>::type;

        template <typename MEAS_TYPE>
        using measurement_sqrt_t = measurement_root_t<MEAS_TYPE, 2>;

        template <typename MEAS_TYPE>
        using measurement_cbrt_t = measurement_root_t<MEAS_TYPE, 3>;


        // ====================================================================================================
        // Utility operations
        // ====================================================================================================

            /// @brief Get the inverse of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto invert(const MEAS_TYPE& meas) 
                -> measurement_inv_t<MEAS_TYPE> {            

                if (meas.value == 0.0) 
                    throw std::runtime_error("Cannot invert a zero measurement");

                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { 1.0 / meas.value, meas.uncertainty / std::pow(meas.value, 2) };

                else 
                    return { 1.0 / meas.value }; 
            
            }


            /// @brief Get the power of a measurement
            template <int POWER, typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto pow(const MEAS_TYPE& meas) noexcept
                -> measurement_pow_t<MEAS_TYPE, POWER> { 
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::pow(meas.value, POWER), std::fabs(POWER * std::pow(meas.value, POWER - 1)) * meas.uncertainty };
                
                else 
                    return std::pow(meas.value, POWER); 

            }       

            /// @brief Get the square of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto square(const MEAS_TYPE& meas) noexcept 
                -> measurement_square_t<MEAS_TYPE> {

                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::pow(meas.value, 2), 2.0 * std::fabs(meas.value) * meas.uncertainty }; 

                else 
                    return { std::pow(meas.value, 2) }; 
            
            }

            /// @brief Get the cube of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto cube(const MEAS_TYPE& meas) noexcept 
                -> measurement_cube_t<MEAS_TYPE> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::pow(meas.value, 3), 3. * std::fabs(meas.value) * meas.uncertainty }; 

                else 
                    return std::pow(meas.value, 3); 
            
            }


            /// @brief Get the power of a measurement
            template <int POWER, typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto root(const MEAS_TYPE& meas) 
                -> measurement_root_t<MEAS_TYPE, POWER> {

                if (POWER % 2 == 0 && meas.value < 0.0) 
                    throw std::runtime_error("Cannot get the root of a negative measurement");
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::pow(meas.value, 1.0 / POWER), std::fabs(1.0 / POWER * std::pow(meas.value, 1.0 / POWER - 1)) * meas.uncertainty };
                
                else
                    return std::pow(meas.value, 1.0 / POWER); 

            }            
            
            /// @brief Get the square root of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto sqrt(const MEAS_TYPE& meas) noexcept 
                -> measurement_sqrt_t<MEAS_TYPE> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::sqrt(meas.value), 0.5 * meas.uncertainty / std::sqrt(meas.value) };

                else 
                    return std::sqrt(meas.value); 
            
            }

            /// @brief Get the square root of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto cbrt(const MEAS_TYPE& meas) noexcept 
                -> measurement_cbrt_t<MEAS_TYPE> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::cbrt(meas.value), std::pow(meas.value, - 2. / 3.) * meas.uncertainty / 3. };

                else    
                    return std::cbrt(meas.value); 
            
            }


            /// @brief Get the absolute of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto abs(const MEAS_TYPE& meas) noexcept 
                -> MEAS_TYPE { 
                
                return (meas.value < 0.0) ? -meas : meas; 
            
            }


            /// @brief Get the sign of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto sign(const MEAS_TYPE& meas) noexcept 
                -> MEAS_TYPE { 
                
                return (meas.value < 0.0) ? -1 : 1; 
            
            }


            /// @brief Get the minimum of two measurements
            template <typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto min(const MEAS_TYPE& meas1, const MEAS_TYPE& meas2) noexcept 
                -> MEAS_TYPE { 
                
                return (meas1.value < meas2.value) ? meas1 : meas2; 
            
            }


            /// @brief Get the maximum of two measurements
            template <typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto max(const MEAS_TYPE& meas1, const MEAS_TYPE& meas2) noexcept 
                -> MEAS_TYPE { 
                
                return (meas1.value > meas2.value) ? meas1 : meas2; 
            
            }


            /// @brief Get the exponential of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            constexpr auto exp(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::scalar>, 
                                      physics::measurement<physics::units::scalar>> {

                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::exp(meas.value), std::exp(meas.uncertainty) };

                else 
                    return std::exp(meas.value); 
            
            }

            /// @brief Get the natural logarithm of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            constexpr auto log(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::scalar>, 
                                      physics::measurement<physics::units::scalar>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::log(meas.value), meas.uncertainty / std::fabs(meas.value) };

                else
                    return std::log(meas.value); 
            
            }


            /// @brief Get the base-10 exponential of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            constexpr auto exp10(const MEAS_TYPE& meas) noexcept
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::scalar>, 
                                      physics::measurement<physics::units::scalar>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::pow(10.0, meas.value), std::log(10) * std::pow(10.0, meas.value) * meas.uncertainty };

                else 
                    return std::pow(10.0, meas.value); 

            }

            /// @brief Get the base-10 logarithm of a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            constexpr auto log10(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::scalar>, 
                                      physics::measurement<physics::units::scalar>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::log10(meas.value), meas.uncertainty / (std::log(10) * std::fabs(meas.value)) };
                    
                else 
                    return std::log10(meas.value); 

            }


        // ====================================================================================================
        // Trigonometric functions
        // ====================================================================================================

            /// @brief Get the sine of an angle_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_angle_v<MEAS_TYPE>)
            constexpr auto sin(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::scalar>, 
                                      physics::measurement<physics::units::scalar>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::sin(meas.value), std::fabs(std::cos(meas.value)) * meas.uncertainty };

                else    
                    return std::sin(meas.value); 
            
            }


            /// @brief Get the cosine of an angle_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_angle_v<MEAS_TYPE>)
            constexpr auto cos(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::scalar>, 
                                      physics::measurement<physics::units::scalar>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::cos(meas.value), std::fabs(std::sin(meas.value)) * meas.uncertainty };

                else    
                    return std::cos(meas.value); 

            }


            /// @brief Get the tangent of an angle_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_angle_v<MEAS_TYPE>)
            constexpr auto tan(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::scalar>, 
                                      physics::measurement<physics::units::scalar>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::tan(meas.value), std::fabs(1. / std::pow(std::cos(meas.value), 2)) * meas.uncertainty };

                else
                    return std::tan(meas.value); 
            
            }


            /// @brief Get the arcsine of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            constexpr auto asin(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::radian>, 
                                      physics::measurement<physics::units::radian>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::asin(meas.value), meas.uncertainty / std::sqrt(1. - std::pow(meas.value, 2)) };

                else
                    return std::asin(meas.value); 
            
            }


            /// @brief Get the arccosine of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            constexpr auto acos(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::radian>, 
                                      physics::measurement<physics::units::radian>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::acos(meas.value), meas.uncertainty / std::sqrt(1. - std::pow(meas.value, 2)) };

                else
                    return std::acos(meas.value); 
            
            }


            /// @brief Get the arctangent of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            constexpr auto atan(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::radian>, 
                                      physics::measurement<physics::units::radian>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::atan(meas.value), meas.uncertainty / (1. + std::pow(meas.value, 2)) };

                else
                    return std::atan(meas.value); 
            
            }


            /// @brief Get the hyperbolic sine of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            constexpr auto sinh(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::scalar>, 
                                      physics::measurement<physics::units::scalar>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::sinh(meas.value), std::fabs(std::cosh(meas.value)) * meas.uncertainty };

                else
                    return std::sinh(meas.value); 

            }


            /// @brief Get the hyperbolic cosine of a unitless_measurement
            template <typename MEAS_TYPE>
                 requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            constexpr auto cosh(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::scalar>, 
                                      physics::measurement<physics::units::scalar>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::cosh(meas.value), std::fabs(std::sinh(meas.value)) * meas.uncertainty };

                else
                    return std::cosh(meas.value); 

            }


            /// @brief Get the hyperbolic tangent of a unitless_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            constexpr auto tanh(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::scalar>, 
                                      physics::measurement<physics::units::scalar>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::tanh(meas.value), std::fabs(1. / std::pow(std::cosh(meas.value), 2)) * meas.uncertainty };

                else
                    return std::tanh(meas.value); 

            }


            /// @brief Get the hyperbolic arcsine of a radian_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            constexpr auto asinh(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::scalar>, 
                                      physics::measurement<physics::units::scalar>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::asinh(meas.value), meas.uncertainty / std::sqrt(1. + std::pow(meas.value, 2)) };
                            
                else
                    return std::asinh(meas.value);

            }


            /// @brief Get the hyperbolic arccosine of a radian_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            constexpr auto acosh(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::scalar>, 
                                      physics::measurement<physics::units::scalar>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::acosh(meas.value), meas.uncertainty / std::sqrt(std::pow(meas.value, 2) - 1) };
                            
                else
                    return std::acosh(meas.value);

            }


            /// @brief Get the hyperbolic arctangent of a radian_measurement
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
            constexpr auto atanh(const MEAS_TYPE& meas) noexcept 
                -> std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                      physics::umeasurement<physics::units::scalar>, 
                                      physics::measurement<physics::units::scalar>> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::atanh(meas.value), meas.uncertainty / (1. - std::pow(meas.value, 2)) };

                else
                    return std::atanh(meas.value);

            }


    } // namespace op


} // namespace scipp::math