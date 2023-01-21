/**
 * @file    unit_base_op.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-21
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {


    namespace op {


        /**
         * @brief Invert the units::unit_base
         *
         * @param other: units::unit_base as l-value const reference
         * 
         * @return constexpr units::unit_base
         */
        consteval units::unit_base inv(const units::unit_base& other) noexcept {
        
            return units::unit_base(-other.metre_, 
                                    -other.second_, 
                                    -other.kilogram_, 
                                    -other.ampere_, 
                                    -other.kelvin_, 
                                    -other.mole_, 
                                    -other.candela_,
                                    -other.radian_);

        }


        /**
         * @brief Take the power of the units::unit_base
         * 
         * @param other: units::unit_base as l-value const reference
         * @param power 
         * 
         * @return consteval units::unit_base 
         */
        consteval units::unit_base pow(const units::unit_base& other, const int& power) noexcept { 

            return units::unit_base(other.metre_ * power, 
                                    other.second_ * power, 
                                    other.kilogram_ * power, 
                                    other.ampere_ * power, 
                                    other.kelvin_ * power, 
                                    other.mole_ * power, 
                                    other.candela_ * power,
                                    other.radian_ * power);

        }


        /**
         * @brief Take the square power of the units::unit_base
         * 
         * @param other: units::unit_base as l-value const reference
         * 
         * @return consteval units::unit_base 
         */
        consteval units::unit_base square(const units::unit_base& other) noexcept { 

            return units::unit_base(other.metre_ * 2, 
                                    other.second_ * 2, 
                                    other.kilogram_ * 2, 
                                    other.ampere_ * 2, 
                                    other.kelvin_ * 2, 
                                    other.mole_ * 2, 
                                    other.candela_ * 2,
                                    other.radian_ * 2);

        }


        /**
         * @brief Take the cube power of the units::unit_base
         * 
         * @param other: units::unit_base as l-value const reference
         * 
         * @return consteval units::unit_base 
         */
        consteval units::unit_base cube(const units::unit_base& other) noexcept { 

            return units::unit_base(other.metre_ * 3, 
                                    other.second_ * 3, 
                                    other.kilogram_ * 3, 
                                    other.ampere_ * 3, 
                                    other.kelvin_ * 3, 
                                    other.mole_ * 3, 
                                    other.candela_ * 3,
                                    other.radian_ * 3);

        }


        /**
         * @brief Take the root power of the units::unit_base
         * 
         * @param other: units::unit_base as l-value const reference
         * @param power 
         * 
         * @return consteval units::unit_base 
         */
        consteval units::unit_base root(const units::unit_base& other, const int& power) noexcept { 

            if (other.has_valid_root(power)) 
                return units::unit_base(other.metre_ / power, 
                                        other.second_ / power, 
                                        other.kilogram_ / power, 
                                        other.ampere_ / power, 
                                        other.kelvin_ / power, 
                                        other.mole_ / power, 
                                        other.candela_ / power,
                                        other.radian_ / power);

        }


        /**
         * @brief Take the square root power of the units::unit_base
         * 
         * @param other: units::unit_base as l-value const reference
         * 
         * @return consteval units::unit_base 
         */
        consteval units::unit_base sqrt(const units::unit_base& other) noexcept { 

            if (other.has_valid_root(2)) 
                return units::unit_base(other.metre_ / 2, 
                                        other.second_ / 2, 
                                        other.kilogram_ / 2, 
                                        other.ampere_ / 2, 
                                        other.kelvin_ / 2, 
                                        other.mole_ / 2, 
                                        other.candela_ / 2,
                                        other.radian_ / 2);

        }


        /**
         * @brief Take the cubic root power of the units::unit_base
         * 
         * @param other: units::unit_base as l-value const reference
         * 
         * @return consteval units::unit_base 
         */
        consteval units::unit_base cbrt(const units::unit_base& other) noexcept { 

            if (other.has_valid_root(3)) 
                return units::unit_base(other.metre_ / 3, 
                                        other.second_ / 3, 
                                        other.kilogram_ / 3, 
                                        other.ampere_ / 3, 
                                        other.kelvin_ / 3, 
                                        other.mole_ / 3, 
                                        other.candela_ / 3,
                                        other.radian_ / 3);

        }


    } // namespace op


} // namespace scipp::math