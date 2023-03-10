/**
 * @file    geometry/vector.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-10
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::geometry {


    template <typename MEAS, std::size_t DIM>
        requires (physics::is_measurement_v<MEAS> || physics::is_umeasurement_v<MEAS>)
    struct vector {

        
        // ===========================================================
        // aliases
        // ===========================================================
            
            using measurement_type = MEAS;

            using data_type = std::array<measurement_type, DIM>;

            using type = vector<measurement_type, DIM>;


        // ===========================================================
        // members
        // ===========================================================

            inline static constexpr std::size_t dim = DIM;

            std::array<measurement_type, DIM> data_;


        // ===========================================================
        // constructors
        // ===========================================================

            /// @brief Default constructor 
            constexpr vector() noexcept = default;
            

            /// @brief Construct a new vector from a pack of measurements
            /// @note The number of components must be the same as the dimension of the vector
            template <typename... MEAS2>
                requires (physics::are_same_measurements_v<measurement_type, MEAS2...>)
            constexpr vector(MEAS2&... measurements) noexcept 
                requires (sizeof...(measurements) == DIM) : 
                
                data_{std::forward<measurement_type>(measurements)...} {}


            /// @brief Construct a new vector from a pack of measurements
            /// @note The number of components must be the same as the dimension of the vector
            template <typename... MEAS2>
                requires (physics::are_same_measurements_v<measurement_type, MEAS2...>)
            constexpr vector(MEAS2&&... measurements) noexcept 
                requires (sizeof...(measurements) == DIM) : 
                
                data_{std::forward<measurement_type>(std::move(measurements))...} {}


            /// @brief Copy constructor
            constexpr vector(const vector& other) noexcept : 
                
                data_(other.data_) {}


            /// @brief Move constructor
            constexpr vector(vector&& other) noexcept : 
                
                data_(std::move(other.data_)) {}


        // ===========================================================
        // operators
        // ===========================================================

            /// @brief Copy assignment operator
            constexpr vector& operator=(const vector& other) noexcept {

                this->data_ = other.data_; 

                return *this; 

            }

            
            /// @brief Move assignment operator
            constexpr vector& operator=(vector&& other) noexcept {
                
                this->data_ = std::move(other.data_); 

                return *this; 

            }


            /// @brief Access the i-th element of the vector
            /// @note: index must be in the range [0, DIM)
            constexpr const measurement_type& operator[](const std::size_t& index) const { 
                
                if (index >= DIM) 
                    throw std::out_of_range("Cannot access a vector with an index out of range");
                    
                return this->data_[index]; 
                
            }


            /// @brief Access the i-th element of the vector
            /// @note: index must be in the range [0, DIM)
            constexpr measurement_type& operator[](const std::size_t& index) { 
                
                if (index >= DIM) 
                    throw std::out_of_range("Cannot access a vector with an index out of range");

                return this->data_[index]; 
                
            }


            /// @brief Equality operator
            constexpr bool operator==(const vector& other) const noexcept {

                for (std::size_t i{}; i < DIM; ++i)
                    if (this->data_[i] != other.data_[i]) 
                        return false;
                
                return true;

            }


            /// @brief Inequality operator
            constexpr bool operator!=(const vector& other) const noexcept {

                for (std::size_t i{}; i < DIM; ++i) 
                    if (this->data_[i] != other.data_[i]) 
                        return true;

                return false;

            }  


            /// @brief Addition operator
            constexpr vector operator+=(const vector& other) noexcept {

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data_[i] += other.data_[i];

                return *this;

            }


            /// @brief Addition operator
            constexpr vector operator-=(const vector& other) noexcept {

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data_[i] -= other.data_[i];

                return *this;
                
            }


            /// @brief Addition operator
            constexpr vector operator+(const vector& other) const noexcept {

                vector result{*this};

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data_[i] += other.data_[i];

                return result;

            }


            /// @brief Subtraction operator
            constexpr vector operator-(const vector& other) const noexcept {

                vector result{*this};

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data_[i] -= other.data_[i];

                return result;

            }


            /// @brief Multiplicate by a scalar
            constexpr vector& operator*=(const double& scalar) noexcept {

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data_[i] *= scalar;

                return *this;

            }

            /// @brief Divide by a scalar
            constexpr vector& operator/=(const double& scalar) {

                if (scalar == 0.0) 
                    throw std::invalid_argument("Cannot divide a vector by zero");

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data_[i] /= scalar;

                return *this;

            }


            /// @brief Multiplicate by a scalar
            constexpr vector operator*(const double& scalar) const noexcept {

                vector result{*this};

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data_[i] *= scalar;

                return result;

            }


            /// @brief Divide by a scalar
            constexpr vector operator/(const double& scalar) const {

                if (scalar == 0.0) 
                    throw std::invalid_argument("Cannot divide a vector by zero");

                vector result{*this};

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data_[i] /= scalar;

                return result;

            }


            /// @brief Multiply the vector by a measurement
            template <typename MEAS2>
                requires (physics::is_measurement_v<MEAS2> || physics::is_umeasurement_v<MEAS2>)
            constexpr auto operator*(const MEAS2& measurement) const noexcept
                -> vector<physics::measurement_prod_t<measurement_type, MEAS2>, DIM> {

                vector<physics::measurement_prod_t<measurement_type, MEAS2>, DIM> result;

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data_[i] = this->data_[i] * measurement;

                return result;
            
            }


            /// @brief Divide the vector by a measurement
            template <typename MEAS2>
                requires (physics::is_measurement_v<MEAS2> || physics::is_umeasurement_v<MEAS2>)
            constexpr auto operator/(const MEAS2& measurement) const noexcept
                -> vector<physics::measurement_div_t<measurement_type, MEAS2>, DIM> {

                vector<physics::measurement_div_t<measurement_type, MEAS2>, DIM> result;

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data_[i] = this->data_[i] / measurement;

                return result;
            
            }


            /// @brief Negate the vector
            constexpr vector operator-() const noexcept {

                vector result{*this};

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data_[i] *= -1.0; 

                return result;

            }         


            /// @brief Print the vector to an output stream
            friend std::ostream& operator<<(std::ostream& os, const vector& vec) noexcept {

                os << "(\t";
                for (std::size_t i{}; i < DIM; ++i) 
                    os << vec[i] << "\t\t";
                os << ')';

                return os;

            }
            
        
        // ===========================================================
        // methods
        // ===========================================================

            /// @brief Get the begin() const iterator
            /// @return constexpr measurement_type& const 
            constexpr measurement_type& begin() const noexcept {

                return this->data_.begin();

            }


            /// @brief Get the begin() iterator
            /// @return constexpr measurement_type&
            constexpr measurement_type& begin() noexcept {

                return this->data_.begin();

            }


            /// @brief Get the end() iterator
            /// @return constexpr measurement_type&
            constexpr measurement_type& end() const noexcept {

                return this->data_.end();

            }


            /// @brief Get the end() iterator
            /// @return constexpr measurement_type&
            constexpr measurement_type& end() noexcept {

                return this->data_.end();

            }


            /**
             * @brief Get the vector components
             * 
             * @return const std::array<measurement_type, DIM>&: vector components
             */
            constexpr std::array<measurement_type, DIM>& data() noexcept {

                return this->data_;

            }


            /// @brief get the vector components as an std::array of measurements
            constexpr const std::array<measurement_type, DIM>& data() const noexcept {

                return this->data_;

            }


            /// @brief Get the first element of the vector
            constexpr auto x() const noexcept {

                return this->data_[0];

            }


            /// @brief Get the first element of the vector
            constexpr auto x() noexcept {

                return this->data_[0];

            }


            /// @brief Get the second element of the vector
            constexpr auto y() const noexcept 
                requires (DIM >= 1) {

                return this->data_[1];

            }


            /// @brief Get the second element of the vector
            constexpr auto y() noexcept 
                requires (DIM >= 1) {

                return this->data_[1];

            }


            /// @brief Get the third element of the vector
            constexpr auto z() const noexcept 
                requires (DIM >= 2) {

                return this->data_[2];

            }


            /// @brief Get the third element of the vector
            constexpr auto z() noexcept 
                requires (DIM >= 2) {

                return this->data_[2];

            }


            /// @brief Get the forth element of the vector
            constexpr auto w() const noexcept 
                requires (DIM >= 3) {

                return this->data_[3];

            }


            /// @brief Get the forth element of the vector
            constexpr auto w() noexcept 
                requires (DIM >= 3) {

                return this->data_[3];

            }


            /// @brief Print the vector components
            constexpr void print() const noexcept {
                
                std::cout << "( ";
                for (std::size_t i{}; i < DIM; ++i) 
                    std::cout << this->data_[i] << ((i < DIM - 1) ? ", " : " )\n"); 

            }


            /// @brief Print the vector components in a specific unit of measurement
            template <typename UNITS, typename = std::enable_if_t<physics::is_unit_v<UNITS>>>
            constexpr void print_as(const UNITS& units) const noexcept {
                
                std::cout << "( ";
                for (std::size_t i{}; i < DIM; ++i) {

                    this->data_[i].print_as(units, false); 
                    std::cout << ((i < DIM - 1) ? ", " : " )\n"); 

                }

            }
            

    }; // struct vector


    template <typename MEAS_TYPE, typename... MEAS>
        requires (physics::are_same_measurements_v<MEAS_TYPE, MEAS...>)
    vector(MEAS&... measurements) 
        -> vector<MEAS_TYPE, sizeof...(measurements)>; 

    template <typename MEAS_TYPE, typename... MEAS>
        requires (physics::are_same_measurements_v<MEAS_TYPE, MEAS...>)
    vector(MEAS&&... measurements) 
        -> vector<MEAS_TYPE, sizeof...(measurements)>; 


    template <typename... MEAS>
        requires (physics::are_same_measurements_v<MEAS...>)
    vector(MEAS&... measurements) 
        -> vector<std::common_type_t<MEAS...>, sizeof...(measurements)>;


    template <typename... MEAS>
        requires (physics::are_same_measurements_v<MEAS...>)
    vector(MEAS&&... measurements) 
        -> vector<std::common_type_t<MEAS...>, sizeof...(measurements)>;


    template <typename MEAS_TYPE, typename... MEAS> 
        requires (physics::are_same_measurements_v<MEAS_TYPE, MEAS...>)
    inline constexpr auto make_vector(MEAS&... measurements) noexcept 
        -> vector<MEAS_TYPE, sizeof...(measurements)> {
        
        return {std::forward<MEAS_TYPE>(measurements)...};

    }


    template <typename... MEAS> 
        requires (physics::are_same_measurements_v<MEAS...>)
    inline constexpr auto make_vector(MEAS&... measurements) noexcept 
        -> vector<std::common_type_t<MEAS...>, sizeof...(measurements)> {
        
        return {std::forward<std::common_type_t<MEAS...>>(measurements)...};

    }


    template <typename T>
    struct is_vector : std::false_type {};

    template <typename MEAS_TYPE, std::size_t DIM> 
        requires (physics::is_measurement_v<MEAS_TYPE> || physics::is_umeasurement_v<MEAS_TYPE>)
    struct is_vector<vector<MEAS_TYPE, DIM>> : std::true_type {};

    template <typename T>
    constexpr bool is_vector_v = is_vector<T>::value;


    template <typename... Ts>
    struct are_vectors : std::conjunction<is_vector<Ts>...> {};

    template <typename... VECTORS>
    constexpr bool are_vectors_v = are_vectors<VECTORS...>::value;


    // template <typename VECTOR_TYPE, typename... VECTORS>
    //     requires (are_vectors_v<VECTOR_TYPE, VECTORS...>)
    // struct have_same_dimension : std::conjunction<VECTOR_TYPE::dim == VECTORS...::dim> {};

    // template <typename... VECTORS>
    // constexpr bool have_same_dimension_v = have_same_dimension<VECTORS...>::value;



    // template <typename VECTOR>
    // struct common_dimension<VECTOR> {

    //     static constexpr size_t value = VECTOR::dim;

    // };

    // template <typename VECTOR, typename... VECTORS>
    //     requires (are_vectors_v<VECTOR, VECTORS...>)
    // struct common_dimension<VECTOR, VECTORS...> {

    //     static constexpr size_t value = std::min({VECTOR::dim, common_dimension<VECTORS...>::value});
    
    // };

    // template <typename... VECTORS>
    // constexpr size_t common_dimension_v = common_dimension<VECTORS...>::value;



    template <typename... VECTORS>
    struct common_base;

    template <typename VECTOR>
    struct common_base<VECTOR> {

        using type = typename VECTOR::base;

    };

    template <typename VECTOR, typename... VECTORS>
        requires (are_vectors_v<VECTOR, VECTORS...>)
    struct common_base<VECTOR, VECTORS...> {

        using type = std::common_type_t<typename VECTOR::base, typename common_base<VECTORS...>::type>;
    
    };

    template <typename... VECTORS>
    using common_base_t = typename common_base<VECTORS...>::type;


} // namespace scipp::geometry