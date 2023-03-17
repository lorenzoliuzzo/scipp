/**
 * @file    geometry/matrix.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-13
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


            inline static constexpr std::size_t rows = common_dimension_v<VECTOR_TYPES...>;

            inline static constexpr std::size_t columns = COLUMNS;

            inline static constexpr matrix zero = { VECTOR_TYPES::zero... };


            // static constexpr matrix identity() 
            //     requires (rows == columns) {

            // }


            // static inline constexpr std::size_t size = rows * columns;


        // ===========================================================
        // constructors
        // ===========================================================

            /// @brief Default constructor 
            constexpr matrix() noexcept = default; 


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


            /// @brief Constructor from an std::tuple of vectors
            constexpr matrix(const std::tuple<VECTOR_TYPES...>& tuple) noexcept :

                data{tuple} {}

            
            /// @brief Constructor from an std::tuple of vectors
            constexpr matrix(std::tuple<VECTOR_TYPES...>&& tuple) noexcept :

                data{std::move(tuple)} {}


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
            constexpr auto& row() {
                
                if (index >= rows)   
                    throw std::out_of_range("Cannot access column " + std::to_string(index) + " of a matrix with " + std::to_string(rows) + " rows");                
                
                return std::get<index>(data);

            }

            template <std::size_t index>
            constexpr auto& row() const {
                
                if (index >= rows)   
                    throw std::out_of_range("Cannot access column " + std::to_string(index) + " of a matrix with " + std::to_string(rows) + " rows");                
                
                return std::get<index>(data);

            }


            template <std::size_t index>
            constexpr auto& column() {
                
                if (index >= columns)                 
                    throw std::out_of_range("Cannot access column " + std::to_string(index) + " of a matrix with " + std::to_string(columns) + " columns");                
                    
                return std::get<index>(data);

            }

            template <std::size_t index>
            constexpr auto& column() const {

                if (index >= columns) 
                    throw std::out_of_range("Cannot access column " + std::to_string(index) + " of a matrix with " + std::to_string(columns) + " columns");
                
                return std::get<index>(data);

            }


            template <std::size_t row_i, std::size_t col_j>
            constexpr auto& element() {

                if (row_i >= rows) 
                    throw std::out_of_range("Cannot access element at row " + std::to_string(row_i) + " of a matrix with " + std::to_string(rows) + " rows");
                
                if (col_j >= columns)
                    throw std::out_of_range("Cannot access element at column " + std::to_string(col_j) + " of a matrix with " + std::to_string(columns) + " columns");

                return std::get<row_i>(data).data[col_j];

            }

            template <std::size_t row_i, std::size_t col_j>
            constexpr auto& element() const {

                if (row_i >= rows) 
                    throw std::out_of_range("Cannot access element at row " + std::to_string(row_i) + " of a matrix with " + std::to_string(rows) + " rows");
                
                if (col_j >= columns)
                    throw std::out_of_range("Cannot access element at column " + std::to_string(col_j) + " of a matrix with " + std::to_string(columns) + " columns");

                return std::get<row_i>(data).data[col_j];

            }
            

        // ===========================================================
        // operators
        // ===========================================================

            /// @brief Addition operator
            constexpr matrix& operator+=(const matrix& other) noexcept {

                std::apply(
                    [&](auto&... lhs_components) {
                        std::apply(
                            [&](const auto&... rhs_components) {
                                ((lhs_components += rhs_components), ...);
                            }, other.data 
                        );
                    }, this->data
                ); 
                               
                return *this;

            }


            /// @brief Subtraction operator
            constexpr matrix& operator-=(const matrix& other) noexcept {

                std::apply(
                    [&](auto&... lhs_components) {
                        std::apply(
                            [&](const auto&... rhs_components) {
                                ((lhs_components -= rhs_components), ...);
                            }, other.data 
                        );
                    }, this->data
                ); 
                               
                return *this;

            }


            /// @brief Addition operator
            constexpr matrix operator+(const matrix& other) const noexcept {

                matrix result;

                std::apply(
                    [&](const auto&... lhs_components) {
                        std::apply(
                            [&](const auto&... rhs_components) {
                                result.data = std::make_tuple(lhs_components + rhs_components...);
                            }, other.data 
                        );
                    }, this->data
                ); 
                               
                return result;

            }


            /// @brief Subtraction operator
            constexpr matrix operator-(const matrix& other) const noexcept {

                matrix result;

                std::apply(
                    [&](const auto&... lhs_components) {
                        std::apply(
                            [&](const auto&... rhs_components) {
                                result.data = std::make_tuple(lhs_components - rhs_components...);
                            }, other.data 
                        );
                    }, this->data
                ); 
                               
                return result;

            }


            /// @brief Negate operator
            constexpr matrix operator-() const noexcept {

                matrix result;

                std::apply(
                    [&](const auto&... components) {
                        result.data = std::make_tuple(-components...);
                    }, this->data
                ); 
                               
                return result;

            }


            /// @brief Multiplication operator
            constexpr matrix& operator*=(const physics::scalar_m& value) noexcept {

                std::apply(
                    [&](auto&... components) {
                        ((components *= value), ...);
                    }, this->data
                );

                return *this;

            }


            /// @brief Division operator
            constexpr matrix& operator/=(const physics::scalar_m& value) {

                if (value == 0.0) 
                    throw std::invalid_argument("Cannot divide a matrix by zero");

                std::apply(
                    [&](auto&... components) {
                        ((components /= value), ...);
                    }, this->data
                );

                return *this;

            }


            /// @brief Multiplication operator
            constexpr matrix operator*(const physics::scalar_m& value) const noexcept {

                matrix result; 

                std::apply(
                    [&](const auto&... components) {
                        result.data = std::make_tuple(components * value...);
                    }, this->data
                );

                return result;

            }


            /// @brief Division operator
            constexpr matrix operator/(const physics::scalar_m& value) const {

                if (value == 0.0) 
                    throw std::invalid_argument("Cannot divide a matrix by zero");

                matrix result; 

                std::apply(
                    [&](const auto&... components) {
                        result.data = std::make_tuple(components / value...);
                    }, this->data
                );

                return result;

            }


            /// @brief Multiplication operator
            // template <typename... OTHER_VECTOR_TYPES>   
            


            
            // /// @brief Multiplication operator
            // constexpr auto operator*(const matrix& other) const noexcept {

            //     matrix<VECTOR_TYPES...> result;

            //     for (size_t i = 0; i < rows; i++) 
            //         for (size_t j = 0; j < columns; j++) 
            //             result[i][j] = this->row<i>() * other.column<j>();

            //     return result;

            // }


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


            /// @brief Augment the matrix with a vector
            template <typename VECTOR> 
                requires (is_vector_v<VECTOR> && have_same_dimension_v<VECTOR, VECTOR_TYPES...>)
            inline constexpr auto augment(const VECTOR& vector) const noexcept 
                -> matrix<COLUMNS + 1, VECTOR_TYPES..., VECTOR> {

                return matrix<COLUMNS + 1, VECTOR_TYPES..., VECTOR>(std::apply([&vector](const auto&... args) { return std::tuple_cat(std::forward_as_tuple(args...), std::forward_as_tuple(vector)); }, this->data));

            }


            /// @brief Print the matrix
            constexpr void print() const noexcept {

                std::apply([](const auto&... args) { ((std::cout << args << '\n'), ...); }, this->data);
                std::cout << '\n'; 

            }


        // ===========================================================
        // static methods
        // ===========================================================

            // /// @brief Create a matrix from a list of vectors
            // static inline constexpr auto identity() noexcept {

            //     matrix result;

            //     std::apply([&result](auto i) {

            //         std::apply([&result, &i])(auto j) {

            //             if (i != j)
            //                 result.row<i>()[j] = 0.0;
            //             else 
            //                 result.row<i>()[j] = 1.0;

            //         }, std::make_index_sequence<columns>();

            //     }, std::make_index_sequence<rows>());

            //     return result; 

            // }


    }; // struct matrix


    template <typename... VECTORS> 
        requires (are_vectors_v<VECTORS...>)
    matrix(VECTORS&... vectors) 
        -> matrix<sizeof...(VECTORS), VECTORS...>;


    template <typename... VECTORS> 
        requires (are_vectors_v<VECTORS...>)
    matrix(VECTORS&&... vectors) 
        -> matrix<sizeof...(VECTORS), VECTORS...>;


    template <int COLUMNS, typename... VECTORS>
        requires (are_vectors_v<VECTORS...> && have_same_dimension_v<VECTORS...> && sizeof...(VECTORS) <= COLUMNS)
    inline constexpr auto make_matrix() noexcept 
        -> matrix<COLUMNS, VECTORS...> {
        
        return matrix<COLUMNS, VECTORS...>();

    }


    template <int COLUMNS, typename VECTOR_TYPE, typename... VECTORS>  
        requires (are_same_vectors_v<VECTOR_TYPE, VECTORS...> && sizeof...(VECTORS) <= COLUMNS)
    inline constexpr auto make_matrix(VECTORS&... vectors) noexcept 
        -> matrix<COLUMNS, VECTORS...> {
        
        return {std::forward<VECTORS>(vectors)...};

    }

    template <int COLUMNS, typename VECTOR_TYPE, typename... VECTORS>  
        requires (are_same_vectors_v<VECTOR_TYPE, VECTORS...> && sizeof...(VECTORS) <= COLUMNS)
    inline constexpr auto make_matrix(VECTORS&&... vectors) noexcept 
        -> matrix<COLUMNS, VECTORS...> {
        
        return {std::forward<VECTORS>(vectors)...};

    }


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