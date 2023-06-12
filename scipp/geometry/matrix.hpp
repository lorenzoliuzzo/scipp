/**
 * @file    geometry/matrix.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * 
 * @brief   
 * 
 * @date    2023-06-12
 * @copyright Copyright (c) 2023
 */



namespace scipp::geometry {


    template <typename VECTOR_TYPE, size_t COLUMNS>
        requires (is_vector_v<VECTOR_TYPE>)
    struct matrix {


        // ===========================================================
        // static members
        // ===========================================================

            inline static constexpr size_t rows = VECTOR_TYPE::dim;

            inline static constexpr size_t columns = COLUMNS;
            

        // ===========================================================
        // aliases
        // ===========================================================

            using value_t = VECTOR_TYPE; 

            using element_t = typename VECTOR_TYPE::value_t; 

            using data_t = std::array<value_t, columns>;

            using _t = matrix<value_t, columns>;


        // ===========================================================
        // members
        // ===========================================================            

            data_t data; 

            std::array<uint, rows> max_idx_row; // array of indices of the maximum element in each row

            std::array<uint, columns> max_idx_col; // array of indices of the maximum element in each column


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


            /// @brief Constructor from an std::array<vector<value_t, rows>, columns>
            constexpr matrix(const data_t& other) noexcept :
                
                data{other} {}
            
            /// @brief Constructor from an std::array<vector<value_t, rows>, columns>
            constexpr matrix(data_t&& other) noexcept :
                
                data{std::move(other)} {}


            /// @brief Constructor from a list of vectors
            /// @note  The list of vectors must be of the same type
            /// @note The number of vectors must be equal to the number of columns
            template <typename... VECTORS>
                requires (sizeof...(VECTORS) == columns) // are_same_vectors_v<VECTORS...> && 
            constexpr matrix(VECTORS&&... other) noexcept :
                
                data{std::forward<value_t>(other)...} {}


            // /// @brief Constructor from a list of vectors
            // /// @note  The list of vectors must be of the same type
            // /// @note The number of vectors must be equal to the number of columns
            // template <typename... VECTORS>
            //     requires (sizeof...(VECTORS) == columns) // are_same_vectors_v<VECTORS...> && 
            // constexpr matrix(VECTORS&&... other) noexcept :
                
            //     data{std::forward<value_t>(other)...} {}

                        
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


        // ===========================================================
        // callable methods
        // ===========================================================
           
            /// @brief Get the identity matrix
            static constexpr auto identity() noexcept
                -> matrix<value_t, columns> 
                    requires (columns == rows) { 

                std::array<value_t, columns> result; 
                for (size_t i{}; i < columns; ++i)
                    for (size_t j{}; j < rows; ++j)
                        if (i == j)
                            result[i][j] = element_t::one; 

                return result; 

            };


            constexpr value_t operator[](size_t index) const noexcept {

                return this->data[index];

            }


            /// @brief Get the column at index
            template <size_t index>
                requires (index < columns)
            constexpr value_t column() const noexcept {
                                    
                return this->data[index];

            }

            /// @brief Get the column at index
            template <size_t index>
                requires (index < columns)
            constexpr value_t column() noexcept {
                                    
                return this->data[index];

            }


            /// @brief Get the column at index
            constexpr value_t column(size_t& index) const {
                                    
                if (index >= columns) 
                    throw std::out_of_range("Cannot access column " + std::to_string(index) + " from a matrix with " + std::to_string(columns) + " columns."); 

                return this->data[index];

            }

            /// @brief Get the column at index
            constexpr value_t column(size_t& index) {
                                    
                if (index >= columns) 
                    throw std::out_of_range("Cannot access column " + std::to_string(index) + " from a matrix with " + std::to_string(columns) + " columns."); 

                return this->data[index];

            }


            /// @brief Get the row at index
            template <size_t index>
                requires (index < rows)
            constexpr decltype(auto) row() const noexcept {
                                    
                return std::apply(
                    [&](auto&&... column) -> row_vector<element_t, rows> {
                        return {column[index]...}; 
                    }, this->data
                );

            }

            /// @brief Get the row at index
            constexpr decltype(auto) row(size_t index) const {
                                    
                if (index >= rows) 
                    throw std::out_of_range("Cannot access row " + std::to_string(index) + " from a matrix with " + std::to_string(rows) + " rows."); 

                return std::apply(
                    [&](auto&&... column) -> row_vector<element_t, rows> {
                        return {column[index]...}; 
                    }, this->data
                );

            }

            /// @brief Get the element at row and column
            constexpr decltype(auto) element(size_t row_i, size_t col_j) {
                                    
                if (row_i >= rows) 
                    throw std::out_of_range("Cannot access row " + std::to_string(row_i) + " from a matrix with " + std::to_string(rows) + " rows."); 
                else if (col_j >= columns) 
                    throw std::out_of_range("Cannot access column " + std::to_string(col_j) + " from a matrix with " + std::to_string(columns) + " columns."); 

                return this->data[col_j][row_i];

            }


            /// @brief Get the element at row and column
            template <size_t row_i, size_t col_j>
                requires (row_i < rows && col_j < columns)
            constexpr decltype(auto) element() noexcept {

                return this->data[col_j][row_i];

            }


            /// @brief Add a column to a matrix
            constexpr auto vstack(const value_t& other) const noexcept {

                return std::apply(
                    [&](const auto&... components) {
                        return std::array<value_t, columns + 1>({components..., other});
                    }, this->data
                );

            }


            // /// @brief Add a row to a matrix
            // constexpr auto hstack(const row_vector_t& other) const noexcept {
                
            //     std::array<vector<value_t, rows + 1>, columns> result;
            //     for (size_t i{}; i < columns; ++i)
            //         for (size_t j{}; j < rows; ++j)
            //             result[i][j] = this->data[i][j];

            //     for (size_t i{}; i < rows; ++i)
            //         result[columns][i] = other.data[i];

            //     return result; 

            // }


            // /// @brief Get the subvector of the matrix
            // template <size_t row_i>
            //     requires (row_i < rows)
            // constexpr vector<value_t, columns> subvector() const noexcept {

            //     vector<value_t, columns> result;

            //     for (size_t i{}; i < columns; ++i)
            //         result[i] = this->data[i][row_i];

            //     return result;

            // }


            // /// @brief Get the submatrix of the matrix
            // template <size_t row_i, size_t col_j>
            //     requires (row_i < rows && col_j < columns)
            // constexpr auto submatrix() const noexcept 
            //     -> matrix<vector<value_t, columns - 1>, rows - 1> {
                    
            //     std::array<vector<value_t, columns - 1>, rows - 1> result;

            //     for (size_t i{}; i < columns - 1; ++i)
            //         for (size_t j{}; j < rows - 1; ++j)
            //             result[i][j] = this->data[i < col_j ? i : i + 1][j < row_i ? j : j + 1];

            //     return result;

            // }


            // /// @brief Get the submatrix of the matrix
            // constexpr auto submatrix(size_t row_i, size_t col_j) const 
            //     -> matrix<vector<value_t, columns - 1>, rows - 1> {
                    
            //     if (row_i >= rows) 
            //         throw std::out_of_range("Cannot access row " + std::to_string(row_i) + " from a matrix with " + std::to_string(rows) + " rows."); 
            //     else if (col_j >= columns) 
            //         throw std::out_of_range("Cannot access column " + std::to_string(col_j) + " from a matrix with " + std::to_string(columns) + " columns.");

            //     std::array<vector<value_t, columns - 1>, rows - 1> result;

            //     for (size_t i{}; i < columns - 1; ++i)
            //         for (size_t j{}; j < rows - 1; ++j)
            //             result[i][j] = this->data[i < col_j ? i : i + 1][j < row_i ? j : j + 1];

            //     return result;

            // }


            /// @brief Transpose the matrix 
            constexpr matrix<vector<element_t, columns, !value_t::flag>, rows> transpose() const noexcept {

                std::array<vector<element_t, columns, !value_t::flag>, rows> result;

                for (size_t i{}; i < columns; ++i) 
                    for (size_t j{}; j < rows; ++j) 
                        result[j][i] = this->data[i][j];

                return result;

            }


            /// @brief Get the trace of the matrix
            constexpr element_t trace() const noexcept 
                requires (columns == rows) {

                element_t result;

                for (size_t i{}; i < columns; ++i)
                    result += this->data[i][i];

                return result;

            }


            /// @brief Get the diagonal of the matrix
            constexpr auto diagonal() const noexcept 
                -> vector<element_t, columns> 
                    requires (columns == rows) {

                std::array<element_t, columns> result;
                for (size_t i{}; i < columns; ++i)
                    result[i] = this->data[i][i];

                return result;

            }


            /// @brief Get the determinant of the matrix
            constexpr auto determinant() const noexcept 
                -> math::functions::power_t<columns, element_t> 
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
            constexpr auto cofactor(const size_t& row_i, const size_t& col_j) const noexcept 
                -> math::functions::power_t<columns - 1, element_t>
                    requires (columns == rows) {
                
                auto submatrix = this->submatrix(row_i, col_j);
                return (((row_i + col_j) % 2 == 0) ? submatrix.determinant() : -submatrix.determinant()); 
                
            }


            /// @brief Get the adjoint matrix
            constexpr auto adjoint() const noexcept 
                -> matrix<vector<math::functions::power_t<columns - 1, element_t>, columns>, rows> 
                    requires (columns == rows) {

                std::array<vector<math::functions::power_t<columns - 1, element_t>, columns>, rows> result;
                for (size_t i{}; i < columns; ++i) 
                    for (size_t j{}; j < rows; ++j) 
                        result[i][j] = this->cofactor(j, i);

                return result;

            }


            /// @brief Get the inverse of the matrix
            constexpr auto inverse() const 
                -> matrix<vector<math::functions::invert_t<element_t>, columns>, rows>
                    requires (columns == rows) {

                if (this->determinant().value == 0.0) 
                    throw std::domain_error("Cannot invert a singular matrix.");

                return this->adjoint().transpose() / this->determinant();

            }


            /// @brief Solve the system of linear equations
            template <typename OTHER_VEC_TYPE>
                requires (is_vector_v<OTHER_VEC_TYPE> && OTHER_VEC_TYPE::dim == rows && columns == rows)
            friend constexpr auto solve(const matrix& A, const OTHER_VEC_TYPE& b) {

                if (A.determinant().value == 0.0) 
                    throw std::domain_error("Cannot solve a singular system of linear equations.");

                return A.inverse() * b;

            }
            

            // /// @brief Solve the linear system Ax = b with the Gauss elimination method
            // friend constexpr auto gauss_solve(const matrix& A, const vector_t& b) noexcept 
            //     -> vector<physics::scalar_m, rows>
            //         requires (columns == rows) {

            //     std::array<vector_t, columns + 1> A_b = A.vstack(b); 
            //     std::array<physics::scalar_m, rows> result;

            //     for (size_t k{}; k < columns; ++k) {
                    
            //         size_t pivot{k};
            //         value_t maxPivot;

            //         // Find the best pivot
            //         for (size_t i{k}; i < columns; ++i) 
            //             if (math::op::abs(A_b[k][i]) > maxPivot) {

            //                 maxPivot = math::op::abs(A_b[k][i]);
            //                 pivot = i;

            //             }

            //         // Swap rows k and p
            //         if (pivot != k)
            //             for (size_t i{k}; i < columns + 1; ++i)
            //                 std::swap(A_b[i][pivot], A_b[i][k]);

            //         // Elimination of variables
            //         for (size_t i{k + 1}; i < columns; ++i) {

            //             auto factor = A_b[k][i] / A_b[k][k];

            //             for (size_t j{k}; j < columns + 1; j++)
            //                 A_b[j][i] -= factor * A_b[j][k];

            //         }

            //     }

            //     // Back substitution
            //     for (long int k = columns - 1; k >= 0; k--) {

            //         value_t sum = A_b[columns][k];
            //         for (size_t j = k + 1; j < columns; j++)
            //             sum -= result[j] * A_b[j][k];

            //         result[k] = sum / A_b[k][k];

            //     }

            //     return result; 

            // }
    

            // friend constexpr auto gauss_jordan_solve(const matrix& A, const vector_t& b) noexcept 
            //     -> vector<physics::scalar_m, rows>
            //         requires (columns == rows) {

            //     std::array<vector_t, columns + 1> A_b = A.vstack(b);
            //     std::array<physics::scalar_m, rows> result;

            //     // partial pivoting
            //     for (int i = columns - 1; i > 0; --i) 
            //         if (math::op::abs(A_b[0][i - 1]) < math::op::abs(A_b[i][0]))
            //             for (size_t j{}; j <= columns; j++) 
            //                 std::swap(A_b[j][i - 1], A_b[j][i]);

            //     // gauss elimination
            //     for (size_t j{}; j < columns; ++j) 
            //         for (size_t i{}; i < columns; ++i) 
            //             if (i != j) {

            //                 auto factor = A_b[j][i] / A_b[j][j];
                            
            //                 for (size_t k{}; k <= columns; k++) 
            //                     A_b[k][i] -= factor * A_b[k][j];

            //             }

            //     // diagonal elements
            //     for (size_t i{}; i < rows; ++i) 
            //         result[i] = A_b[columns][i] / A_b[i][i];

            //     return result;

            // }


            // /// @brief Reduce the matrix to an upper triangular matrix
            // constexpr auto upper_triangular() const noexcept 
            //     -> matrix<vector_t, rows>
            //         requires (columns == rows) {

            //     matrix<vector_t, rows> result{*this};

            //     for (size_t i{}; i < columns; ++i) 
            //         for (size_t j{i + 1}; j < columns; ++j) {

            //             auto factor = result.data[i][j] / result.data[i][i];

            //             for (size_t k{}; k < columns; ++k) 
            //                 result.data[k][j] -= factor * result.data[k][i];

            //         }

            //     return result;

            // }


            // /// @brief Reduce the matrix to a lower triangular matrix
            // constexpr auto lower_triangular() const noexcept 
            //     -> matrix<vector_t, rows>
            //         requires (columns == rows) {

            //     matrix<vector_t, rows> result{*this};

            //     for (size_t i{columns - 1}; i > 0; --i) 
            //         for (size_t j{i - 1}; j > 0; --j) {

            //             auto factor = result.data[i][j] / result.data[i][i];

            //             for (size_t k{}; k < columns; ++k) 
            //                 result.data[k][j] -= factor * result.data[k][i];

            //         }

            //     return result;

            // }


            // template <int row_start, int col_start, int row_end, int col_end>
            // friend constexpr auto submatrix(const matrix& other) {
                
            //     if constexpr (row_start > row_end || col_start > col_end) 
            //         throw std::invalid_argument("Invalid submatrix range.");
                
            //     if constexpr (row_end >= rows || col_end >= columns) 
            //         throw std::out_of_range("Submatrix range out of bounds.");
                
            //     constexpr size_t sub_rows = row_end - row_start + 1;
            //     constexpr size_t sub_cols = col_end - col_start + 1;
            //     matrix<vector<value_t, sub_rows>, sub_cols> sub;
                
            //     for (size_t i = 0; i < sub_rows; ++i) 
            //         for (size_t j = 0; j < sub_cols; ++j) 
            //             sub.data[i][j] = other.data[row_start + i][col_start + j];

            //     return sub;

            // }


            // template <int row_start, int col_start, int row_end, int col_end>
            // constexpr auto submatrix() {
                
            //     if constexpr (row_start > row_end || col_start > col_end) 
            //         throw std::invalid_argument("Invalid submatrix range.");
                
            //     if constexpr (row_end >= rows || col_end >= columns) 
            //         throw std::out_of_range("Submatrix range out of bounds.");
                
            //     constexpr size_t sub_rows = row_end - row_start + 1;
            //     constexpr size_t sub_cols = col_end - col_start + 1;
            //     matrix<vector<value_t, sub_rows>, sub_cols> sub;
                
            //     for (size_t i = 0; i < sub_rows; ++i) 
            //         for (size_t j = 0; j < sub_cols; ++j) 
            //             sub.data[i][j] = data[row_start + i][col_start + j];

            //     return sub;

            // }



            // friend constexpr auto qr_factorization(const matrix& mat) {

            //     matrix Q = matrix::identity();
            //     auto R = constexpr (rows < columns) ? A.transpose() : A;

            //     for (size_t i = 0; i < rows - 1; ++i) {
            //         // Compute the Householder reflection vector
            //         matrix<value_t, 1> v = R.submatrix(i, i, columns - 1, 0);
            //         value_t sigma = math::op::sign(v.data[0][0]) * math::op::norm(v);
            //         v.data[0][0] += sigma;
            //         value_t beta = 2.0 / (math::op::norm2(v) + sigma * sigma);

            //         // Apply the Householder reflection to the remaining columns of R
            //         R.submatrix(i, i, m - 1, rows - 1) -= beta * (v * (v.transpose() * R.submatrix(i, i, columns - 1, rows - 1)));

            //         // Update Q
            //         Q.submatrix(0, i, columns - 1, i) -= beta * (Q.submatrix(0, i, columns - 1, columns - 1) * (v * v.transpose()));
            //     }

            //     if constexpr (rows < columns)
            //         return std::make_tuple(R.transpose(), Q.transpose());

            //     return std::make_tuple(Q, R);

            // }
                        


            // constexpr uint max_entry_row(uint i) const noexcept {

            //     uint j_max = i + 1;
            //     for (uint j = i + 2; j < rows; ++j)
            //         if (math::op::abs(this->data[i][j]) > math::op::abs(this->data[i][j_max]))
            //             j_max = j;

            //     return j_max;

            // }


            // constexpr auto max_entry() const noexcept 
            //     -> std::pair<uint, uint> {

            //     uint i_max = 0;
            //     uint j_max = this->max_idx_row[i_max];
            //     auto max_entry = math::op::abs(this->data[i_max][j_max]);
            //     uint nm1 = rows - 1;
            //     for (uint i = 1; i < nm1; ++i) {

            //         uint j = this->max_idx_row[i];
            //         auto x = math::op::abs(this->data[i][j]);
            //         if (x > max_entry) {
            //             max_entry = x;
            //             i_max = i;
            //             j_max = j;
            //         }

            //     }

            //     return std::make_pair(i_max, j_max);

            // }


            // template <bool EIGEN = true, uint ITER_MAX = 1000>  
            //     requires (rows == columns)
            // friend constexpr auto diagonalize(const matrix& mat) 
            //     -> std::conditional_t<EIGEN, std::pair<matrix, matrix::vector_t>, matrix> {

            //     matrix M{mat};
            //     matrix evec = matrix::identity();
            //     std::array<value_t, matrix::rows> eval;
            //     double t, c, s; // = tan(θ), cos(θ), sin(θ)

            //     auto calc_rot = [&](uint i_, uint j_) {
                
            //         t = 0.0; // Initialize with zero (not 1.0)
            //         auto M_jj_ii = (M.data[j_][j_] - M.data[i_][i_]);
            //         auto M_ij = M.data[i_][j_];

            //         if (M_jj_ii != value_t::zero && 
            //             M_ij != value_t::zero) { // Use double precision comparison
                        
            //             double kappa = M_jj_ii / (2.0 * M_ij);

            //             // t satisfies: t^2 + 2*t*kappa - 1 = 0 (choose the root which has the smaller absolute value)
            //             t = (kappa < 0) ? (1.0 / (-kappa + std::sqrt(1 + kappa * kappa))) :
            //                   ((kappa == 0) ? 1.0 : (1.0 / (kappa + std::sqrt(1 + kappa * kappa))));
                        
            //         }

            //         c = 1.0 / std::sqrt(1.0 + t * t);
            //         s = t * c;
                    
            //     };      

            //     auto apply_rot = [&](uint i_, uint j_) {

            //         for (uint w = 0; w < i_; ++w) {
            //             auto a = M.data[w][i_];
            //             auto b = M.data[w][j_];
            //             M.data[w][i_] = c * a - s * b;
            //             M.data[w][j_] = s * a + c * b;
            //             if (w == M.max_idx_row[i_]) 
            //                 M.max_idx_row[i_] = M.max_entry_row(i_);
            //             if (w == M.max_idx_row[j_]) 
            //                 M.max_idx_row[j_] = M.max_entry_row(j_);
            //         }

            //         std::cout << "1\n";
            //         for (uint w = i_ + 1; w < j_; ++w) {
            //             auto a = M.data[i_][w];
            //             auto b = M.data[w][j_];
            //             M.data[i_][w] = c * a - s * b;
            //             M.data[w][j_] = s * a + c * b;
            //             if (w == M.max_idx_row[i_]) 
            //                 M.max_idx_row[i_] = M.max_entry_row(i_);
            //             if (w == M.max_idx_row[j_]) 
            //                 M.max_idx_row[j_] = M.max_entry_row(j_);
            //         }
            //         std::cout << "2\n";
            //         for (uint w = j_ + 1; w < rows; ++w) {
            //             auto a = M.data[i_][w];
            //             auto b = M.data[j_][w];
            //             M.data[i_][w] = c * a - s * b;
            //             M.data[j_][w] = s * a + c * b;
            //             if (w == M.max_idx_row[i_]) 
            //                 M.max_idx_row[i_] = M.max_entry_row(i_);
            //             if (w == M.max_idx_row[j_]) 
            //                 M.max_idx_row[j_] = M.max_entry_row(j_);
            //         }
            //         std::cout << "3...\n";
            //         M.data[i_][j_] = 0.0;
            //         M.max_idx_row[i_] = M.max_entry_row(i_);
            //         std::swap(M.max_idx_row[j_], M.max_idx_col[i_]);

            //     };

            //     auto apply_rot_left = [&](uint i_, uint j_) {

            //         for (uint v = 0; v < rows; ++v) {

            //             auto Eiv = evec.data[i_][v];
            //             evec.data[i_][v] = c * evec.data[i_][v] - s * evec.data[j_][v];
            //             evec.data[j_][v] = s * Eiv + c * evec.data[j_][v];

            //         }
  
            //     };

            //     for (uint i = 0; i < rows - 1; ++i)          //Initialize the "M.max_idx_row[]" array 
            //         M.max_idx_row[i] = M.max_entry_row(i);  //(which is needed by MaxEntry())

            //     uint n_iters;
            //     uint max_num_iters = ITER_MAX * rows * (rows - 1) / 2; //"sweep" = n*(n-1)/2 iters
            //     for (n_iters = 0; n_iters < max_num_iters; ++n_iters) {
                    
            //         auto [i, j] = M.max_entry(); // Find the maximum entry in the matrix. Store in i,j
            //         if ((M.data[i][i] + M.data[i][j] == M.data[i][i]) && 
            //             (M.data[j][j] + M.data[i][j] == M.data[j][j])) {

            //             M.data[i][j] = value_t::zero;
            //             M.max_idx_row[i] = M.max_entry_row(i); //update max_idx_row[i]

            //         }

            //         if (M.data[i][j] == value_t::zero)
            //             break; // If M.data[i][j] = 0, then M is diagonal. Stop iterating.

            //         // Otherwise, apply a rotation to make M.data[i][j] = 0
            //         calc_rot(i, j);  
            //         apply_rot(i, j); 
                    
            //         if constexpr (EIGEN) 
            //             apply_rot_left(i, j);
                     
            //     } 

            //     // // Optional: Sort Ms by eigenvalue.
            //     // SortRows(eval, evec, rows, sort_criteria);

            //     if ((n_iters > max_num_iters) && (rows > 1))   // If we exceeded max_num_iters,
            //         throw std::runtime_error("Diagonalize() failed to converge"); // indicate an error occured.

            //     if constexpr (EIGEN) {

            //         /// eigenvalues
            //         for (uint i = 0; i < rows; ++i)
            //             eval[i] = M.data[i][i];
                    
            //         return std::make_pair(evec, eval);

            //     }

            //     else 
            //         return M;

            // }


            // template <uint ITER_MAX = 100 * rows>
            //     requires (rows == columns)
            // friend constexpr auto jacobi(const matrix& mat) noexcept {

            //     std::cout << "numeric eps: " << std::numeric_limits<double>::epsilon() << "\n";


            //     // Check if the matrix is already symmetric
            //     bool is_symmetric = true;
            //     for (size_t i = 0; i < rows; ++i) {
            //         for (size_t j = i + 1; j < rows; ++j) {
            //             if (math::op::abs(mat.data[i][j] - mat.data[j][i]) > std::numeric_limits<double>::epsilon()) {
            //                 is_symmetric = false;
            //                 break;
            //             }
            //         }
            //         if (!is_symmetric) 
            //             break;
            //     }

            //     if (is_symmetric) {
            //         // The matrix is already symmetric, return the diagonal elements as eigenvalues
            //         std::cout << "The matrix is already symmetric\n";
            //         vector_t eigenvalues;
            //         for (size_t i = 0; i < rows; ++i) 
            //             eigenvalues.data[i] = mat.data[i][i];

            //         return std::make_pair(eigenvalues, matrix::identity());

            //     }


            //     matrix M = mat;
            //     matrix eigenvectors = matrix::identity();
            //     vector_t eigenvalues;

            //     size_t iterations = 0;

            //     while (iterations < ITER_MAX) {

            //         value_t max_elem{};
            //         size_t p = 0, q = 0;

            //         // Find the largest off-diagonal element
            //         for (size_t i = 0; i < rows; ++i) {
            //             for (size_t j = i + 1; j < rows; ++j) {
            //                 value_t elem = math::op::abs(M.data[i][j]);
            //                 if (elem > max_elem) {
            //                     max_elem = elem;
            //                     p = i;
            //                     q = j;
            //                 }
            //             }
            //         }

            //         // Check for convergence
            //         if (math::op::abs(max_elem).value < std::numeric_limits<double>::epsilon()) 
            //             break;

            //         if (math::op::abs(M.data[p][q]).value < std::numeric_limits<double>::epsilon()) {
            //             M.data[p][q] = M.data[q][p] = value_t::zero;
            //             continue;
            //         }

            //         // Compute the rotation angle
            //         double theta = 0.5 * std::atan2(2.0 * math::op::abs(M.data[p][q]).value, math::op::abs(M.data[p][p] - M.data[q][q]).value);

            //         // Compute the rotation matrix
            //         auto rotation = matrix<vector<physics::scalar_m, rows>, rows>::identity();
            //         rotation.data[p][p] = std::cos(theta);
            //         rotation.data[q][q] = std::cos(theta);

            //         if (M.data[p][p] < M.data[q][q]) {
            //             rotation.data[p][q] = std::sin(theta);
            //             rotation.data[q][p] = -std::sin(theta);
            //         } else {
            //             rotation.data[p][q] = -std::sin(theta);
            //             rotation.data[q][p] = std::sin(theta);
            //         }

            //         // Update the matrix and eigenvectors
            //         M = rotation.transpose() * M * rotation;
            //         eigenvectors = eigenvectors * rotation;

            //         ++iterations;

            //     }

            //     // Store the eigenvalues
            //     for (size_t i = 0; i < rows; ++i) {

            //         if (math::op::abs(M.data[i][i]).value < std::numeric_limits<double>::epsilon())
            //             M.data[i][i] = value_t::zero;
            //         eigenvalues.data[i] = M.data[i][i];

            //     }


            //     return std::make_pair(eigenvalues, eigenvectors);                            

            // }

            
            // constexpr matrix diagonalized() const noexcept {

            //     return diagonalize<false>(*this);

            // }

            // /// @brief Get the eigenvalues of the matrix
            // constexpr auto eigenvalues() const noexcept 
            //     -> vector<value_t, rows> {

            //     auto [evec, eval] = diagonalize(*this);
            //     return eval;            
                        
            // }


            // /// @brief Get the eigenvectors of the matrix
            // constexpr auto eigenvectors() const noexcept {

            //     auto [evec, eval] = diagonalize(*this);
            //     return evec;            
                        
            // }


        //     constexpr matrix eigenvectors(const vector_t& eigenvalues) const noexcept {
                
        //         matrix<vector<physics::scalar_m, rows>, rows> result;
        //         for (size_t i{}; i < rows; ++i) 
        //             result.data[i] = solve((*this) - matrix<vector<physics::scalar_m, rows>, rows>::identity() * eigenvalues[i], vector_t::zero);

        //         return result * value_t::one;

        //     }


        //     template <uint ITER_MAX = 1000>  
        //         requires (rows == columns)
        //     constexpr auto eigen() const {

        //         using scalar_t = physics::scalar_m;
        //         using scalar_vector_t = vector<scalar_t, rows>;
        //         using scalar_matrix_t = matrix<scalar_vector_t, rows>;

        //         vector_t eig_values, wp;
        //         matrix eig_vectors, eig_val; 
        //         scalar_matrix_t Q;
        //         scalar_vector_t dumsum;
        //         double f;

        //         // Copy the values of the current matrix to eig_val
        //         eig_val = *this;

        //         // Initialize Q and eig_val for computation of eigenvectors
        //         Q = scalar_matrix_t::identity();
        //         for (uint i = 0; i < rows; ++i)
        //             eig_val[i][i] = value_t::one;

        //         // Eigen decomposition iterations
        //         for (uint it = 0; it < ITER_MAX; ++it) {

        //             // Gram-Schmidt decorrelation
        //             for (uint p = 0; p < rows; ++p) {

        //                 for (uint i = 0; i < rows; ++i)
        //                     wp[i] = eig_val[i][p];

        //                 auto eval_wp = math::op::normalize(wp);

        //                 for (uint i = 0; i < rows; ++i)
        //                     dumsum[i] = 0.0;

        //                 for (uint i = 0; i < rows; ++i) {
        //                     for (uint j = 0; j < p; ++j) {
        //                         f = 0.0;
        //                         for (uint k = 0; k < rows; ++k)
        //                             f += eval_wp[k] * Q[k][j];

        //                         dumsum[i] += f * Q[i][j];
        //                     }
        //                 }

        //                 for (uint i = 0; i < rows; ++i)
        //                     eval_wp[i] -= dumsum[i];

        //                 eval_wp = math::op::normalize(eval_wp);

        //                 // Store estimated rows of the inverse of the mixing matrix as columns in Q
        //                 for (uint i = 0; i < rows; ++i)
        //                     Q[i][p] = eval_wp[i];

        //             }

        //             auto R = Q.transpose() * eig_val;
        //             eig_val = R * Q;
        //             eig_vectors = eig_vectors * Q;

        //         }

        //         // Set results
        //         for (uint i = 0; i < rows; ++i)
        //             eig_values[i] = eig_val[i][i];

        //         return std::make_pair(eig_values, eig_vectors);

        // }


            // friend auto gram_schmidt(const matrix& basis) {

            //     matrix appo;
            //     matrix<vector<physics::scalar_m, rows>, columns> result;

            //     // do the first vector before the loop
            //     appo.data[0] = basis.data[0];

            //     for (size_t i{1}; i < columns; ++i) {

            //         vector_t projection;
            //         for (size_t j{}; j < i; ++j) 
            //             projection -= math::op::proj(appo.data[j], basis.data[i]);
                    
            //         appo.data[i] = basis.data[i] + projection;
            //     }

            //     for (size_t i{}; i < columns; ++i) 
            //         result.data[i] = appo.data[i] / math::op::norm(appo.data[i]);

            //     return result;
                
            // }


            // friend auto gram_schmidt_qr(const matrix& A) noexcept {

            //     auto Q = gram_schmidt(A);        
            //     return std::make_pair(Q, Q.transpose() * A);
                
            // }


            // template <size_t ITERATIONS>
            // friend auto eigen_qr(const matrix& A) noexcept {

            //     auto A_k = A; 
            //     auto eigvec = matrix<vector<value_t, rows>, rows>::identity(); 

            //     for (size_t i{}; i < ITERATIONS; ++i) {

            //         value_t s = A_k.data[rows - 1][rows - 1];
            //         auto smult = matrix<vector<physics::scalar_m, rows>, rows>::identity() * s;
                    
            //         auto [Q, R] = gram_schmidt_qr(A_k - smult);
            //         A_k = R * Q + smult;
            //         eigvec = eigvec * Q;

            //     }

            //     return std::make_pair(A_k.diagonal(), eigvec);

            // }


            // template <size_t ITERATIONS = 500>
            // friend auto householder_qr(const matrix& A) noexcept {

            //     auto Q = matrix<vector<physics::scalar_m, rows>, rows>::identity() ;
            //     auto R = A; 

            //     for (size_t i{}; i < ITERATIONS; ++i) {

            //         % -- Find H = I-tau*w*w’ to put zeros below R(j,j)
            //         auto normx = math::op::norm(R(j:end,j));
            //         s = -sign(R(j,j));
            //         u1 = R(j,j) - s*normx;
            //         w = R(j:end,j)/u1;
            //         w(1) = 1;
            //         tau = -s*u1/normx;
            //         % -- R := HR, Q := QH
            //         R(j:end,:) = R(j:end,:)-(tau*w)*(w’*R(j:end,:));
            //         Q(:,j:end) = Q(:,j:end)-(Q(:,j:end)*w)*(tau*w)’;



            // // Reduce A to a Hessenberg matrix H so that A and H are similar:
            // auto hessenberg_reduction(const matrix& A) {

            //     auto A_copy = A;
            //     auto H = A;
                
            //     if constexpr (columns > 2) {

            //         geometry::vector<value_t, columns - 1> a1;
            //         for (size_t i{1}; i < columns; ++i)
            //             a1.data[i] = A_copy.data[i][0]; 

            //         geometry::vector<physics::scalar_m, columns - 1> e1;
            //         e1.data[0] = 1.0;
            //         int sgn = math::op::sign(v1.data[1]);

            //         auto norm_a1 = math::op::norm(a1);
            //         geometry::vector<physics::scalar_m, columns - 1> v = (a1 + sgn * norm_a1 * e1) / norm_a1;


            //         auto Q1 = matrix<vector<physics::scalar_m, columns - 1>, columns - 1>::identity() - 2 * (v * v.transpose()); 

            //         auto Q1A = Q1 * A_copy;
            //         }
            //         for (int i = 1; i < n; i++) {
            //             Q1A[i][0] = 0;
            //         }
            //         for (int i = 0; i < n-1; i++) {
            //             for (int j = 0; j < n; j++) {
            //                 H[i+1][j] = 0;
            //             }
            //         }
            //         for (int i = 1; i < n; i++) {
            //             for (int j = 0; j < n-1; j++) {
            //                 H[i][j+1] = Q1A[i][j];
            //             }
            //         }
            //         Matrix


                    

            //         a1 = A[2:n, 1];
            //         e1 = zeros(n-1); 
            //         e1[1] = 1;
            //         sgn = sign(a1[1]);
            //         v = (a1 + sgn*norm(a1)*e1); 
            //         v = v./norm(v)
            //         Q1 = eye(n-1) - 2*(v*v)
            //         A[2:n,1] = Q1*A[2:n,1]
            //         A[1,2:n] = Q1*A[1,2:n]
            //         A[2:n,2:n] = Q1*A[2:n,2:n]*Q1
            //         auto H = hessenberg_reduction(A[2:n,2:n])

            //     } 

            //     return A

            // }

            /// @brief Print the matrix
            constexpr void print() const noexcept {

                std::apply([](const auto&... args) { ((std::cout << args << '\n'), ...); }, this->data);
                std::cout << '\n'; 

            }


    }; 
    

    // template <typename VEC_TYPE, typename... VECTORS> 
    //     requires (are_same_vectors_v<VEC_TYPE, VECTORS...>)
    // matrix(const VECTORS&... vectors) 
    //     -> matrix<VEC_TYPE, sizeof...(VECTORS)>;


    // template <typename VEC_TYPE, typename..
    // template <typename VEC_TYPE, typename... VECTORS>  
    //     requires (are_same_vectors_v<VEC_TYPE, VECTORS...>) 
    // inline constexpr auto make_matrix(VECTORS&... other) noexcept 
    //     -> matrix<VEC_TYPE, sizeof...(other)> {
        
    //     return {std::forward<VECTORS>(other)...};

    // }
    


    template <typename T, typename... Ts> 
        requires ((are_column_vectors_v<Ts...> || are_row_vectors_v<Ts...>) && have_same_dimension_v<Ts...>)
    inline constexpr auto make_matrix(Ts&... others) {
        
        return matrix<T, sizeof...(others)>(std::forward<T>(others)...);

    }
        

    // template <typename VEC_TYPE, size_t DIM, typename... VECTORS>  
    //     requires (are_same_vectors_v<VEC_TYPE, VECTORS...>) 
    // inline constexpr auto make_matrix(const VECTORS&... other) noexcept 
    //     -> matrix<VEC_TYPE, DIM> 
    //         requires (sizeof...(other) == DIM) {
        
    //     return {std::forward<VECTORS>(other)...};

    // }
    
    // template <typename VEC_TYPE, size_t DIM, typename... VECTORS>  
    //     requires (are_same_vectors_v<VEC_TYPE, VECTORS...>) 
    // inline constexpr auto make_matrix(VECTORS&&... other) noexcept 
    //     -> matrix<VEC_TYPE, DIM> 
    //         requires (sizeof...(other) == DIM) {
        
    //     return {std::forward<VECTORS>(other)...};

    // }


    template <typename VEC_TYPE, size_t DIM>  
        requires (is_vector_v<VEC_TYPE>)
    inline constexpr auto make_random_matrix() noexcept 
        -> matrix<VEC_TYPE, DIM> {

        matrix<VEC_TYPE, DIM> result;

        for (size_t i{}; i < DIM; i++) 
            for (size_t j{}; j < DIM; j++) 
                result.data[j][i] = std::rand(); 

        return result;

    }


} // namespace scipp::geometry