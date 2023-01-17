/**
 * @file    op.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-17
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {


    namespace op {



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
         * @brief Take the power of an umeasurement
         * 
         * @param umeas: umeasurement as l-value const reference
         * @param power: int as l-value const reference
         * 
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr auto pow(const umeasurement<UB>& umeas, const int& power) noexcept { 
            
            return umeasurement<UB.pow(power)>(std::pow(umeas.value(), power), std::fabs(power * std::pow(umeas.value(), power - 1)) * umeas.uncertainty(), unit(UB.pow(power)));
            
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
            
            return umeasurement<UB.pow(power)>(std::pow(umeas.value(), power), std::fabs(power * std::pow(umeas.value(), power - 1)) * umeas.uncertainty(), unit(UB.pow(power)));
            
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
         * @brief Take the square of an umeasurement
         * 
         * @param umeas: umeasurement as l-value const reference
         *
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr umeasurement<UB.square()> square(const umeasurement<UB>& umeas) noexcept { 
            
            return { std::pow(umeas.value(), 2), 2. * std::fabs(umeas.value()) * umeas.uncertainty() }; 
            
        }


        /**
         * @brief Take the square of an umeasurement
         * 
         * @param umeas: umeasurement as r-value reference
         *
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr umeasurement<UB.square()> square(umeasurement<UB>&& umeas) noexcept { 
            
            return { std::pow(umeas.value(), 2), 2. * std::fabs(umeas.value()) * umeas.uncertainty() }; 
            
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
         * @brief Take the cube of an umeasurement
         * 
         * @param umeas: umeasurement as l-value const reference
         *
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr umeasurement<UB.cube()> cube(const umeasurement<UB>& umeas) noexcept { 
            
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
        constexpr umeasurement<UB.cube()> cube(umeasurement<UB>&& umeas) noexcept { 
            
            return { std::pow(umeas.value(), 3), 3. * std::fabs(umeas.value()) * umeas.uncertainty() }; 
            
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
         * @brief Take the root power of an umeasurement
         * 
         * @param umeas: umeasurement as l-value const reference
         * @param power: int as l-value const reference
         * 
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr auto root(const umeasurement<UB>& umeas, const int& power) { 
            
            return umeasurement<UB.root(power)>(std::pow(umeas.value(), 1.0 / power), std::fabs(std::pow(umeas.value(), 1.0 / power - 1)) * umeas.uncertainty() / power, unit(UB.root(power))); 
            
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
            
            return umeasurement<UB.root(power)>(std::pow(umeas.value(), 1.0 / power), std::fabs(std::pow(umeas.value(), 1.0 / power - 1)) * umeas.uncertainty() / power, unit(UB.root(power))); 
            
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
         * @brief Take the square root of an umeasurement
         * 
         * @param umeas: umeasurement as l-value const reference
         *
         * @return umeasurement
         */
        template <unit_base UB>
        constexpr umeasurement<UB.sqrt()> sqrt(const umeasurement<UB>& umeas) { 
            
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
        constexpr umeasurement<UB.sqrt()> sqrt(umeasurement<UB>&& umeas) { 
            
            return { std::sqrt(umeas.value()), umeas.uncertainty() / (2. * std::sqrt(umeas.value())) }; 
            
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
         * @brief Take the cubic root of an umeasurement
         * 
         * @param umeas: umeasurement as l-value const reference
         *         
         * @return umeasurement
         */               
        template <unit_base UB>
        constexpr umeasurement<UB.cbrt()> cbrt(const umeasurement<UB>& umeas) { 
            
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
        constexpr umeasurement<UB.cbrt()> cbrt(umeasurement<UB>&& umeas) { 
            
            return { std::cbrt(umeas.value()), std::pow(umeas.value(), - 2. / 3.) * umeas.uncertainty() / 3. };
            
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