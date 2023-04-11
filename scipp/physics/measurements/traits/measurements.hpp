/**
 * @file    physics/measurements/traits/measurements.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the
 * @note    
 * @date    2023-04-03
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::physics {


    // =============================================
    // forward declarations
    // =============================================

        template <typename BASE_TYPE>
            requires (is_base_v<BASE_TYPE>)
        struct measurement; 

        template <typename BASE_TYPE>
            requires (is_base_v<BASE_TYPE>)
        struct umeasurement;


    // =============================================
    // is measurements type traits
    // =============================================

        /// @brief Type trait to check if a type is a measurement
        template <typename T>
        struct is_measurement : std::false_type{};

        template <typename MEAS_TYPE>
        constexpr bool is_measurement_v = is_measurement<MEAS_TYPE>::value;

        /// @brief Type trait to check if a type is an umeasurement
        template <typename T>
        struct is_umeasurement : std::false_type{};

        template <typename T>
        constexpr bool is_umeasurement_v = is_umeasurement<T>::value;


        /// @brief Type trait to check if a type is a generic measurement
        template <typename T>
        struct is_generic_measurement : std::conditional_t<is_measurement_v<T> || is_umeasurement_v<T>, std::true_type, std::false_type>{};

        template <typename T>
        constexpr bool is_generic_measurement_v = is_generic_measurement<T>::value;


    // =============================================
    // are_measurements type traits
    // =============================================

        template <typename... MEAS_TYPES>
        struct are_measurements : std::conjunction<is_measurement<MEAS_TYPES>...>{};

        template <typename... Ts>
        struct are_umeasurements : std::conjunction<is_umeasurement<Ts>...>{};

        template <typename... MEAS_TYPES>
        struct are_generic_measurements : std::conjunction<is_generic_measurement<MEAS_TYPES>...>{};


        template <typename... MEAS_TYPES>
        constexpr bool are_measurements_v = are_measurements<MEAS_TYPES...>::value;

        template <typename... Ts>
        constexpr bool are_umeasurements_v = are_umeasurements<Ts...>::value;

        template <typename... MEAS_TYPEs>
        constexpr bool are_generic_measurements_v = are_generic_measurements<MEAS_TYPEs...>::value;


    // =============================================
    // are_same_measurements type traits
    // =============================================

        template <typename T, typename... Ts>
        struct are_same_measurements : std::false_type{};

        template <typename MEAS_TYPE, typename... MEAS_TYPEs>
        constexpr bool are_same_measurements_v = are_same_measurements<MEAS_TYPE, MEAS_TYPEs...>::value;


    // =============================================
    // scalar measurements type traits
    // =============================================

        template <>  
        struct is_measurement<float> : std::true_type{};

        template <>  
        struct is_measurement<double> : std::true_type{};

        template <>  
        struct is_measurement<long double> : std::true_type{};

        template <>
        struct is_measurement<int> : std::true_type{};

        template <>
        struct is_measurement<uint> : std::true_type{};


        template <>  
        struct is_umeasurement<float> : std::false_type{};

        template <>  
        struct is_umeasurement<double> : std::false_type{};

        template <>  
        struct is_umeasurement<long double> : std::false_type{};

        template <>
        struct is_umeasurement<int> : std::false_type{};

        template <>
        struct is_umeasurement<uint> : std::false_type{};


        template <>
        struct is_scalar<double> : std::true_type {};
        
        template <>
        struct is_scalar<float> : std::true_type {};    
        
        template <>
        struct is_scalar<long double> : std::true_type {};    
        
        template <>
        struct is_scalar<int> : std::true_type {};

        template <>
        struct is_scalar<uint> : std::true_type {};
        
        template <>
        struct is_scalar<measurement<units::scalar>> : std::true_type {};

        template <typename T>
        constexpr bool is_scalar_v = is_scalar<T>::value;
    

    // =============================================
    // is complex_measurements type traits
    // =============================================

        // template <typename T>
        // struct is_generic_complex_measurement : std::conditional_t<is_complex_measurement_v<T> || is_complex_umeasurement_v<T>, std::true_type, std::false_type>{};

        // template <typename T>
        // constexpr bool is_generic_complex_measurement_v = is_generic_complex_measurement<T>::value;


        // template <typename T>
        //     requires (std::is_arithmetic_v<T>)  
        // struct is_complex_measurement<std::complex<T>> : std::true_type{};

        // template <typename T>
        //     requires (std::is_arithmetic_v<T>)
        // struct is_complex_umeasurement<std::complex<T>> : std::false_type{};


        // template <typename... MEAS_TYPES>
        // struct are_generic_complex_measurements : std::conjunction<is_generic_complex_measurement<MEAS_TYPES>...>{};

        // template <typename... MEAS_TYPEs>
        // constexpr bool are_generic_complex_measurements_v = are_generic_complex_measurements<MEAS_TYPEs...>::value;


} // namespace scipp::physics