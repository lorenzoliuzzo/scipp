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

        template <typename T, size_t DIM, bool ROW_VECTOR_FLAG>
            requires (physics::is_generic_measurement_v<T> || math::is_generic_number_v<T>)
        struct vector;


        template <typename T, size_t DIM>
        using column_vector = vector<T, DIM, false>;

        template <typename T, size_t DIM>
        using row_vector = vector<T, DIM, true>;


        template <typename T>
        struct is_column_vector : std::false_type{};

        template <typename T>
        inline static constexpr bool is_column_vector_v = is_column_vector<T>::value;

        template <typename T, size_t DIM> 
            requires (physics::is_generic_measurement_v<T> || math::is_generic_number_v<T>)
        struct is_column_vector<column_vector<T, DIM>> : std::true_type {};

        template <typename... VECTORS>
        struct are_column_vectors : std::conjunction<is_column_vector<VECTORS>...> {};

        template <typename... VECTORS>
        constexpr bool are_column_vectors_v = are_column_vectors<VECTORS...>::value;


        template <typename T>
        struct is_row_vector : std::false_type{};

        template <typename T>
        inline static constexpr bool is_row_vector_v = is_row_vector<T>::value;

        template <typename T, size_t DIM> 
            requires (physics::is_generic_measurement_v<T> || math::is_generic_number_v<T>)
        struct is_row_vector<row_vector<T, DIM>> : std::true_type {};

        template <typename... Ts>
        struct are_row_vectors : std::conjunction<is_row_vector<Ts>...> {};

        template <typename... VECTORS>
        constexpr bool are_row_vectors_v = are_row_vectors<VECTORS...>::value;


        template <typename T>
        struct is_vector : std::conditional_t<is_column_vector_v<T> || is_row_vector_v<T>, std::true_type, std::false_type> {};

        template <typename T>
        inline static constexpr bool is_vector_v = is_vector<T>::value;

        template <typename... Ts>
        struct are_vectors : std::conjunction<is_vector<Ts>...> {};

        template <typename... VECTORS>
        constexpr bool are_vectors_v = are_vectors<VECTORS...>::value;


        template <typename T, typename... Ts>
        struct have_same_dimension : std::conjunction<std::bool_constant<T::dim == Ts::dim>...> {};

        template <typename... Ts>
        constexpr bool have_same_dimension_v = have_same_dimension<Ts...>::value;


        template <typename VECTOR_TYPE1, typename VECTOR_TYPE2>
            requires (are_vectors_v<VECTOR_TYPE1, VECTOR_TYPE2> && 
                      have_same_dimension_v<VECTOR_TYPE1, VECTOR_TYPE2> &&
                      physics::are_same_measurement_v<typename VECTOR_TYPE1::value_t, typename VECTOR_TYPE2::value_t> &&
                      VECTOR_TYPE1::flag == VECTOR_TYPE2::flag)
        struct is_same_vector : std::true_type {};

        template <typename VECTOR_TYPE1, typename VECTOR_TYPE2>
        inline static constexpr bool is_same_vector_v = is_same_vector<VECTOR_TYPE1, VECTOR_TYPE2>::value;

        template <typename VECTOR_TYPE, typename... VECTORS>
        struct are_same_vectors : std::conjunction<is_same_vector<VECTOR_TYPE, VECTORS>...> {};

        template <typename... VECTORS>
        constexpr bool are_same_vectors_v = are_same_vectors<VECTORS...>::value;


        template <typename T>
        struct is_scalar_vector : std::false_type {};

        template <typename T> 
            requires (is_vector_v<T>)
        struct is_scalar_vector<T> : physics::is_scalar<typename T::value_t> {};

        template <typename T>
        inline static constexpr bool is_scalar_vector_v = is_scalar_vector<T>::value;


    // =============================================
    // vector traits
    // =============================================

        template <typename VECTOR_TYPE, size_t COLUMNS>
            requires (is_vector_v<VECTOR_TYPE>)
        struct matrix;

        template <typename T>
        struct is_matrix : std::false_type{};

        template <typename VECTOR_TYPE, size_t COLUMNS>
        struct is_matrix<matrix<VECTOR_TYPE, COLUMNS>> : std::true_type {};

        template <typename T>
        inline static constexpr bool is_matrix_v = is_matrix<T>::value;


        template <typename... Ts>
        struct are_matrix : std::conjunction<is_matrix<Ts>...> {};

        template <typename... Ts>
        inline static constexpr bool are_matrix_v = are_matrix<Ts...>::value;


} /// namespace scipp::geometry