/**
 * @file    geometry/matrix.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-10
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once



namespace scipp::geometry {


    template <size_t COLUMNS, typename... VECTOR_TYPES> 
        requires (are_vectors_v<VECTOR_TYPES...> && have_same_dimension_v<VECTOR_TYPES...>)
    struct matrix {


        // ===========================================================
        // aliases
        // ===========================================================

            using type = matrix<COLUMNS, VECTOR_TYPES...>;


        // ===========================================================
        // members
        // ===========================================================

            std::tuple<VECTOR_TYPES...> data; ///< The matrix data


            static inline constexpr std::size_t rows = std::tuple_size_v<std::tuple<VECTOR_TYPES...>>;

            static inline constexpr std::size_t columns = COLUMNS;

            // static inline constexpr std::size_t size = rows * columns;


        // ===========================================================
        // constructors
        // ===========================================================


            // /// @brief Construct a matrix from a single VECTOR_TYPE
            // template <typename VECTOR_TYPE2>    
            //     requires (is_vector_v<VECTOR_TYPE2> && are_same_vectors_v<VECTOR_TYPE2, VECTOR_TYPES...>)
            // constexpr matrix(std::initializer_list<VECTOR_TYPE2> list) noexcept :

            //     data{

            /// @brief Constructor from a list of vectors
            constexpr matrix(VECTOR_TYPES&... vectors) noexcept 
                requires (sizeof...(vectors) == columns) : 

                data{std::forward<VECTOR_TYPES>(vectors)...} {}


            /// @brief Constructor from a list of vectors
            constexpr matrix(VECTOR_TYPES&&... vectors) noexcept 
                requires (sizeof...(vectors) == columns) : 

                data{std::forward<VECTOR_TYPES>(vectors)...} {}

            
            /// @brief Copy constructor
            constexpr matrix(const matrix& other) noexcept :

                data{other.data} {}


            /// @brief Move constructor
            constexpr matrix(matrix&& other) noexcept :

                data{std::move(other.data)} {}


        // ===========================================================
        // operators
        // ===========================================================

            /// @brief Copy assignment operator
            constexpr matrix& operator=(const matrix& other) noexcept {

                data = other.data;
                return *this;

            }


            /// @brief Move assignment operator
            constexpr matrix& operator=(matrix&& other) noexcept {

                data = std::move(other.data);
                return *this;

            }


            template <std::size_t index>
            inline constexpr auto get_row() noexcept -> decltype(std::get<index>(data))& {
                
                static_assert(index < COLUMNS, "Index out of bounds");
                return std::get<index>(data);

            }


            template <std::size_t index>
            inline constexpr auto get_column() noexcept -> decltype(std::get<index>(data))& {
                
                static_assert(index < COLUMNS, "Index out of bounds");
                return std::get<index>(data);

            }


            template <std::size_t index>
            inline constexpr auto get_column() const noexcept -> const decltype(std::get<index>(data))& {
                
                static_assert(index < COLUMNS, "Index out of bounds");
                return std::get<index>(data);

            }



        // ===========================================================
        // operators
        // ===========================================================

            /// @brief Access the i-th row
            inline constexpr auto& operator[](size_t i) noexcept {

                return this->get_column<i>();

            }

        // ===========================================================
        // methods
        // ===========================================================
            
            // /// @brief Transpose the matrix
            // inline constexpr auto transpose() const noexcept {

            //     matrix<transposed_vector_t<TYPES>...> result;

            //     for (size_t i = 0; i < columns; i++) {
            //         for (size_t j = 0; j < rows; j++) {
            //             result[i][j] = (*this)[j][i];
            //         }
            //     }

            //     return result;

            // }


            // /// @brief Augment the matrix with a vector
            // template <typename VECTOR> requires (is_vector_v<VECTOR>)
            // inline constexpr auto augment(const VECTOR& vector) const noexcept {

            //     static_assert(VECTOR::dimension == this->rows, "The vector must have the same dimension of the matrix");

            //     matrix<COLUMNS + 1, TYPES..., VECTOR> result;

            //     for (size_t i{}; i < this->columns; ++i) 
            //         result.get_column<i>() = (*this).get_column<i>();

            //     result.get_column<this->columns>() = vector;

            //     return result;
 
            // }


            /// @brief Print the matrix
            inline constexpr void print() const noexcept {

                std::apply([](const auto&... args) { ((std::cout << args << '\n'), ...); }, this->data);

            }

    
    }; // struct matrix


    template <typename... VECTORS> 
        requires (are_vectors_v<VECTORS...>)
    matrix(VECTORS&... vectors) 
        -> matrix<sizeof...(VECTORS), VECTORS...>;


    template <typename... VECTORS> 
        requires (are_vectors_v<VECTORS...>)
    matrix(VECTORS&&... vectors) 
        -> matrix<sizeof...(VECTORS), VECTORS...>;

    template <typename VECTOR_TYPE>  
        requires (is_vector_v<VECTOR_TYPE>)
    matrix(std::initializer_list<VECTOR_TYPE> vectors) 
        -> matrix<sizeof(vectors), VECTOR_TYPE>;


    template <typename... VECTORS>  
        requires (are_vectors_v<VECTORS...> && have_same_dimension_v<VECTORS...>)
    inline constexpr auto make_matrix(VECTORS&... vectors) noexcept 
        -> matrix<sizeof...(vectors), VECTORS...> {
        
        return {std::forward<VECTORS>(vectors)...};

    }

    template <typename... VECTORS>  
        requires (are_vectors_v<VECTORS...> && have_same_dimension_v<VECTORS...>)
    inline constexpr auto make_matrix(VECTORS&&... vectors) noexcept 
        -> matrix<sizeof...(vectors), VECTORS...> {
        
        return matrix<sizeof...(vectors), VECTORS...>(std::forward<VECTORS>(vectors)...);

    }
    
    
} // namespace scipp::geometry