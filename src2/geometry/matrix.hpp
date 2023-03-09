/**
 * @file    geometry/matrix.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-12
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once



namespace scipp::geometry {


    template <size_t COLUMNS, typename... TYPES> 
        requires (are_vectors_v<TYPES...>)
    struct matrix {


        // ===========================================================
        // aliases
        // ===========================================================

            using type = matrix<COLUMNS, TYPES...>;


        // ===========================================================
        // members
        // ===========================================================

            std::tuple<TYPES...> data_; ///< The matrix data


            static inline constexpr std::size_t rows = common_dimention_v<TYPES...>;

            static inline constexpr std::size_t columns = COLUMNS;

            static inline constexpr std::size_t size = rows * columns;


        // ===========================================================
        // constructors
        // ===========================================================

            /// @brief Default constructor
            constexpr matrix() noexcept : 

                data_{} {}


            /// @brief Constructor from a list of vectors
            constexpr matrix(TYPES&&... vectors) noexcept requires (sizeof...(vectors) == columns) : 

                data_{std::forward<TYPES>(vectors)...} {}

            
            /// @brief Copy constructor
            constexpr matrix(const matrix& other) noexcept :

                data_{other.data_} {}


            /// @brief Move constructor
            constexpr matrix(matrix&& other) noexcept :

                data_{std::move(other.data_)} {}


        // ===========================================================
        // operators
        // ===========================================================

            /// @brief Copy assignment operator
            constexpr matrix& operator=(const matrix& other) noexcept {

                data_ = other.data_;
                return *this;

            }


            /// @brief Move assignment operator
            constexpr matrix& operator=(matrix&& other) noexcept {

                data_ = std::move(other.data_);
                return *this;

            }


            template <std::size_t index>
            inline constexpr auto get_row() noexcept -> decltype(std::get<index>(data_))& {
                
                static_assert(index < COLUMNS, "Index out of bounds");
                return std::get<index>(data_);

            }


            template <std::size_t index>
            inline constexpr auto get_column() noexcept -> decltype(std::get<index>(data_))& {
                
                static_assert(index < COLUMNS, "Index out of bounds");
                return std::get<index>(data_);

            }


            template <std::size_t index>
            inline constexpr auto get_column() const noexcept -> const decltype(std::get<index>(data_))& {
                
                static_assert(index < COLUMNS, "Index out of bounds");
                return std::get<index>(data_);

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

                std::apply([](const auto&... args) { ((std::cout << args), ...); }, this->data_);

            }

    
    }; // struct matrix


    // ===========================================================
    // MATRIX TYPE TRAITS
    // ===========================================================

        template <typename T>
        struct is_matrix : std::false_type {};


        template <size_t COLUMNS, typename... TYPES>
        struct is_matrix<matrix<COLUMNS, TYPES...>> : std::true_type {};


        template <typename T>
        inline constexpr bool is_matrix_v = typename is_matrix<T>::value();


        template <typename T>
        inline constexpr bool is_square_matrix_v = false;


        template <size_t COLUMNS, typename... TYPES>
        inline constexpr bool is_square_matrix_v<matrix<COLUMNS, TYPES...>> = (COLUMNS == common_dimention_v<TYPES...>);


        // template <typename T>
        // inline constexpr bool is_diagonal_matrix_v = false;


        // template <size_t COLUMNS, typename... TYPES>
        // inline constexpr bool is_diagonal_matrix_v<matrix<COLUMNS, TYPES...>> = (COLUMNS == common_dimention_v<TYPES...>);


    


    template <typename... VECTORS> requires (are_vectors_v<VECTORS...>)
    matrix(VECTORS&&... vectors) -> matrix<sizeof...(VECTORS), VECTORS...>;


    template <typename... VECTORS> requires (are_vectors_v<VECTORS...>)
    inline constexpr auto make_matrix(VECTORS&&... vectors) noexcept -> matrix<sizeof...(VECTORS), VECTORS...> {
        
        return {std::forward<VECTORS>(vectors)...};

    }


    enum matrix_solver_methods {

        GEPP, // Gauss elimination with partial pivoting

        GJEPP, // Gauss-Jordan elimination with partial pivoting

        gauss_seidel,

        jacobi

    };


    // /**
    //     * @brief Solve the linear system Ax = b
    //     * 
    //     * @tparam DIM: dimension of the vector b
    //     * @tparam rows: number of rows of the matrix A
    //     * @tparam cols: number of columns of the matrix A
    //     * @param A: matrix<rows, cols> as l-value const reference
    //     * @param b: vector<DIM> as l-value const reference
    //     * @param method: matrix_solver_methods
    //     * 
    //     * @return vector<DIM> 
    //     */

    // template <typename MATRIX, typename VECTOR> requires (is_matrix_v<MATRIX> && is_vector_v<VECTOR> && MATRIX::columns == VECTOR::dimension)
    // inline constexpr auto solve_matrix(const MATRIX& A, const VECTOR& b, matrix_solver_methods method) {

    //     switch (method) {

    //         case matrix_solver_methods::GEPP: 
    //             return gauss_elimination(A, b);

    //         case matrix_solver_methods::GJEPP:
    //             return gauss_jordan_elimination(A, b);

    //         // case methods::gauss_seidel:
    //         //     return gauss_seidel(A, b);

    //         // case methods::jacobi:
    //         //     return jacobi(A, b);

    //         default:
    //             throw std::invalid_argument("The method is not implemented");

    //     }


    // }; // struct matrix_solver


    // /// @brief Solve the linear system Ax = b with the Gauss elimination method
    // template <typename MATRIX, typename VECTOR, typename RESULT> requires (is_matrix_v<MATRIX> && is_vector_v<VECTOR> && MATRIX::columns == VECTOR::dimension)
    // RESULT gauss_elimination(const MATRIX& A, const VECTOR& b) {


    //     static constexpr std::size_t DIM = VECTOR::dimension;

    //     if (A.rows != DIM || A.columns != DIM)
    //         throw std::invalid_argument("The matrix A must be a square matrix");

    //     // if (A.is_singular())
    //     //     throw std::invalid_argument("The matrix A is singular");


    //     matrix A_b = A.augment(b);
    //     RESULT x;

    //     for (std::size_t k{}; k < DIM; k++) {

    //         // Elimination of variables
    //         for (std::size_t i{k + 1}; i < DIM; i++) {

    //             auto factor = A_b(i, k) / A_b(k, k);

    //             for (std::size_t j{k}; j < DIM + 1; j++) 
    //                 A_b(i, j) -= factor * A_b(k, j);

    //         }

    //     }

    //     // Back substitution
    //     for (std::size_t i{DIM - 1}; i >= 0; i--) {

    //         x[i] = A_b(i, DIM) / A_b(i, i);

    //         for (std::size_t j{i + 1}; j < DIM; j++) 
    //             x[i] -= A_b(i, j) * x[j] / A_b(i, i);

    //     }

    //     return x;

    // }


    //     matrix<DIM, DIM + 1> A_b = A.augmented(b); 
    //     vector<DIM> x;

    //     for (std::size_t k{}; k < DIM; k++) {
            
    //         std::size_t pivot{k};
    //         measurement maxPivot;

    //         // Find the best pivot
    //         for (std::size_t i{k}; i < DIM; i++) 
    //             if (abs(A_b(i, k) > maxPivot)) {

    //                 maxPivot = abs(A_b(i, k));
    //                 pivot = i;

    //             }

    //         // Swap rows k and p
    //         if (pivot != k)
    //             for (std::size_t i{k}; i < DIM + 1; i++)
    //                 std::swap(A_b(pivot, i), A_b(k, i));

    //         // Elimination of variables
    //         for (std::size_t i{k + 1}; i < DIM; i++) {

    //             measurement factor = A_b(i, k) / A_b(k, k);

    //             for (std::size_t j{k}; j < DIM + 1; j++)
    //                 A_b(i, j) -= factor * A_b(k, j);

    //         }

    //     }

    //     // Back substitution
    //     for (long int k = DIM - 1; k >= 0; k--) {

    //         measurement sum = A_b(k, DIM);
    //         for (std::size_t j = k + 1; j < DIM; j++)
    //             sum -= A_b(k, j) * x[j];

    //         x[k] = sum / A_b(k, k);

    //     }

    //     return x; 

    // }


    // /// @brief Solve the linear system Ax = b with the Gauss-Jordan elimination method
    // template <std::size_t DIM, std::size_t rows, std::size_t cols>
    // vector<DIM> gauss_jordan_elimination(const matrix<rows, cols>& A, const vector<DIM>& b) {

    //     matrix<rows, cols + 1> A_b = A.augmented(b);
    //     measurement element;
    //     vector<DIM> result;

    //     // partial pivoting
    //     for (int i = DIM - 1; i > 0; i--) 
    //         if (abs(A_b(i - 1, 0)) < abs(A_b(i, 0)))
    //             for (std::size_t j{}; j <= DIM; j++) 
    //                 std::swap(A_b(i - 1, j), A_b(i, j));

    //     // gauss elimination
    //     for (std::size_t j{}; j < DIM; j++) 
    //         for (std::size_t i{}; i < DIM; i++) 
    //             if (i != j) {

    //                 element = A_b(i, j) / A_b(j, j);
                    
    //                 for (std::size_t k{}; k <= DIM; k++) 
    //                     A_b(i, k) -= element * A_b(j, k);

    //             }

    //     // diagonal elements
    //     for (std::size_t i{}; i < DIM; i++) 
    //         result[i] = A_b(i, DIM) / A_b(i, i);

    //     return result;

    // }



            // constexpr matrix& operator=(const matrix& other) noexcept {
            //     m_vectors = other.m_vectors;
            //     return *this;
            // }


            // constexpr matrix& operator=(matrix&& other) noexcept {
            //     m_vectors = std::move(other.m_vectors);
            //     return *this;
            // }


            // constexpr auto operator[](const std::size_t index) const noexcept {
            //     return m_vectors[index];
            // }


            // constexpr auto operator[](const std::size_t index) noexcept {
            //     return m_vectors[index];
            // }


            // constexpr auto operator()(const std::size_t row, const std::size_t column) const noexcept {
            //     return m_vectors[column][row];
            // }


            // constexpr auto operator()(const std::size_t row, const std::size_t column) noexcept {
            //     return m_vectors[column][row];
            // }


            // constexpr auto operator==(const matrix& other) const noexcept {
            //     return m_vectors == other.m_vectors;
            // }


            // constexpr auto operator!=(const matrix& other) const noexcept {
            //     return m_vectors != other.m_vectors;
            // }


            // constexpr auto operator+(const matrix& other) const noexcept {
            //     return matrix{m_vectors + other.m_vectors};
            // }


            // constexpr auto operator-(const matrix& other) const noexcept {
            //     return matrix{m_vectors - other.m_vectors};
            // }


            // constexpr auto operator*(const matrix& other) const noexcept {
            //     return matrix{m_vectors * other.m_vectors};
            // }


            // constexpr auto operator/(const matrix& other) const noexcept {
            //     return matrix{m_vectors / other.m_vectors};
            // }


            // constexpr auto operator+=(const matrix& other) noexcept {
            //     m_vectors += other.m_vectors;
            //     return *this;
            // }


            // constexpr auto operator-=(const matrix& other) noexcept {
            //     m_vectors -= other.m_vectors;
            //     return *this;
            // }


            // constexpr auto operator*=(const matrix& other) noexcept {
            //     m_vectors *= other.m_vectors;
            //     return *this;
            // }


            // constexpr auto operator/=(const matrix& other) noexcept {
            //     m_vectors /= other.m_vectors;
            //     return *this;
            // }


            // constexpr auto operator+(const value_type& value) const noexcept {
            //     return matrix{m_vectors + value};
            // }



            // constexpr auto operator-(const value_type& value) const noexcept {
            //     return matrix{m_vectors - value};
            // }


            // constexpr auto operator*(const value_type& value) const noexcept {
            //     return matrix{m_vectors * value};
            // }


            // constexpr auto operator/(const value_type& value) const noexcept {
            //     return matrix{m_vectors / value};
            // }


            // constexpr auto operator+=(const value_type& value) noexcept {
            //     m_vectors += value;
            //     return *this;
            // }


            // constexpr auto operator-=(const value_type& value) noexcept {
            //     m_vectors -= value;
            //     return *this;
            // }


            // constexpr auto operator*=(const value_type& value) noexcept {
            //     m_vectors *= value;
            //     return *this;
            // }



            







} // namespace scipp::geometry