/**
 * @file matrix.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2022-12-12
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp {


    namespace geometry {


        namespace linear_algebra {


            /**
             * @brief Class expressing a generic matrix of vectors of measurements in a n-dimesional system
             * @see vector
             * 
             * @tparam cols: std::size_t number of columns
             * @tparam rows: std::size_t number of rows
             * 
             * @note the matrix is stored in row-major order
             * @note cols is set equal to rows by default 
             */
            template <std::size_t rows, std::size_t cols = rows> 
            class matrix {


                public:

                // =============================================
                // constructors & destructor
                // =============================================

                    /// @brief Construct a new matrix object with all elements equal to zero
                    explicit constexpr matrix(const units::unit_base& base = unit_base()) noexcept {

                        data_.fill(vector<rows>(base));     

                    }


                    /**
                     * @brief Construct a new base from a pack of vectors
                     * 
                     * @param vec: list of all the vectors
                     * 
                     * @note The number of components must be the same as the dimesion of the space
                     */
                    template <typename... vectors>
                    explicit constexpr matrix(const vectors&... vec) noexcept {
                        
                        if (sizeof...(vec) != cols) 

                            throw std::invalid_argument("The number of vectors passed must be equal to the number of columns");

                        else 

                            this->data_ = {vec...}; 
                    
                    }

                    
                    /**
                     * @brief Construct a new matrix object from an std::array of vector
                     * 
                     * @param data: std::array of vector as l-value const reference
                     */
                    constexpr matrix(const std::array<vector<rows>, cols>& data) noexcept : 
                        
                        data_{data} {}


                    /**
                     * @brief Construct a new matrix object from an std::array of vector
                     * 
                     * @param data: std::array of vector as r-value reference
                     */
                    constexpr matrix(std::array<vector<rows>, cols>&& data) noexcept : 
                        
                        data_{std::move(data)} {}


                    /**
                     * @brief Copy construct a new matrix object
                     * 
                     * @param other: matrix as l-value const reference
                     */
                    constexpr matrix(const matrix& other) noexcept :

                        data_{other.data_} {}


                    /**
                     * @brief Move construct a new matrix object
                     * 
                     * @param other: matrix as r-value reference
                     */
                    constexpr matrix(matrix&& other) noexcept :

                        data_{std::move(other.data_)} {}
                        

                // =============================================
                // operators
                // =============================================

                    /**
                     * @brief Get a vector of measurements from the current matrix
                     * 
                     * @param i: index of the vector to get as l-value const reference
                     * 
                     * @return constexpr vector<rows> 
                     */
                    constexpr vector<rows> operator[](const std::size_t& i) const noexcept { 
                        
                        return data_[i]; 
                        
                    }


                    /**
                     * @brief Get a vector of measurements from the current matrix
                     * 
                     * @param i: index of the vector to get as l-value const reference
                     * 
                     * @return constexpr vector<rows>& 
                     */
                    constexpr vector<rows>& operator[](const std::size_t& i) noexcept { 
                        
                        return data_[i]; 
                        
                    }


                    /**
                     * @brief Get a measurement from the current matrix
                     * 
                     * @param i: row index of the measurement to get as l-value const reference
                     * @param j: column index of the measurement to get as l-value const reference
                     * 
                     * @return constexpr measurement 
                     */
                    constexpr measurement operator()(const std::size_t& row, const std::size_t& col) const noexcept { 
                        
                        return data_[col][row]; 
                        
                    }


                    /**
                     * @brief Get a measurement from the current matrix
                     * 
                     * @param i: row index of the measurement to get as l-value const reference
                     * @param j: column index of the measurement to get as l-value const reference
                     * 
                     * @return constexpr measurement& 
                     */
                    constexpr measurement& operator()(const std::size_t& row, const std::size_t& col) noexcept { 
                        
                        return data_[col][row]; 
                        
                    }


                    /**
                     * @brief Equality operator
                     * 
                     * @param other: matrix as l-value const reference
                     * 
                     * @return constexpr bool 
                     */
                    constexpr bool operator==(const matrix& other) const noexcept {

                        for (std::size_t i{}; i < cols; ++i) 
                            if (data_[i] != other[i])
                                return false;

                        return true;

                    }

                    
                    /**
                     * @brief Equality operator
                     * 
                     * @param other: matrix as r-value reference
                     * 
                     * @return constexpr bool& 
                     */
                    constexpr bool operator==(matrix&& other) const noexcept {
                        
                        for (std::size_t i{}; i < cols; ++i) 
                            if (data_[i] != other[i])
                                return false;

                        return true; 

                    }


                    /**
                     * @brief Inequality operator
                     * 
                     * @param other: matrix as l-value const reference
                     * 
                     * @return constexpr bool 
                     */
                    constexpr bool operator!=(const matrix& other) const noexcept {

                        for (std::size_t i{}; i < cols; ++i) 
                            if (data_[i] == other[i])
                                return false;

                        return true;

                    }

                    
                    /**
                     * @brief Inequality operator
                     * 
                     * @param other: matrix as r-value reference
                     * 
                     * @return constexpr bool& 
                     */
                    constexpr bool operator!=(matrix&& other) const noexcept {
                        
                        for (std::size_t i{}; i < cols; ++i) 
                            if (data_[i] == other[i])
                                return false;

                        return true; 

                    }


                    /**
                     * @brief Copy assignment operator
                     * 
                     * @param other: matrix as l-value const reference
                     * 
                     * @return constexpr matrix 
                     */
                    constexpr matrix& operator=(const matrix& other) noexcept {

                        for (std::size_t i{}; i < rows; ++i) 
                            data_[i] = other.data_[i];

                        return *this;

                    }

                    
                    /**
                     * @brief Move assignment operator
                     * 
                     * @param other: matrix as r-value reference
                     * 
                     * @return constexpr matrix& 
                     */
                    constexpr matrix& operator=(matrix&& other) noexcept {
                        
                        data_ = std::move(other.data_); 

                        return *this; 

                    }


                    /**
                     * @brief Sum a matrix to the current one
                     * 
                     * @param other: matrix as l-value const reference
                     * 
                     * @return constexpr matrix& 
                     */
                    constexpr matrix& operator+=(const matrix& other) {

                        for(std::size_t i{}; i < cols; ++i) 
                            data_[i] += other.data_[i];

                        return *this; 

                    }


                    /**
                     * @brief Add a matrix to the current matrix
                     * @note: the reciprocal vectors of the two matrices must have the same unit of measurement
                     * 
                     * @param other: matrix to add as r-value reference
                     * 
                     * @return constexpr matrix& 
                     */
                    constexpr matrix& operator+=(matrix&& other) {

                        for (std::size_t i{}; i < cols; ++i) 
                            data_[i] += std::move(other.data_[i]);

                        return *this; 

                    }


                    /**
                     * @brief Subtract a matrix to the current matrix
                     * 
                     * @param other: matrix as l-value const reference
                     * 
                     * @return constexpr matrix& 
                     */
                    constexpr matrix operator-=(const matrix& other) {

                        for(std::size_t i{}; i < cols; ++i) 
                            data_[i] -= other.data_[i];

                        return *this; 

                    }


                    /**
                     * @brief Subtract a matrix to the current matrix
                     * @note: the reciprocal vectors of the two matrices must have the same unit of measurement
                     * 
                     * @param other: matrix to subtract as r-value reference
                     * 
                     * @return constexpr matrix& 
                     */
                    constexpr matrix& operator-=(matrix&& other) {

                        for (std::size_t i{}; i < cols; ++i) 
                            data_[i] -= std::move(other.data_[i]);

                        return *this; 

                    }


                    /**
                     * @brief Multiply the current matrix by a measurement
                     * 
                     * @param meas: measurement to multiply with as l-value const reference
                     * 
                     * @return constexpr matrix& 
                     */
                    constexpr matrix& operator*=(const measurement& meas) noexcept {

                        for (std::size_t i{}; i < cols; ++i)  
                            data_[i] *= meas;

                        return *this; 

                    }


                    /**
                     * @brief Multiply the current matrix by a measurement
                     * 
                     * @param meas: measurement to multiply with as r-value reference
                     * 
                     * @return constexpr matrix&
                     */
                    constexpr matrix& operator*=(measurement&& meas) noexcept {

                        for (std::size_t i{}; i < cols; ++i) 
                            data_[i] *= std::move(meas);

                        return *this; 

                    }


                    /**
                     * @brief Divide the current matrix by a measurement
                     * 
                     * @param meas: measurement to divide by as l-value const reference
                     *  
                     * @return constexpr matrix& 
                     */
                    constexpr matrix& operator/=(const measurement& meas) {
                        
                        if (meas.value() == 0.0) 
                            throw std::runtime_error("Cannot divide a matrix by a zero measurement");

                        for (std::size_t i{}; i < cols; ++i) 
                            data_[i] /= meas;
                        
                        return *this; 

                    }


                    /**
                     * @brief Divide the current matrix by a measurement
                     * 
                     * @param meas: measurement to divide by as r-value reference
                     * 
                     * @return constexpr matrix&
                     */
                    constexpr matrix& operator/=(measurement&& meas) {

                        if (meas.value() == 0.0) 
                            throw std::runtime_error("Cannot divide a matrix by a zero measurement");
                        
                        for (std::size_t i{}; i < cols; ++i)
                            data_[i] /= meas;

                        return *this; 

                    }


                    /**
                     * @brief Multiply the current matrix by a scalar
                     * 
                     * @param scalar: scalar as l-value const reference
                     * 
                     * @return constexpr matrix& 
                     */
                    constexpr matrix& operator*=(const scalar& scalar) noexcept {

                        for (std::size_t i{}; i < cols; ++i) 
                            data_[i] *= scalar;

                        return *this; 

                    }


                    /**
                     * @brief Divide the current matrix by a scalar
                     * 
                     * @param scalar: scalar as l-value const reference
                     *  
                     * @return constexpr matrix& 
                     */
                    constexpr matrix& operator/=(const scalar& scalar) {

                        if (scalar == 0.0) 
                            throw std::runtime_error("Cannot divide a matrix by zero");

                        for (std::size_t i{}; i < cols; ++i)
                            data_[i] /= scalar;
                        
                        return *this; 
                        
                    }


                    /**
                     * @brief Sum two matrices
                     * 
                     * @param other: matrix as l-value const reference
                     * 
                     * @return constexpr matrix 
                     */
                    constexpr matrix operator+(const matrix& other) const noexcept {

                        matrix result;
                        for(std::size_t i{}; i < cols; ++i) 
                            result.data_[i] = data_[i] + other.data_[i];

                        return result;

                    }


                    /**
                     * @brief Subtract a matrix to the current one
                     * 
                     * @param other: matrix as l-value const reference
                     * 
                     * @return constexpr matrix& 
                     */
                    constexpr matrix operator-(const matrix& other) const noexcept {

                        matrix result;
                        for(std::size_t i{}; i < cols; ++i) 
                            result[i] = data_[i] - other.data_[i];

                        return result;

                    }


                    /**
                     * @brief Get the opposite of the matrix
                     * 
                     * @return constexpr matrix 
                     */
                    constexpr matrix operator-() const noexcept {

                        matrix result;
                        for(std::size_t i{}; i < cols; ++i) 
                            result[i] = -data_[i];

                        return result;

                    }


                    /**
                     * @brief Multiply the current matrix by a matrix
                     * 
                     * @param mat1: matrix<cols, new_rows> to multiply with as l-value const reference
                     * 
                     * @return constexpr matrix<>
                     */
                    template <std::size_t new_rows>
                    constexpr matrix<new_rows, rows> operator*(const matrix<cols, new_rows>& mat) const noexcept {

                        matrix<new_rows, rows> result; 
                        for(std::size_t i{}; i < new_rows; ++i)
                            for(std::size_t j{}; j < rows; ++j)
                                for(std::size_t k{}; k < cols; ++k)
                                    result(i, j) += this->element(j, k) * mat(k, i);

                        return result; 

                    }


                    /**
                     * @brief Multiply the current matrix by a matrix
                     * 
                     * @param mat1: matrix<cols, new_rows> to multiply with as r-value reference
                     * 
                     * @return constexpr matrix<> 
                     */
                    template <std::size_t new_rows>
                    constexpr matrix<new_rows, rows> operator*(matrix<cols, new_rows>&& mat) const noexcept {

                        matrix<new_rows, rows> result; 
                        for(std::size_t i{}; i < new_rows; ++i)
                            for(std::size_t j{}; j < rows; ++j)
                                for(std::size_t k{}; k < cols; ++k)
                                    result(i, j) += this->element(j, k) * mat(k, i);

                        return result; 

                    }


                    /**
                     * @brief Multiply the current matrix by a vector of measurements
                     * 
                     * @param mat: matrix<cols, new_rows> to multiply with as l-value const reference
                     * @param vec: vector of measurements to multiply with as l-value const reference
                     * 
                     * @return constexpr matrix 
                     */
                    constexpr matrix<1, rows> operator*(const vector<cols>& vec) const noexcept {

                        return *this * matrix<cols, 1>(vec); 

                    }


                    /**
                     * @brief Multiply the current matrix by a vector of measurements
                     * 
                     * @param vec: vector of measurements to multiply with as r-value reference
                     * 
                     * @return constexpr matrix 
                     */
                    constexpr matrix<1, rows> operator*(vector<cols>&& vec) const noexcept {

                        return *this * matrix<cols, 1>(vec);

                    }


                    /**
                     * @brief Multiply the current matrix by a measurement
                     * 
                     * @param meas: measurement to multiply with as l-value const reference
                     * 
                     * @return constexpr matrix 
                     */
                    constexpr matrix operator*(const measurement& meas) const noexcept {
                        
                        matrix result;
                        for (std::size_t j{}; j < cols; ++j) 
                            result.data_[j] = data_[j] * meas;

                        return result;

                    }


                    /**
                     * @brief Multiply the current matrix by a measurement
                     * 
                     * @param meas: measurement to multiply with as r-value reference
                     * 
                     * @return constexpr matrix 
                     */
                    constexpr matrix operator*(measurement&& meas) const noexcept {
                        
                        matrix result;
                        for (std::size_t j{}; j < cols; ++j) 
                            result.data_[j] = data_[j] * meas;

                        return result;

                    }


                    /**
                     * @brief Divide the current matrix by a measurement
                     * 
                     * @param meas: measurement to divide by as l-value const reference
                     * 
                     * @return constexpr matrix 
                     */
                    constexpr matrix operator/(const measurement& meas) const {
                        
                        if (meas.value() == 0.0)
                            throw std::runtime_error("Can't divide a matrix by a zero measurement"); 

                        matrix result;
                        for (std::size_t i{}; i < rows; ++i) 
                            for (std::size_t j{}; j < cols; ++j) 
                                result.data_[i][j] = data_[i][j] / meas;
                        
                        return result;

                    }


                    /**
                     * @brief Divide the current matrix by a measurement
                     * 
                     * @param meas: measurement to divide by as r-value reference
                     * 
                     * @return constexpr matrix 
                     */
                    constexpr matrix operator/(measurement&& meas) const {
                        
                        if (meas.value() == 0.0)
                            throw std::runtime_error("Can't divide a matrix by a zero measurement"); 

                        matrix result;
                        for (std::size_t i{}; i < rows; ++i) 
                            for (std::size_t j{}; j < cols; ++j) 
                                result.data_[i][j] = data_[i][j] / meas;
                        
                        return result;

                    }


                    /**
                     * @brief Multiply the current matrix by a scalar
                     * 
                     * @param val: scalar to multiply with as l-value const reference
                     * 
                     * @return constexpr matrix 
                     */
                    constexpr matrix operator*(const scalar& val) const noexcept {
                        
                        matrix result;
                        for (std::size_t i{}; i < cols; ++i) 
                            result.data_[i] = data_[i] * val;

                        return result;

                    }


                    /**
                     * @brief Divide a scalar by a matrix
                     * 
                     * @param val: scalar to divide by as l-value const reference
                     * 
                     * @return constexpr matrix 
                     */
                    constexpr matrix operator/(const scalar& val) const {

                        if (val == 0.0)
                            throw std::runtime_error("Can't divide a matrix by zero"); 
                            
                        matrix result;
                        for (std::size_t i{}; i < cols; ++i) 
                            result.data_[i] = data_[i] / val;

                        return result;

                    }


                    /**
                     * @brief Multiply a measurement by a matrix
                     * 
                     * @param meas: measurement to multiply with as l-value const reference
                     * @param mat: matrix to multiply by as l-value const reference
                     * @return constexpr matrix 
                     */
                    friend constexpr matrix operator*(const measurement& meas, const matrix& mat) noexcept {
                        
                        matrix result;
                        for (std::size_t j{}; j < mat.cols; ++j) 
                            result[j] = meas * mat[j];

                        return result;

                    }


                    /**
                     * @brief Divide a measurement by a matrix
                     * 
                     * @param meas: measurement to divide by as l-value const reference
                     * @param mat: matrix to divide by as l-value const reference
                     * 
                     * @return constexpr matrix 
                     */
                    friend constexpr matrix operator/(const measurement& meas, const matrix& mat) noexcept {

                        matrix result;
                        for (std::size_t j{}; j < mat.cols; ++j) 
                            result[j] = meas / mat[j];

                        return result;

                    }


                // =============================================
                // check methods
                // =============================================

                    /// @brief Check if this matrix is a zero matrix
                    constexpr bool is_zero() const noexcept {

                        for (std::size_t i{}; i < cols; ++i)
                            if (!this->column(i).is_zero())
                                return false; 

                        return true; 

                    }


                    /// @brief Check if this matrix is an identity matrix
                    constexpr bool is_identity() const noexcept {

                        return false; 

                    }


                    /// @brief  Check if this matrix is squared
                    constexpr bool is_squared() const noexcept {
                        
                        return (rows == cols); 

                    }

                    
                    /// @brief Check if this matrix is triangolar superior
                    constexpr bool is_triang_sup() const noexcept {

                        return false; 

                    } 


                    /// @brief Check if this matrix is triangolar inferior
                    constexpr bool is_triang_inf() const noexcept {

                        return false; 

                    }


                // =============================================
                // get methods
                // =============================================

                    /**
                     * @brief Get the number of rows of the matrix
                     * 
                     * @return constexpr std::size_t 
                     */
                    constexpr std::size_t rows_size() const noexcept { 
                        
                        return rows; 
                        
                    }


                    /**
                     * @brief Get the number of columns of the matrix
                     * 
                     * @return constexpr std::size_t 
                     */
                    constexpr std::size_t cols_size() const noexcept { 
                        
                        return cols; 
                        
                    }


                    /**
                     * @brief Get an element of the matrix
                     * 
                     * @param row: std::size_t number of row
                     * @param col: std::size_t number of column
                     * 
                     * @return constexpr measurement 
                     */
                    constexpr measurement element(const std::size_t& row, const std::size_t& col) const {

                        if (col > cols || row > rows)
                            throw std::out_of_range("Cannot access a matrix element with an index out of range");

                        return data_[col][row];  

                    }


                    /**
                     * @brief Get an element of the matrix
                     * 
                     * @param row: std::size_t number of row
                     * @param col: std::size_t number of column
                     * 
                     * @return constexpr measurement&
                     */
                    constexpr measurement& element(const std::size_t& row, const std::size_t& col) {

                        if (col > cols || row > rows)
                            throw std::out_of_range("Cannot access a matrix element with an index out of range");

                        return data_[col][row];  

                    }


                    /**
                     * @brief Get a column vector of the matrix
                     * 
                     * @param n_col: index of the column vector to get as l-value const reference
                     * 
                     * @return constexpr vector<rows> 
                     */
                    constexpr vector<rows> column(const std::size_t& n_col) const noexcept {
                        
                        return data_[n_col]; 
                        
                    }


                    /**
                     * @brief Get a column vector of the matrix
                     * 
                     * @param n_col: index of the column vector to get as l-value const reference
                     * 
                     * @return constexpr vector<rows>&
                     */
                    constexpr vector<rows>& column(const std::size_t& n_col) noexcept {
                        
                        return data_[n_col]; 
                        
                    }


                    /**
                     * @brief Get a row vector of the matrix
                     * 
                     * @param n_row: index of the row vector to get as l-value const reference
                     * 
                     * @return constexpr vector<cols> 
                     */
                    constexpr vector<cols> row(const std::size_t& m_row) const noexcept {

                        vector<cols> appo; 
                        for (std::size_t i{}; i < cols; ++i)    
                            appo[i] = data_[i][m_row];

                        return appo; 

                    }


                    /**
                     * @brief Get a row vector of the matrix
                     * 
                     * @param n_row: index of the row vector to get as l-value const reference
                     * 
                     * @return constexpr vector<cols>& 
                     */
                    constexpr vector<cols>& row(const std::size_t& m_row) noexcept {

                        vector<cols> appo; 
                        for (std::size_t i{}; i < cols; ++i)    
                            appo[i] = data_[i][m_row];

                        return appo; 

                    }


                    /**
                     * @brief Get the traspose of the matrix
                     * 
                     * @return constexpr matrix<cols, rows> 
                     */
                    constexpr matrix<cols, rows> traspose() const noexcept {

                        matrix<cols, rows> result;
                        for (std::size_t i{}; i < cols; ++i)
                            for (std::size_t j{}; j < rows; ++j) 
                                result(i, j) = this->element(j, i);

                        return result;

                    }


                    /**
                     * @brief Get the augmented matrix of the matrix
                     * 
                     * @param vec: vector to augment the matrix
                     * 
                     * @return constexpr matrix<rows, cols + 1> 
                     */
                    constexpr matrix<rows, cols + 1> augmented(const vector<rows>& vec) const noexcept {

                        matrix<rows, cols + 1> result;
                        for (std::size_t i{}; i < rows; ++i) {

                            for (std::size_t j{}; j < cols; ++j) 
                                result(i, j) = this->element(i, j);

                            result(i, cols) = vec[i];
                            
                        }

                        return result;
                    
                    }


                    /**
                     * @brief Get the determinant of the matrix
                     * @note The matrix must be square
                     * @note This is not safe! All the measurement must have the same unit
                     * 
                     * @return constexpr scalar 
                     */
                    constexpr measurement determinant() const {

                        if constexpr (rows != cols) 
                            throw std::runtime_error("Can't get the determinant of a non-square matrix");

                        else {
                            
                            switch (cols) {

                                case 1: 
                                    return data_[0][0];

                                case 2:
                                    return data_[0][0] * data_[1][1] - 
                                        data_[0][1] * data_[1][0];

                                case 3:
                                    return data_[0][0] * data_[1][1] * data_[2][2] + 
                                        data_[0][1] * data_[1][2] * data_[2][0] + 
                                        data_[0][2] * data_[1][0] * data_[2][1] - 
                                        data_[0][2] * data_[1][1] * data_[2][0] - 
                                        data_[0][1] * data_[1][0] * data_[2][2] - 
                                        data_[0][0] * data_[1][2] * data_[2][1];

                                default: 

                                    measurement det;
                                    for (std::size_t i{}; i < cols; ++i) 
                                        for (std::size_t j{}; j < rows; ++j)
                                            det += data_[i][0] * cofactor(i, 0);

                                    return det;

                            }

                        }
                    
                    }


                    /**
                     * @brief Get the cofactor of the matrix
                     * 
                     * @param n_col: index of the column vector to get as l-value const reference
                     * @param n_row: index of the row vector to get as l-value const reference
                     * 
                     * @return constexpr scalar 
                     */
                    constexpr measurement cofactor(const std::size_t& n_col, const std::size_t& n_row) const {

                        std::cout << "Cofactor called\n"; 

                        if constexpr (rows == 1 && cols == 1) 
                            return data_[0][0];

                        else if constexpr (rows == 2 && cols == 2) 
                            return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];

                        else {

                            matrix<cols - 1,rows - 1> result;
                            for (std::size_t i{}; i < cols - 1; ++i) 
                                for (std::size_t j{}; j < rows - 1; ++j) 
                                    if (i != n_col && j != n_row) 
                                        result[i][j] = data_[i][j];

                            return result.determinant() * (((n_col + n_row) % 2 == 0) ? 1. : -1.);

                        }

                    }


                    /**
                     * @brief Get the adjoint of the matrix
                     * 
                     * @return constexpr matrix<cols, rows> 
                     */
                    constexpr matrix<cols, rows> adjoint() const noexcept {

                        matrix<cols, rows> result;
                        for (std::size_t i{}; i < cols; ++i) 
                            for (std::size_t j{}; j < rows; ++j) 
                                result[i][j] = this->cofactor(i, j);

                        return result;

                    }


                    /**
                     * @brief Get the inverse of the matrix
                     * 
                     * @return constexpr matrix<cols, rows> 
                     */
                    constexpr matrix<cols, rows> inverse() const {

                        if constexpr (rows == cols)
                            return this->adjoint() / this->determinant();

                        else 
                            std::cerr << "other methods will follow\n"; 

                        return matrix<cols, rows>();

                    }


                    /**
                     * @brief Get the trace of the matrix
                     * @note This is not safe! If the units are not the same, the result is undefined
                     * 
                     * @return constexpr measurement 
                     */
                    constexpr measurement trace() const noexcept {

                        measurement result{};
                        for (std::size_t i{}; i < cols; ++i) 
                            result += data_[i][i];

                        return result;

                    }


                    /**
                     * @brief Get the elements of the matrix
                     * 
                     * @return constexpr std::array<vector<rows>, cols> 
                     */
                    constexpr std::array<vector<rows>, cols> data() const noexcept { 
                        
                        return data_; 
                        
                    }


                    /**
                     * @brief Get the elements of the matrix
                     * 
                     * @return constexpr std::array<vector<rows>, cols>& 
                     */
                    constexpr std::array<vector<rows>, cols>& data() noexcept { 
                        
                        return data_; 
                        
                    }


                    /**
                     * @brief Get the matrix object 
                     * 
                     * @return constexpr matrix<rows, cols> 
                     */
                    constexpr matrix<rows, cols> as_matrix() const noexcept {

                        return *this;

                    }


                    /**
                     * @brief Get the matrix object 
                     * 
                     * @return constexpr matrix<rows, cols>&
                     */
                    constexpr matrix<rows, cols>& as_matrix() noexcept {

                        return *this;

                    }


                    /// @brief Print the matrix to the standard output
                    void print() const noexcept {

                        std::cout << "{"; 
                        for (std::size_t j{}; j < cols; ++j) 
                            std::cout << "\n\t" << this->data_[j];
                        std::cout << "\n}\n";

                    }


                private: 

                // =============================================
                // class members
                // =============================================

                    std::array<vector<rows>, cols> data_; ///< The elements of the matrix

                    static_assert(rows != 0 && cols != 0, "The size of the matrix cannot be 0."); 


            }; // class matrix


            /**
             * @brief Traspose a vector into a matrix<1, DIM>
             * 
             * @tparam DIM: dimesions of the vector
             * @param vec: vector<DIM> as l-value const reference
             * 
             * @return constexpr matrix<1, DIM> 
             */
            template <std::size_t DIM>
            constexpr matrix<1, DIM> traspose(const vector<DIM>& vec) noexcept {
                
                matrix<1, DIM> trasposed; 
                for (std::size_t i{}; i < DIM; ++i)
                    trasposed(0, i) = vec[i]; 

                return trasposed; 

            }


            template <std::size_t DIM>
            constexpr vector<DIM> operator+(const vector<DIM>& vec, const matrix<DIM, 1>& vec_mat) noexcept {

                vector<DIM> result;
                for (std::size_t i{}; i < DIM; ++i)
                    result[i] = vec[i] + vec_mat(0, i);

                return result;

            }


            template <std::size_t DIM>
            constexpr vector<DIM> operator+(const matrix<DIM, 1>& vec_mat, const vector<DIM>& vec) noexcept {

                vector<DIM> result;
                for (std::size_t i{}; i < DIM; ++i)
                    result[i] =  vec_mat(0, i) + vec[i];

                return result;

            }


        } // namespace linear_algebra 


    } // namespace geometry 


} // namespace scipp