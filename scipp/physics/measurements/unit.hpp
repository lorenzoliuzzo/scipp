/**
 * @file    physics/measurements/unit.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the unit struct and its type traits.
 * @date    2023-04-23
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    template <intmax_t N, intmax_t D>
    struct is_prefix<std::ratio<N, D>> : std::true_type {};


    /// @brief The prefix map contains all SI prefix multipliers and char representation
    static std::map<double, char> prefix_map = {

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
        {1.0e24,  'Y'}, //< yotta prefix

    }; 


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

                auto prefix = prefix_map.find(mult);
                if (prefix == prefix_map.end()) 
                    return base_t::to_string();
                else
                    return std::string(1, '[') + std::string(1, prefix->second) + std::string(1, ']') + base_t::to_string(); 

            }


            /// @brief Convert a value from the base unit to another unit 
            template <typename OTHER_UNIT> 
                requires(is_same_base_v<base_t, typename OTHER_UNIT::base_t>)
            static inline constexpr double convert(const double val, const OTHER_UNIT&) noexcept {

                return val * mult / OTHER_UNIT::mult; 

            }


    }; // struct unit


    /// @brief Perform a multiplication between unit objects
    template <typename UNIT1, typename UNIT2> 
        requires (are_units_v<UNIT1, UNIT2>)
    constexpr auto operator*(const UNIT1&, const UNIT2&) noexcept 
        -> math::meta::multiply_t<UNIT1, UNIT2> {

        return {}; 
        
    } 

    /// @brief Perform a division between unit objects
    template <typename UNIT1, typename UNIT2> 
        requires (are_units_v<UNIT1, UNIT2>)
    constexpr auto operator/(const UNIT1&, const UNIT2&) noexcept 
        -> math::meta::divide_t<UNIT1, UNIT2> {
        
        return {}; 
        
    } 


    template <typename BASE>
    struct is_unit<unit<BASE>> : std::true_type {};

    template <typename BASE, typename PREFIX>
    struct is_unit<unit<BASE, PREFIX>> : std::true_type {};


    template <typename BASE> 
    struct is_same_unit<unit<BASE>, unit<BASE>> : std::true_type {};

    template <typename BASE, typename PREFIX> 
    struct is_same_unit<unit<BASE>, unit<BASE, PREFIX>> : std::true_type {};

    template <typename BASE, typename PREFIX> 
    struct is_same_unit<unit<BASE, PREFIX>, unit<BASE>> : std::true_type {};

    template <typename BASE, typename PREFIX> 
    struct is_same_unit<unit<BASE, PREFIX>, unit<BASE, PREFIX>> : std::true_type {};


    template <typename BASE>
    struct is_prefixed_unit<unit<BASE>> : std::false_type {};

    template <typename BASE, typename PREFIX>
    struct is_prefixed_unit<unit<BASE, PREFIX>> : std::true_type {};

    template <typename BASE>
    struct is_base_unit<unit<BASE>> : std::true_type {};


} // namespace scipp::physics 