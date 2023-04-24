/**
 * @file    traits/physics.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the type traits for the scipp::physics namespace
 * @date    2023-04-24
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    // =============================================
    // common traits
    // =============================================

        template <typename T>
        struct is_scalar : std::false_type {};

        template <typename T>
        inline static constexpr bool is_scalar_v = is_scalar<T>::value; 


    // =============================================
    // base_quantity traits
    // =============================================

        /// @brief base_quantity is a type that represents a physical base quantity using the 7 SI units
        template <int, int, int, int, int, int, int>
        struct base_quantity; 

        /// @brief Type trait to check if a type is a base_quantity
        template <typename T>
        struct is_base : std::false_type {};

        template <typename T>
        constexpr bool is_base_v = is_base<T>::value;

        /// @brief Type trait to check if a list of types are base_quantities
        template <typename... Ts>
        struct are_base : std::conjunction<is_base<Ts>...> {};

        template <typename... Ts>
        inline static constexpr bool are_base_v = are_base<Ts...>::value;

        template <typename BASE1, typename BASE2>
        struct is_same_base : std::false_type {}; 

        template <typename BASE1, typename BASE2>
        constexpr bool is_same_base_v = is_same_base<BASE1, BASE2>::value;


        /// @brief Type trait to check if a list of base_quantity types are the same
        template <typename BASE, typename... OTHER_BASEs> 
        struct are_same_base : std::conjunction<is_same_base<BASE, OTHER_BASEs>...> {};

        template <typename BASE, typename... OTHER_BASEs>
        constexpr bool are_same_base_v = are_same_base<BASE, OTHER_BASEs...>::value;


        template <typename BASE, int POWER>
        struct has_valid_root : std::false_type {};

        template <typename BASE, int POWER>
        constexpr bool has_valid_root_v = has_valid_root<BASE, POWER>::value;


    // =============================================
    // prefix traits
    // =============================================
            
        /// @brief Type trait to check if a type is an std::ratio 
        template <typename T>
        struct is_prefix : std::false_type {};

        template <typename T>
        inline static constexpr bool is_prefix_v = is_prefix<T>::value;

        /// @brief Type trait to check if a type is a valid prefix
        template <typename... Ts>
        struct are_prefix : std::conjunction<is_prefix<Ts>...> {};

        template <typename... Ts>
        inline static constexpr bool are_prefix_v = are_prefix<Ts...>::value;
    
    
    // =============================================
    // unit traits
    // =============================================

        template <typename BASE_TYPE, typename PREFIX_TYPE> 
            requires (is_base_v<BASE_TYPE> && is_prefix_v<PREFIX_TYPE>)  
        struct unit;

        /// @brief Type trait to check if a type is an unit
        template <typename T>
        struct is_unit : std::false_type {}; 

        template <typename T>
        inline constexpr bool is_unit_v = is_unit<T>::value;

        /// @brief Type trait to check if a list of types are unit types
        template <typename... Ts>
        struct are_units : std::conjunction<is_unit<Ts>...> {};

        template <typename... Ts>
        inline constexpr bool are_units_v = are_units<Ts...>::value;

        /// @brief Type trait to check if a type is the same unit as another unit type
        template <typename T1, typename T2>
        struct is_same_unit : std::false_type {};

        template <typename T1, typename T2>
        inline constexpr bool is_same_unit_v = is_same_unit<T1, T2>::value;
        
        /// @brief Type trait to check if a list of base_quantity types are the same
        template <typename T, typename... Ts> 
        struct are_same_unit : public std::conjunction<is_same_unit<T, Ts>...> {};

        template <typename T, typename... Ts>
        constexpr bool are_same_unit_v = are_same_unit<T, Ts...>::value;


        /// @brief Type trait to check if an unit type is prefixed
        template <typename T>
        struct is_prefixed_unit : std::false_type {};

        template <typename T>
        inline constexpr bool is_prefixed_unit_v = is_prefixed_unit<T>::value;

        /// @brief Type trait to check if an unit type is a base unit type
        template <typename T>
        struct is_base_unit : std::false_type {};

        template <typename T>
        inline constexpr bool is_base_unit_v = is_base_unit<T>::value;


    // =============================================
    // measurement traits
    // =============================================

        /// @brief Type trait to check if a type is a measurement
        template <typename T>
        struct is_measurement : std::false_type{};

        template <typename MEAS_TYPE>
        inline static constexpr bool is_measurement_v = is_measurement<MEAS_TYPE>::value;

        template <typename... MEAS_TYPES>
        struct are_measurements : std::conjunction<is_measurement<MEAS_TYPES>...>{};

        template <typename... MEAS_TYPES>
        inline static constexpr bool are_measurements_v = are_measurements<MEAS_TYPES...>::value;


        /// @brief Type trait to check if two measurement types are the same
        template <typename MEAS_TYPE1, typename MEAS_TYPE2> 
            requires (are_measurements_v<MEAS_TYPE1, MEAS_TYPE2> && is_same_base_v<typename MEAS_TYPE1::base_t, typename MEAS_TYPE2::base_t>)
        struct is_same_measurement : std::true_type {};

        template <typename MEAS_TYPE1, typename MEAS_TYPE2> 
        inline static constexpr bool is_same_measurement_v = is_same_measurement<MEAS_TYPE1, MEAS_TYPE2>::value; 


        template <typename MEAS_TYPE, typename... OTHER_MEAS_TYPEs> 
        struct are_same_measurement : std::conjunction<is_same_measurement<MEAS_TYPE, OTHER_MEAS_TYPEs>...> {};
        
        template <typename MEAS_TYPE, typename... MEAS_TYPEs>
        inline static constexpr bool are_same_measurement_v = are_same_measurement<MEAS_TYPE, MEAS_TYPEs...>::value;


        template <typename T>
        struct is_scalar_measurement : std::false_type {};

        template <typename T>
        inline static constexpr bool is_scalar_measurement_v = is_scalar_measurement<T>::value;


} // namespace scipp::physics