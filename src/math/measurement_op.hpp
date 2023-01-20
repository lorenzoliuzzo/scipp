/**
 * @file    op.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-20
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {


    namespace op {


                /**
                 * @brief Take the square unit_base
                 * 
                 * @return consteval unit_base 
                 */
                consteval unit_base square(const unit_base& other) noexcept { 
                    
                    return unit_base(other.metre_ * 2, 
                                     other.second_ * 2, 
                                     other.kilogram_ * 2, 
                                     other.ampere_ * 2, 
                                     other.kelvin_ * 2, 
                                     other.mole_ * 2, 
                                     other.candela_ * 2,
                                     other.radian_ * 2);

                }



        /**
         * @brief Get the absolute measurement object
         * 
         * @param meas: measurement as l-value const reference
         * 
         * @return constexpr measurement
         */
        template <unit_base UB>
        constexpr measurement<UB> abs(const measurement<UB>& meas) noexcept { 
            
            return (meas.value() < 0.0) ? -meas : meas; 
        
        }


        /**
         * @brief Get the absolute measurement object
         * 
         * @param meas: measurement as r-value reference
         * 
         * @return constexpr measurement
         */
        template <unit_base UB>
        constexpr measurement<UB> abs(measurement<UB>&& meas) noexcept { 
            
            return (meas.value() < 0.0) ? -meas : meas; 
        
        }


        /**
         * @brief Get the sign of a measurement 
         * 
         * @param meas: measurement
         * 
         * @return constexpr int32_t
         */
        template <unit_base UB>
        constexpr int32_t sign(const measurement<UB>& meas) noexcept { 
            
            if (meas.value() == 0.) 
                return 0; 

            else 
                return (meas.value() > 0) ? 1 : -1; 
            
        }


        /**                  
         * @brief Invert a measurement
         * 
         * @param umeas: measurement as l-value const reference
         * 
         * @return constexpr measurement 
         * 
         * @note Cannot invert an measurement with a zero value
         * @note The uncertainty is not inverted
         */
        template <unit_base UB>
        constexpr measurement<UB.inv()> inv(const measurement<UB>& umeas) { 
            
            if (umeas.value() == 0) 
                throw std::runtime_error("Cannot invert a measurement with a zero value");

            return { 1 / umeas.value() };
            
        } 


        /**                  
         * @brief Invert a measurement
         * 
         * @param umeas: measurement as r-value reference
         * 
         * @return constexpr measurement 
         * 
         * @note Cannot invert an measurement with a zero value
         * @note The uncertainty is not inverted
         */
        template <unit_base UB>
        constexpr measurement<UB.inv()> inv(measurement<UB>&& umeas) { 
            
            if (umeas.value() == 0) 
                throw std::runtime_error("Cannot invert a measurement with a zero value");

            return { 1 / umeas.value() };
            
        } 


        /**
         * @brief Take the power of a measurement
         * 
         * @param meas: measurement as l-value const reference
         * @param power: int as l-value const reference
         * 
         * @return measurement 
         */
        template <unit_base UB>
        constexpr auto pow(const measurement<UB>& meas, const int& power) noexcept { 
            
            return measurement<UB.pow(power)>(std::pow(meas.value(), power), unit(UB.pow(power)));
            
        }        
        

        /**
         * @brief Take the power of a measurement
         * 
         * @param meas: measurement as r-value reference
         * @param power: int as l-value const reference
         * 
         * @return measurement 
         */
        template <unit_base UB>
        constexpr auto pow(measurement<UB>&& meas, const int& power) noexcept { 
            
            return measurement<UB.pow(power)>(std::pow(meas.value(), power), unit(UB.pow(power)));
            
        }


        /**
         * @brief Take the square of a measurement
         * 
         * @param meas: measurement as l-value const reference
         *
         * @return measurement 
         */
        template <unit_base UB>
        constexpr measurement<UB.square()> square(const measurement<UB>& meas) noexcept { 
            
            return { std::pow(meas.value(), 2) }; 
            
        }


        /**
         * @brief Take the square of a measurement
         * 
         * @param meas: measurement as r-value reference
         *
         * @return measurement 
         */
        template <unit_base UB>
        constexpr measurement<UB.square()> square(measurement<UB>&& meas) noexcept { 
            
            return { std::pow(meas.value(), 2) }; 
            
        }


        /**
         * @brief Take the cube of a measurement
         * 
         * @param meas: measurement as l-value const reference
         *
         * @return measurement 
         */
        template <unit_base UB>
        constexpr measurement<UB.cube()> cube(const measurement<UB>& meas) noexcept { 
            
            return { std::pow(meas.value(), 3) }; 
            
        }


        /**
         * @brief Take the cube of a measurement
         * 
         * @param meas: measurement as r-value reference
         *
         * @return measurement 
         */
        template <unit_base UB>
        constexpr measurement<UB.cube()> cube(measurement<UB>&& meas) noexcept { 
            
            return { std::pow(meas.value(), 3) }; 
            
        }


        /**
         * @brief Take the root power of a measurement
         * 
         * @param meas: measurement as l-value const reference
         * @param power: int as l-value const reference
         * 
         * @return measurement 
         */
        template <unit_base UB>
        constexpr auto root(const measurement<UB>& meas, const int& power) { 
            
            return measurement<UB.root(power)>(std::pow(meas.value(), 1.0 / power), unit(UB.root(power))); 
            
        }


        /**
         * @brief Take the root power of a measurement
         * 
         * @param meas: measurement as r-value reference
         * @param power: int as l-value const reference
         * 
         * @return measurement 
         */
        template <unit_base UB>
        constexpr auto root(measurement<UB>&& meas, const int& power) { 
            
            return measurement<UB.root(power)>(std::pow(meas.value(), 1.0 / power), unit(UB.root(power))); 
            
        }


        /**
         * @brief Take the square root of a measurement
         * 
         * @param meas: measurement as l-value const reference
         *
         * @return measurement
         */
        template <unit_base UB>
        constexpr measurement<UB.sqrt()> sqrt(const measurement<UB>& meas) { 
            
            return { std::sqrt(meas.value()) }; 
            
        }


        /**
         * @brief Take the square root of a measurement
         * 
         * @param meas: measurement as r-value reference
         *
         * @return measurement
         */
        template <unit_base UB>
        constexpr measurement<UB.sqrt()> sqrt(measurement<UB>&& meas) { 
            
            return { std::sqrt(meas.value()) }; 
            
        }


        /**
         * @brief Take the cubic root of a measurement
         * 
         * @param meas: measurement as l-value const reference
         *
         * @return measurement
         */
        template <unit_base UB>
        constexpr measurement<UB.cbrt()> cbrt(const measurement<UB>& meas) { 
            
            return { std::cbrt(meas.value()) }; 
            
        }


        /**
         * @brief Take the cubic root of a measurement
         * 
         * @param meas: measurement as r-value reference
         *
         * @return measurement
         */
        template <unit_base UB>
        constexpr measurement<UB.cbrt()> cbrt(measurement<UB>&& meas) { 
            
            return { std::cbrt(meas.value()) }; 
            
        }


        /**
         * @brief Take the exponential of a measurement
         * @note The base of the exponential is e
         * 
         * @param meas: measurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr measurement<basis::scalar>
         */
        constexpr measurement<basis::scalar> exp(const measurement<basis::scalar>& meas) noexcept { 
            
            return { std::exp(meas.value()) }; 
        
        }


        /**
         * @brief Take the logarithm of a measurement
         * @note The base of the logarithm is e
         * 
         * @param meas: measurement as l-value const reference
         * 
         * @return constexpr measurement
         */
        constexpr measurement<basis::scalar> log(const measurement<basis::scalar>& meas) noexcept { 
            
            return { std::log(meas.value()) };
        
        }
        

        /**
         * @brief Take the exponential base 10 of a measurement
         * 
         * @param meas: measurement as l-value const reference
         * 
         * @return constexpr measurement
         */
        constexpr measurement<basis::scalar> exp10(const measurement<basis::scalar>& meas) noexcept { 
            
            return { std::pow(10, meas.value()) };
        
        }


        /**
         * @brief Take the logarithm base 10 of a measurement
         * 
         * @param meas: measurement as l-value const reference
         * 
         * @return constexpr measurement
         */
        constexpr measurement<basis::scalar> log10(const measurement<basis::scalar>& meas) noexcept { 
                        
            return { std::log10(meas.value()) };
        
        }


        /**
         * @brief Take the sine of a measurement
         * 
         * @param meas: measurement<basis::radian> as l-value const reference
         * 
         * @return constexpr measurement<basis::scalar>
         */
        constexpr measurement<basis::scalar> sin(const measurement<basis::radian>& meas) noexcept { 
                        
            return { std::sin(meas.value()) };
        
        }


        /**
         * @brief Take the sine of a measurement
         * 
         * @param meas: measurement<basis::radian> as r-value reference
         * 
         * @return constexpr measurement<basis::scalar>
         */
        constexpr measurement<basis::scalar> sin(measurement<basis::radian>&& meas) noexcept { 
                        
            return { std::sin(meas.value()) };
        
        }


        /**
         * @brief Take the cosine of a measurement
         * 
         * @param meas: measurement<basis::radian> as l-value const reference
         * 
         * @return constexpr measurement<basis::scalar>
         */
        constexpr measurement<basis::scalar> cos(const measurement<basis::radian>& meas) noexcept { 
                        
            return { std::cos(meas.value()) };
        
        }


        /**
         * @brief Take the cosine of a measurement
         * 
         * @param meas: measurement<basis::radian> as r-value reference
         * 
         * @return constexpr measurement<basis::scalar>
         */
        constexpr measurement<basis::scalar> cos(measurement<basis::radian>&& meas) noexcept { 
                        
            return { std::cos(meas.value()) };
        
        }


        /**
         * @brief Take the tangent of a measurement
         * 
         * @param meas: measurement<basis::radian> as l-value const reference
         * 
         * @return constexpr measurement<basis::scalar>
         */
        constexpr measurement<basis::scalar> tan(const measurement<basis::radian>& meas) noexcept { 
                        
            return { std::tan(meas.value()) };

        }


        /**
         * @brief Take the tangent of a measurement
         * 
         * @param meas: measurement<basis::radian> as r-value reference
         * 
         * @return constexpr measurement<basis::scalar>
         */
        constexpr measurement<basis::scalar> tan(measurement<basis::radian>&& meas) noexcept { 
                        
            return { std::tan(meas.value()) };

        }


        /**
         * @brief Take the arcsine of a measurement
         * 
         * @param meas: measurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr measurement<basis::radian>
         */
        constexpr measurement<basis::radian> asin(const measurement<basis::scalar>& meas) noexcept { 
                        
            return { std::asin(meas.value()) };

        }


        /**
         * @brief Take the arcsine of a measurement
         * 
         * @param meas: measurement<basis::scalar> as r-value reference
         * 
         * @return constexpr measurement<basis::radian>
         */
        constexpr measurement<basis::radian> asin(measurement<basis::scalar>&& meas) noexcept { 
                        
            return { std::asin(meas.value()) };

        }


        /**
         * @brief Take the arccosine of a measurement
         * 
         * @param meas: measurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr measurement<basis::radian>
         */
        constexpr measurement<basis::radian> acos(const measurement<basis::scalar>& meas) noexcept { 
            
            return { std::acos(meas.value()) };

        }


        /**
         * @brief Take the arccosine of a measurement
         * 
         * @param meas: measurement<basis::scalar> as r-value reference
         * 
         * @return constexpr measurement<basis::radian>
         */
        constexpr measurement<basis::radian> acos(measurement<basis::scalar>&& meas) noexcept { 
            
            return { std::acos(meas.value()) };

        }


        /**
         * @brief Take the arctangent of a measurement
         * 
         * @param meas: measurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr measurement<basis::radian>
         */
        constexpr measurement<basis::radian> atan(const measurement<basis::scalar>& meas) noexcept { 
            
            return { std::atan(meas.value()) };

        }


        /**
         * @brief Take the arctangent of a measurement
         * 
         * @param meas: measurement<basis::scalar> as r-value reference
         * 
         * @return constexpr measurement<basis::radian>
         */
        constexpr measurement<basis::radian> atan(measurement<basis::scalar>&& meas) noexcept { 
            
            return { std::atan(meas.value()) };

        }


        /**
         * @brief Take the hyperbolic sine of a measurement
         * 
         * @param meas: measurement<basis::radian> as l-value const reference
         * 
         * @return constexpr measurement<basis::scalar>
         */
        constexpr measurement<basis::scalar> sinh(const measurement<basis::radian>& meas) noexcept { 
                        
            return { std::sinh(meas.value()) };

        }


        /**
         * @brief Take the hyperbolic sine of a measurement
         * 
         * @param meas: measurement<basis::radian> as r-value reference
         * 
         * @return constexpr measurement<basis::scalar>
         */
        constexpr measurement<basis::scalar> sinh(measurement<basis::radian>&& meas) noexcept { 
                        
            return { std::sinh(meas.value()) };

        }


        /**
         * @brief Take the hyperbolic cosine of a measurement
         * 
         * @param meas: measurement<basis::radian> as l-value const reference
         * 
         * @return constexpr measurement<basis::scalar>
         */
        constexpr measurement<basis::scalar> cosh(const measurement<basis::radian>& meas) noexcept { 
                        
            return { std::cosh(meas.value()) };
        
        }


        /**
         * @brief Take the hyperbolic cosine of a measurement
         * 
         * @param meas: measurement<basis::radian> as r-value reference
         * 
         * @return constexpr measurement<basis::scalar>
         */
        constexpr measurement<basis::scalar> cosh(measurement<basis::radian>&& meas) noexcept { 
                        
            return { std::cosh(meas.value()) };
        
        }


        /**
         * @brief Take the hyperbolic tangent of a measurement
         * 
         * @param meas: measurement<basis::radian> as l-value const reference
         * 
         * @return constexpr measurement<basis::scalar>
         */
        constexpr measurement<basis::scalar> tanh(const measurement<basis::radian>& meas) noexcept { 
                        
            return { std::tanh(meas.value()) };

        }


        /**
         * @brief Take the hyperbolic tangent of a measurement
         * 
         * @param meas: measurement<basis::radian> as r-value reference
         * 
         * @return constexpr measurement<basis::scalar>
         */
        constexpr measurement<basis::scalar> tanh(measurement<basis::radian>&& meas) noexcept { 
                        
            return { std::tanh(meas.value()) };

        }


        /**
         * @brief Take the hyperbolic arcsine of a measurement
         * 
         * @param meas: measurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr measurement<basis::radian>
         */
        constexpr measurement<basis::radian> asinh(const measurement<basis::scalar>& meas) noexcept { 
                        
            return { std::asinh(meas.value()) };

        }


        /**
         * @brief Take the hyperbolic arcsine of a measurement
         * 
         * @param meas: measurement<basis::scalar> as r-value reference
         * 
         * @return constexpr measurement<basis::radian>
         */
        constexpr measurement<basis::radian> asinh(measurement<basis::scalar>&& meas) noexcept { 
                        
            return { std::asinh(meas.value()) };

        }


        /**
         * @brief Take the hyperbolic arccosine of a measurement
         * 
         * @param meas: measurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr measurement<basis::radian>
         */
        constexpr measurement<basis::radian> acosh(const measurement<basis::scalar>& meas) noexcept { 
            
            return { std::acosh(meas.value()) };
        
        }


        /**
         * @brief Take the hyperbolic arccosine of a measurement
         * 
         * @param meas: measurement<basis::scalar> as r-value reference
         * 
         * @return constexpr measurement<basis::radian>
         */
        constexpr measurement<basis::radian> acosh(measurement<basis::scalar>&& meas) noexcept { 
            
            return { std::acosh(meas.value()) };
        
        }
        
        
        /**
         * @brief Take the hyperbolic arctangent of a measurement
         * 
         * @param meas: measurement<basis::scalar> as l-value const reference
         * 
         * @return constexpr measurement<basis::radian>
         */
        constexpr measurement<basis::radian> atanh(const measurement<basis::scalar>& meas) noexcept { 
                        
            return { std::atanh(meas.value()) };

        }


        /**
         * @brief Take the hyperbolic arctangent of a measurement
         * 
         * @param meas: measurement<basis::scalar> as r-value reference
         * 
         * @return constexpr measurement<basis::radian>
         */
        constexpr measurement<basis::radian> atanh(measurement<basis::scalar>&& meas) noexcept { 
                        
            return { std::atanh(meas.value()) };

        }


    } // namespace op
    

} // namespace scipp::math