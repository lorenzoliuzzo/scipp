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


            // =============================================
            // aliases
            // =============================================

                using base = BASE;

                using prefix = PREFIX;

                using type = unit<BASE, PREFIX>; 


            // =============================================
            // static members
            // =============================================

                inline static constexpr double mult = static_cast<double>(PREFIX::num) / static_cast<double>(PREFIX::den);


            // =============================================
            // operators
            // =============================================

                friend inline std::ostream& operator<<(std::ostream& os, const unit& units) noexcept {

                    return os << units.to_string();

                }


            // =============================================
            // methods
            // =============================================

                inline static constexpr std::string to_string() noexcept {

                    return prefix_map.find(mult)->second + BASE::to_string(); 

                }


                /// @brief Convert a value from the base unit to another unit 
                template <typename UNIT, typename = std::enable_if_t<is_same_base_v<BASE, typename UNIT::base>>>
                inline static constexpr scalar convert(const scalar val, const UNIT&) noexcept {

                    return val * mult / UNIT::mult; 

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
        

    } // namespace units


} // namespace scipp::physics