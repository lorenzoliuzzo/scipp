/**
 * @file    physics/measurements/unit.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the unit struct and its type traits.
 * @date    2023-05-23
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    /// @brief The prefix map contains all SI prefix multipliers and char representation
    inline static constexpr std::array<std::pair<double, char>, 19> prefix_map = {{

        {1.0e-24, 'y'}, //< yocto prefix
        {1.0e-21, 'z'}, //< zepto prefix
        {1.0e-18, 'a'}, //< atto prefix
        {1.0e-15, 'f'}, //< femto prefix
        {1.0e-12, 'p'}, //< pico prefix
        {1.0e-9,  'n'}, //< nano prefix
        {1.0e-6,  'u'}, //< micro prefix
        {1.0e-3,  'm'}, //< milli prefix
        {1.0e-2,  'c'}, //< centi prefix
        {1.0e-1,  'd'}, //< deci prefix
        {1.0e2,   'h'}, //< hecto prefix
        {1.0e3,   'k'}, //< kilo prefix
        {1.0e6,   'M'}, //< mega prefix
        {1.0e9,   'G'}, //< giga prefix
        {1.0e12,  'T'}, //< tera prefix
        {1.0e15,  'P'}, //< peta prefix
        {1.0e18,  'E'}, //< exa prefix
        {1.0e21,  'Z'}, //< zetta prefix
        {1.0e24,  'Y'} //< yotta prefix

    }}; 


    /// @brief  Struct unit is an union of an base_quantity and an std::ratio prefix
    /// @tparam BASE_TYPE: base_quantity
    /// @tparam PREFIX_TYPE: std::ratio
    template <typename BASE_TYPE, typename PREFIX_TYPE = std::ratio<1>> 
        requires (is_base_v<BASE_TYPE> && is_prefix_v<PREFIX_TYPE>)  
    struct unit {


        // =============================================
        // type aliases
        // =============================================

            using base_t = BASE_TYPE;

            using prefix_t = PREFIX_TYPE;

            using _t = unit<base_t, prefix_t>; 


        // =============================================
        // static members
        // =============================================

            inline static constexpr double mult = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den);


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

                std::stringstream ss;
                auto prefix = std::lower_bound(prefix_map.begin(), prefix_map.end(), mult,
                    [](const auto& p, const auto& value) { return p.first < value; });
                
                if (prefix == prefix_map.end())
                    ss << base_t::to_string();
                else
                    ss << "[" << prefix->second << "]" << base_t::to_string();

                return ss.str();

            }


    }; // struct unit
    

} // namespace scipp::physics 



            // /// @brief Convert a value from the base unit to another unit 
            // template <typename OTHER_UNIT> 
            //     requires(is_same_base_v<base_t, typename OTHER_UNIT::base_t>)
            // static inline constexpr double convert(const double val, const OTHER_UNIT&) noexcept {

            //     return val * mult / OTHER_UNIT::mult; 

            // }

