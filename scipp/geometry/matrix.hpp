/**
 * @file    geometry/matrix.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-02
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::geometry {


    template <typename VECTOR_TYPE, std::size_t COLUMNS>
        requires (is_vector_v<VECTOR_TYPE>)
    struct matrix {


        // ===========================================================
        // aliases
        // ===========================================================

            using type = matrix<VECTOR_TYPE, COLUMNS>;

            using data_t = std::array<VECTOR_TYPE, COLUMNS>;

            using measurement_t = typename VECTOR_TYPE::measurement_t; 

            using vector_type = VECTOR_TYPE; 

            using row_vector_type = vector<measurement_t, COLUMNS>;


        // ===========================================================
        // members
        // ===========================================================            

            inline static constexpr std::size_t rows = VECTOR_TYPE::dim;

            inline static constexpr std::size_t columns = COLUMNS;

            data_t data; 


        // ===========================================================
        // constructors
        // ===========================================================

            /// @brief Default constructor 
            constexpr matrix() noexcept = default;

            /// @brief Default destructor 
            constexpr ~matrix() noexcept = default; 


            /// @brief Copy constructor
            constexpr matrix(const matrix& other) noexcept :
                
                data{other.data} {}

            /// @brief Move constructor
            constexpr matrix(matrix&& other) noexcept :
                
                data{std::move(other.data)} {}


            /// @brief Constructor from an std::array<vector<measurement_t, rows>, columns>
            constexpr matrix(const data_t& other) noexcept :
                
                data{other} {}
            
            /// @brief Constructor from an std::array<vector<measurement_t, rows>, columns>
            constexpr matrix(data_t&& other) noexcept :
                
                data{std::move(other)} {}


            /// @brief Constructor from a list of vectors
            /// @note  The list of vectors must be of the same type
            /// @note The number of vectors must be equal to the number of columns
            template <typename... VECTORS>
                requires (are_same_vectors_v<VECTORS...> && sizeof...(VECTORS) == columns)
            constexpr matrix(VECTORS&... other) noexcept :
                
                data{std::forward<VECTOR_TYPE>(other...)} {}

            /// @brief Constructor from a list of vectors
            /// @note  The list of vectors must be of the same type
            /// @note The number of vectors must be equal to the number of columns
            template <typename... VECTORS>
                requires (are_same_vectors_v<VECTORS...> && sizeof...(VECTORS) == columns)
            constexpr matrix(VECTORS&&... other) noexcept :
                
                data{std::forward<VECTOR_TYPE>(std::move(other))...} {}


            /// @brief Construct a new matrix from a single vector
            constexpr matrix(const measurement_t& other) noexcept {
                
                this->data.fill(vector<measurement_t, rows>(other)); 

            }

            /// @brief Construct a new matrix from a single vector
            constexpr matrix(measurement_t&& other) noexcept {
                
                this->data.fill(vector<measurement_t, rows>(std::move(other))); 

            }

                        
        // ===========================================================
        // operators
        // ===========================================================
            
            /// @brief Equality operator
            constexpr bool operator==(const matrix& other) const noexcept {

                return std::equal(std::execution::par, this->data.begin(), this->data.end(), other.data.begin());

            }

            /// @brief Inequality operator
            constexpr bool operator!=(const matrix& other) const noexcept {

                return !std::equal(std::execution::par, this->data.begin(), this->data.end(), other.data.begin());

            }  
            

            /// @brief Copy assignment operator from a matrix object
            constexpr matrix& operator=(const matrix& other) noexcept {

                this->data = other.data;
                return *this;

            }

            /// @brief Move assignment operator from a matrix object
            constexpr matrix& operator=(matrix&& other) noexcept {

                this->data = std::move(other.data);
                return *this;

            }


            /// @brief Copy assignment operator from a data_t object
            constexpr matrix& operator=(const data_t& other) noexcept {

                this->data = other;
                return *this;

            }

            /// @brief Move assignment operator from a data_t object
            constexpr matrix& operator=(data_t&& other) noexcept {

                this->data = std::move(other);
                return *this;

            }


            /// @brief Addition operator
            constexpr matrix& operator+=(const matrix& other) noexcept {

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               other.data.begin(), 
                               this->data.begin(), 
                               std::plus<vector_type>());

                return *this;

            }

            /// @brief Addition operator
            constexpr matrix& operator+=(matrix&& other) noexcept {

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               std::move(other).data.begin(), 
                               this->data.begin(), 
                               std::plus<vector_type>());

                return *this;

            }


            /// @brief Subtraction operator
            constexpr matrix& operator-=(const matrix& other) noexcept {

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               other.data.begin(), 
                               this->data.begin(), 
                               std::minus<vector_type>());

                return *this;
                
            }

            /// @brief Subtraction operator
            constexpr matrix& operator-=(matrix&& other) noexcept {

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               std::move(other).data.begin(), 
                               this->data.begin(), 
                               std::minus<vector_type>());

                return *this;

            }


            /// @brief Addition operator
            constexpr matrix operator+(const matrix& other) const noexcept {

                data_t result;
                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               other.data.begin(), 
                               result.begin(), 
                               std::plus<vector_type>());

                return result;

            }

            /// @brief Addition operator
            constexpr matrix operator+(matrix&& other) const noexcept {

                data_t result;
                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               other.data.begin(), 
                               result.begin(), 
                               std::plus<vector_type>());

                return result;

            }


            /// @brief Subtraction operator
            constexpr matrix operator-(const matrix& other) const noexcept {

                data_t result;
                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               other.data.begin(), 
                               result.begin(), 
                               std::minus<vector_type>());

                return result;

            }

            /// @brief Subtraction operator
            constexpr matrix operator-(matrix&& other) const noexcept {

                data_t result;
                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               std::move(other).data.begin(), 
                               result.begin(), 
                               std::minus<vector_type>());

                return result;

            }


            /// @brief Negate a matrix
            constexpr matrix operator-() const noexcept {

                data_t result; 
                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               result.begin(), 
                               std::negate<vector_type>()); 

                return result;    

            }


            /// @brief Multiply this matrix by a scalar measurement
            constexpr matrix& operator*=(const physics::scalar_m& other) noexcept {

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               this->data.begin(), 
                               [&other](vector_type& x) { return x *= other; });

                return *this;

            }

            /// @brief Multiply this matrix by a scalar measurement
            constexpr matrix& operator*=(physics::scalar_m&& other) noexcept {

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               this->data.begin(), 
                               [&other](vector_type& x) { return std::move(x *= other); });

                return *this;

            }


            /// @brief Divide this matrix by a scalar measurement
            constexpr matrix& operator/=(const physics::scalar_m& other) {
                
                if (other.value == 0.0)
                    throw std::invalid_argument("Cannot divide a matrix by zero"); 

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               this->data.begin(), 
                               [&other](vector_type& x) { return x /= other; });

                return *this;

            }

            /// @brief Divide this matrix by a scalar measurement
            constexpr matrix& operator/=(physics::scalar_m&& other) {
                
                if (other.value == 0.0)
                    throw std::invalid_argument("Cannot divide a matrix by zero"); 

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               this->data.begin(), 
                               [&other](vector_type& x) { return std::move(x /= other); });

                return *this;

            }


            /// @brief Multiplicate a matrix with a generic measurement
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const OTHER_MEAS_TYPE& other) const noexcept 
                -> matrix<vector<math::op::multiply_t<measurement_t, OTHER_MEAS_TYPE>, rows>, columns> {

                std::array<vector<math::op::multiply_t<measurement_t, OTHER_MEAS_TYPE>, rows>, columns> result;

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               result.begin(), 
                               [&other](const vector_type& x) { return x * other; });

                return result; 

            }

            /// @brief Multiplicate a matrix with a generic measurement
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(OTHER_MEAS_TYPE&& other) const noexcept 
                -> matrix<vector<math::op::multiply_t<measurement_t, OTHER_MEAS_TYPE>, rows>, columns> {

                std::array<vector<math::op::multiply_t<measurement_t, OTHER_MEAS_TYPE>, rows>, columns> result;

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               result.begin(), 
                               [&other](const vector_type& x) { return std::move(x * other); });

                return result;

            }


            /// @brief Divide a matrix by a generic measurement
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(const OTHER_MEAS_TYPE& other) const 
                -> matrix<vector<math::op::divide_t<measurement_t, OTHER_MEAS_TYPE>, rows>, columns> {

                if (other.value == 0.0)
                    throw std::invalid_argument("Cannot divide a matrix by a zero measurement");

                return std::apply(
                    [&](const auto&... components) {
                        return std::array<vector<math::op::divide_t<measurement_t, OTHER_MEAS_TYPE>, rows>, columns>({components / other ...});
                    }, this->data
                );

            }

            /// @brief Divide a matrix by a generic measurement
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(OTHER_MEAS_TYPE&& other) const 
                -> matrix<vector<math::op::divide_t<measurement_t, OTHER_MEAS_TYPE>, rows>, columns> {

                if (other.value == 0.0)
                    throw std::invalid_argument("Cannot divide a matrix by a zero measurement");

                return std::apply(
                    [&](const auto&... components) {
                        return std::array<vector<math::op::divide_t<measurement_t, OTHER_MEAS_TYPE>, rows>, columns>({components / std::move(other) ...});
                    }, this->data
                );

            }


            /// @brief  Multiply a matrix by a vector
            template <typename OTHER_VEC_TYPE>
                requires (is_vector_v<OTHER_VEC_TYPE> && OTHER_VEC_TYPE::dim == columns)
            constexpr auto operator*(const OTHER_VEC_TYPE& other) const noexcept 
                -> vector<math::op::multiply_t<measurement_t, typename OTHER_VEC_TYPE::measurement_t>, rows> {
                
                std::array<math::op::multiply_t<measurement_t, typename OTHER_VEC_TYPE::measurement_t>, rows> result;
                const auto transposed_data = this->transpose().data;

                std::transform(std::execution::par,
                               transposed_data.begin(), transposed_data.end(), 
                               result.begin(), 
                               [&other](auto&& row) { return math::op::dot(row, other); });

                return result;            

            }

            /// @brief  Multiply a matrix by a vector
            template <typename OTHER_VEC_TYPE>
                requires (is_vector_v<OTHER_VEC_TYPE> && OTHER_VEC_TYPE::dim == columns)
            constexpr auto operator*(OTHER_VEC_TYPE&& other) const noexcept 
                -> vector<math::op::multiply_t<measurement_t, typename OTHER_VEC_TYPE::measurement_t>, rows> {
                
                std::array<math::op::multiply_t<measurement_t, typename OTHER_VEC_TYPE::measurement_t>, rows> result;
                const auto transposed_data = this->transpose().data;  

                std::transform(std::execution::par,
                               transposed_data.begin(), transposed_data.end(), 
                               result.begin(), 
                               [&other](auto&& row) { return math::op::dot(row, std::move(other)); });
                               
                return result;               

            }


            /// @brief Multiply a matrix to another matrix
            template <typename OTHER_VEC_TYPE>
                requires (is_vector_v<OTHER_VEC_TYPE> && OTHER_VEC_TYPE::dim == columns) 
            constexpr auto operator*(const matrix<OTHER_VEC_TYPE, rows>& other) const noexcept 
                -> matrix<vector<math::op::multiply_t<measurement_t, typename OTHER_VEC_TYPE::measurement_t>, rows>, columns> {

                std::array<vector<math::op::multiply_t<measurement_t, typename OTHER_VEC_TYPE::measurement_t>, rows>, columns> result;
                const auto transposed_data = this->transpose().data;  
                for (std::size_t i{}; i < columns; ++i)
                    for (std::size_t j{}; j < rows; ++j)
                        result[i][j] = math::op::dot(transposed_data[j], other.data[i]);

                return result;

            }

            /// @brief Multiply a matrix to another matrix
            template <typename OTHER_VEC_TYPE>
                requires (is_vector_v<OTHER_VEC_TYPE> && OTHER_VEC_TYPE::dim == columns) 
            constexpr auto operator*(matrix<OTHER_VEC_TYPE, rows>&& other) const noexcept 
                -> matrix<vector<math::op::multiply_t<measurement_t, typename OTHER_VEC_TYPE::measurement_t>, rows>, columns> {

                std::array<vector<math::op::multiply_t<measurement_t, typename OTHER_VEC_TYPE::measurement_t>, rows>, columns> result;
                const auto transposed_data = this->transpose().data;  
                for (std::size_t i{}; i < columns; ++i)
                    for (std::size_t j{}; j < rows; ++j)
                        result[i][j] = math::op::dot(transposed_data[j], std::move(other).data[i]);

                return result;

            }

        // ===========================================================
        // callable methods
        // ===========================================================
           
            /// @brief Get the identity matrix
            static constexpr auto identity() noexcept
                -> matrix<vector<physics::scalar_m, rows>, columns> 
                    requires (columns == rows) { 

                std::array<vector<physics::scalar_m, rows>, columns> result; 
                for (std::size_t i{}; i < columns; ++i)
                    for (std::size_t j{}; j < rows; ++j)
                        if (i == j)
                            result[i][j] = 1.0; 

                return result; 

            };


            /// @brief Get the column at index
            template <std::size_t index>
                requires (index < columns)
            constexpr vector_type column() const noexcept {
                                    
                return this->data[index];

            }

            /// @brief Get the column at index
            template <std::size_t index>
                requires (index < columns)
            constexpr vector_type column() noexcept {
                                    
                return this->data[index];

            }


            /// @brief Get the column at index
            constexpr vector_type column(std::size_t& index) const {
                                    
                if (index >= columns) 
                    throw std::out_of_range("Cannot access column " + std::to_string(index) + " from a matrix with " + std::to_string(columns) + " columns."); 

                return this->data[index];

            }

            /// @brief Get the column at index
            constexpr vector_type column(std::size_t& index) {
                                    
                if (index >= columns) 
                    throw std::out_of_range("Cannot access column " + std::to_string(index) + " from a matrix with " + std::to_string(columns) + " columns."); 

                return this->data[index];

            }


            /// @brief Get the row at index
            template <std::size_t index>
                requires (index < rows)
            constexpr decltype(auto) row() const noexcept {
                                    
                return std::apply(
                    [&](auto&&... column) -> row_vector_type {
                        return row_vector_type({column[index]...}); 
                    }, this->data
                );

            }

            /// @brief Get the row at index
            constexpr decltype(auto) row(std::size_t index) const {
                                    
                if (index >= rows) 
                    throw std::out_of_range("Cannot access row " + std::to_string(index) + " from a matrix with " + std::to_string(rows) + " rows."); 

                return std::apply(
                    [&](auto&&... column) -> row_vector_type {
                        return row_vector_type({column[index]...}); 
                    }, this->data
                );

            }

            /// @brief Get the element at row and column
            constexpr decltype(auto) element(std::size_t row_i, std::size_t col_j) {
                                    
                if (row_i >= rows) 
                    throw std::out_of_range("Cannot access row " + std::to_string(row_i) + " from a matrix with " + std::to_string(rows) + " rows."); 
                else if (col_j >= columns) 
                    throw std::out_of_range("Cannot access column " + std::to_string(col_j) + " from a matrix with " + std::to_string(columns) + " columns."); 

                return this->data[col_j][row_i];

            }


            /// @brief Get the element at row and column
            template <std::size_t row_i, std::size_t col_j>
                requires (row_i < rows && col_j < columns)
            constexpr decltype(auto) element() noexcept {

                return this->data[col_j][row_i];

            }


            /// @brief Add a column to a matrix
            constexpr auto vstack(const vector_type& other) const noexcept {

                return std::apply(
                    [&](const auto&... components) {
                        return std::array<vector_type, columns + 1>({components..., other});
                    }, this->data
                );

            }


            /// @brief Add a row to a matrix
            constexpr auto hstack(const row_vector_type& other) const noexcept {
                
                std::array<vector<measurement_t, rows + 1>, columns> result;
                for (std::size_t i{}; i < columns; ++i)
                    for (std::size_t j{}; j < rows; ++j)
                        result[i][j] = this->data[i][j];

                for (std::size_t i{}; i < rows; ++i)
                    result[columns][i] = other.data[i];

                return result; 

            }


            // /// @brief Get the subvector of the matrix
            // template <std::size_t row_i>
            //     requires (row_i < rows)
            // constexpr vector<measurement_t, columns> subvector() const noexcept {

            //     vector<measurement_t, columns> result;

            //     for (std::size_t i{}; i < columns; ++i)
            //         result[i] = this->data[i][row_i];

            //     return result;

            // }


            /// @brief Get the submatrix of the matrix
            template <std::size_t row_i, std::size_t col_j>
                requires (row_i < rows && col_j < columns)
            constexpr auto submatrix() const noexcept 
                -> matrix<vector<measurement_t, columns - 1>, rows - 1> {
                    
                std::array<vector<measurement_t, columns - 1>, rows - 1> result;

                for (std::size_t i{}; i < columns - 1; ++i)
                    for (std::size_t j{}; j < rows - 1; ++j)
                        result[i][j] = this->data[i < col_j ? i : i + 1][j < row_i ? j : j + 1];

                return result;

            }


            /// @brief Get the submatrix of the matrix
            constexpr auto submatrix(std::size_t row_i, std::size_t col_j) const 
                -> matrix<vector<measurement_t, columns - 1>, rows - 1> {
                    
                if (row_i >= rows) 
                    throw std::out_of_range("Cannot access row " + std::to_string(row_i) + " from a matrix with " + std::to_string(rows) + " rows."); 
                else if (col_j >= columns) 
                    throw std::out_of_range("Cannot access column " + std::to_string(col_j) + " from a matrix with " + std::to_string(columns) + " columns.");

                std::array<vector<measurement_t, columns - 1>, rows - 1> result;

                for (std::size_t i{}; i < columns - 1; ++i)
                    for (std::size_t j{}; j < rows - 1; ++j)
                        result[i][j] = this->data[i < col_j ? i : i + 1][j < row_i ? j : j + 1];

                return result;

            }


            /// @brief Transpose the matrix 
            constexpr matrix<row_vector_type, rows> transpose() const noexcept {

                std::array<row_vector_type, rows> result;

                for (std::size_t i{}; i < columns; ++i) 
                    for (std::size_t j{}; j < rows; ++j) 
                        result[j][i] = this->data[i][j];

                return result;

            }


            /// @brief Get the trace of the matrix
            constexpr measurement_t trace() const noexcept 
                requires (columns == rows) {

                measurement_t result;

                for (std::size_t i{}; i < columns; ++i)
                    result += this->data[i][i];

                return result;

            }


            /// @brief Get the diagonal of the matrix
            constexpr auto diagonal() const noexcept 
                -> vector<measurement_t, columns> 
                    requires (columns == rows) {

                std::array<measurement_t, columns> result;
                for (std::size_t i{}; i < columns; ++i)
                    result[i] = this->data[i][i];

                return result;

            }


            /// @brief Get the determinant of the matrix
            constexpr auto determinant() const noexcept 
                -> math::op::power_t<measurement_t, columns> 
                    requires (columns == rows) {

                if constexpr (columns == 1)
                    return this->data[0][0];

                else if constexpr (columns == 2) 
                    return this->data[0][0] * this->data[1][1] - this->data[0][1] * this->data[1][0];

                else if constexpr (columns == 3) 
                    return this->data[0][0] * this->data[1][1] * this->data[2][2] + 
                           this->data[0][1] * this->data[1][2] * this->data[2][0] + 
                           this->data[0][2] * this->data[1][0] * this->data[2][1] - 
                           this->data[0][2] * this->data[1][1] * this->data[2][0] - 
                           this->data[0][1] * this->data[1][0] * this->data[2][2] - 
                           this->data[0][0] * this->data[1][2] * this->data[2][1];

                else 
                    return std::apply([this](const auto&... args) { return (args * ...); }, this->upper_triangular().diagonal().data);

            }


            /// @brief Get the cofactor at row and column
            constexpr auto cofactor(const std::size_t& row_i, const std::size_t& col_j) const noexcept 
                -> math::op::power_t<measurement_t, columns - 1>
                    requires (columns == rows) {

                return this->submatrix(row_i, col_j).determinant() * (((row_i + col_j) % 2 == 0) ? 1. : -1.);

            }


            /// @brief Get the adjoint matrix
            constexpr auto adjoint() const noexcept 
                -> matrix<vector<math::op::power_t<measurement_t, columns - 1>, columns>, rows> 
                    requires (columns == rows) {

                std::array<vector<math::op::power_t<measurement_t, columns - 1>, columns>, rows> result;
                for (std::size_t i{}; i < columns; ++i) 
                    for (std::size_t j{}; j < rows; ++j) 
                        result[i][j] = this->cofactor(j, i);

                return result;

            }


            /// @brief Get the inverse of the matrix
            constexpr auto inverse() const 
                -> matrix<vector<math::op::invert_t<measurement_t>, columns>, rows>
                    requires (columns == rows) {

                if (this->determinant().value == 0.0) 
                    throw std::domain_error("Cannot invert a singular matrix.");

                return this->adjoint().transpose() / this->determinant();

            }


            /// @brief Solve the system of linear equations
            template <typename OTHER_VEC_TYPE>
                requires (is_vector_v<OTHER_VEC_TYPE> && OTHER_VEC_TYPE::dim == rows && columns == rows)
            constexpr auto solve(const OTHER_VEC_TYPE& b) const 
                -> vector<math::op::divide_t<typename OTHER_VEC_TYPE::measurement_t, measurement_t>, columns> {

                if (this->determinant().value == 0.0) 
                    throw std::domain_error("Cannot solve a singular system of linear equations.");

                return this->inverse() * b;

            }
            

            /// @brief Solve the linear system Ax = b with the Gauss elimination method
            constexpr auto gauss_solve(const vector_type& other) const noexcept 
                -> vector<physics::scalar_m, rows>
                    requires (columns == rows) {

                std::array<vector_type, columns + 1> A_b = this->vstack(other); 
                std::array<physics::scalar_m, rows> result;

                for (std::size_t k{}; k < columns; ++k) {
                    
                    std::size_t pivot{k};
                    measurement_t maxPivot;

                    // Find the best pivot
                    for (std::size_t i{k}; i < columns; ++i) 
                        if (math::op::abs(A_b[k][i]) > maxPivot) {

                            maxPivot = math::op::abs(A_b[k][i]);
                            pivot = i;

                        }

                    // Swap rows k and p
                    if (pivot != k)
                        for (std::size_t i{k}; i < columns + 1; ++i)
                            std::swap(A_b[i][pivot], A_b[i][k]);

                    // Elimination of variables
                    for (std::size_t i{k + 1}; i < columns; ++i) {

                        physics::scalar_m factor = A_b[k][i] / A_b[k][k];

                        for (std::size_t j{k}; j < columns + 1; j++)
                            A_b[j][i] -= factor * A_b[j][k];

                    }

                }

                // Back substitution
                for (long int k = columns - 1; k >= 0; k--) {

                    measurement_t sum = A_b[columns][k];
                    for (std::size_t j = k + 1; j < columns; j++)
                        sum -= result[j] * A_b[j][k];

                    result[k] = sum / A_b[k][k];

                }

                return result; 

            }
    

            constexpr auto gauss_jordan_solve(const vector_type& other) const noexcept 
                -> vector<physics::scalar_m, rows>
                    requires (columns == rows) {

                std::array<vector_type, columns + 1> A_b = this->vstack(other);
                physics::scalar_m factor;
                std::array<physics::scalar_m, rows> result;

                // partial pivoting
                for (int i = columns - 1; i > 0; --i) 
                    if (math::op::abs(A_b[0][i - 1]) < math::op::abs(A_b[i][0]))
                        for (std::size_t j{}; j <= columns; j++) 
                            std::swap(A_b[j][i - 1], A_b[j][i]);

                // gauss elimination
                for (std::size_t j{}; j < columns; ++j) 
                    for (std::size_t i{}; i < columns; ++i) 
                        if (i != j) {

                            factor = A_b[j][i] / A_b[j][j];
                            
                            for (std::size_t k{}; k <= columns; k++) 
                                A_b[k][i] -= factor * A_b[k][j];

                        }

                // diagonal elements
                for (std::size_t i{}; i < rows; ++i) 
                    result[i] = A_b[columns][i] / A_b[i][i];

                return result;

            }


            /// @brief Reduce the matrix to an upper triangular matrix
            constexpr auto upper_triangular() const noexcept 
                -> matrix<vector_type, rows>
                    requires (columns == rows) {

                matrix<vector_type, rows> result{*this};
                physics::scalar_m factor;

                for (std::size_t i{}; i < columns; ++i) 
                    for (std::size_t j{i + 1}; j < columns; ++j) {

                        factor = result.data[i][j] / result.data[i][i];

                        for (std::size_t k{}; k < columns; ++k) 
                            result.data[k][j] -= factor * result.data[k][i];

                    }

                return result;

            }


            /// @brief Reduce the matrix to a lower triangular matrix
            constexpr auto lower_triangular() const noexcept 
                -> matrix<vector_type, rows>
                    requires (columns == rows) {

                matrix<vector_type, rows> result{*this};
                physics::scalar_m factor;

                for (std::size_t i{columns - 1}; i > 0; --i) 
                    for (std::size_t j{i - 1}; j > 0; --j) {

                        factor = result.data[i][j] / result.data[i][i];

                        for (std::size_t k{}; k < columns; ++k) 
                            result.data[k][j] -= factor * result.data[k][i];

                    }

                return result;

            }


            /// @brief Get the eigenvalues of the matrix
            constexpr auto eigenvalues() const noexcept 
                -> std::array<physics::scalar_m, rows>
                    requires (columns == rows) {
                        
            }


            /// @brief Print the matrix
            constexpr void print() const noexcept {

                std::apply([](const auto&... args) { ((std::cout << args << '\n'), ...); }, this->data);
                std::cout << '\n'; 

            }


    }; 
    

    template <typename VEC_TYPE, typename... VECTORS> 
        requires (are_same_vectors_v<VEC_TYPE, VECTORS...>)
    matrix(VECTORS&... vectors) 
        -> matrix<VEC_TYPE, sizeof...(VECTORS)>;


    template <typename VEC_TYPE, typename... VECTORS> 
        requires (are_same_vectors_v<VEC_TYPE, VECTORS...>)
    matrix(VECTORS&&... vectors) 
        -> matrix<VEC_TYPE, sizeof...(VECTORS)>;


    template <typename VEC_TYPE, typename... VECTORS>  
        requires (are_same_vectors_v<VEC_TYPE, VECTORS...>) 
    inline constexpr auto make_matrix(VECTORS&... other) noexcept 
        -> matrix<VEC_TYPE, sizeof...(other)> {
        
        return {std::forward<VECTORS>(other)...};

    }
    
    template <typename VEC_TYPE, typename... VECTORS>  
        requires (are_same_vectors_v<VEC_TYPE, VECTORS...>) 
    inline constexpr auto make_matrix(VECTORS&&... other) noexcept 
        -> matrix<VEC_TYPE, sizeof...(other)> {
        
        return {std::forward<VECTORS>(other)...};

    }
        

    template <typename VEC_TYPE, std::size_t DIM, typename... VECTORS>  
        requires (are_same_vectors_v<VEC_TYPE, VECTORS...>) 
    inline constexpr auto make_matrix(VECTORS&... other) noexcept 
        -> matrix<VEC_TYPE, DIM> 
            requires (sizeof...(other) == DIM) {
        
        return {std::forward<VECTORS>(other)...};

    }
    
    template <typename VEC_TYPE, std::size_t DIM, typename... VECTORS>  
        requires (are_same_vectors_v<VEC_TYPE, VECTORS...>) 
    inline constexpr auto make_matrix(VECTORS&&... other) noexcept 
        -> matrix<VEC_TYPE, DIM> 
            requires (sizeof...(other) == DIM) {
        
        return {std::forward<VECTORS>(other)...};

    }


    template <typename VEC_TYPE, std::size_t DIM>  
        requires (is_vector_v<VEC_TYPE>)
    inline constexpr auto make_random_matrix() noexcept 
        -> matrix<VEC_TYPE, DIM> {

        matrix<VEC_TYPE, DIM> result;

        for (std::size_t i{}; i < DIM; i++) 
            for (std::size_t j{}; j < DIM; j++) 
                result.data[j][i] = std::rand(); 

        return result;

    }


    template <typename T>
    struct is_matrix : std::false_type {};


    template <typename VEC_TYPE, std::size_t DIM>
        requires (is_vector_v<VEC_TYPE>)
    struct is_matrix<matrix<VEC_TYPE, DIM>> : std::true_type {};


    template <typename T>
    inline constexpr bool is_matrix_v = is_matrix<T>::value;


} // namespace scipp::geometry