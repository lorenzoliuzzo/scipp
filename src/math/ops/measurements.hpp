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


        template <typename MEAS1, typename MEAS2>
            requires (physics::are_measurements_v<MEAS1, MEAS2>)
        struct measurements_div { 
            
            using type = physics::measurement<math::op::base_division_t<typename MEAS1::base, typename MEAS2::base>>; 
            
        };

        template <typename T1, typename T2>
        using measurements_div_t = typename measurements_div<T1, T2>::type;


        template <typename T>
        struct measurement_inv { 
            
            using type = T; 

        }; 

        template <typename BASE>
            requires (physics::is_base_v<BASE>)
        struct measurement_inv<physics::measurement<BASE>> { 
            
            using type = physics::measurement<math::op::base_invert_t<BASE>>; 

        };

        template <typename BASE>
            requires (physics::is_base_v<BASE>)
        struct measurement_inv<physics::umeasurement<BASE>> { 
            
            using type = physics::measurement<math::op::base_invert_t<BASE>>; 

        };

        template <typename... Ts>
        using measurement_inv_t = typename measurement_inv<Ts...>::type;


        template <typename T, int>
        struct measurement_pow { 
            
            using type = T; 

        }; 

        template <typename BASE_TYPE, int POWER>
            requires (physics::is_base_v<BASE_TYPE> && POWER > 0)
        struct measurement_pow<physics::measurement<BASE_TYPE>, POWER> { 
            
            using type = physics::measurement<math::op::base_pow_t<BASE_TYPE, POWER>>; 

        };


        template <typename BASE_TYPE, int POWER>
            requires (physics::is_base_v<BASE_TYPE> && POWER > 0)
        struct measurement_pow<physics::umeasurement<BASE_TYPE>, POWER> { 
            
            using type = physics::umeasurement<math::op::base_pow_t<BASE_TYPE, POWER>>; 

        };

        template <typename T, int POWER>
        using measurement_pow_t = typename measurement_pow<T, POWER>::type;


        template <typename T>
        using measurement_square_t = measurement_pow_t<T, 2>;

        template <typename T>
        using measurement_cube_t = measurement_pow_t<T, 3>;


        template <typename T, int>
        struct measurement_root { 
            
            using type = T; 

        }; 

        template <typename BASE_TYPE, int POWER>
            requires (physics::is_base_v<BASE_TYPE> && POWER > 0)
        struct measurement_root<physics::measurement<BASE_TYPE>, POWER> { 
            
            using type = physics::measurement<math::op::base_root_t<BASE_TYPE, POWER>>; 

        };


        template <typename T, int POWER>
        using measurement_root_t = typename measurement_root<T, POWER>::type;


        template <typename T>
        using measurement_sqrt_t = measurement_root_t<T, 2>;

        template <typename T>
        using measurement_cbrt_t = measurement_root_t<T, 3>;



        // ====================================================================================================
        // Utility operations
        // ====================================================================================================

            /// @brief Get the type of the inverse of a measurement
            template <typename MEAS_TYPE> 
                requires (physics::is_generic_measurement_v<MEAS_TYPE>)
            struct measurement_invert : public std::conditional_t<physics::is_measurement_v<MEAS_TYPE>, 
                                                                   physics::measurement<op::base_invert_t<typename MEAS_TYPE::base>>, 
                                                                   physics::umeasurement<op::base_invert_t<typename MEAS_TYPE::base>>> {};

            template <typename MEAS_TYPE>   
            using measurement_invert_t = typename measurement_invert<MEAS_TYPE>::type;


            /// @brief Get the inverse of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto invert(const MEAS_TYPE& meas) 
                -> measurement_invert_t<MEAS_TYPE> {            

                if (meas.value == 0.0) 
                    throw std::runtime_error("Cannot invert a zero measurement");

                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { 1.0 / meas.value, meas.uncertainty / std::pow(meas.value, 2) };

                else 
                    return { 1.0 / meas.value }; 
            
            }

            /// @brief Get the type of the multiplication of measurements as a parameter pack
            template <typename... MEAS_TYPES>
                requires (physics::are_generic_measurements_v<MEAS_TYPES...>)
            struct measurements_multiply {

                using base = op::base_product_t<typename MEAS_TYPES::base...>;

                static constexpr bool is_measurement = physics::are_measurements_v<MEAS_TYPES...>;
                static constexpr bool is_umeasurement = physics::are_umeasurements_v<MEAS_TYPES...>;

                using type = std::conditional_t<is_measurement && !is_umeasurement,
                                                physics::measurement<base>,
                                                std::conditional_t<!is_measurement && is_umeasurement,
                                                                    physics::umeasurement<base>,
                                                                    physics::measurement<base>>>;

            };

            template <typename... MEAS_TYPES>
            using measurements_multiply_t = typename measurements_multiply<MEAS_TYPES...>::type;


            /// @brief Get the type of the division of measurements
            template <typename MEAS1, typename MEAS2> 
                requires (physics::are_generic_measurements_v<MEAS1, MEAS2>)
            struct measurements_divide {

                using base = op::base_division_t<typename MEAS1::base, typename MEAS2::base>;

                static constexpr bool is_measurement = physics::are_measurements_v<MEAS1, MEAS2>;
                static constexpr bool is_umeasurement = physics::are_umeasurements_v<MEAS1, MEAS2>;

                using type = std::conditional_t<is_measurement && !is_umeasurement,
                                                physics::measurement<base>,
                                                std::conditional_t<!is_measurement && is_umeasurement,
                                                                    physics::umeasurement<base>,
                                                                    physics::measurement<base>>>;

            };

            template <typename MEAS1, typename MEAS2>
            using measurements_divide_t = typename measurements_divide<MEAS1, MEAS2>::type;


            /// @brief Get the type of measurement raised to a power
            template <typename MEAS_TYPE, int POWER_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE>)
            struct measurements_pow {

                using base = op::base_pow_t<typename MEAS_TYPE::base, POWER_TYPE>;

                static constexpr bool is_measurement = physics::is_measurement_v<MEAS_TYPE>;
                static constexpr bool is_umeasurement = physics::is_umeasurement_v<MEAS_TYPE>;

                using type = std::conditional_t<is_measurement && !is_umeasurement,
                                                physics::measurement<base>,
                                                std::conditional_t<!is_measurement && is_umeasurement,
                                                                    physics::umeasurement<base>,
                                                                    physics::measurement<base>>>;

            };

            template <typename MEAS_TYPE, int POWER_TYPE>
            using measurements_pow_t = typename measurements_pow<MEAS_TYPE, POWER_TYPE>::type;

            template <typename MEAS_TYPE>
            using measurements_square_t = measurements_pow_t<MEAS_TYPE, 2>;

            template <typename MEAS_TYPE>
            using measurements_cube_t = measurements_pow_t<MEAS_TYPE, 3>;

            /// @brief Get the power of a measurement
            template <int POWER, typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto pow(const MEAS_TYPE& meas) noexcept
                -> measurements_pow_t<MEAS_TYPE, POWER> { 
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::pow(meas.value, POWER), std::fabs(POWER * std::pow(meas.value, POWER - 1)) * meas.uncertainty };
                
                else 
                    return std::pow(meas.value, POWER); 

            }       

            /// @brief Get the square of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto square(const MEAS_TYPE& meas) noexcept 
                -> measurements_square_t<MEAS_TYPE> {

                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::pow(meas.value, 2), 2.0 * std::fabs(meas.value) * meas.uncertainty }; 

                else 
                    return { std::pow(meas.value, 2) }; 
            
            }

            /// @brief Get the cube of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto cube(const MEAS_TYPE& meas) noexcept 
                -> measurements_cube_t<MEAS_TYPE> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::pow(meas.value, 3), 3. * std::fabs(meas.value) * meas.uncertainty }; 

                else 
                    return std::pow(meas.value, 3); 
            
            }


            /// @brief Get the type of measurement raised to a power
            template <typename MEAS_TYPE, int POWER_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE>)
            struct measurements_root {
                
                using base = op::base_root_t<typename MEAS_TYPE::base, POWER_TYPE>;

                static constexpr bool is_measurement = physics::is_measurement_v<MEAS_TYPE>;
                static constexpr bool is_umeasurement = physics::is_umeasurement_v<MEAS_TYPE>;

                using type = std::conditional_t<is_measurement && !is_umeasurement,
                                                physics::measurement<base>,
                                                std::conditional_t<!is_measurement && is_umeasurement,
                                                                    physics::umeasurement<base>,
                                                                    physics::measurement<base>>>;

            };

            template <typename MEAS_TYPE, int POWER_TYPE>
            using measurements_root_t = typename measurements_root<MEAS_TYPE, POWER_TYPE>::type;

            template <typename MEAS_TYPE>
            using measurements_sqrt_t = measurements_root_t<MEAS_TYPE, 2>;

            template <typename MEAS_TYPE>
            using measurements_cbrt_t = measurements_root_t<MEAS_TYPE, 3>;

            /// @brief Get the power of a measurement
            template <int POWER, typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto root(const MEAS_TYPE& meas) 
                -> measurements_root_t<MEAS_TYPE, POWER> {

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
                -> measurements_sqrt_t<MEAS_TYPE> {
                
                if constexpr (physics::is_umeasurement_v<MEAS_TYPE>)
                    return { std::sqrt(meas.value), 0.5 * meas.uncertainty / std::sqrt(meas.value) };

                else 
                    return std::sqrt(meas.value); 
            
            }

            /// @brief Get the square root of a measurement
            template <typename MEAS_TYPE>
                requires physics::is_generic_measurement_v<MEAS_TYPE>
            constexpr auto cbrt(const MEAS_TYPE& meas) noexcept 
                -> measurements_cbrt_t<MEAS_TYPE> {
                
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