/**
 * @file vector.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2022-12-19
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp {


    namespace geometry {


        namespace linear_algebra {


            /**
             * @brief Class expressing a generic vector of measurements in a n-dimesional system
             * 
             * @tparam DIM: the number of dimensions
             */
            template <std::size_t DIM> 
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
                    explicit constexpr vector(const unit_base& base = basis::default_type) noexcept {

                        data_.fill(measurement(0, unit(base)));

                    }


                    /**
                     * @brief Construct a new vector from a pack of measurements
                     * 
                     * @param vec: list of all the vector components
                     * 
                     * @note The number of components must be the same as the dimesion of the vector
                     */
                    template <typename... meas>
                    constexpr vector(const meas&... vec) {
                        
                        if (sizeof...(vec) != DIM) 
                            throw std::invalid_argument("Cannot construct a vector with a number of components different from the dimension of the vector");

                        else 
                            this->data_({measurement(vec)...});

                    }


                    /**
                     * @brief Construct a new vector from a std::array of measurements
                     * 
                     * @param data: std::array<measurement, DIM> as l-value const reference
                     */
                    constexpr vector(const std::array<measurement, DIM>& data) noexcept : 
                        
                        data_(data) {}


                    /**
                     * @brief Construct a new vector from an std::array of measurements
                     * 
                     * @param data: std::array<measurement, DIM> as r-value reference
                     */
                    constexpr vector(std::array<measurement, DIM>&& data) noexcept : 
                        
                        data_(std::move(data)) {}


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
                    constexpr const measurement& operator[](const std::size_t& index) const { 
                        
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
                    constexpr measurement& operator[](const std::size_t& index) { 
                        
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
                     * @brief Multiply the current vector by a measurement
                     * 
                     * @param meas: measurement to multiply with as l-value const reference
                     * 
                     * @return constexpr vector& 
                     */
                    constexpr vector& operator*=(const measurement& meas) noexcept {

                        for (std::size_t i{}; i < DIM; ++i)  
                            data_[i] *= meas;

                        return *this; 

                    }


                    /**
                     * @brief Multiply the current vector by a measurement
                     * 
                     * @param meas: measurement to multiply with as r-value reference
                     * 
                     * @return constexpr vector&
                     */
                    constexpr vector& operator*=(measurement&& meas) noexcept {

                        for (std::size_t i{}; i < DIM; ++i) 
                            data_[i] *= std::move(meas);

                        return *this; 

                    }


                    /**
                     * @brief Divide the current vector by a measurement
                     * 
                     * @param meas: measurement to divide by as l-value const reference
                     *  
                     * @return constexpr vector& 
                     */
                    constexpr vector& operator/=(const measurement& meas) {
                        
                        if (meas.value() == 0.0) 
                            throw std::runtime_error("Cannot divide a vector by a zero measurement");

                        for (std::size_t i{}; i < DIM; ++i) 
                            data_[i] /= meas;
                        
                        return *this; 

                    }


                    /**
                     * @brief Divide the current vector by a measurement
                     * 
                     * @param meas: measurement to divide by as r-value reference
                     * 
                     * @return constexpr vector&
                     */
                    constexpr vector& operator/=(measurement&& meas) {

                        if (meas.value() == 0.0) 
                            throw std::runtime_error("Cannot divide a vector by a zero measurement");
                        
                        for (std::size_t i{}; i < DIM; ++i)
                            data_[i] /= meas;

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
                     * @brief Return the opposite of the current vector
                     * 
                     * @return constexpr vector 
                     */
                    constexpr vector operator-() const noexcept {

                        std::array<measurement, DIM> result; 
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

                        std::array<measurement, DIM> result; 
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

                        std::array<measurement, DIM> result; 
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
                    constexpr vector operator*(const measurement& meas) const noexcept {

                        std::array<measurement, DIM> result; 
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
                    constexpr vector operator/(const measurement& meas) const {

                        if (meas.value() == 0.0) 
                            throw std::runtime_error("Cannot divide a vector by a zero measurement");

                        std::array<measurement, DIM> result; 
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

                        std::array<measurement, DIM> result; 
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

                        std::array<measurement, DIM> result; 
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

                        std::array<measurement, DIM> result; 
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

                        std::array<measurement, DIM> result; 
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
                    friend constexpr vector operator*(const measurement& meas, const vector& vec) noexcept {

                        std::array<measurement, DIM> result; 
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
                    friend constexpr vector operator/(const measurement& meas, const vector& other) {

                        std::array<measurement, DIM> result; 
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

                        std::array<measurement, DIM> result; 
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
                    friend constexpr vector operator/(const scalar& scalar, const vector& vec) {

                        std::array<measurement, DIM> result; 
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
                    friend constexpr vector operator*(const std::array<scalar, DIM>& scalar_vec, const vector& other) noexcept {

                        std::array<measurement, DIM> result; 
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
                    friend constexpr vector operator/(const std::array<scalar, DIM>& scalar_vec, const vector& other) noexcept {

                        std::array<measurement, DIM> result; 
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

                        // constexpr std::size_t cols{static_cast<int>(std::ceil(std::log10(DIM)))};
                        // std::cout << "{\t";
                        // for (std::size_t i{}; i < DIM; ++i) {

                        //     if (i % (cols + 3) == 0 && i != 0)
                        //         std::cout << "\n\t";

                        //     std::cout << vec.data_[i] << '\t'; 
                            
                        //     if (i == DIM - 1) 
                        //         std::cout << "}";

                        // }

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
                    constexpr vector inv() const {

                        std::array<measurement, DIM> result;
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
                    friend constexpr vector pow(const vector& vec, const int& power) noexcept {

                        std::array<measurement, DIM> result;
                        for (std::size_t i{}; i < DIM; ++i)
                            result[i] = pow(vec.data_[i], power);
                        
                        return result;

                    }


                    /**
                     * @brief Take the square of the vector
                     * 
                     * @param vec: vector as l-value const reference

                    * @return constexpr vector 
                    */
                    friend constexpr vector square(const vector& vec) noexcept {

                        std::array<measurement, DIM> result;
                        for (std::size_t i{}; i < DIM; ++i)
                            result[i] = square(vec.data_[i]);
                        
                        return result;

                    }


                    /**
                     * @brief Take the cube of the vector
                     * 
                     * @param vec: vector as l-value const reference
                     * 
                     * @return constexpr vector 
                     */
                    friend constexpr vector cube(const vector& vec) noexcept {

                        std::array<measurement, DIM> result;
                        for (std::size_t i{}; i < DIM; ++i)
                            result[i] = cube(vec.data_[i]);
                        
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
                    friend constexpr vector root(const vector& vec, const int& power) {

                        std::array<measurement, DIM> result;
                        for (std::size_t i{}; i < DIM; ++i)
                            result[i] = root(vec.data_[i], power);
                        
                        return result;

                    }


                    /**
                     * @brief Take the square root of the vector
                     * 
                     * @param vec: vector as l-value const reference
                     * 
                     * @return constexpr vector 
                     */
                    friend constexpr vector sqrt(const vector& vec) {

                        std::array<measurement, DIM> result;
                        for (std::size_t i{}; i < DIM; ++i)
                            result[i] = sqrt(vec.data_[i]);
                        
                        return result;

                    }


                    /**
                     * @brief Take the cube root of the vector
                     * 
                     * @param vec: vector as l-value const reference
                     * 
                     * @return constexpr vector 
                     */
                    friend constexpr vector cbrt(const vector& vec) {

                        std::array<measurement, DIM> result;
                        for (std::size_t i{}; i < DIM; ++i)
                            result[i] = cbrt(vec.data_[i]);
                        
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
                    friend constexpr vector cross(const vector& v1, const vector& v2) {

                        std::array<measurement, DIM> cross_vec;
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
                    friend constexpr measurement dot(const vector& v1, const vector& v2) noexcept {

                        measurement result(0.0, v1[0].units() * v2[0].units());
                        for (std::size_t i{}; i < v1.size(); ++i)
                            result += v1[i] * v2[i]; 
                        
                        return result;
                    
                    }


                // =============================================
                // check methods
                // =============================================

                    /// @brief Check the current vector is a scalar vector
                    constexpr bool is_scalar() const noexcept {

                        for (std::size_t i{}; i < DIM; ++i)
                            if (data_[i].units() != unit()) 
                                return false;
                        
                        return true; 

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
                    constexpr measurement x() const noexcept { 
                        
                        return data_[0]; 
                    
                    }
                                    

                    /**
                     * @brief Get the first element of the vector
                     * 
                     * @note the vector must have at least one element
                     * 
                     * @return constexpr measurement&
                     */
                    constexpr measurement& x() noexcept { 
                        
                        return data_[0]; 
                    
                    }


                    /**
                     * @brief Get the second element of the vector
                     * 
                     * @note the vector must have at least two elements
                     * 
                     * @return constexpr measurement
                     */
                    constexpr measurement y() const {
                        
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
                    constexpr measurement& y() {
                        
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
                    constexpr measurement z() const {
                        
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
                    constexpr measurement& z() {
                        
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
                    constexpr measurement w() const {
                        
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
                    constexpr measurement& w() {
                        
                        if constexpr (DIM < 4) 
                            throw std::out_of_range("Cannot access the fourth element of a vector with less than four elements"); 
                        
                        return data_[3]; 
                    
                    }


                    /**
                     * @brief Get the norm of the vector
                     * 
                     * @return constexpr measurement 
                     */
                    constexpr measurement norm() const noexcept { 

                        if constexpr (DIM == 1) 
                            return data_[0];

                        vector squared = square(*this);

                        return sqrt(std::accumulate(squared.data().begin(), squared.data().end(), measurement(0.0, squared.units())));

                    }


                    /**
                     * @brief Get the squared norm of the vector
                     * 
                     * @return constexpr measurement 
                     */
                    constexpr measurement norm2() const noexcept { 

                        if constexpr (DIM == 1) 
                            return data_[0]; 

                        vector squared(square(*this));

                        return std::accumulate(squared.data().begin(), squared.data().end(), measurement{0.0, squared.units()});
                        
                    }


                    /**
                     * @brief Get the normalization of the vector
                     * 
                     * @return constexpr vector 
                     */
                    constexpr vector normalize() const {

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
                    constexpr vector projection(const vector<DIM>& vec) const noexcept {

                        return dot(vec, *this) * (*this  / this->norm2()); 

                    }


                    /**
                     * @brief Get the polar angle
                     * 
                     * @note the vector must have at least two elements
                     * 
                     * @return constexpr measurement
                     */
                    constexpr measurement phi() const {
                        
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
                    constexpr measurement theta() const {
                        
                        if constexpr (DIM < 3) 
                            throw std::out_of_range("Cannot access the azimuthal angle of a vector with less than three elements"); 
                        
                        if (data_[2] == 0.0 * m) 
                            return 0.0 * rad;
                        else    
                            return acos((data_[2] / norm()));

                    }
                    

                    /**
                     * @brief Get the unit of the vector
                     * 
                     * @return constexpr unit 
                     */
                    constexpr unit units() const noexcept { 

                        if constexpr (DIM == 1)
                            return data_.front().units(); 

                        bool are_same_unit = true; 
                        const unit_base first_unit_base = data_.front().units().base(); 

                        for (std::size_t i{1}; i < DIM; ++i)
                            if (data_[i].units().base() != first_unit_base) 
                                are_same_unit = false; 

                        if (are_same_unit) 
                            return unit(first_unit_base); 

                        else {
                            std::cerr << "This vector stores different measurements, therefor it is not possible to return the units of the vector\n"; 
                            return unit();
                        }

                    }


                    /**
                     * @brief Get the data of the vector
                     * 
                     * @return constexpr std::array<measurement> 
                     */
                    constexpr std::array<measurement, DIM> data() const noexcept { 
                        
                        return data_; 
                    
                    }


                    /**
                     * @brief Get the data of the vector
                     * 
                     * @return constexpr std::array<measurement, DIM>& 
                     */
                    constexpr std::array<measurement, DIM>& data() noexcept { 
                        
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


                    /**
                     * @brief Save the vector to a file
                     * 
                     * @param file_name: the name of the file
                     * @param units: desired units for the output
                     * 
                     * @return void
                     */
                    void save(const std::string& file_name, const unit& units) const {

                        std::ofstream file_out(file_name, std::ios::app);
                        if (file_out.is_open()) 

                            for (std::size_t i{}; i < DIM; ++i) {

                                file_out << data_[i].value_as(units) << '\t'; 

                            }

                        else 
                            throw std::invalid_argument("Unable to open '" + file_name + "'");

                        file_out << '\n';
                        file_out.close();

                    }


                protected:

                // =============================================
                // class members
                // =============================================

                    std::array<measurement, DIM> data_; ///< array of measurements

                    static_assert(DIM != 0, "The dimesion of the vector cannot be 0."); ///< Check for the dimesion of the vector


            }; // class vector


            /// @brief Template deduction guide for a list of measurements
            template <typename... meas>
            vector(const meas&...) -> vector<sizeof...(meas)>;


            /// @brief Template deduction guide for an array of measurements
            template <class measurement, class... U>
            vector(const std::array<measurement, sizeof...(U) + 1>&, const U&...) -> vector<sizeof...(U) + 1>;
            

            #define vector2 vector<2>

            #define vector3 vector<3>

            #define quaternion vector<4>


        } // namespace linear_algebra


    } // namespace geometry


} // namespace scipp