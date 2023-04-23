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

    
    /// @brief  Struct unit is an union of an base_quantity and an std::ratio prefix
    /// @tparam BASE_TYPE: base_quantity
    /// @tparam PREFIX_TYPE: std::ratio
    template <typename BASE_TYPE, typename PREFIX_TYPE = std::ratio<1>> 
        requires (is_base_v<BASE_TYPE>)  
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


    /// @brief Type trait to check if a type is an unit
    template <typename T>
    struct is_unit : std::false_type {}; 

    template <typename T>
    inline constexpr bool is_unit_v = is_unit<T>::value;

    template <typename BASE>
    struct is_unit<unit<BASE>> : std::true_type {};

    template <typename BASE, typename PREFIX>
    struct is_unit<unit<BASE, PREFIX>> : std::true_type {};


    /// @brief Type trait to check if a list of types are unit types
    template <typename... Ts>
    struct are_units : std::conjunction<is_unit<Ts>...> {};

    template <typename... Ts>
    inline constexpr bool are_units_v = are_units<Ts...>::value;


    /// @brief Type trait to check if a type is the same unit as another unit type
    template <typename T1, typename T2>
    struct is_same_unit : std::false_type {};

    template <typename BASE> 
    struct is_same_unit<unit<BASE>, unit<BASE>> : std::true_type {};

    template <typename BASE, typename PREFIX> 
    struct is_same_unit<unit<BASE>, unit<BASE, PREFIX>> : std::true_type {};

    template <typename BASE, typename PREFIX> 
    struct is_same_unit<unit<BASE, PREFIX>, unit<BASE>> : std::true_type {};

    template <typename BASE, typename PREFIX> 
    struct is_same_unit<unit<BASE, PREFIX>, unit<BASE, PREFIX>> : std::true_type {};

    template <typename T1, typename T2>
    inline constexpr bool is_same_unit_v = is_same_unit<T1, T2>::value;
    

    /// @brief Type trait to check if a list of base_quantity types are the same
    template <typename UNIT, typename... OTHER_UNITs> 
    struct are_same_unit : public std::conjunction<is_same_unit<UNIT, OTHER_UNITs>...> {};

    template <typename UNIT, typename... OTHER_UNITs>
    constexpr bool are_same_unit_v = are_same_unit<UNIT, OTHER_UNITs...>::value;


    /// @brief Type trait to check if an unit type is prefixed
    template <typename T>
    struct is_prefixed : std::false_type {};

    template <typename BASE>
    struct is_prefixed<unit<BASE>> : std::false_type {};

    template <typename BASE, typename PREFIX>
    struct is_prefixed<unit<BASE, PREFIX>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_prefixed_v = is_prefixed<T>::value;


    /// @brief Type trait to check if an unit type is a base unit type
    template <typename T>
    struct is_base_unit : std::false_type {};

    template <typename BASE>
    struct is_base_unit<unit<BASE>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_base_unit_v = is_base_unit<T>::value;


    /// @brief Perform a multiplication between unit objects
    template <typename UNIT1, typename UNIT2> 
        requires (are_units_v<UNIT1, UNIT2>)
    constexpr auto operator*(const UNIT1&, const UNIT2&) noexcept 
        -> unit<math::op::base_product_t<typename UNIT1::base_t, typename UNIT2::base_t>, 
                std::ratio_multiply<typename UNIT1::prefix_t, typename UNIT2::prefix_t>> {

        return {}; 
        
    } 

    /// @brief Perform a division between unit objects
    template <typename UNIT1, typename UNIT2> 
        requires (are_units_v<UNIT1, UNIT2>)
    constexpr auto operator/(const UNIT1&, const UNIT2&) noexcept 
        -> unit<math::op::base_division_t<typename UNIT1::base_t, typename UNIT2::base_t>, 
                std::ratio_divide<typename UNIT1::prefix_t, typename UNIT2::prefix_t>> {
        
        return {}; 
        
    } 


} // namespace scipp::physics 