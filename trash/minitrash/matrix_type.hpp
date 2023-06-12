            // /// @brief Addition operator
            // constexpr matrix& operator+=(const matrix& other) noexcept {

            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    other.data.begin(), 
            //                    this->data.begin(), 
            //                    std::plus<vector_t>());

            //     return *this;

            // }

            // /// @brief Addition operator
            // constexpr matrix& operator+=(matrix&& other) noexcept {

            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    std::move(other).data.begin(), 
            //                    this->data.begin(), 
            //                    std::plus<vector_t>());

            //     return *this;

            // }


            // /// @brief Subtraction operator
            // constexpr matrix& operator-=(const matrix& other) noexcept {

            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    other.data.begin(), 
            //                    this->data.begin(), 
            //                    std::minus<vector_t>());

            //     return *this;
                
            // }

            // /// @brief Subtraction operator
            // constexpr matrix& operator-=(matrix&& other) noexcept {

            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    std::move(other).data.begin(), 
            //                    this->data.begin(), 
            //                    std::minus<vector_t>());

            //     return *this;

            // }


            // /// @brief Addition operator
            // constexpr matrix operator+(const matrix& other) const noexcept {

            //     data_t result;
            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    other.data.begin(), 
            //                    result.begin(), 
            //                    std::plus<vector_t>());

            //     return result;

            // }

            // /// @brief Addition operator
            // constexpr matrix operator+(matrix&& other) const noexcept {

            //     data_t result;
            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    other.data.begin(), 
            //                    result.begin(), 
            //                    std::plus<vector_t>());

            //     return result;

            // }


            // /// @brief Subtraction operator
            // constexpr matrix operator-(const matrix& other) const noexcept {

            //     data_t result;
            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    other.data.begin(), 
            //                    result.begin(), 
            //                    std::minus<vector_t>());

            //     return result;

            // }

            // /// @brief Subtraction operator
            // constexpr matrix operator-(matrix&& other) const noexcept {

            //     data_t result;
            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    std::move(other).data.begin(), 
            //                    result.begin(), 
            //                    std::minus<vector_t>());

            //     return result;

            // }


            // /// @brief Negate a matrix
            // constexpr matrix operator-() const noexcept {

            //     data_t result; 
            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    result.begin(), 
            //                    std::negate<vector_t>()); 

            //     return result;    

            // }


            // /// @brief Multiply this matrix by a scalar measurement
            // constexpr matrix& operator*=(const physics::scalar_m& other) noexcept {

            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    this->data.begin(), 
            //                    [&other](vector_t& x) { return x *= other; });

            //     return *this;

            // }

            // /// @brief Multiply this matrix by a scalar measurement
            // constexpr matrix& operator*=(physics::scalar_m&& other) noexcept {

            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    this->data.begin(), 
            //                    [&other](vector_t& x) { return std::move(x *= other); });

            //     return *this;

            // }


            // /// @brief Divide this matrix by a scalar measurement
            // constexpr matrix& operator/=(const physics::scalar_m& other) {
                
            //     if (other.value == 0.0)
            //         throw std::invalid_argument("Cannot divide a matrix by zero"); 

            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    this->data.begin(), 
            //                    [&other](vector_t& x) { return x /= other; });

            //     return *this;

            // }

            // /// @brief Divide this matrix by a scalar measurement
            // constexpr matrix& operator/=(physics::scalar_m&& other) {
                
            //     if (other.value == 0.0)
            //         throw std::invalid_argument("Cannot divide a matrix by zero"); 

            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    this->data.begin(), 
            //                    [&other](vector_t& x) { return std::move(x /= other); });

            //     return *this;

            // }


            // /// @brief Multiplicate a matrix with a generic measurement
            // template <typename OTHER_MEAS_TYPE>
            //     requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            // constexpr auto operator*(const OTHER_MEAS_TYPE& other) const noexcept 
            //     -> matrix<math::functions::multiply_t<vector_t, OTHER_MEAS_TYPE>, columns> {

            //     std::array<math::functions::multiply_t<vector_t, OTHER_MEAS_TYPE>, columns> result;

            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    result.begin(), 
            //                    [&other](const vector_t& x) { return x * other; });

            //     return result; 

            // }

            // /// @brief Multiplicate a matrix with a generic measurement
            // template <typename OTHER_MEAS_TYPE>
            //     requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            // constexpr auto operator*(OTHER_MEAS_TYPE&& other) const noexcept 
            //     -> matrix<math::functions::multiply_t<vector_t, OTHER_MEAS_TYPE>, columns> {

            //     std::array<math::functions::multiply_t<vector_t, OTHER_MEAS_TYPE>, columns> result;

            //     std::transform(std::execution::par,
            //                    this->data.begin(), this->data.end(), 
            //                    result.begin(), 
            //                    [&other](const vector_t& x) { return std::move(x * other); });

            //     return result;

            // }


            // /// @brief Divide a matrix by a generic measurement
            // template <typename OTHER_MEAS_TYPE>
            //     requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            // constexpr auto operator/(const OTHER_MEAS_TYPE& other) const 
            //     -> matrix<vector<math::functions::divide_t<value_t, OTHER_MEAS_TYPE>, rows>, columns> {

            //     if (other.value == 0.0)
            //         throw std::invalid_argument("Cannot divide a matrix by a zero measurement");

            //     return std::apply(
            //         [&](const auto&... components) {
            //             return std::array<vector<math::functions::divide_t<value_t, OTHER_MEAS_TYPE>, rows>, columns>({components / other ...});
            //         }, this->data
            //     );

            // }

            // /// @brief Divide a matrix by a generic measurement
            // template <typename OTHER_MEAS_TYPE>
            //     requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            // constexpr auto operator/(OTHER_MEAS_TYPE&& other) const 
            //     -> matrix<vector<math::functions::divide_t<value_t, OTHER_MEAS_TYPE>, rows>, columns> {

            //     if (other.value == 0.0)
            //         throw std::invalid_argument("Cannot divide a matrix by a zero measurement");

            //     return std::apply(
            //         [&](const auto&... components) {
            //             return std::array<vector<math::functions::divide_t<value_t, OTHER_MEAS_TYPE>, rows>, columns>({components / std::move(other) ...});
            //         }, this->data
            //     );

            // }


            // /// @brief  Multiply a matrix by a vector
            // template <typename OTHER_VEC_TYPE>
            //     requires (is_vector_v<OTHER_VEC_TYPE> && OTHER_VEC_TYPE::dim == columns)
            // constexpr auto operator*(const OTHER_VEC_TYPE& other) const noexcept 
            //     -> vector<math::functions::multiply_t<value_t, typename OTHER_VEC_TYPE::value_t>, rows> {
                
            //     std::array<math::functions::multiply_t<value_t, typename OTHER_VEC_TYPE::value_t>, rows> result;
            //     const auto transposed_data = this->transpose().data;

            //     std::transform(std::execution::par,
            //                    transposed_data.begin(), transposed_data.end(), 
            //                    result.begin(), 
            //                    [&other](auto&& row) { return math::op::dot(row, other); });

            //     return result;            

            // }

            // /// @brief  Multiply a matrix by a vector
            // template <typename OTHER_VEC_TYPE>
            //     requires (is_vector_v<OTHER_VEC_TYPE> && OTHER_VEC_TYPE::dim == columns)
            // constexpr auto operator*(OTHER_VEC_TYPE&& other) const noexcept 
            //     -> vector<math::functions::multiply_t<value_t, typename OTHER_VEC_TYPE::value_t>, rows> {
                
            //     std::array<math::functions::multiply_t<value_t, typename OTHER_VEC_TYPE::value_t>, rows> result;
            //     const auto transposed_data = this->transpose().data;  

            //     std::transform(std::execution::par,
            //                    transposed_data.begin(), transposed_data.end(), 
            //                    result.begin(), 
            //                    [&other](auto&& row) { return math::op::dot(row, std::move(other)); });
                               
            //     return result;               

            // }


            // // /// @brief Multiply a matrix to another matrix
            // // template <typename OTHER_VEC_TYPE>
            // //     requires (is_vector_v<OTHER_VEC_TYPE> && OTHER_VEC_TYPE::dim == columns) 
            // // constexpr auto operator*(const matrix<OTHER_VEC_TYPE, rows>& other) const noexcept 
            // //     -> matrix<vector<math::functions::multiply_t<value_t, typename OTHER_VEC_TYPE::value_t>, rows>, columns> {

            // //     std::array<vector<math::functions::multiply_t<value_t, typename OTHER_VEC_TYPE::value_t>, rows>, columns> result;
            // //     const auto transposed_data = this->transpose().data;  
            // //     for (size_t i{}; i < columns; ++i)
            // //         for (size_t j{}; j < rows; ++j)
            // //             result[i][j] = math::op::dot(transposed_data[j], other.data[i]);

            // //     return result;

            // // }

            // template <typename OTHER_VEC_TYPE>
            //     requires (is_vector_v<OTHER_VEC_TYPE> && OTHER_VEC_TYPE::dim == columns)
            // constexpr auto operator*(const matrix<OTHER_VEC_TYPE, rows>& other) const noexcept 
            //     -> matrix<vector<math::functions::multiply_t<value_t, typename OTHER_VEC_TYPE::value_t>, rows>, OTHER_VEC_TYPE::dim> {

            //     matrix<vector<math::functions::multiply_t<value_t, typename OTHER_VEC_TYPE::value_t>, rows>, OTHER_VEC_TYPE::dim> result;
            //     const auto transposed = this->transpose();  
            //     for (size_t i{}; i < OTHER_VEC_TYPE::dim; ++i)
            //         for (size_t j{}; j < rows; ++j)
            //             result.data[i][j] = math::op::dot(transposed[j], other.data[i]);

            //     return result;
                
            // }

