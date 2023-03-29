/**
 * @file    geometry/vector.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the vector struct and its type traits.
 * @date    2023-03-24
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief geometry namespace contains all the classes and functions of the geometry library
namespace scipp::geometry {


    template <typename MEAS_TYPE, std::size_t DIM>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    struct vector {

        
        // ===========================================================
        // aliases
        // ===========================================================
            
            using measurement_type = MEAS_TYPE;

            using data_type = std::array<measurement_type, DIM>;

            using type = vector<measurement_type, DIM>;


        // ===========================================================
        // members
        // ===========================================================

            inline static constexpr std::size_t dim = DIM;

            std::array<measurement_type, DIM> data;

            inline static constexpr vector zero = vector(); 

            inline static constexpr vector one = vector(std::array<measurement_type, DIM>{measurement_type::one});


        // ===========================================================
        // constructors
        // ===========================================================

            /// @brief Default constructor 
            constexpr vector() noexcept : 

                data{} {}
            

            /// @brief Construct a new vector from a pack of measurements
            /// @note The number of components must be the same as the dimension of the vector
            template <typename... MEAS2>
                requires (physics::are_same_measurements_v<measurement_type, MEAS2...>)
            constexpr vector(MEAS2&... measurements) noexcept 
                requires (sizeof...(measurements) == DIM) : 
                
                data{std::forward<measurement_type>(measurements)...} {}


            /// @brief Construct a new vector from a pack of measurements
            /// @note The number of components must be the same as the dimension of the vector
            template <typename... MEAS2>
                requires (physics::are_same_measurements_v<measurement_type, MEAS2...>)
            constexpr vector(MEAS2&&... measurements) noexcept 
                requires (sizeof...(measurements) == DIM) : 
                
                data{std::forward<measurement_type>(std::move(measurements))...} {}


            /// @brief Copy constructor from an std::array
            constexpr vector(const std::array<measurement_type, DIM>& other) noexcept : 
                
                data(other.data) {}


            /// @brief Move constructor
            constexpr vector(std::array<measurement_type, DIM>&& other) noexcept : 
                
                data(std::move(other)) {}


            /// @brief Copy constructor
            constexpr vector(const vector& other) noexcept : 
                
                data(other.data) {}


            /// @brief Move constructor
            constexpr vector(vector&& other) noexcept : 
                
                data(std::move(other.data)) {}

            
            /// @brief Destructor
            ~vector() noexcept = default;
            

        // ===========================================================
        // operators
        // ===========================================================

            /// @brief Copy assignment operator
            constexpr vector& operator=(const vector& other) noexcept {

                this->data = other.data; 

                return *this; 

            }

            
            /// @brief Move assignment operator
            constexpr vector& operator=(vector&& other) noexcept {
                
                this->data = std::move(other.data); 

                return *this; 

            }


            /// @brief Access the i-th element of the vector
            /// @note: index must be in the range [0, DIM)
            constexpr const measurement_type& operator[](const std::size_t& index) const { 
                
                if (index >= DIM) 
                    throw std::out_of_range("Cannot access a vector with an index out of range");
                    
                return this->data[index]; 
                
            }


            /// @brief Access the i-th element of the vector
            /// @note: index must be in the range [0, DIM)
            constexpr measurement_type& operator[](const std::size_t& index) { 
                
                if (index >= DIM) 
                    throw std::out_of_range("Cannot access a vector with an index out of range");

                return this->data[index]; 
                
            }


            /// @brief Equality operator
            constexpr bool operator==(const vector& other) const noexcept {

                for (std::size_t i{}; i < DIM; ++i)
                    if (this->data[i] != other.data[i]) 
                        return false;
                
                return true;

            }


            /// @brief Inequality operator
            constexpr bool operator!=(const vector& other) const noexcept {

                for (std::size_t i{}; i < DIM; ++i) 
                    if (this->data[i] != other.data[i]) 
                        return true;

                return false;

            }  


            /// @brief Addition operator
            constexpr vector operator+=(const vector& other) noexcept {

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data[i] += other.data[i];

                return *this;

            }


            /// @brief Addition operator
            constexpr vector operator-=(const vector& other) noexcept {

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data[i] -= other.data[i];

                return *this;
                
            }


            /// @brief Addition operator
            constexpr vector operator+(const vector& other) const noexcept {

                vector result{*this};

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data[i] += other.data[i];

                return result;

            }

            /// @brief Addition operator
            constexpr vector operator+(vector&& other) const noexcept {

                vector result{*this};

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data[i] += std::move(other).data[i];

                return result;

            }


            /// @brief Subtraction operator
            constexpr vector operator-(const vector& other) const noexcept {

                vector result{*this};

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data[i] -= other.data[i];

                return result;

            }


            /// @brief Negation operator
            constexpr vector operator-() const noexcept {

                vector result;

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data[i] = -this->data[i];

                return result;

            }
            

            /// @brief Multiply this vector by a scalar measurement
            constexpr vector& operator*=(const physics::scalar_m& meas) noexcept {

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data[i] *= meas;

                return *this;

            }

            /// @brief Multiply this vector by a scalar measurement
            constexpr vector& operator*=(physics::scalar_m&& meas) noexcept {

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data[i] *= std::move(meas);

                return *this;

            }


            /// @brief Divide this vector by a scalar measurement
            constexpr vector& operator/=(const physics::scalar_m& meas) {

                if (meas.value == 0.0) 
                    throw std::invalid_argument("Cannot divide a vector by zero");

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data[i] /= meas;

                return *this;

            }

            /// @brief Divide this vector by a scalar measurement
            constexpr vector& operator/=(physics::scalar_m&& meas) {

                if (meas.value == 0.0) 
                    throw std::invalid_argument("Cannot divide a vector by zero");

                for (std::size_t i{}; i < DIM; ++i) 
                    this->data[i] /= std::move(meas);

                return *this;

            }


            /// @brief Multiplicate by a scalar
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const OTHER_MEAS_TYPE& meas) const noexcept
                -> vector<math::op::measurements_prod_t<MEAS_TYPE, OTHER_MEAS_TYPE>, DIM> {

                vector<math::op::measurements_prod_t<MEAS_TYPE, OTHER_MEAS_TYPE>, DIM> result;

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data[i] = this->data[i] * meas;

                return result;

            }

            /// @brief Multiplicate by a scalar
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(OTHER_MEAS_TYPE&& meas) const noexcept
                -> vector<math::op::measurements_prod_t<MEAS_TYPE, OTHER_MEAS_TYPE>, DIM> {

                vector<math::op::measurements_prod_t<MEAS_TYPE, OTHER_MEAS_TYPE>, DIM> result;

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data[i] = this->data[i] * std::move(meas);

                return result;

            }

            /// @brief Divide a vector by a measurement 
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(const OTHER_MEAS_TYPE& meas) const
                -> vector<math::op::measurements_div_t<MEAS_TYPE, OTHER_MEAS_TYPE>, DIM> {

                if (meas.value == 0.0) 
                    throw std::invalid_argument("Cannot divide a vector by a zero measurement");

                vector<math::op::measurements_div_t<MEAS_TYPE, OTHER_MEAS_TYPE>, DIM> result;

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data[i] = this->data[i] / meas;

                return result;

            }

            /// @brief Divide a vector by a measurement 
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(OTHER_MEAS_TYPE&& meas) const
                -> vector<math::op::measurements_div_t<MEAS_TYPE, OTHER_MEAS_TYPE>, DIM> {
                
                if (meas.value == 0.0) 
                    throw std::invalid_argument("Cannot divide a vector by a zero measurement");

                vector<math::op::measurements_div_t<MEAS_TYPE, OTHER_MEAS_TYPE>, DIM> result;

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data[i] = this->data[i] / std::move(meas);

                return result;

            }


            /// @brief Multiply a measureent by a vector
            template <typename MEAS2>
                requires (physics::is_generic_measurement_v<MEAS2>)
            friend constexpr auto operator*(const MEAS2& meas, const vector& vec) noexcept
                -> vector<math::op::measurements_prod_t<MEAS2, MEAS_TYPE>, DIM> {

                vector<math::op::measurements_prod_t<MEAS2, MEAS_TYPE>, DIM> result;

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data[i] = meas * vec.data[i];

                return result;
            
            }

            /// @brief Divide a measurement by a vector
            template <typename MEAS2>
                requires (physics::is_generic_measurement_v<MEAS2>)
            friend constexpr auto operator/(const MEAS2& meas, const vector& vec) noexcept
                -> vector<math::op::measurements_div_t<MEAS2, MEAS_TYPE>, DIM> {

                vector<math::op::measurements_div_t<MEAS2, MEAS_TYPE>, DIM> result;

                for (std::size_t i{}; i < DIM; ++i) 
                    result.data[i] = meas / vec.data[i];

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
            
            /// @brief Print the vector to an output stream
            friend std::ofstream& operator<<(std::ofstream& os, const vector& vec) noexcept {

                os << "(\t";
                for (std::size_t i{}; i < DIM; ++i) 
                    os << vec[i] << "\t\t";
                os << ')';

                return os;

            }
            
        
        // ===========================================================
        // methods
        // ===========================================================

            /// @brief Get the first element of the vector
            constexpr measurement_type x() const noexcept {

                return this->data[0];

            }

            /// @brief Get the first element of the vector
            constexpr measurement_type x() noexcept {

                return this->data[0];

            }

            /// @brief Get the second element of the vector
            constexpr measurement_type y() const noexcept 
                requires (DIM >= 1) {

                return this->data[1];

            }

            /// @brief Get the second element of the vector
            constexpr measurement_type y() noexcept 
                requires (DIM >= 1) { 

                return this->data[1];

            }

            /// @brief Get the third element of the vector
            constexpr measurement_type z() const noexcept 
                requires (DIM >= 2) { 

                return this->data[2];

            }

            /// @brief Get the third element of the vector
            constexpr measurement_type z() noexcept 
                requires (DIM >= 2) { 

                return this->data[2];

            }

            /// @brief Get the forth element of the vector
            constexpr measurement_type w() const noexcept 
                requires (DIM >= 3) { 

                return this->data[3];

            }

            /// @brief Get the forth element of the vector
            constexpr measurement_type w() noexcept 
                requires (DIM >= 3) { 

                return this->data[3];

            }


            /// @brief Get the magnitude of the vector
            constexpr measurement_type magnitude() const noexcept {

                measurement_type result;

                for (std::size_t i{}; i < DIM; ++i) 
                    result += math::op::square(this->data[i]); 

                return result;

            }


            // /// @brief Get the projection of a vector on the current vector
            // template <unit_base UB2>
            // constexpr vector<UB * UB2, DIM> projection(const vector<UB2, DIM>& vec) const noexcept {

            //     return dot(vec, *this) * (*this  / this->norm2()); 

            // }


            /// @brief Get the polar angle
            /// @note the vector must have at least two elements
            constexpr auto polar_angle() const 
                -> std::conditional_t<physics::is_umeasurement_v<measurement_type>, 
                                      physics::umeasurement<physics::units::radian>,
                                      physics::measurement<physics::units::radian>> {

                if constexpr (DIM < 2) 
                    throw std::out_of_range("Cannot access the polar angle of a vector with less than two elements"); 
                
                return math::op::atan(this->data[1] / this->data[0]); 
            
            }     
            

            // /// @brief Get the azimuthal angle
            // /// @note the vector must have at least three elements
            // constexpr auto azimuthal_angle() const 
            //     -> std::conditional_t<physics::is_umeasurement_v<measurement_type>, 
            //                           physics::umeasurement<physics::units::radian>,
            //                           physics::measurement<physics::units::radian>> {
                
            //     if constexpr (DIM < 3) 
            //         throw std::out_of_range("Cannot access the azimuthal angle of a vector with less than three elements"); 
                
            //     return math::op::acos(this->data[2] / norm(*this));

            // }
            

            // /// @brief Get the angle between two vectors
            // template <typename MEAS2>
            //     requires (DIM == 2 || DIM == 3)
            // friend constexpr physics::angle_m angle_between(const vector& v1, 
            //                                                 const vector<MEAS2, DIM>& v2) noexcept {

            //     return math::op::acos(dot(v1, v2) / (norm(v1) * norm(v2)));

            // }
            

            /// @brief Print the vector components
            constexpr void print() const noexcept {
                
                std::cout << "( ";
                for (std::size_t i{}; i < DIM; ++i) 
                    std::cout << this->data[i] << ((i < DIM - 1) ? ", " : " )\n"); 

            }


            /// @brief Print the vector components in a specific unit of measurement
            template <typename UNITS>
                requires (physics::is_unit_v<UNITS>)
            constexpr void print_as(const UNITS& units) const noexcept {
                
                std::cout << "( ";
                for (std::size_t i{}; i < DIM; ++i) {

                    this->data[i].print_as(units, false); 
                    std::cout << ((i < DIM - 1) ? ", " : " )\n"); 

                }

            }
            

    }; // struct vector


    template <typename... MEAS>
        requires (physics::are_same_measurements_v<MEAS...>)
    vector(const MEAS&... measurements) 
        -> vector<std::common_type_t<MEAS...>, sizeof...(measurements)>;

    template <typename... MEAS>
        requires (physics::are_same_measurements_v<MEAS...>)
    vector(MEAS&... measurements) 
        -> vector<std::common_type_t<MEAS...>, sizeof...(measurements)>;

    template <typename... MEAS>
        requires (physics::are_same_measurements_v<MEAS...>)
    vector(MEAS&&... measurements) 
        -> vector<std::common_type_t<MEAS...>, sizeof...(measurements)>;


    template <typename... MEAS> 
        requires (physics::are_same_measurements_v<MEAS...>)
    inline constexpr auto make_vector(MEAS&... measurements) noexcept 
        -> vector<std::common_type_t<MEAS...>, sizeof...(measurements)> {
        
        return { std::forward<std::common_type_t<MEAS...>>(measurements)... };

    }

    template <typename... MEAS> 
        requires (physics::are_same_measurements_v<MEAS...>)
    inline constexpr auto make_vector(MEAS&&... measurements) noexcept 
        -> vector<std::common_type_t<MEAS...>, sizeof...(measurements)> {
        
        return { std::forward<std::common_type_t<MEAS...>>(measurements)... };

    }


    template <typename T>
    struct is_vector : std::false_type {};

    template <typename MEAS_TYPE, std::size_t DIM> 
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    struct is_vector<vector<MEAS_TYPE, DIM>> : std::true_type {};

    template <typename T>
    constexpr bool is_vector_v = is_vector<T>::value;


    template <typename... Ts>
    struct are_vectors : std::conjunction<is_vector<Ts>...> {};

    template <typename... VECTORS>
    constexpr bool are_vectors_v = are_vectors<VECTORS...>::value;


    template <typename VECTOR_TYPE, typename... VECTORS>
        requires (are_vectors_v<VECTOR_TYPE, VECTORS...>)
    struct are_same_vectors : std::conjunction<std::bool_constant<VECTOR_TYPE::dim == VECTORS::dim>..., 
                                               std::bool_constant<physics::are_same_measurements_v<typename VECTOR_TYPE::measurement_type, 
                                                                                                   typename VECTORS::measurement_type>>...> {};

    template <typename... VECTORS>  
    constexpr bool are_same_vectors_v = are_same_vectors<VECTORS...>::value;


    template <typename VECTOR_TYPE, typename... VECTORS>
        requires (are_vectors_v<VECTOR_TYPE, VECTORS...>)
    struct have_same_dimension : std::conjunction<std::bool_constant<VECTOR_TYPE::dim == VECTORS::dim>...> {};

    // template <>
    // struct have_same_dimension<> : std::true_type {};

    template <typename... VECTORS>
    constexpr bool have_same_dimension_v = have_same_dimension<VECTORS...>::value;


    template <typename... Ts>
    struct common_dimension : std::integral_constant<std::size_t, 0> {};

    template <typename VECTOR_TYPE>
        requires (is_vector_v<VECTOR_TYPE>)
    struct common_dimension<VECTOR_TYPE> : std::integral_constant<std::size_t, VECTOR_TYPE::dim> {};

    template <typename VECTOR_TYPE, typename... VECTORS>
        requires (have_same_dimension_v<VECTOR_TYPE, VECTORS...>)
    struct common_dimension<VECTOR_TYPE, VECTORS...> : std::integral_constant<std::size_t, VECTOR_TYPE::dim> {};

    template <typename... VECTORS>
    constexpr std::size_t common_dimension_v = common_dimension<VECTORS...>::value;


    template <typename T, typename... Us>
    struct has_same_vector;

    template <typename T>
    struct has_same_vector<T> : std::false_type {};

    template <typename T, typename... Us>
    struct has_same_vector<T, T, Us...> : std::true_type {};

    template <typename T, typename U, typename... Us>
    struct has_same_vector<T, U, Us...> : has_same_vector<T, Us...> {};


    template <typename T, typename... Us>
    struct have_same_vectors : std::conjunction<has_same_vector<T, Us>..., has_same_vector<Us, T>...> {};

    template <typename T>
    struct have_same_vectors<T> : std::true_type {};

    template <typename... VECTORS>
    constexpr bool have_same_vectors_v = have_same_vectors<VECTORS...>::value;


    // template <typename... VECTORS>
    // struct common_vector;

    // template <typename VECTOR>
    // struct common_vector<VECTOR> {

    //     using type = VECTOR;

    // };

    // template <typename VECTOR, typename... VECTORS>
    //     requires (are_vectors_v<VECTOR, VECTORS...>)
    // struct common_vector<VECTOR, VECTORS...> {

    //     using type = std::common_type_t<VECTOR, typename common_vector<VECTORS...>::type>;
    
    // };


    // template <typename... VECTORS>
    // struct common_base;

    // template <typename VECTOR>
    // struct common_base<VECTOR> {

    //     using type = typename VECTOR::base;

    // };

    // template <typename VECTOR, typename... VECTORS>
    //     requires (are_vectors_v<VECTOR, VECTORS...>)
    // struct common_base<VECTOR, VECTORS...> {

    //     using type = std::common_type_t<typename VECTOR::base, typename common_base<VECTORS...>::type>;
    
    // };

    // template <typename... VECTORS>
    // using common_base_t = typename common_base<VECTORS...>::type;


} // namespace scipp::geometry