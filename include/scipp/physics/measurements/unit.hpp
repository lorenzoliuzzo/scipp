/**
 * @file    physics/measurements/unit.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the unit struct and its type traits.
 * @date    2023-03-23
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {

    
    /// @brief  Struct unit is an union of an base_quantity and an std::ratio prefix
    /// @tparam BASE_TYPE: base_quantity
    /// @tparam PREFIX_TYPE: std::ratio
    template <typename BASE_TYPE, typename PREFIX_TYPE = std::ratio<1>> 
        requires (is_base_v<BASE_TYPE>)  
    struct unit {


        // =============================================
        // type aliases
        // =============================================

            using base = BASE_TYPE;

            using prefix = PREFIX_TYPE;

            using type = unit<base, prefix>; 


        // =============================================
        // static members
        // =============================================

            inline static constexpr double mult = static_cast<double>(prefix::num) / static_cast<double>(prefix::den);


        // =============================================
        // operators
        // =============================================

            /// @brief Print the unit to the standard output
            friend inline constexpr std::ostream& operator<<(std::ostream& os, const unit&) noexcept {

                return os << unit::to_string();

            }


        // =============================================
        // methods
        // =============================================

            /// @brief to_string returns a string representation of the unit
            static constexpr std::string to_string() noexcept {

                auto prefix = prefix_map.find(mult);
                if (prefix == prefix_map.end()) 
                    return BASE_TYPE::to_string();
                else
                    return std::string(1, '[') + std::string(1, prefix->second) + std::string(1, ']') + BASE_TYPE::to_string(); 

            }


            /// @brief Convert a value from the base unit to another unit 
            template <typename OTHER_UNIT> 
                requires(is_same_base_v<BASE_TYPE, typename OTHER_UNIT::base>)
            static inline constexpr double convert(const double val, const OTHER_UNIT&) noexcept {

                return val * mult / OTHER_UNIT::mult; 

            }


    }; // struct unit


} // namespace scipp::physics 