/**
 * @file    physics/measurements/generic_measurement_traits.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the
 * @note    
 * @date    2023-04-23
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::physics {




    // =============================================
    // are_measurements type traits
    // =============================================



    // =============================================
    // are_same_measurements type traits
    // =============================================


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
      


    // =============================================
    // is cmeasurements type traits
    // =============================================

        // template <typename T>
        // struct is_generic_cmeasurement : std::conditional_t<is_cmeasurement_v<T> || is_complex_umeasurement_v<T>, std::true_type, std::false_type>{};

        // template <typename T>
        // constexpr bool is_generic_cmeasurement_v = is_generic_cmeasurement<T>::value;


        // template <typename T>
        //     requires (std::is_arithmetic_v<T>)  
        // struct is_cmeasurement<std::complex<T>> : std::true_type{};

        // template <typename T>
        //     requires (std::is_arithmetic_v<T>)
        // struct is_complex_umeasurement<std::complex<T>> : std::false_type{};


        // template <typename... MEAS_TYPES>
        // struct are_generic_cmeasurements : std::conjunction<is_generic_cmeasurement<MEAS_TYPES>...>{};

        // template <typename... MEAS_TYPEs>
        // constexpr bool are_generic_cmeasurements_v = are_generic_cmeasurements<MEAS_TYPEs...>::value;


} // namespace scipp::physics