/**
 * @file vector.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2023-01-19
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::geometry {


    namespace linear_algebra {


        /**
         * @brief Class expressing a generic vector of measurements in a n-dimesional system
         * 
         * @tparam UB: the unit_base of the measurement
         * @tparam DIM: the number of dimensions
         */
        template <unit_base UB, std::size_t DIM> 
        class vector {


            public: 

            // =============================================
            // constructors and destructor
            // =============================================

                /**
                 * @brief Construct a new vector specifying the unit_base of the vector
                 * 
                 * @param unit: unit_base (default = unit_base())
                 */
                explicit constexpr vector() noexcept {

                    this->data_.fill(measurement<UB>(0.0));

                }


                /**
                 * @brief Construct a new vector from a pack of measurements
                 * 
                 * @param vec: list of all the vector components
                 * 
                 * @note The number of components must be the same as the dimesion of the vector
                 */
                template <typename... measurements_type>
                constexpr vector(const measurements_type&... measurements) {
                    
                    if (sizeof...(measurements) != DIM) 
                        throw std::invalid_argument("Cannot construct a vector with a number of components different from the dimension of the vector");

                    else 
                        this->data_ = {std::forward<measurement<UB>>(measurements)...};

                }


                /**
                 * @brief Construct a new vector from a pack of measurements
                 * 
                 * @param vec: list of all the vector components
                 * 
                 * @note The number of components must be the same as the dimesion of the vector
                 */
                template <typename... measurements_type>
                constexpr vector(measurements_type&&... measurements) {
                    
                    if (sizeof...(measurements) != DIM) 
                        throw std::invalid_argument("Cannot construct a vector with a number of components different from the dimension of the vector");

                    else 
                        this->data_ = {std::forward<measurement<UB>>(measurements)...};

                }


                /**
                 * @brief Copy construct a new vector from a vector object 
                 * 
                 * @param other: vector as l-value const reference
                 */
                constexpr vector(const vector& other) noexcept : 
                    
                    data_(other.data_) {}


                /**
                 * @brief Move construct a new vector from a vector object
                 * 
                 * @param other: vector as r-value reference
                 */
                constexpr vector(vector&& other) noexcept : 
                    
                    data_(std::move(other.data_)) {}


                /// @brief Default destructor
                ~vector() = default;


            // =============================================
            // operators
            // =============================================

                /**
                 * @brief Access the i-th element of the vector
                 * 
                 * @param index: std::size_t
                 * 
                 * @return constexpr measurement 
                 * 
                 * @note: index must be in the range [0, DIM)
                 */
                constexpr const measurement<UB>& operator[](const std::size_t& index) const { 
                    
                    if (index >= DIM) 
                        throw std::out_of_range("Cannot access a vector element with an index out of range");

                    return data_[index]; 
                    
                }


                /**
                 * @brief Access the i-th element of the vector
                 * 
                 * @param index: std::size_t 
                 * 
                 * @return constexpr measurement& 
                 * 
                 * @note: index must be in the range [0, DIM)
                 */
                constexpr measurement<UB>& operator[](const std::size_t& index) { 
                    
                    if (index >= DIM) 
                        throw std::out_of_range("Cannot access a vector with an index out of range");

                    return data_[index]; 
                    
                }


                /**
                 * @brief Equality operator
                 * 
                 * @param other: vector as l-value const reference
                 */
                constexpr bool operator==(const vector& other) const noexcept {

                    for (std::size_t i{}; i < DIM; ++i)
                        if (data_[i] != other.data_[i]) 
                            return false;
                    
                    return true;

                }


                /**
                 * @brief Equality operator
                 * 
                 * @param other: vector as r-value reference
                 */
                constexpr bool operator==(vector&& other) const noexcept {

                    for (std::size_t i{}; i < DIM; ++i)
                        if (data_[i] != other.data_[i]) 
                            return false;
                    
                    return true;

                }


                /**
                 * @brief Inequality operator
                 * 
                 * @param other: vector as l-value const reference
                 * 
                 * @return bools
                 *  
                 */
                constexpr bool operator!=(const vector& other) const noexcept {

                    for (std::size_t i{}; i < DIM; ++i) 
                        if (data_[i] != other.data_[i]) 
                            return true;

                    return false;

                }


                /**
                 * @brief Inequality operator
                 * 
                 * @param other: vector as r-value reference
                 * 
                 * @return bools
                 *  
                 */
                constexpr bool operator!=(vector&& other) const noexcept {

                    for (std::size_t i{}; i < DIM; ++i) 
                        if (data_[i] != other.data_[i]) 
                            return true;

                    return false;

                }            


                /**
                 * @brief Copy assignment operator
                 * 
                 * @param other: vector as l-value const reference
                 * 
                 * @return constexpr vector&
                 */
                constexpr vector& operator=(const vector& other) noexcept {

                    data_ = other.data_; 

                    return *this; 

                }

                
                /**
                 * @brief Move assignment operator
                 * 
                 * @param other: vector as r-value reference
                 * 
                 * @return constexpr vector& 
                 */
                constexpr vector& operator=(vector&& other) noexcept {
                    
                    data_ = std::move(other.data_); 

                    return *this; 

                }


                /**
                 * @brief Add a vector to the current vector
                 * 
                 * @note: the two vectors must have the same unit of measurement
                 * 
                 * @param other: vector to add as l-value const reference
                 * 
                 * @return constexpr vector& 
                 */
                constexpr vector& operator+=(const vector& other) {

                    for (std::size_t i{}; i < DIM; ++i) 
                        data_[i] += other.data_[i];

                    return *this; 

                }


                /**
                 * @brief Add a vector to the current vector
                 * @note: the two vectors must have the same unit of measurement
                 * 
                 * @param other: vector to add as r-value reference
                 * 
                 * @return constexpr vector& 
                 */
                constexpr vector& operator+=(vector&& other) {

                    for (std::size_t i{}; i < DIM; ++i) 
                        data_[i] += std::move(other.data_[i]);

                    return *this; 

                }


                /**
                 * @brief Subtract a vector to the current vector
                 * 
                 * @param other: vector to subtract as l-value const reference
                 * 
                 * @return constexpr vector& 
                 * 
                 * @note: the two vectors must have the same unit of measurement
                 */
                constexpr vector& operator-=(const vector& other) {

                    for (std::size_t i{}; i < DIM; ++i) 
                        data_[i] -= other.data_[i];

                    return *this; 

                }


                /**
                 * @brief Subtract a vector to the current vector
                 * 
                 * @param other: vector to subtract as r-value reference
                 * 
                 * @return constexpr vector& 
                 * 
                 * @note: the two vectors must have the same unit of measurement
                 */
                constexpr vector& operator-=(vector&& other) {

                    for (std::size_t i{}; i < DIM; ++i) 
                        data_[i] -= std::move(other.data_[i]);

                    return *this; 

                }


                /**
                 * @brief Multiply the current vector by a scalar
                 * 
                 * @param scalar: scalar as l-value const reference
                 * 
                 * @return constexpr vector& 
                 */
                constexpr vector& operator*=(const scalar& scalar) noexcept {

                    for (std::size_t i{}; i < DIM; ++i) 
                        data_[i] *= scalar;

                    return *this; 

                }


                /**
                 * @brief Multiply the current vector by a scalar
                 * 
                 * @param scalar: scalar as r-value reference
                 * 
                 * @return constexpr vector& 
                 */
                constexpr vector& operator*=(scalar&& scalar) noexcept {

                    for (std::size_t i{}; i < DIM; ++i) 
                        data_[i] *= scalar;

                    return *this; 

                }


                /**
                 * @brief Divide the current vector by a scalar
                 * 
                 * @param scalar: scalar as l-value const reference
                 *  
                 * @return constexpr vector& 
                 */
                constexpr vector& operator/=(const scalar& scalar) {

                    if (scalar == 0.0) 
                        throw std::runtime_error("Cannot divide a vector by zero");

                    for (std::size_t i{}; i < DIM; ++i)
                        data_[i] /= scalar;
                    
                    return *this; 
                    
                }


                /**
                 * @brief Divide the current vector by a scalar
                 * 
                 * @param scalar: scalar as r-value reference
                 *  
                 * @return constexpr vector& 
                 */
                constexpr vector& operator/=(scalar&& scalar) {

                    if (scalar == 0.0) 
                        throw std::runtime_error("Cannot divide a vector by zero");

                    for (std::size_t i{}; i < DIM; ++i)
                        data_[i] /= scalar;
                    
                    return *this; 
                    
                }


                /**
                 * @brief Return the opposite of the current vector
                 * 
                 * @return constexpr vector 
                 */
                constexpr vector operator-() const noexcept {

                    std::array<measurement<UB>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = -data_[i]; 
                    
                    return result;

                }


                /**
                 * @brief Sum the current vector and another vector
                 * 
                 * @param other: vector to add as l-value const reference
                 * 
                 * @return constexpr vector 
                 * 
                 * @note: the two vectors must have the same unit of measurement and the same size
                 */
                constexpr vector operator+(const vector& other) const {

                    std::array<measurement<UB>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = data_[i] + other.data_[i]; 
                    
                    return result;

                }


                /**
                 * @brief Subtract the current vector and another vector
                 * 
                 * @param other: vector to subtract as l-value const reference
                 * 
                 * @return constexpr vector 
                 * 
                 * @note: the two vectors must have the same unit of measurement and the same size
                 */
                constexpr vector operator-(const vector& other) const {

                    std::array<measurement<UB>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = data_[i] - other.data_[i]; 
                    
                    return result;

                }


                /**
                 * @brief Multiply the current vector by a measurement
                 * 
                 * @param meas: measurement as l-value const reference
                 * 
                 * @return constexpr vector 
                 */
                template <unit_base UB2>
                constexpr vector<UB * UB2, DIM> operator*(const measurement<UB2>& meas) const noexcept {

                    std::array<measurement<UB * UB2>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = data_[i] * meas; 
                    
                    return result;

                }


                /**
                 * @brief Multiply the current vector by a measurement
                 * 
                 * @param meas: measurement as r-value reference
                 * 
                 * @return constexpr vector 
                 */
                template <unit_base UB2>
                constexpr vector<UB * UB2, DIM> operator*(measurement<UB2>&& meas) const noexcept {

                    std::array<measurement<UB * UB2>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = data_[i] * meas; 
                    
                    return result;

                }


                /**
                 * @brief Divide the current vector by a measurement
                 * 
                 * @param meas: measurement as l-value const reference
                 * 
                 * @return constexpr vector 
                 */
                template <unit_base UB2>
                constexpr vector<UB / UB2, DIM> operator/(const measurement<UB2>& meas) const {

                    if (meas.value() == 0.0) 
                        throw std::runtime_error("Cannot divide a vector by a zero measurement");

                    std::array<measurement<UB / UB2>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = data_[i] / meas; 
                    
                    return result;

                }


                /**
                 * @brief Divide the current vector by a measurement
                 * 
                 * @param meas: measurement as r-value reference
                 * 
                 * @return constexpr vector 
                 */
                template <unit_base UB2>
                constexpr vector<UB / UB2, DIM> operator/(measurement<UB2>&& meas) const {

                    if (meas.value() == 0.0) 
                        throw std::runtime_error("Cannot divide a vector by a zero measurement");

                    std::array<measurement<UB / UB2>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = data_[i] / meas; 
                    
                    return result;

                }


                /**
                 * @brief Multiply the current vector by a scalar
                 * 
                 * @param scalar: scalar as l-value const reference
                 * 
                 * @return constexpr vector
                 *  
                 */
                constexpr vector operator*(const scalar& scalar) const noexcept {

                    std::array<measurement<UB>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = data_[i] * scalar; 
                    
                    return result;

                }


                /**
                 * @brief Divide the current vector by a scalar
                 * 
                 * @param scalar: scalar as l-value const reference
                 * 
                 * @return constexpr vector
                 *  
                 */
                constexpr vector operator/(const scalar& scalar) const {

                    if (scalar == 0.0) 
                        throw std::runtime_error("Cannot divide a vector by zero");

                    std::array<measurement<UB>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = data_[i] / scalar; 
                    
                    return result;

                }


                /**
                 * @brief Multiply the current vector with a std::array<scalar>
                 * 
                 * @param scalar_arr: std::array<scalar> as l-value const reference
                 * 
                 * @return constexpr vector 
                 */
                constexpr vector operator*(const std::array<scalar, DIM>& scalar_arr) const noexcept {

                    std::array<measurement<UB>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = data_[i] * scalar_arr[i]; 
                    
                    return result;

                }


                /**
                 * @brief Divide the current vector by a std::array<scalar>
                 * 
                 * @param scalar_arr: std::array<scalar> as l-value const reference
                 * 
                 * @return constexpr vector 
                 */
                constexpr vector operator/(const std::array<scalar, DIM>& scalar_arr) const {

                    std::array<measurement<UB>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        if (scalar_arr[i] != 0)
                            result[i] = data_[i] / scalar_arr[i];
                        else throw std::runtime_error("Cannot divide a vector by a vector with a zero component");
                    
                    return result;

                }


                /**
                 * @brief Multiply the a measurement and a vector
                 * 
                 * @param meas: measurement as l-value const reference
                 * @param vec: vector as l-value const reference
                 * 
                 * @return constexpr vector 
                 */
                template <unit_base UB2>
                friend constexpr vector<UB * UB2, DIM> operator*(const measurement<UB>& meas, const vector<UB2, DIM>& vec) noexcept {

                    std::array<measurement<UB * UB2>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = meas * vec.data_[i]; 
                    
                    return result;

                }


                /**
                 * @brief Divide the a measurement and a vector
                 * 
                 * @param meas: measurement as l-value const reference
                 * @param vec: vector as l-value const reference
                 * 
                 * @return constexpr vector 
                 */
                template <unit_base UB2>
                friend constexpr vector<UB / UB2, DIM> operator/(const measurement<UB>& meas, const vector<UB2, DIM>& other) {

                    std::array<measurement<UB / UB2>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = meas / other.data_[i];
                    
                    return result;

                }


                /**
                 * @brief Multiply the a scalar and a vector
                 * 
                 * @param scalar: scalar as l-value const reference
                 * @param vec: vector as l-value const reference
                 * 
                 * @return constexpr vector 
                 */
                friend constexpr vector operator*(const scalar& scalar, const vector& vec) noexcept {

                    std::array<measurement<UB>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = scalar * vec.data_[i]; 
                    
                    return result;

                }


                /**
                 * @brief Divide the a scalar and a vector
                 * 
                 * @param scalar: scalar as l-value const reference
                 * @param vec: vector as l-value const reference
                 * 
                 * @return constexpr vector 
                 */                
                friend constexpr vector<UB.inv(), DIM> operator/(const scalar& scalar, const vector& vec) {

                    std::array<measurement<UB.inv()>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = scalar / vec.data_[i]; 
                    
                    return result;

                }


                /**
                 * @brief Multiply the a std::array<scalar> and a vector
                 * 
                 * @param scalar_arr: std::array<scalar> as l-value const reference
                 * @param vec: vector as l-value const reference
                 * 
                 * @return constexpr vector
                 */
                friend constexpr vector<UB.inv(), DIM> operator*(const std::array<scalar, DIM>& scalar_vec, const vector& other) noexcept {

                    std::array<measurement<UB.inv()>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = scalar_vec[i] * other.data_[i]; 
                    
                    return result;

                }


                /**
                 * @brief Divide the a std::array<scalar> and a vector
                 * 
                 * @param scalar_arr: std::array<scalar> as l-value const reference
                 * @param vec: vector as l-value const reference
                 * 
                 * @return constexpr vector 
                 */
                friend constexpr vector<UB.inv(), DIM> operator/(const std::array<scalar, DIM>& scalar_vec, const vector& other) noexcept {

                    std::array<measurement<UB.inv()>, DIM> result; 
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = scalar_vec[i] / other.data_[i]; 
                    
                    return result;

                }


                /**
                 * @brief Print the vector to the standard output
                 * 
                 * @param os: ostream as l-value reference
                 * @param vec: vector as l-value const reference
                 * 
                 * @return std::ostream&
                 */
                friend std::ostream& operator<<(std::ostream& os, const vector& vec) noexcept {
                    
                    os << "{ "; 
                    for (std::size_t i{}; i < DIM; ++i) 
                        os << vec.data_[i] << ((i != DIM - 1) ? ", " : " }"); 

                    return os;

                }


                /**
                 * @brief Print the vector to file
                 * 
                 * @param file: ofstream as l-value reference
                 * @param vec: vector as l-value const reference
                 * 
                 * @return std::ofstream&
                 */
                friend std::ofstream& operator<<(std::ofstream& file, const vector& vec) noexcept {


                    constexpr std::size_t cols{static_cast<int>(std::ceil(std::log10(DIM)))};
                    file << "{\t";
                    for (std::size_t i{}; i < DIM; ++i) {

                        if (i % (cols + 3) == 0 && i != 0)
                            file << "\n\t";

                        file << vec.data_[i] << std::setw(8); 
                        
                        if (i == DIM - 1) 
                            file << "}";

                    }

                    return file;

                }


            // =============================================
            // operations
            // =============================================

                /**
                 * @brief Invert the vector
                 * 
                 * @return constexpr vector 
                 */
                constexpr vector<UB.inv(), DIM> inv() const {

                    std::array<measurement<UB.inv()>, DIM> result;
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = data_[i].inv(); 
                    
                    return result;

                }


                /**
                 * @brief Take the power of the vector
                 * 
                 * @param vec: vector as l-value const reference
                 * @param power: int
                 *  
                 * @return constexpr vector 
                 */
                friend constexpr auto pow(const vector& vec, const int& power) noexcept {

                    std::array<measurement<UB.pow(power)>, DIM> result;
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = math::op::pow(vec.data_[i], power);
                    
                    return result;

                }


                /**
                 * @brief Take the square of the vector
                 * 
                 * @param vec: vector as l-value const reference

                * @return constexpr vector 
                */
                friend constexpr vector<UB.square(), DIM> square(const vector& vec) noexcept {

                    std::array<measurement<UB.square()>, DIM> result;
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = math::op::square(vec.data_[i]);
                    
                    return result;

                }


                /**
                 * @brief Take the cube of the vector
                 * 
                 * @param vec: vector as l-value const reference
                 * 
                 * @return constexpr vector 
                 */
                friend constexpr vector<UB.cube(), DIM> cube(const vector& vec) noexcept {

                    std::array<measurement<UB.cube()>, DIM> result;
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = math::op::cube(vec.data_[i]);
                    
                    return result;

                }


                /**
                 * @brief Take the root of the vector
                 * 
                 * @param vec: vector as l-value const reference
                 * @param power: int
                 * 
                 * @return constexpr vector 
                 */
                friend constexpr auto root(const vector& vec, const int& power) {

                    std::array<measurement<UB.root(power)>, DIM> result;
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = math::op::root(vec.data_[i], power);
                    
                    return result;

                }


                /**
                 * @brief Take the square root of the vector
                 * 
                 * @param vec: vector as l-value const reference
                 * 
                 * @return constexpr vector 
                 */
                friend constexpr auto sqrt(const vector& vec) {

                    std::array<measurement<UB.sqrt()>, DIM> result;
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = math::op::sqrt(vec.data_[i]);
                    
                    return result;

                }


                /**
                 * @brief Take the cube root of the vector
                 * 
                 * @param vec: vector as l-value const reference
                 * 
                 * @return constexpr vector 
                 */
                friend constexpr auto cbrt(const vector& vec) {

                    std::array<measurement<UB.cbrt()>, DIM> result;
                    for (std::size_t i{}; i < DIM; ++i)
                        result[i] = math::op::cbrt(vec.data_[i]);
                    
                    return result;

                }


                /**
                 * @brief Compute the cross product between two vectors
                 * 
                 * @param v1: vector as l-value const reference
                 * @param v2: vector as l-value const reference
                 * 
                 * @return constexpr vector 
                 */
                template <unit_base UB2>
                friend constexpr vector<UB * UB2, DIM> cross(const vector& v1, const vector<UB2, DIM>& v2) {

                    std::array<measurement<UB * UB2>, DIM> cross_vec;
                    for (std::size_t i{}; i < DIM; ++i) 
                        cross_vec[i] = v1[(i + 1) % v1.size()] * v2[(i + 2) % v1.size()] - v1[(i + 2) % v1.size()] * v2[(i + 1) % v1.size()]; 

                    return cross_vec;
                
                }

                
                /**
                 * @brief Compute the dot product between two vectors
                 * 
                 * @param v1: vector as l-value const reference
                 * @param v2: vector as l-value const reference
                 * 
                 * @return constexpr vector 
                 */
                template <unit_base UB2>
                friend constexpr measurement<UB * UB2> dot(const vector& v1, const vector<UB2, DIM>& v2) noexcept {

                    measurement<UB * UB2> result(0.0, v1[0].units() * v2[0].units());
                    for (std::size_t i{}; i < v1.size(); ++i)
                        result += v1[i] * v2[i]; 
                    
                    return result;
                
                }


            // =============================================
            // check methods
            // =============================================

                /// @brief Check the current vector is a scalar vector
                constexpr bool is_scalar() const noexcept {

                    return (UB == basis::scalar); 

                }


                /// @brief Check if the vector is a zero vector
                constexpr bool is_zero() const noexcept {

                    for (std::size_t i{}; i < DIM; ++i)
                        if (data_[i] != 0.0) 
                            return false;
                    
                    return true; 

                }


                /// @brief Check if the vector is a one vector
                constexpr bool is_one() const noexcept {

                    for (std::size_t i{}; i < DIM; ++i)
                        if (data_[i] != 1.0) 
                            return false;
                    
                    return true; 

                }


                /// @brief Check if the vector is a NAN vector
                constexpr bool is_nan() const noexcept {

                    for (std::size_t i{}; i < DIM; ++i)
                        if (data_[i] == math::constants::nan) 
                            return true;
                    
                    return false; 

                }


                /// @brief Check if the vector is a infinity vector
                constexpr bool is_infinite() const noexcept {

                    for (std::size_t i{}; i < DIM; ++i)
                        if (data_[i] == math::constants::infinity) 
                            return true;
                    
                    return false; 

                }


                /// @brief Check if the vector is normalized
                constexpr bool is_normalized() const noexcept {

                    if (this->norm() == 1.) 
                        return true; 

                    else 
                        return false;  

                }


            // =============================================
            // set & get methods
            // =============================================

                /**
                 * @brief Get the size of the vector
                 * 
                 * @return constexpr std::size_t 
                 */
                constexpr std::size_t size() const noexcept { 
                    
                    return DIM; 
                    
                }


                /**
                 * @brief Get the first element of the vector
                 * 
                 * @note the vector must have at least one element
                 * 
                 * @return constexpr measurement
                 */
                constexpr measurement<UB> x() const noexcept { 
                    
                    return data_[0]; 
                
                }
                                

                /**
                 * @brief Get the first element of the vector
                 * 
                 * @note the vector must have at least one element
                 * 
                 * @return constexpr measurement&
                 */
                constexpr measurement<UB>& x() noexcept { 
                    
                    return data_[0]; 
                
                }


                /**
                 * @brief Get the second element of the vector
                 * 
                 * @note the vector must have at least two elements
                 * 
                 * @return constexpr measurement
                 */
                constexpr measurement<UB> y() const {
                    
                    if constexpr (DIM < 2) 
                        throw std::out_of_range("Cannot access the second element of a vector with less than two elements"); 
                    
                    return data_[1]; 
                
                }


                /**
                 * @brief Get the second element of the vector
                 * 
                 * @note the vector must have at least two elements
                 * 
                 * @return constexpr measurement&
                 */
                constexpr measurement<UB>& y() {
                    
                    if constexpr (DIM < 2) 
                        throw std::out_of_range("Cannot access the second element of a vector with less than two elements"); 
                    
                    return data_[1]; 
                
                }


                /**
                 * @brief Get the third element of the vector
                 * 
                 * @note the vector must have at least three elements
                 *
                 * @return constexpr measurement
                 */
                constexpr measurement<UB> z() const {
                    
                    if constexpr (DIM < 3) 
                        throw std::out_of_range("Cannot access the third element of a vector with less than three elements"); 
                    
                    return data_[2]; 
                
                }


                /**
                 * @brief Get the third element of the vector
                 * 
                 * @note the vector must have at least three elements
                 * 
                 * @return constexpr measurement&
                 */
                constexpr measurement<UB>& z() {
                    
                    if constexpr (DIM < 3) 
                        throw std::out_of_range("Cannot access the third element of a vector with less than three elements"); 
                    
                    return data_[2]; 
                
                }


                /**
                 * @brief Get the fourth element of the vector
                 * 
                 * @note the vector must have at least four elements
                 *
                 * @return constexpr measurement
                 */
                constexpr measurement<UB> w() const {
                    
                    if constexpr (DIM < 4) 
                        throw std::out_of_range("Cannot access the fourth element of a vector with less than four elements"); 
                    
                    return data_[3]; 
                
                }
                    

                /**
                 * @brief Get the fourth element of the vector
                 * 
                 * @note the vector must have at least four elements
                 *
                 * @return constexpr measurement&
                 */
                constexpr measurement<UB>& w() {
                    
                    if constexpr (DIM < 4) 
                        throw std::out_of_range("Cannot access the fourth element of a vector with less than four elements"); 
                    
                    return data_[3]; 
                
                }


                /**
                 * @brief Get the norm of the vector
                 * 
                 * @return constexpr measurement 
                 */
                constexpr measurement<UB> norm() const noexcept { 

                    if constexpr (DIM == 1) 
                        return data_[0];

                    vector<UB, DIM> squared = square(*this);

                    return sqrt(std::accumulate(squared.data().begin(), squared.data().end(), measurement(0.0, squared.units())));

                }


                /**
                 * @brief Get the squared norm of the vector
                 * 
                 * @return constexpr measurement 
                 */
                constexpr measurement<UB.square()> norm2() const noexcept { 

                    if constexpr (DIM == 1) 
                        return data_[0]; 

                    vector<UB.square(), DIM> squared(square(*this));

                    return std::accumulate(squared.data().begin(), squared.data().end(), measurement{0.0, squared.units()});
                    
                }


                /**
                 * @brief Get the normalization of the vector
                 * 
                 * @return constexpr vector 
                 */
                constexpr vector<basis::scalar, DIM> normalize() const {

                    if (this->is_normalized())
                        return *this; 
                        
                    else 
                        return *this / this->norm(); 

                } 


                /**
                 * @brief Get the projection of a vector on the current vector
                 * 
                 * @return vector
                 */
                template <unit_base UB2>
                constexpr vector<UB * UB2, DIM> projection(const vector<UB2, DIM>& vec) const noexcept {

                    return dot(vec, *this) * (*this  / this->norm2()); 

                }


                /**
                 * @brief Get the polar angle
                 * 
                 * @note the vector must have at least two elements
                 * 
                 * @return constexpr measurement
                 */
                constexpr measurement<basis::radian> phi() const {
                    
                    if constexpr (DIM < 2) 
                        throw std::out_of_range("Cannot access the polar angle of a vector with less than two elements"); 
                    
                    return atan(data_[1] / data_[0]); 
                
                }     
                

                /**
                 * @brief Get the azimuthal angle
                 * 
                 * @note the vector must have at least three elements
                 * 
                 * @return constexpr measurement
                 */
                constexpr measurement<basis::radian> theta() const {
                    
                    if constexpr (DIM < 3) 
                        throw std::out_of_range("Cannot access the azimuthal angle of a vector with less than three elements"); 
                    
                    if (data_[2] == 0.0 * m) 
                        return 0.0 * rad;
                    else    
                        return acos((data_[2] / norm()));

                }
                

                /**
                 * @brief Get the unit_base of the vector
                 * 
                 * @return constexpr unit_base
                 */
                constexpr unit_base base() const noexcept { 
                    
                    return UB; 
                
                }


                /**
                 * @brief Get the data of the vector
                 * 
                 * @return constexpr std::array<measurement> 
                 */
                constexpr std::array<measurement<UB>, DIM> data() const noexcept { 
                    
                    return data_; 
                
                }


                /**
                 * @brief Get the data of the vector
                 * 
                 * @return constexpr std::array<measurement<UB>, DIM>& 
                 */
                constexpr std::array<measurement<UB>, DIM>& data() noexcept { 
                    
                    return data_;
                
                }


                /**
                 * @brief Get the vector object
                 * 
                 * @return constexpr vector 
                 */
                constexpr vector as_vector() const noexcept { 
                    
                    return *this; 
                
                }


                /**
                 * @brief Get the vector object
                 * 
                 * @return constexpr vector&
                 */
                constexpr vector& as_vector() noexcept { 
                    
                    return *this; 
                
                }


                /// @brief Print the vector to the standard output
                void print() const noexcept {

                    constexpr std::size_t cols{static_cast<int>(std::ceil(std::log10(DIM)))};
                    std::cout << "{\t";
                    for (std::size_t i{}; i < DIM; ++i) {

                        if (i % (cols + 3) == 0 && i != 0)
                            std::cout << "\n\t";

                        std::cout << data_[i] << '\t'; 
                        
                        if (i == DIM - 1) 
                            std::cout << "}";

                    }
                    std::cout << '\n';

                }   


                // /**
                //  * @brief Save the vector to a file
                //  * 
                //  * @param file_name: the name of the file
                //  * @param units: desired units for the output
                //  * 
                //  * @return void
                //  */
                // void save(const std::string& file_name, const unit& units) const {

                //     std::ofstream file_out{file_name, std::ios::app};
                //     if (file_out.is_open()) 

                //         for (std::size_t i{}; i < DIM; ++i) {

                //             file_out << data_[i].value_as(units) << '\t'; 

                //         }

                //     else 
                //         throw std::invalid_argument("Unable to open '" + file_name + "'");

                //     file_out << '\n';
                //     file_out.close();

                // }


            protected:

            // =============================================
            // class members
            // =============================================

                std::array<measurement<UB>, DIM> data_; ///< array of measurements

                static_assert(DIM != 0, "The dimesion of the vector cannot be 0."); ///< Check for the dimesion of the vector


        }; // class vector


    } // namespace linear_algebra


} // namespace scipp::geometry