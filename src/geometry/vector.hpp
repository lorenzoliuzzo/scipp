/**
 * @file vector.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2023-02-10
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::geometry {


    template <typename BASE, std::size_t DIM> requires (physics::units::is_base_v<BASE> && (DIM > 0))
    struct vector {

        
        // ===========================================================
        // aliases
        // ===========================================================

            using type = vector<BASE, DIM>;

            using base = BASE;
            
            using value_type = physics::measurement<BASE>;


        // ===========================================================
        // constructors
        // ===========================================================

            /// @brief Construct a default vector 
            inline constexpr vector() noexcept {

                this->data_.fill(value_type());

            }


            /**
             * @brief Construct a new vector from a pack of measurements
             * 
             * @param vec: list of all the vector components
             * 
             * @note The number of components must be the same as the dimesion of the vector
             */
            template <typename... MEAS>
            constexpr vector(const MEAS&... measurements) noexcept requires (physics::are_measurements_v<MEAS...> && (sizeof...(measurements) == DIM)) : 
                
                data_{std::forward<value_type>(measurements)...} {}


            /**
             * @brief Construct a new vector from a pack of measurements
             * 
             * @param vec: list of all the vector components
             * 
             * @note The number of components must be the same as the dimesion of the vector
             */
            template <typename... MEAS>
            constexpr vector(MEAS&&... measurements) noexcept requires (physics::are_measurements_v<MEAS...> && (sizeof...(measurements) == DIM)) : 
                
                data_{std::forward<value_type>(std::move(measurements))...} {}


            /**
             * @brief Copy construct a new vector from a vector object 
             * 
             * @param other: std::array<value_type, DIM> as l-value const reference
             */
            constexpr vector(const std::array<value_type, DIM>& other) noexcept : 
                
                data_(other) {}


            /**
             * @brief Copy construct a new vector from a vector object 
             * 
             * @param other: std::array<value_type, DIM> as r-value reference
             */
            constexpr vector(std::array<value_type, DIM>&& other) noexcept : 
                
                data_(std::move(other)) {}


            /**
             * @brief Copy construct a new vector from a vector object 
             * 
             * @param other: vector as l-value const reference
             */
            vector(const vector& other) noexcept : 
                
                data_(other.data_) {}


            /**
             * @brief Move construct a new vector from a vector object
             * 
             * @param other: vector as r-value reference
             */
            constexpr vector(vector&& other) noexcept : 
                
                data_(std::move(other.data_)) {}


        // ===========================================================
        // operators
        // ===========================================================

            /**
             * @brief Access the i-th element of the vector
             * 
             * @param index: std::size_t
             * 
             * @return constexpr value_type
             * 
             * @note: index must be in the range [0, DIM)
             */
            constexpr const value_type& operator[](const std::size_t& index) const { 
                
                if (index >= DIM) 
                    throw std::out_of_range("Cannot access a vector with an index out of range");
                    
                return this->data_[index]; 
                
            }


            /**
             * @brief Access the i-th element of the vector
             * 
             * @param index: std::size_t 
             * 
             * @return constexpr value_type& 
             * 
             * @note: index must be in the range [0, DIM)
             */
            constexpr value_type& operator[](const std::size_t& index) { 
                
                if (index >= DIM) 
                    throw std::out_of_range("Cannot access a vector with an index out of range");

                return this->data_[index]; 
                
            }


            /**
             * @brief Equality operator
             * 
             * @param other: vector as l-value const reference
             */
            constexpr bool operator==(const vector& other) const noexcept {

                for (std::size_t i{}; i < DIM; ++i)
                    if (this->data_[i] != other.data_[i]) 
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
                    if (this->data_[i] != other.data_[i]) 
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

                this->data_ = other.data_; 

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
                
                this->data_ = std::move(other.data_); 

                return *this; 

            }


            /**
             * @brief Add two vectors
             * 
             * @param vec: vector to add
             * 
             * @return vector&: reference to the vector
             */
            constexpr vector& operator+=(const vector& vec) noexcept {

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data_[i] += vec.data_[i];

                return *this;

            }


            /**
             * @brief Subtract two vectors
             * 
             * @param vec: vector to subtract
             * 
             * @return vector&: reference to the vector
             */
            constexpr vector& operator-=(const vector& vec) noexcept {

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data_[i] -= vec.data_[i];

                return *this;

            }

            /**
             * @brief Multiply the current vector by a scalar
             * 
             * @param scal: scalar as l-value const reference
             * 
             * @return constexpr vector& 
             */
            constexpr vector& operator*=(const scalar& scal) noexcept {

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data_[i] *= scal;

                return *this; 

            }


            /**
             * @brief Multiply the current vector by a scalar
             * 
             * @param scal: scalar as r-value reference
             * 
             * @return constexpr vector& 
             */
            constexpr vector& operator*=(scalar&& scal) noexcept {

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data_[i] *= scal;

                return *this; 

            }


            /**
             * @brief Divide the current vector by a scalar
             * 
             * @param scal: scalar as l-value const reference
             *  
             * @return constexpr vector& 
             */
            constexpr vector& operator/=(const scalar& scal) {

                if (scal == 0.0) 
                    throw std::runtime_error("Cannot divide a vector by zero");

                for (std::size_t i{}; i < DIM; ++i)
                    this->data_[i] /= scal;
                
                return *this; 
                
            }


            /**
             * @brief Divide the current vector by a scalar
             * 
             * @param scal: scalar as r-value reference
             *  
             * @return constexpr vector& 
             */
            constexpr vector& operator/=(scalar&& scal) {

                if (scal == 0.0) 
                    throw std::runtime_error("Cannot divide a vector by zero");

                for (std::size_t i{}; i < DIM; ++i)
                    this->data_[i] /= scal;
                
                return *this; 
                
            }


            /**
             * @brief Return the opposite of the current vector
             * 
             * @return constexpr vector 
             */
            constexpr vector operator-() const noexcept {

                std::array<value_type, DIM> result; 
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

                std::array<value_type, DIM> result; 
                for (std::size_t i{}; i < DIM; ++i)
                    result[i] = this->data_[i] + other.data_[i]; 
                
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

                std::array<value_type, DIM> result; 
                for (std::size_t i{}; i < DIM; ++i)
                    result[i] = this->data_[i] - other.data_[i]; 
                
                return result;

            }


            /**
             * @brief Multiply the current vector by a measurement
             * 
             * @param meas: measurement as l-value const reference
             * 
             * @return constexpr vector 
             */
            template <typename MEAS>
            constexpr auto operator*(const MEAS& meas) const noexcept -> vector<physics::units::base_prod_t<BASE, typename MEAS::base>, DIM> {

                std::array<physics::units::base_prod_t<BASE, typename MEAS::base>, DIM> result; 
                for (std::size_t i{}; i < DIM; ++i)
                    result[i] = this->data_[i] * meas; 
                
                return result;
            
            }


            /**
             * @brief Multiply the current vector by a measurement
             * 
             * @param meas: measurement as r-value reference
             * 
             * @return constexpr vector 
             */
            template <typename MEAS>
            constexpr auto operator*(MEAS&& meas) const noexcept -> vector<physics::units::base_prod_t<BASE, typename MEAS::base>, DIM> {

                std::array<physics::units::base_prod_t<BASE, typename MEAS::base>, DIM> result; 
                for (std::size_t i{}; i < DIM; ++i)
                    result[i] = this->data_[i] * meas; 
                
                return result;
            
            }


            /**
             * @brief Multiply the current vector by a measurement
             * 
             * @param meas: measurement as l-value const reference
             * 
             * @return constexpr vector 
             */
            template <typename MEAS>
            constexpr vector<physics::units::base_div_t<BASE, typename MEAS::base>, DIM> operator/(const MEAS& meas) const noexcept {

                std::array<physics::measurement<physics::units::base_div_t<BASE, typename MEAS::base>>, DIM> result; 
                for (std::size_t i{}; i < DIM; ++i)
                    result[i] = this->data_[i] / meas; 
                
                return result;
            
            }


            /**
             * @brief Multiply the current vector by a measurement
             * 
             * @param meas: measurement as r-value reference
             * 
             * @return constexpr vector 
             */
            template <typename MEAS>
            constexpr auto operator/(MEAS&& meas) const noexcept -> vector<physics::units::base_div_t<BASE, typename MEAS::base>, DIM> {

                std::array<physics::measurement<physics::units::base_div_t<BASE, typename MEAS::base>>, DIM> result; 
                for (std::size_t i{}; i < DIM; ++i)
                    result[i] = this->data_[i] / meas; 
                
                return result;
            
            }


            /// @brief Print the vector to an output stream
            friend std::ostream& operator<<(std::ostream& os, const vector& vec) {

                os << "( ";
                for (std::size_t i{}; i < DIM; ++i) {

                    vec.data_[i].print(false); 
                    os << ((i < DIM - 1) ? ", " : " )\n"); 

                }

                return os;

            }
            
        
        // ===========================================================
        // methods
        // ===========================================================

            /**
             * @brief Get the vector magnitude
             * 
             * @return constexpr value_type 
             */
            inline constexpr value_type magnitude() const noexcept {

                physics::measurement<physics::units::base_square_t<BASE>> result; 
                for (std::size_t i{}; i < DIM; ++i)
                    result += math::op::square(this->data_[i]); 

                return math::op::sqrt(result);

            }


            /**
             * @brief Get the normal vector 
             * 
             * @return constexpr vector<units::unitless> 
             */
            inline constexpr vector<physics::units::unitless, DIM> normalize() const noexcept {

                return *this / this->magnitude();

            }


            /**
             * @brief Get the vector components
             * 
             * @return const std::array<value_type, DIM>&: vector components
             */
            inline constexpr std::array<value_type, DIM>& data() noexcept {

                return this->data_;

            }


            /**
             * @brief Get the vector components
             * 
             * @return const std::array<value_type, DIM>&: vector components
             */
            inline constexpr const std::array<value_type, DIM>& data() const noexcept {

                return this->data_;

            }


            /// @brief Print the vector components
            inline constexpr void print() const noexcept {
                
                std::cout << "( ";
                for (std::size_t i{}; i < DIM; ++i) 
                    std::cout << this->data_[i] << ((i < DIM - 1) ? ", " : " )\n"); 

            }


            template <typename UNITS, typename = std::enable_if_t<physics::units::is_unit_v<UNITS>>>
            inline constexpr void print(const UNITS& units) const noexcept {
                
                std::cout << "( ";
                for (std::size_t i{}; i < DIM; ++i) {

                    this->data_[i].print(units, false); 
                    std::cout << ((i < DIM - 1) ? ", " : " )\n"); 

                }

            }
            

        // ===========================================================
        // members
        // ===========================================================

            std::array<physics::measurement<BASE>, DIM> data_;

            inline static constexpr std::size_t dimension = DIM;


    }; // struct vector


    template <typename T, typename... MEAS>
    vector(const MEAS&... measurements) -> vector<T, sizeof...(measurements)>; 

    template <typename T, typename... MEAS>
    vector(MEAS&&... measurements) -> vector<T, sizeof...(measurements)>; 


    // template <template <unit_base UB> class... measurements_type, unit_base UB>
    // vector(measurements_type<UB>&&... measurements) -> vector<UB, sizeof...(measurements)>; 


} // namespace scipp::geometry