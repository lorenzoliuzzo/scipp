/**
 * @file    geometry/matrix.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-23
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::geometry {
    

    /// @brief Tuple constructed from a fixed size and a list of types 
    template <size_t N, typename... Ts>
    struct types_tuple {

        using type = std::tuple<Ts...>;

    };


    /// @brief Tuple constructed from a fixed size and single type
    template <size_t N, typename T>
    struct types_tuple<N, T> {

        template <std::size_t... Is>
        static auto create_tuple(std::index_sequence<Is...>) {

            // Create a tuple with N copies of T
            return std::make_tuple((static_cast<void>(Is), T{})...);

        }

        using type = decltype(create_tuple(std::make_index_sequence<N>{}));

    };

    template <size_t N, typename... Ts>
    using types_tuple_t = typename types_tuple<N, Ts...>::type;


    /// @brief Matrix of vectors
    /// @tparam COLUMNS: Number of columns
    /// @tparam VECTOR_TYPES: list of vector types
    /// @note All the vectors must have same dimension
    /// @note The number of rows is the common dimension of the vectors
    template <size_t COLUMNS, typename... VECTOR_TYPES> 
        requires (are_vectors_v<VECTOR_TYPES...> && have_same_dimension_v<VECTOR_TYPES...>)
    struct matrix {


        // ===========================================================
        // aliases
        // ===========================================================

            using type = matrix<COLUMNS, VECTOR_TYPES...>;

            using data_type = types_tuple_t<COLUMNS, VECTOR_TYPES...>;


        // ===========================================================
        // members
        // ===========================================================            

            inline static constexpr std::size_t rows = common_dimension_v<VECTOR_TYPES...>;

            inline static constexpr std::size_t columns = COLUMNS;

            types_tuple_t<columns, VECTOR_TYPES...> data; 


        // ===========================================================
        // static members
        // ===========================================================            

            inline static constexpr matrix zero = { VECTOR_TYPES::zero... };


        // ===========================================================
        // constructors
        // ===========================================================

            /// @brief Default constructor 
            constexpr matrix() noexcept {}


            /// @brief Constructor from a list of vectors
            constexpr matrix(VECTOR_TYPES&... other) noexcept 
                requires (sizeof...(other) == columns) : 

                data{std::forward_as_tuple(other...)} {}


            /// @brief Constructor from a list of vectors
            constexpr matrix(VECTOR_TYPES&&... other) noexcept 
                requires (sizeof...(other) == columns) : 

                data{std::forward_as_tuple(std::move(other)...)} {}

            
            /// @brief Copy constructor
            constexpr matrix(const matrix& other) noexcept :

                data{other.data} {}


            /// @brief Move constructor
            constexpr matrix(matrix&& other) noexcept :

                data{std::move(other.data)} {}


            /// @brief Constructor from an std::tuple of vectors
            constexpr matrix(const data_type& other) noexcept :

                data{other} {}

            
            /// @brief Constructor from an std::tuple of vectors
            constexpr matrix(data_type&& other) noexcept :

                data{std::move(other)} {}


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


            /// @brief Copy assignment operator
            constexpr matrix& operator=(const data_type& other) noexcept {

                data = other;
                return *this;

            }


            /// @brief Move assignment operator
            constexpr matrix& operator=(data_type&& other) noexcept {

                data = std::move(other);
                return *this;

            }


            /// @brief Get the row at index
            template <std::size_t index>
            constexpr auto& row() {
                
                if (index >= rows)   
                    throw std::out_of_range("Cannot access column " + std::to_string(index) + " of a matrix with " + std::to_string(rows) + " rows");                
                
                return std::get<index>(data);

            }

            /// @brief Get the row at index
            template <std::size_t index>
            constexpr auto& row() const {
                
                if (index >= rows)   
                    throw std::out_of_range("Cannot access column " + std::to_string(index) + " of a matrix with " + std::to_string(rows) + " rows");                
                
                return std::get<index>(data);

            }


            /// @brief Get the column at index
            template <std::size_t index>
            constexpr auto& column() {
                
                if (index >= columns)                 
                    throw std::out_of_range("Cannot access column " + std::to_string(index) + " of a matrix with " + std::to_string(columns) + " columns");                
                    
                return std::get<index>(data);

            }

            /// @brief Get the column at index
            template <std::size_t index>
            constexpr auto& column() const {

                if (index >= columns) 
                    throw std::out_of_range("Cannot access column " + std::to_string(index) + " of a matrix with " + std::to_string(columns) + " columns");
                
                return std::get<index>(data);

            }


            /// @brief Get the element at row and column
            template <std::size_t row_i, std::size_t col_j>
            constexpr auto& element() {

                if (row_i >= rows) 
                    throw std::out_of_range("Cannot access element at row " + std::to_string(row_i) + " of a matrix with " + std::to_string(rows) + " rows");
                
                if (col_j >= columns)
                    throw std::out_of_range("Cannot access element at column " + std::to_string(col_j) + " of a matrix with " + std::to_string(columns) + " columns");

                return std::get<row_i>(data).data[col_j];

            }

            /// @brief Get the element at row and column
            template <std::size_t row_i, std::size_t col_j>
            constexpr auto& element() const {

                if (row_i >= rows) 
                    throw std::out_of_range("Cannot access element at row " + std::to_string(row_i) + " of a matrix with " + std::to_string(rows) + " rows");
                
                if (col_j >= columns)
                    throw std::out_of_range("Cannot access element at column " + std::to_string(col_j) + " of a matrix with " + std::to_string(columns) + " columns");

                return std::get<row_i>(data).data[col_j];

            }
            

        // ===================================ì========================
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
                        result.data = std::make_tuple(components * value ...);
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
                        result.data = std::make_tuple(components / value ...);
                    }, this->data
                );

                return result;

            }


            /// @brief Multiplication operator
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE>)
            constexpr auto operator*(const MEAS_TYPE& other) const noexcept 
                -> matrix<columns, vector<math::op::measurements_prod_t<typename VECTOR_TYPES::measurement_type, MEAS_TYPE>, rows>...> {

                matrix<columns, vector<math::op::measurements_prod_t<typename VECTOR_TYPES::measurement_type, MEAS_TYPE>, rows>...> result; 

                std::apply(
                    [&](const auto&... components) -> void {
                        result.data = std::make_tuple(components * other ...);
                    }, this->data
                );

                return result;

            }


            /// @brief Multiplication operator
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE>)
            constexpr auto operator*(MEAS_TYPE&& other) const noexcept 
                -> matrix<columns, vector<math::op::measurements_prod_t<typename VECTOR_TYPES::measurement_type, MEAS_TYPE>, rows>...> {

                matrix<columns, vector<math::op::measurements_prod_t<typename VECTOR_TYPES::measurement_type, MEAS_TYPE>, rows>...> result; 

                std::apply(
                    [&](const auto&... components) -> void {
                        result.data = std::make_tuple(components * other ...);
                    }, this->data
                );

                return result;

            }



            /// @brief Multiplication operator
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE>)
            constexpr auto operator/(const MEAS_TYPE& other) const 
                -> matrix<columns, vector<math::op::measurements_div_t<typename VECTOR_TYPES::measurement_type, MEAS_TYPE>, rows>...> {

                matrix<columns, vector<math::op::measurements_div_t<typename VECTOR_TYPES::measurement_type, MEAS_TYPE>, rows>...> result; 

                std::apply(
                    [&](const auto&... components) -> void {
                        result.data = std::make_tuple(components / other ...);
                    }, this->data
                );

                return result;

            }


            /// @brief Multiplication operator
            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE>)
            constexpr auto operator/(MEAS_TYPE&& other) const 
                -> matrix<columns, vector<math::op::measurements_div_t<typename VECTOR_TYPES::measurement_type, MEAS_TYPE>, rows>...> {

                matrix<columns, vector<math::op::measurements_div_t<typename VECTOR_TYPES::measurement_type, MEAS_TYPE>, rows>...> result; 

                std::apply(
                    [&](const auto&... components) -> void {
                        result.data = std::make_tuple(components / other ...);
                    }, this->data
                );

                return result;

            }


            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE>)
            friend constexpr auto operator*(const MEAS_TYPE& value, const matrix& mat) noexcept {

                matrix<columns, vector<math::op::measurements_prod_t<typename VECTOR_TYPES::measurement_type, MEAS_TYPE>, rows>...> result; 

                std::apply(
                    [&](const auto&... components) -> void {
                        result.data = std::make_tuple(value * components ...);
                    }, mat.data
                );

                return result;

            }


            template <typename MEAS_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE>)
            friend constexpr auto operator/(const MEAS_TYPE& value, const matrix& mat) noexcept {

                matrix<columns, vector<math::op::measurements_prod_t<typename VECTOR_TYPES::measurement_type, MEAS_TYPE>, rows>...> result; 

                std::apply(
                    [&](const auto&... components) -> void {
                        result.data = std::make_tuple(value / components ...);
                    }, mat.data
                );

                return result;

            }
            
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