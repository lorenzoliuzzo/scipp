/**
 * @file    umeasurement_op.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-20
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {


    namespace op {


        /**
         * @brief Get the absolute umeasurement object
         * 
         * @param umeas: umeasurement as l-value const reference
         * 
         * @return constexpr umeasurement
         */
        template <unit_base UB>
        constexpr umeasurement<UB> abs(const umeasurement<UB>& umeas) noexcept { 
            
            return (umeas.value() < 0.0) ? -umeas : umeas; 
        
        }


        /**
         * @brief Get the absolute umeasurement object
         * 
         * @param umeas: umeasurement as r-value reference
         * 
         * @return constexpr umeasurement
         */
        template <unit_base UB>
        constexpr umeasurement<UB> abs(umeasurement<UB>&& umeas) noexcept { 
            
            return (umeas.value() < 0.0) ? -umeas : umeas; 
        
        }


        /**
         * @brief Get the sign of an umeasurement 
         * 
         * @param umeas: umeasurement
         * 
         * @return constexpr int32_t
         */
        template <unit_base UB>
        constexpr int32_t sign(const umeasurement<UB>& umeas) noexcept { 
            
            if (umeas.value() == 0.) 
                return 0; 

            else 
                return (umeas.value() > 0) ? 1 : -1; 
            
        }


        /**                  
         * @brief Invert an umeasurement
         * 
         * @param umeas: umeasurement as l-value const reference
         * 
         * @return constexpr umeasurement 
         * 
         * @note Cannot invert an umeasurement with a zero value
         * @note The uncertainty is not inverted
         */
        template <unit_base UB>
        constexpr umeasurement<math::op::inv(UB)> inv(const umeasurement<UB>& umeas) { 
            
            if (umeas.value() == 0) 
                throw std::runtime_error("Cannot invert an umeasurement with a zero value");

            return { 1 / umeas.value(), umeas.uncertainty_ / std::pow(umeas.value(), 2) };
            
        } 


        /**                  
         * @brief Invert an umeasurement
         * 
         * @param umeas: umeasurement as r-value reference
         * 
         * @return constexpr umeasurement 
         * 
         * @note Cannot invert an umeasurement with a zero value
         * @note The uncertainty is not inverted
         */
        template <unit_base UB>
        constexpr umeasurement<math::op::inv(UB)> inv(umeasurement<UB>&& umeas) { 
            
            if (umeas.value() == 0) 
                throw std::runtime_error("Cannot invert an umeasurement with a zero value");

            return { 1 / umeas.value(), umeas.uncertainty_ / std::pow(umeas.value(), 2) };
            
        } 
    

        /**
         * @brief Take the power of an umeasurement
         * 
         * @param umeas: umeasurement as l-value const reference
         * @param power: int as l-value const reference
         * 
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr auto pow(const umeasurement<UB>& umeas, const int& power) noexcept { 
            
            return umeasurement<math::op::pow(UB, power)>(std::pow(umeas.value(), power), std::fabs(power * std::pow(umeas.value(), power - 1)) * umeas.uncertainty(), unit(math::op::pow(UB, power)));
            
        }        
        

        /**
         * @brief Take the power of an umeasurement
         * 
         * @param umeas: umeasurement as r-value reference
         * @param power: int as l-value const reference
         * 
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr auto pow(umeasurement<UB>&& umeas, const int& power) noexcept { 
            
            return umeasurement<math::op::pow(UB, power)>(std::pow(umeas.value(), power), std::fabs(power * std::pow(umeas.value(), power - 1)) * umeas.uncertainty(), unit(math::op::pow(UB, power)));
            
        }


        /**
         * @brief Take the square of an umeasurement
         * 
         * @param umeas: umeasurement as l-value const reference
         *
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr umeasurement<math::op::square(UB)> square(const umeasurement<UB>& umeas) noexcept { 
            
            return { std::pow(umeas.value(), 2),  
            
        }


        /**
         * @brief Take the square of an umeasurement
         * 
         * @param umeas: umeasurement as r-value reference
         *
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr umeasurement<math::op::square(UB)> square(umeasurement<UB>&& umeas) noexcept { 
            
            return { std::pow(umeas.value(), 2), 2. * std::fabs(umeas.value()) * umeas.uncertainty() }; 
            
        }
        
        
        /**
         * @brief Take the cube of an umeasurement
         * 
         * @param umeas: umeasurement as l-value const reference
         *
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr umeasurement<math::op::cube(UB)> cube(const umeasurement<UB>& umeas) noexcept { 
            
            return { std::pow(umeas.value(), 3), 3. * std::fabs(umeas.value()) * umeas.uncertainty() }; 
            
        }


        /**
         * @brief Take the cube of an umeasurement
         * 
         * @param umeas: umeasurement as r-value reference
         *
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr umeasurement<math::op::cube(UB)> cube(umeasurement<UB>&& umeas) noexcept { 
            
            return { std::pow(umeas.value(), 3), 3. * std::fabs(umeas.value()) * umeas.uncertainty() }; 
            
        }


        /**
         * @brief Take the root power of an umeasurement
         * 
         * @param umeas: umeasurement as l-value const reference
         * @param power: int as l-value const reference
         * 
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr auto root(const umeasurement<UB>& umeas, const int& power) { 
            
            return umeasurement<math::op::root(UB, power)>(std::pow(umeas.value(), 1.0 / power), std::fabs(std::pow(umeas.value(), 1.0 / power - 1)) * umeas.uncertainty() / power, unit(math::op::root(UB, power))); 
            
        }


        /**
         * @brief Take the root power of an umeasurement
         * 
         * @param umeas: umeasurement as r-value reference
         * @param power: int as l-value const reference
         * 
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr auto root(umeasurement<UB>&& umeas, const int& power) { 
            
            return umeasurement<math::op::root(UB, power)>(std::pow(umeas.value(), 1.0 / power), std::fabs(std::pow(umeas.value(), 1.0 / power - 1)) * umeas.uncertainty() / power, unit(math::op::root(UB, power))); 
            
        }


        /**
         * @brief Take the square root of an umeasurement
         * 
         * @param umeas: umeasurement as l-value const reference
         *
         * @return umeasurement
         */
        template <unit_base UB>
        constexpr umeasurement<math::op::sqrt(UB)> sqrt(const umeasurement<UB>& umeas) { 
            
            return { std::sqrt(umeas.value()), umeas.uncertainty() / (2. * std::sqrt(umeas.value())) }; 
            
        }


        /**
         * @brief Take the square root of an umeasurement
         * 
         * @param umeas: umeasurement as r-value reference
         *
         * @return umeasurement
         */
        template <unit_base UB>
        constexpr umeasurement<math::op::sqrt(UB)> sqrt(umeasurement<UB>&& umeas) { 
            
            return { std::sqrt(umeas.value()), umeas.uncertainty() / (2. * std::sqrt(umeas.value())) }; 
            
        }


        /**
         * @brief Take the cubic root of an umeasurement
         * 
         * @param umeas: umeasurement as l-value const reference
         *         
         * @return umeasurement
         */               
        template <unit_base UB>
        constexpr umeasurement<math::op::cbrt(UB)> cbrt(const umeasurement<UB>& umeas) { 
            
            return { std::cbrt(umeas.value()), std::pow(umeas.value(), - 2. / 3.) * umeas.uncertainty() / 3. };
            
        }


        /**
         * @brief Take the cubic root of an umeasurement
         * 
         * @param umeas: umeasurement as r-value reference
         *         
         * @return umeasurement
         */               
        template <unit_base UB>
        constexpr umeasurement<math::op::cbrt(UB)> cbrt(umeasurement<UB>&& umeas) { 
            
            return { std::cbrt(umeas.value()), std::pow(umeas.value(), - 2. / 3.) * umeas.uncertainty() / 3. };
            
        }


        /**
         * @brief Take the exponential of an umeasurement
         * @note The base of the exponential is e
         * 
         * @param umeas: umeasurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr umeasurement<basis::scalar>
         */
        constexpr umeasurement<basis::scalar> exp(const umeasurement<basis::scalar>& umeas) noexcept { 
            
            return { std::exp(umeas.value()), std::exp(umeas.uncertainty()) }; 
        
        }


        /**
         * @brief Take the sine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::radian> as l-value const reference
         * 
         * @return constexpr umeasurement<basis::scalar>
         */
        constexpr umeasurement<basis::scalar> sin(const umeasurement<basis::radian>& umeas) noexcept { 
                        
            return { std::sin(umeas.value()), std::fabs(std::cos(umeas.value())) * umeas.uncertainty() };
        
        }


        /**
         * @brief Take the sine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::radian> as r-value reference
         * 
         * @return constexpr umeasurement<basis::scalar>
         */
        constexpr umeasurement<basis::scalar> sin(umeasurement<basis::radian>&& umeas) noexcept { 
                        
            return { std::sin(umeas.value()), std::fabs(std::cos(umeas.value())) * umeas.uncertainty() };
        
        }


        /**
         * @brief Take the cosine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::radian> as l-value const reference
         * 
         * @return constexpr umeasurement<basis::scalar>
         */
        constexpr umeasurement<basis::scalar> cos(const umeasurement<basis::radian>& umeas) noexcept { 
                        
            return { std::cos(umeas.value()), std::fabs(-std::sin(umeas.value())) * umeas.uncertainty() };
        
        }


        /**
         * @brief Take the cosine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::radian> as r-value reference
         * 
         * @return constexpr umeasurement<basis::scalar>
         */
        constexpr umeasurement<basis::scalar> cos(umeasurement<basis::radian>&& umeas) noexcept { 
                        
            return { std::cos(umeas.value()), std::fabs(-std::sin(umeas.value())) * umeas.uncertainty() };
        
        }


        /**
         * @brief Take the tangent of an umeasurement
         * 
         * @param umeas: umeasurement<basis::radian> as l-value const reference
         * 
         * @return constexpr umeasurement<basis::scalar>
         */
        constexpr umeasurement<basis::scalar> tan(const umeasurement<basis::radian>& umeas) noexcept { 
                        
            return { std::tan(umeas.value()), (1 + std::pow(umeas.value(), 2)) * umeas.uncertainty() };

        }


        /**
         * @brief Take the tangent of an umeasurement
         * 
         * @param umeas: umeasurement<basis::radian> as r-value reference
         * 
         * @return constexpr umeasurement<basis::scalar>
         */
        constexpr umeasurement<basis::scalar> tan(umeasurement<basis::radian>&& umeas) noexcept { 
                        
            return { std::tan(umeas.value()), (1 + std::pow(umeas.value(), 2)) * umeas.uncertainty() };

        }    


        /**
         * @brief Take the arcsine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr umeasurement<basis::radian>
         */
        constexpr umeasurement<basis::radian> asin(const umeasurement<basis::scalar>& umeas) noexcept { 

            return { std::asin(umeas.value()), umeas.uncertainty() / std::sqrt(1 - std::pow(umeas.value(), 2)) };

        }


        /**
         * @brief Take the arcsine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::scalar> as r-value reference
         * 
         * @return constexpr umeasurement<basis::radian>
         */
        constexpr umeasurement<basis::radian> asin(umeasurement<basis::scalar>&& umeas) noexcept { 

            return { std::asin(umeas.value()), umeas.uncertainty() / std::sqrt(1 - std::pow(umeas.value(), 2)) };

        }


        /**
         * @brief Take the arccosine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr umeasurement<basis::radian>
         */
        constexpr umeasurement<basis::radian> acos(const umeasurement<basis::scalar>& umeas) noexcept { 
            
            return { std::acos(umeas.value()), umeas.uncertainty() / std::sqrt(1 - std::pow(umeas.value(), 2)) };

        }


        /**
         * @brief Take the arccosine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::scalar> as r-value reference
         * 
         * @return constexpr umeasurement<basis::radian>
         */
        constexpr umeasurement<basis::radian> acos(umeasurement<basis::scalar>&& umeas) noexcept { 
            
            return { std::acos(umeas.value()), umeas.uncertainty() / std::sqrt(1 - std::pow(umeas.value(), 2)) };

        }


        /**
         * @brief Take the arctangent of an umeasurement
         * 
         * @param umeas: umeasurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr umeasurement<basis::radian>
         */
        constexpr umeasurement<basis::radian> atan(const umeasurement<basis::scalar>& umeas) noexcept { 
            
            return { std::atan(umeas.value()), umeas.uncertainty() / (1 + std::pow(umeas.value(), 2)) };

        }


        /**
         * @brief Take the arctangent of an umeasurement
         * 
         * @param umeas: umeasurement<basis::scalar> as r-value reference
         * 
         * @return constexpr umeasurement<basis::radian>
         */
        constexpr umeasurement<basis::radian> atan(umeasurement<basis::scalar>&& umeas) noexcept { 
            
            return { std::atan(umeas.value()), umeas.uncertainty() / (1 + std::pow(umeas.value(), 2)) };

        }


        /**
         * @brief Take the hyperbolic sine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::radian> as l-value const reference
         * 
         * @return constexpr umeasurement<basis::scalar>
         */
        constexpr umeasurement<basis::scalar> sinh(const umeasurement<basis::radian>& umeas) noexcept { 
                        
            return { std::sinh(umeas.value()), std::cosh(umeas.value()) * umeas.uncertainty() };

        }


        /**
         * @brief Take the hyperbolic sine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::radian> as r-value reference
         * 
         * @return constexpr umeasurement<basis::scalar>
         */
        constexpr umeasurement<basis::scalar> sinh(umeasurement<basis::radian>&& umeas) noexcept { 
                        
            return { std::sinh(umeas.value()), std::cosh(umeas.value()) * umeas.uncertainty() };

        }


        /**
         * @brief Take the hyperbolic cosine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::radian> as l-value const reference
         * 
         * @return constexpr umeasurement<basis::scalar>
         */
        constexpr umeasurement<basis::scalar> cosh(const umeasurement<basis::radian>& umeas) noexcept { 
                        
            return { std::cosh(umeas.value()), std::fabs(std::sinh(umeas.value())) * umeas.uncertainty() };
        
        }


        /**
         * @brief Take the hyperbolic cosine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::radian> as r-value reference
         * 
         * @return constexpr umeasurement<basis::scalar>
         */
        constexpr umeasurement<basis::scalar> cosh(umeasurement<basis::radian>&& umeas) noexcept { 
                        
            return { std::cosh(umeas.value()), std::fabs(std::sinh(umeas.value())) * umeas.uncertainty() };
        
        }


        /**
         * @brief Take the hyperbolic tangent of an umeasurement
         * 
         * @param umeas: umeasurement<basis::radian> as l-value const reference
         * 
         * @return constexpr umeasurement<basis::scalar>
         */
        constexpr umeasurement<basis::scalar> tanh(const umeasurement<basis::radian>& umeas) noexcept { 
                        
            return { std::tanh(umeas.value()), std::fabs((1 - std::pow(umeas.value(), 2))) * umeas.uncertainty() };

        }


        /**
         * @brief Take the hyperbolic tangent of an umeasurement
         * 
         * @param umeas: umeasurement<basis::radian> as r-value reference
         * 
         * @return constexpr umeasurement<basis::scalar>
         */
        constexpr umeasurement<basis::scalar> tanh(umeasurement<basis::radian>&& umeas) noexcept { 
                        
            return { std::tanh(umeas.value()), std::fabs((1 - std::pow(umeas.value(), 2))) * umeas.uncertainty() };

        }


        /**
         * @brief Take the hyperbolic arcsine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr umeasurement<basis::radian>
         */
        constexpr umeasurement<basis::radian> asinh(const umeasurement<basis::scalar>& umeas) noexcept { 
                        
            return { std::asinh(umeas.value()), umeas.uncertainty() / std::sqrt(std::pow(umeas.value(), 2) + 1) };

        }


        /**
         * @brief Take the hyperbolic arcsine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::scalar> as r-value reference
         * 
         * @return constexpr umeasurement<basis::radian>
         */
        constexpr umeasurement<basis::radian> asinh(umeasurement<basis::scalar>&& umeas) noexcept { 
                        
            return { std::asinh(umeas.value()), umeas.uncertainty() / std::sqrt(std::pow(umeas.value(), 2) + 1) };

        }


        /**
         * @brief Take the hyperbolic arccosine of an umeasurement
         * 
         * @param umeas: umeasurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr umeasurement<basis::radian>
         */
        constexpr umeasurement<basis::radian> acosh(const umeasurement<basis::scalar>& umeas) { 
                        
            return { std::acosh(umeas.value()), umeas.uncertainty() / std::fabs(std::sqrt(std::pow(umeas.value(), 2) - 1)) };
        
        }


        /**
         * @brief Take the hyperbolic arccosine of an umeasurement
         *
         * @param umeas: umeasurement<basis::scalar> as r-value reference
         * 
         * @return constexpr umeasurement<basis::radian>
         */
        constexpr umeasurement<basis::radian> acosh(umeasurement<basis::scalar>&& umeas) { 
                        
            return { std::acosh(umeas.value()), umeas.uncertainty() / std::fabs(std::sqrt(std::pow(umeas.value(), 2) - 1)) };
        
        }

        
        /**
         * @brief Take the hyperbolic arctangent of an umeasurement
         * 
         * @param umeas: umeasurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr umeasurement<basis::radian>
         */
        constexpr umeasurement<basis::radian> atanh(const umeasurement<basis::scalar>& umeas) noexcept { 
                        
            return { std::atanh(umeas.value()), umeas.uncertainty() / std::fabs(std::sqrt(1 - std::pow(umeas.value(), 2))) };
        
        }


        /**
         * @brief Take the hyperbolic arctangent of an umeasurement
         *
         * @param umeas: umeasurement<basis::scalar> as r-value reference
         * 
         * @return constexpr umeasurement<basis::radian>
         */
        constexpr umeasurement<basis::radian> atanh(umeasurement<basis::scalar>&& umeas) noexcept { 
                        
            return { std::atanh(umeas.value()), umeas.uncertainty() / std::fabs(std::sqrt(1 - std::pow(umeas.value(), 2))) };
        
        }


    } // namespace op
    

} // namespace scipp::math