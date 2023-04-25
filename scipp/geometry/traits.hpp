/**
 * @file    geometry/traits.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the type traits for the scipp::geometry namespace
 * @date    2023-04-25
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief geometry namespace contains all the classes and functions of the geometry library
namespace scipp::geometry {


    // =============================================
    // common traits
    // =============================================


    // =============================================
    // vector traits
    // =============================================

        template <typename MEAS_TYPE, std::size_t DIM>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct vector;


        template <typename T>
        struct is_vector : std::false_type{};

        template <typename T>
        inline static constexpr bool is_vector_v = is_vector<T>::value;

        template <typename MEAS_TYPE, std::size_t DIM> 
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct is_vector<vector<MEAS_TYPE, DIM>> : std::true_type {};


        template <typename... Ts>
        struct are_vectors : std::conjunction<is_vector<Ts>...> {};

        template <typename... VECTORS>
        constexpr bool are_vectors_v = are_vectors<VECTORS...>::value;


        template <typename VECTOR_TYPE, typename... VECTORS>
            requires (are_vectors_v<VECTOR_TYPE, VECTORS...>)
        struct are_same_vectors : std::conjunction<std::bool_constant<VECTOR_TYPE::dim == VECTORS::dim>..., 
                                                   std::bool_constant<physics::are_same_measurement_v<typename VECTOR_TYPE::measurement_t, 
                                                                                                      typename VECTORS::measurement_t>>...> {};

        template <typename... VECTORS>  
        constexpr bool are_same_vectors_v = are_same_vectors<VECTORS...>::value;


        template <typename VECTOR_TYPE, typename... VECTORS>
            requires (are_vectors_v<VECTOR_TYPE, VECTORS...>)
        struct have_same_dimension : std::conjunction<std::bool_constant<VECTOR_TYPE::dim == VECTORS::dim>...> {};

        template <typename... VECTORS>
        constexpr bool have_same_dimension_v = have_same_dimension<VECTORS...>::value;


    // =============================================
    // vector traits
    // =============================================

        template <typename VECTOR_TYPE, std::size_t COLUMNS>
            requires (is_vector_v<VECTOR_TYPE>)
        struct matrix;


        template <typename T>
        struct is_matrix : std::false_type{};

        template <typename VECTOR_TYPE, std::size_t COLUMNS>
            requires (is_vector_v<VECTOR_TYPE>)
        struct is_matrix<matrix<VECTOR_TYPE, COLUMNS>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_matrix_v = is_matrix<T>::value;


        template <typename... Ts>
        struct are_matrices : std::conjunction<is_matrix<Ts>...> {};

        template <typename... MATRICES>
        inline static constexpr bool are_matrices_v = are_matrices<MATRICES...>::value;


} /// namespace scipp::geometry