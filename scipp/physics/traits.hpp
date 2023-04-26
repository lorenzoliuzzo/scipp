/**
 * @file    physics/traits.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the type traits for the scipp::physics namespace
 * @date    2023-04-25
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {

    // =============================================
    // base_quantity traits
    // =============================================

        /// @brief base_quantity is a type that represents a physical base quantity using the 7 SI units
        template <int, int, int, int, int, int, int>
        struct base_quantity; 


        /// @brief Type trait to check if a type is a base_quantity
        template <typename T>
        struct is_base : std::false_type {};

        template <int LENGTH, int TIME, int MASS, int TEMPERATURE, int ELETTRIC_CURRENT, int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY>
        struct is_base<base_quantity<LENGTH, TIME, MASS, TEMPERATURE, ELETTRIC_CURRENT, SUBSTANCE_AMOUNT, LUMINOUS_INTENSITY>> : std::true_type {};
            
        template <typename T>
        constexpr bool is_base_v = is_base<T>::value;

        /// @brief Type trait to check if a list of types are base_quantities
        template <typename... Ts>
        struct are_base : std::conjunction<is_base<Ts>...> {};

        template <typename... Ts>
        inline static constexpr bool are_base_v = are_base<Ts...>::value;


        /// @brief Type trait to check if two base_quantity types are the same
        template <typename BASE1, typename BASE2>
        struct is_same_base : std::false_type {}; 

        /// @brief Type trait to check if two base_quantity types are the same
        template <typename BASE1, typename BASE2> 
            requires (are_base_v<BASE1, BASE2>)
        struct is_same_base<BASE1, BASE2> : std::bool_constant<BASE1::length == BASE2::length &&
                                                               BASE1::time == BASE2::time &&
                                                               BASE1::mass == BASE2::mass &&
                                                               BASE1::temperature == BASE2::temperature &&
                                                               BASE1::elettric_current == BASE2::elettric_current &&
                                                               BASE1::substance_amount == BASE2::substance_amount &&
                                                               BASE1::luminous_intensity == BASE2::luminous_intensity> {};

        template <typename BASE1, typename BASE2>
        constexpr bool is_same_base_v = is_same_base<BASE1, BASE2>::value;

        /// @brief Type trait to check if a list of base_quantity types are the same
        template <typename BASE, typename... OTHER_BASEs> 
        struct are_same_base : std::conjunction<is_same_base<BASE, OTHER_BASEs>...> {};

        template <typename BASE, typename... OTHER_BASEs>
        constexpr bool are_same_base_v = are_same_base<BASE, OTHER_BASEs...>::value;


        template <typename BASE, int POWER>
        struct has_valid_root : std::false_type {};

        /// @brief Type trait to check if a base_quantity type has valid root
        template <typename BASE, int POWER> 
            requires (is_base_v<BASE>)
        struct has_valid_root<BASE, POWER> : std::bool_constant<BASE::length % POWER == 0 && 
                                                                BASE::time % POWER == 0 && 
                                                                BASE::mass % POWER == 0 && 
                                                                BASE::temperature % POWER == 0 && 
                                                                BASE::elettric_current % POWER == 0 && 
                                                                BASE::substance_amount % POWER == 0 && 
                                                                BASE::luminous_intensity % POWER == 0> {};

        template <typename BASE, int POWER>
        constexpr bool has_valid_root_v = has_valid_root<BASE, POWER>::value;


    // =============================================
    // prefix traits
    // =============================================
            
        /// @brief Type trait to check if a type is an std::ratio 
        template <typename T>
        struct is_prefix : std::false_type {};

        template <intmax_t N, intmax_t D>
        struct is_prefix<std::ratio<N, D>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_prefix_v = is_prefix<T>::value;

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

        template <typename BASE_TYPE, typename PREFIX_TYPE>
        struct is_unit<unit<BASE_TYPE, PREFIX_TYPE>> : std::true_type {};

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
            requires (are_units_v<T1, T2>)
        struct is_same_unit<T1, T2> : std::bool_constant<is_same_base_v<typename T1::base_t, typename T2::base_t> && 
                                                         std::ratio_equal_v<typename T1::prefix_t, typename T2::prefix_t>> {};

        template <typename T1, typename T2>
        inline constexpr bool is_same_unit_v = is_same_unit<T1, T2>::value;
        
        /// @brief Type trait to check if a list of base_quantity types are the same
        template <typename T, typename... Ts> 
        struct are_same_unit : public std::conjunction<is_same_unit<T, Ts>...> {};

        template <typename T, typename... Ts>
        constexpr bool are_same_unit_v = are_same_unit<T, Ts...>::value;


        /// @brief Type trait to check if an unit type is prefixed
        template <typename UNIT_TYPE>
            requires (is_unit_v<UNIT_TYPE>)
        struct is_prefixed_unit : std::bool_constant<!std::ratio_equal_v<typename UNIT_TYPE::prefix_t, std::ratio<1>>> {};
        
        template <typename UNIT_TYPE>
            requires (is_unit_v<UNIT_TYPE>)
        struct is_based_unit : std::bool_constant<std::ratio_equal_v<typename UNIT_TYPE::prefix_t, std::ratio<1>>> {};
        
        template <typename T>
        inline constexpr bool is_prefixed_unit_v = is_prefixed_unit<T>::value;

        template <typename T>
        inline constexpr bool is_based_unit_v = is_prefixed_unit<T>::value;


    // =============================================
    // measurement traits
    // =============================================

        template <typename BASE_TYPE> 
            requires (is_base_v<BASE_TYPE>)  
        struct measurement;


        /// @brief Type trait to check if a type is a measurement
        template <typename T>
        struct is_measurement : std::false_type{};

        template <typename BASE_TYPE>
        struct is_measurement<measurement<BASE_TYPE>> : std::true_type{};

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


        template <typename UNIT_TYPE> 
            requires (is_unit_v<UNIT_TYPE>)  
        struct fixed_measurement;


    // =============================================
    // umeasurement traits
    // =============================================

        template <typename BASE_TYPE> 
            requires (is_base_v<BASE_TYPE>)  
        struct umeasurement;


        /// @brief Type trait to check if a type is a measurement
        template <typename T>
        struct is_umeasurement : std::false_type{};

        template <typename MEAS_TYPE>
        inline static constexpr bool is_umeasurement_v = is_umeasurement<MEAS_TYPE>::value;

        template <typename... MEAS_TYPES>
        struct are_umeasurements : std::conjunction<is_umeasurement<MEAS_TYPES>...>{};

        template <typename... MEAS_TYPES>
        inline static constexpr bool are_umeasurements_v = are_umeasurements<MEAS_TYPES...>::value;


    // =============================================
    // cmeasurement traits
    // =============================================

        template <typename MEAS_TYPE> 
            requires (is_measurement_v<MEAS_TYPE> || is_umeasurement_v<MEAS_TYPE>)  
        struct cmeasurement;


        /// @brief Type trait to check if a type is a measurement
        template <typename T>
        struct is_cmeasurement : std::false_type{};

        template <typename MEAS_TYPE>
        struct is_cmeasurement<cmeasurement<MEAS_TYPE>> : std::true_type{};

        template <typename MEAS_TYPE>
        inline static constexpr bool is_cmeasurement_v = is_cmeasurement<MEAS_TYPE>::value;

        template <typename... MEAS_TYPES>
        struct are_cmeasurements : std::conjunction<is_cmeasurement<MEAS_TYPES>...>{};

        template <typename... MEAS_TYPES>
        inline static constexpr bool are_cmeasurements_v = are_cmeasurements<MEAS_TYPES...>::value;


    // =============================================
    // generic_measurement traits
    // =============================================

        /// @brief Type trait to check if a type is a generic measurement
        template <typename T>
        struct is_generic_measurement : std::conditional_t<is_measurement_v<T> || is_umeasurement_v<T> || is_cmeasurement_v<T>, 
                                                           std::true_type, 
                                                           std::false_type>{};

        template <typename T>
        constexpr bool is_generic_measurement_v = is_generic_measurement<T>::value;

        template <typename... MEAS_TYPES>
        struct are_generic_measurements : std::conjunction<is_generic_measurement<MEAS_TYPES>...>{};

        template <typename... MEAS_TYPEs>
        constexpr bool are_generic_measurements_v = are_generic_measurements<MEAS_TYPEs...>::value;



    // =============================================
    // scalar traits
    // =============================================

        template <typename T>
        struct is_scalar_base : std::false_type {};

        template <>
        struct is_scalar_base<base_quantity<0, 0, 0, 0, 0, 0, 0>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_scalar_base_v = is_scalar_base<T>::value;


        template <typename T>
        struct is_scalar_unit : std::false_type {};

        template <typename SCALAR_BASE_TYPE, typename PREFIX_TYPE>
            requires (is_scalar_base_v<SCALAR_BASE_TYPE>)
        struct is_scalar_unit<unit<SCALAR_BASE_TYPE, PREFIX_TYPE>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_scalar_unit_v = is_scalar_unit<T>::value;


        template <typename T>
        struct is_scalar_measurement : std::false_type {};

        template <typename SCALAR_BASE_TYPE>
            requires (is_scalar_base_v<SCALAR_BASE_TYPE>)
        struct is_scalar_measurement<measurement<SCALAR_BASE_TYPE>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_scalar_measurement_v = is_scalar_measurement<T>::value;


        template <typename T>
        struct is_scalar_umeasurement : std::false_type {};

        template <typename SCALAR_BASE_TYPE>
            requires (is_scalar_base_v<SCALAR_BASE_TYPE>)
        struct is_scalar_umeasurement<umeasurement<SCALAR_BASE_TYPE>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_scalar_umeasurement_v = is_scalar_umeasurement<T>::value;


        template <typename T>
        struct is_scalar_cmeasurement : std::false_type {};

        template <typename SCALAR_MEAS_TYPE>
            requires (is_scalar_measurement_v<SCALAR_MEAS_TYPE> || is_scalar_umeasurement_v<SCALAR_MEAS_TYPE>)
        struct is_scalar_cmeasurement<cmeasurement<SCALAR_MEAS_TYPE>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_scalar_cmeasurement_v = is_scalar_cmeasurement<T>::value;


        template <typename... MEAS_TYPEs>
        struct are_scalar_measurements : std::conjunction<is_scalar_measurement<MEAS_TYPEs>...> {};

        template <typename... MEAS_TYPEs>
        inline static constexpr bool are_scalar_measurements_v = are_scalar_measurements<MEAS_TYPEs...>::value;
        
        template <typename... UMEAS_TYPEs>
        struct are_scalar_umeasurements : std::conjunction<is_scalar_umeasurement<UMEAS_TYPEs>...> {};

        template <typename... UMEAS_TYPEs>
        inline static constexpr bool are_scalar_umeasurements_v = are_scalar_umeasurements<UMEAS_TYPEs...>::value;
        
        template <typename... CMEAS_TYPEs>
        struct are_scalar_cmeasurements : std::conjunction<is_scalar_cmeasurement<CMEAS_TYPEs>...> {};

        template <typename... CMEAS_TYPEs>
        inline static constexpr bool are_scalar_cmeasurements_v = are_scalar_cmeasurements<CMEAS_TYPEs...>::value;
        

} // namespace scipp::physics