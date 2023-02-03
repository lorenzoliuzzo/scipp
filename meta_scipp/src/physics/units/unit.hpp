/**
 * @file    unit.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {

    
    /// @brief units namespace contains the implementation of units of measurements
    namespace units {


        /** 
         * @brief unit is an union of an unit_base and an std::ratio prefix
         *
         * @tparam BASE: meta_base of the unit
         * @tparam PREFIX: std::ratio prefix of the unit
         */
        template <typename BASE, typename PREFIX = std::ratio<1, 1>>
        struct unit {


            using base = BASE;

            using prefix = PREFIX;

            using type = unit<BASE, PREFIX>; 


            // =============================================
            // static members
            // =============================================

                static constexpr double mult = static_cast<double>(PREFIX::num) / static_cast<double>(PREFIX::den);


            // =============================================
            // operators
            // =============================================

                friend inline std::ostream& operator<<(std::ostream& os, const unit& units) noexcept {

                    os << units.to_string(); 

                    return os; 

                }


            // =============================================
            // methods
            // =============================================

                static constexpr std::string to_string() {

                    return prefix_map.find(mult)->second + BASE::to_string(); 

                }


        }; // struct unit


        // =============================================
        // TRAITS
        // =============================================


        /// @brief is_unit is a trait to check if a type is an unit
        template <typename T>
        struct is_unit : std::false_type {};

        template <typename BASE, typename PREFIX>
        struct is_unit<unit<BASE, PREFIX>> : std::true_type {};


        template <typename BASE, typename PREFIX>
        struct is_unit<const unit<BASE, PREFIX>> : std::true_type {};


        template <typename BASE, typename PREFIX>
        struct is_unit<unit<BASE, PREFIX>&> : std::true_type {};


        template <typename BASE, typename PREFIX>
        struct is_unit<const unit<BASE, PREFIX>&> : std::true_type {};


        template <typename BASE, typename PREFIX>
        struct is_unit<unit<BASE, PREFIX>&&> : std::true_type {};


        template <typename BASE, typename PREFIX>
        struct is_unit<const unit<BASE, PREFIX>&&> : std::true_type {};


        template <typename T>
        inline constexpr bool is_unit_v = is_unit<T>::value;


        /// @brief Convert a value from the base unit to another unit 
        template <typename UNIT, typename = std::enable_if_t<is_unit_v<UNIT>>>
        static constexpr scalar convert(const scalar val, const UNIT&) {

            return val / UNIT::mult; 

        }


        /// @brief Convert a value from one unit to another 
        template <typename UNIT1, typename UNIT2, typename = std::enable_if_t<is_unit_v<UNIT1> && is_unit_v<UNIT2>>>
        static constexpr scalar convert(const scalar val, const UNIT1&, const UNIT2&) {

            return val * (UNIT1::mult / UNIT2::mult); 

        }
        

    } // namespace units


} // namespace scipp::physics