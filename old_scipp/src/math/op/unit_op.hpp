/**
 * @file    unit_op.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-21
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {


    namespace op {


        /**
         * @brief Invert the unit
         *
         * @param other: units::unit<UB> as l-value const reference
         * 
         * @return consteval unit   
         */
        template <units::unit_base UB>
        consteval units::unit<op::inv(UB)> inv(const units::unit<UB>& other) noexcept { 
            
            return { 1. / other.prefix() }; 
            
        }


        /**
         * @brief Take the power of the unit
         * 
         * @param other: units::unit<UB> as l-value const reference
         * @param power
         * 
         * @return consteval unit 
         */
        template <units::unit_base UB>
        consteval auto pow(const units::unit<UB>& other, const int& power) noexcept { 
            
            return { op::pow(UB, power), std::pow(other.prefix(), power) }; 
            
        }


        /**
         * @brief Take the square of the unit
         * 
         * @param other: units::unit<UB> as l-value const reference
         *
         * @return consteval unit 
         */
        template <units::unit_base UB>
        consteval units::unit<op::square(UB)> square(const units::unit<UB>& other) noexcept { 
            
            return { std::pow(other.prefix(), 2) }; 
            
        }


        /**
         * @brief Take the cube of the unit
         * 
         * @param other: units::unit<UB> as l-value const reference
         *
         * @return consteval unit 
         */
        template <units::unit_base UB>
        consteval units::unit<op::cube(UB)> cube(const units::unit<UB>& other) noexcept { 
            
            return { std::pow(other.prefix(), 3) }; 
            
        }


        /**
         * @brief Take the root of the unit
         * 
         * @param other: units::unit<UB> as l-value const reference
         * @param power
         * 
         * @return consteval unit 
         */
        template <units::unit_base UB>
        consteval auto root(const units::unit<UB>& other, const int& power) { 
            
            return { op::root(UB, power), std::pow(other.prefix(), 1. / power) }; 

        }


        /**
         * @brief Take the square root of the unit
         * 
         * @param other: units::unit<UB> as l-value const reference
         *
         * @return consteval unit 
         */
        template <units::unit_base UB>
        consteval units::unit<op::sqrt(UB)> sqrt(const units::unit<UB>& other) { 
            
            return { op::sqrt(UB), std::sqrt(other.prefix()) }; 
            
        }


        /**
         * @brief Take the cube root of the unit
         * 
         * @param other: units::unit<UB> as l-value const reference
         *
         * @return consteval unit 
         */
        template <units::unit_base UB>
        consteval units::unit<op::cbrt(UB)> cbrt(const units::unit<UB>& other) { 
            
            return { op::cbrt(UB), std::cbrt(other.prefix()) }; 
            
        }
        

    } // namespace op


} // namespace scipp::math