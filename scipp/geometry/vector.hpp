/**
 * @file    geometry/linear_algebra/vector.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the vector struct and its type traits.
 * @date    2023-04-02
 * 
 * @copyright Copyright (c) 2023
 */





/// @brief geometry namespace contains all the classes and functions of the geometry library
namespace scipp::geometry {


    template <typename MEAS_TYPE, std::size_t DIM>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    struct vector {

        
        // ===========================================================
        // aliases
        // ===========================================================
            
            using _t = vector<MEAS_TYPE, DIM>;

            using data_t = std::array<MEAS_TYPE, DIM>;

            using measurement_t = MEAS_TYPE;


        // ===========================================================
        // members
        // ===========================================================

            inline static constexpr std::size_t dim = DIM;

            data_t data;

            inline static constexpr vector zero = vector(std::array<measurement_t, DIM>{measurement_t::zero}); 

            inline static constexpr vector one = vector(std::array<measurement_t, DIM>{measurement_t::one});


        // ===========================================================
        // constructors
        // ===========================================================

            /// @brief Default constructor 
            constexpr vector() noexcept = default;

            /// @brief Default destructor
            constexpr ~vector() noexcept = default;


            /// @brief Copy constructor
            constexpr vector(const vector& other) noexcept : 
                
                data(other.data) {}

            /// @brief Move constructor
            constexpr vector(vector&& other) noexcept : 
                
                data(std::move(other.data)) {}


            /// @brief Copy constructor from an std::array<measurement_t, dim>
            constexpr vector(const data_t& other) noexcept : 
                
                data(other.data) {}

            /// @brief Move constructor from an std::array<measurement_t, dim>
            constexpr vector(data_t&& other) noexcept : 
                
                data(std::move(other)) {}


            /// @brief Construct a new vector from a pack of measurements
            /// @note The number of components must be the same as the dimension of the vector
            template <typename... OTHER_MEAS_TYPE>
                requires (physics::are_same_measurement_v<measurement_t, OTHER_MEAS_TYPE...>)
            constexpr vector(OTHER_MEAS_TYPE&... other) noexcept 
                requires (sizeof...(other) == dim) : 
                
                data{std::forward<measurement_t>(other)...} {}

            /// @brief Construct a new vector from a pack of measurements
            /// @note The number of components must be the same as the dimension of the vector
            template <typename... OTHER_MEAS_TYPE>
                requires (physics::are_same_measurement_v<measurement_t, OTHER_MEAS_TYPE...>)
            constexpr vector(OTHER_MEAS_TYPE&&... other) noexcept 
                requires (sizeof...(other) == dim) : 
                
                data{std::forward<measurement_t>(std::move(other))...} {}


            /// @brief Construct a new vector from a single measurement
            constexpr vector(const measurement_t& other) noexcept {
                
                this->data.fill(other); 

            }

            /// @brief Construct a new vector from a single measurement
            constexpr vector(measurement_t&& other) noexcept {
                
                this->data.fill(std::move(other)); 

            }
                        

        // ===========================================================
        // operators
        // ===========================================================
            
            /// @brief Convert the vector to an std::vector<double>
            constexpr operator std::vector<double>() const noexcept {

                std::vector<double> vec(dim); 

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               vec.begin(), 
                               [](const measurement_t& meas) { return meas.value; }); 

                return vec; 

            }


            /// @brief Access the i-th element of the vector
            /// @note: index must be in the range [0, dim)
            constexpr const measurement_t& operator[](const std::size_t& index) const { 
                
                if (index >= dim) 
                    throw std::out_of_range("Cannot access a vector with an index out of range");
                    
                return this->data[index]; 
                
            }

            /// @brief Access the i-th element of the vector
            /// @note: index must be in the range [0, dim)
            constexpr measurement_t& operator[](const std::size_t& index) { 
                
                if (index >= dim) 
                    throw std::out_of_range("Cannot access a vector with an index out of range");

                return this->data[index]; 
                
            }


            /// @brief Equality operator
            constexpr bool operator==(const vector& other) const noexcept {

                return std::equal(std::execution::par, this->data.begin(), this->data.end(), other.data.begin());

            }

            /// @brief Inequality operator
            constexpr bool operator!=(const vector& other) const noexcept {

                return !std::equal(std::execution::par, this->data.begin(), this->data.end(), other.data.begin());

            }  


            /// @brief Copy assignment operator from another vector
            constexpr vector& operator=(const vector& other) noexcept {

                this->data = other.data; 
                return *this; 

            }
            
            /// @brief Move assignment operator from another vector
            constexpr vector& operator=(vector&& other) noexcept {
                
                this->data = std::move(other.data); 
                return *this; 

            }


            /// @brief Copy assignment operator from an std::array<measurement_t, dim>
            constexpr vector& operator=(const data_t& other) noexcept {

                this->data = other; 
                return *this; 

            }
            
            /// @brief Move assignment operator from an std::array<measurement_t, dim>
            constexpr vector& operator=(data_t&& other) noexcept {
                
                this->data = std::move(other); 
                return *this; 

            }


            /// @brief Addition operator
            constexpr vector& operator+=(const vector& other) noexcept {

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               other.data.begin(), 
                               this->data.begin(), 
                               std::plus<measurement_t>());

                return *this;

            }

            /// @brief Addition operator
            constexpr vector& operator+=(vector&& other) noexcept {

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               std::move(other).data.begin(), 
                               this->data.begin(), 
                               std::plus<measurement_t>());

                return *this;

            }


            /// @brief Subtraction operator
            constexpr vector& operator-=(const vector& other) noexcept {

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               other.data.begin(), 
                               this->data.begin(), 
                               std::minus<measurement_t>());

                return *this;
                
            }

            /// @brief Subtraction operator
            constexpr vector& operator-=(vector&& other) noexcept {

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               std::move(other).data.begin(), 
                               this->data.begin(), 
                               std::minus<measurement_t>());

                return *this;

            }


            /// @brief Addition operator
            constexpr vector operator+(const vector& other) const noexcept {

                data_t result;
                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               other.data.begin(), 
                               result.begin(), 
                               std::plus<measurement_t>());

                return result;

            }

            /// @brief Addition operator
            constexpr vector operator+(vector&& other) const noexcept {

                data_t result;
                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               other.data.begin(), 
                               result.begin(), 
                               std::plus<measurement_t>());

                return result;

            }


            /// @brief Subtraction operator
            constexpr vector operator-(const vector& other) const noexcept {

                data_t result;
                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               other.data.begin(), 
                               result.begin(), 
                               std::minus<measurement_t>());

                return result;

            }

            /// @brief Subtraction operator
            constexpr vector operator-(vector&& other) const noexcept {

                data_t result;
                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               std::move(other).data.begin(), 
                               result.begin(), 
                               std::minus<measurement_t>());

                return result;

            }


            /// @brief Negation operator
            constexpr vector operator-() const noexcept {

                data_t result; 
                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               result.begin(), 
                               std::negate<measurement_t>()); 

                return result;    

            }


            /// @brief Multiply this vector by a scalar measurement
            constexpr vector& operator*=(const physics::scalar_m& other) noexcept {

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               this->data.begin(), 
                               [&other](measurement_t& x) { return x *= other; });

                return *this;

            }

            /// @brief Multiply this vector by a scalar measurement
            constexpr vector& operator*=(physics::scalar_m&& other) noexcept {

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               this->data.begin(), 
                               [&other](measurement_t& x) { return std::move(x *= other); });

                return *this;

            }


            /// @brief Divide this vector by a scalar measurement
            constexpr vector& operator/=(const physics::scalar_m& other) {

                if (other == physics::scalar_m::zero) 
                    throw std::invalid_argument("Cannot divide a vector by zero");

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               this->data.begin(), 
                               [&other](measurement_t& x) { return x /= other; });

                return *this;

            }

            /// @brief Divide this vector by a scalar measurement
            constexpr vector& operator/=(physics::scalar_m&& other) {

                if (other == physics::scalar_m::zero) 
                    throw std::invalid_argument("Cannot divide a vector by zero");
                
                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               this->data.begin(), 
                               [&other](measurement_t& x) { return std::move(x /= other); });

                return *this;

            }


            /// @brief Multiplicate by a scalar
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const OTHER_MEAS_TYPE& other) const noexcept
                -> vector<math::meta::multiply_t<measurement_t, OTHER_MEAS_TYPE>, dim> {

                std::array<math::meta::multiply_t<measurement_t, OTHER_MEAS_TYPE>, dim> result;

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               result.begin(), 
                               [&other](const measurement_t& x) { return x * other; });

                return result;

            }

            /// @brief Multiplicate by a scalar
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(OTHER_MEAS_TYPE&& other) const noexcept
                -> vector<math::meta::multiply_t<measurement_t, OTHER_MEAS_TYPE>, dim> {

                std::array<math::meta::multiply_t<measurement_t, OTHER_MEAS_TYPE>, dim> result;

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               result.begin(), 
                               [&other](const measurement_t& x) { return std::move(x * other); });

                return result;

            }

            /// @brief Divide a vector by a measurement 
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(const OTHER_MEAS_TYPE& other) const
                -> vector<math::meta::divide_t<measurement_t, OTHER_MEAS_TYPE>, dim> {

                if (other == measurement_t::zero) 
                    throw std::invalid_argument("Cannot divide a vector by a zero measurement");

                std::array<math::meta::divide_t<measurement_t, OTHER_MEAS_TYPE>, dim> result;

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               result.begin(), 
                               [&other](const measurement_t& x) { return x / other; });

                return result;

            }

            /// @brief Divide a vector by a measurement 
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(OTHER_MEAS_TYPE&& other) const
                -> vector<math::meta::divide_t<measurement_t, OTHER_MEAS_TYPE>, dim> {
                
                if (other == OTHER_MEAS_TYPE::zero) 
                    throw std::invalid_argument("Cannot divide a vector by a zero measurement");

                std::array<math::meta::divide_t<measurement_t, OTHER_MEAS_TYPE>, dim> result;

                std::transform(std::execution::par,
                               this->data.begin(), this->data.end(), 
                               result.begin(), 
                               [&other](const measurement_t& x) { return std::move(x / other); });

                return result;

            }


            /// @brief Multiply a measureent by a vector
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            friend constexpr auto operator*(const OTHER_MEAS_TYPE& meas, const vector& vec) noexcept
                -> vector<math::meta::multiply_t<OTHER_MEAS_TYPE, measurement_t>, dim> {

                std::array<math::meta::multiply_t<OTHER_MEAS_TYPE, measurement_t>, dim> result;

                std::transform(std::execution::par,
                               vec.data.begin(), vec.data.end(), 
                               result.begin(), 
                               [&meas](const measurement_t& x) { return meas * x; });

                return result;
            
            }

            /// @brief Divide a measurement by a vector
            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            friend constexpr auto operator/(const OTHER_MEAS_TYPE& meas, const vector& vec) noexcept
                -> vector<math::meta::divide_t<OTHER_MEAS_TYPE, measurement_t>, dim> {
                
                std::array<math::meta::divide_t<OTHER_MEAS_TYPE, measurement_t>, dim> result;

                std::transform(std::execution::par,
                               vec.data.begin(), vec.data.end(), 
                               result.begin(), 
                               [&meas](const measurement_t& x) { return meas / x; });

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

            /// @brief Access the i-th element of the vector
            /// @note: index must be in the range [0, dim)
            template <std::size_t INDEX>
                requires (INDEX < dim)
            constexpr measurement_t& element() noexcept { 
                
                return this->data[INDEX]; 
                
            }


            /// @brief Access the i-th element of the vector
            /// @note: index must be in the range [0, dim)
            template <std::size_t INDEX>
                requires (INDEX < dim)
            constexpr const measurement_t& element() const noexcept { 
                
                return this->data[INDEX]; 
                
            }


            /// @brief Get the first element of the vector
            constexpr measurement_t x() const noexcept {

                return this->data[0];

            }

            /// @brief Get the first element of the vector
            constexpr measurement_t x() noexcept {

                return this->data[0];

            }

            /// @brief Get the second element of the vector
            constexpr measurement_t y() const noexcept 
                requires (DIM >= 1) {

                return this->data[1];

            }

            /// @brief Get the second element of the vector
            constexpr measurement_t y() noexcept 
                requires (DIM >= 1) { 

                return this->data[1];

            }

            /// @brief Get the third element of the vector
            constexpr measurement_t z() const noexcept 
                requires (DIM >= 2) { 

                return this->data[2];

            }

            /// @brief Get the third element of the vector
            constexpr measurement_t z() noexcept 
                requires (DIM >= 2) { 

                return this->data[2];

            }

            /// @brief Get the forth element of the vector
            constexpr measurement_t w() const noexcept 
                requires (DIM >= 3) { 

                return this->data[3];

            }

            /// @brief Get the forth element of the vector
            constexpr measurement_t w() noexcept 
                requires (DIM >= 3) { 

                return this->data[3];

            }


            // /// @brief If the measurement has an uncertainty, get the values vector
            // constexpr auto values() const noexcept 
            //     -> vector<physics::measurement<typename measurement_t::base>, dim> 
            //         requires (physics::is_umeasurement_v<measurement_t>) {

            //     std::array<physics::measurement<typename measurement_t::base>, dim> result;
            //     std::transform(this->data.begin(), this->data.end(), result.begin(), [](const auto& x) { return x.value; });
            //     return result;

            // }

            // /// @brief If the measurement has an uncertainty, get the uncertainties vector
            // constexpr auto uncertainties() const noexcept 
            //     -> vector<physics::measurement<typename measurement_t::base>, dim> 
            //         requires (physics::is_umeasurement_v<measurement_t>) {

            //     std::array<physics::measurement<typename measurement_t::base>, dim> result;
            //     std::transform(this->data.begin(), this->data.end(), result.begin(), [](const auto& x) { return x.uncertainty; });
            //     return result;

            // }


            /// @brief Get the magnitude of the vector
            constexpr measurement_t magnitude() const noexcept {

                return math::op::sqrt(std::accumulate(this->data.begin(), this->data.end(), [](auto acc, auto val) { return acc + math::op::square(val); }, math::meta::square_t<measurement_t>{}));

            }


            // /// @brief Get the projection of a vector on the current vector
            // template <unit_base UB2>
            // constexpr vector<UB * UB2, DIM> projection(const vector<UB2, DIM>& vec) const noexcept {

            //     return dot(vec, *this) * (*this  / this->norm2()); 

            // }


            /// @brief Get the polar angle
            /// @note the vector must have at least two elements
            constexpr auto polar_angle() const {

                if constexpr (DIM < 2) 
                    throw std::out_of_range("Cannot access the polar angle of a vector with less than two elements"); 
                
                else
                    return math::op::atan(this->data[1] / this->data[0]); 
            
            }     
            

            // /// @brief Get the azimuthal angle
            // /// @note the vector must have at least three elements
            // constexpr auto azimuthal_angle() const 
            //     -> std::conditional_t<physics::is_umeasurement_v<measurement_t>, 
            //                           physics::umeasurement<physics::units::radian>,
            //                           physics::measurement<physics::units::radian>> {
                
            //     if constexpr (DIM < 3) 
            //         throw std::out_of_range("Cannot access the azimuthal angle of a vector with less than three elements"); 
                
            //     return math::op::acos(this->data[2] / norm(*this));

            // }
            

            // /// @brief Get the angle between two vectors
            // template <typename OTHER_MEAS_TYPE>
            //     requires (DIM == 2 || DIM == 3)
            // friend constexpr physics::angle_m angle_between(const vector& v1, 
            //                                                 const vector<OTHER_MEAS_TYPE, DIM>& v2) noexcept {

            //     return math::op::acos(dot(v1, v2) / (norm(v1) * norm(v2)));

            // }
            
            

    }; // struct vector


    template <typename... MEAS>
        requires (physics::are_same_measurement_v<MEAS...>)
    vector(const MEAS&... measurements) 
        -> vector<std::common_type_t<MEAS...>, sizeof...(measurements)>;

    template <typename... MEAS>
        requires (physics::are_same_measurement_v<MEAS...>)
    vector(MEAS&... measurements) 
        -> vector<std::common_type_t<MEAS...>, sizeof...(measurements)>;

    template <typename... MEAS>
        requires (physics::are_same_measurement_v<MEAS...>)
    vector(MEAS&&... measurements) 
        -> vector<std::common_type_t<MEAS...>, sizeof...(measurements)>;


    template <typename MEAS_TYPE, std::size_t DIM>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    vector(const std::array<MEAS_TYPE, DIM>& measurements) 
        -> vector<MEAS_TYPE, DIM>;

    template <typename MEAS_TYPE, std::size_t DIM>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    vector(std::array<MEAS_TYPE, DIM>&& measurements) 
        -> vector<MEAS_TYPE, DIM>;


    template <typename... MEAS> 
        requires (physics::are_same_measurement_v<MEAS...>)
    inline constexpr auto make_vector(MEAS&... measurements) noexcept 
        -> vector<std::common_type_t<MEAS...>, sizeof...(measurements)> {
        
        return { std::forward<std::common_type_t<MEAS...>>(measurements)... };

    }

    template <typename... MEAS> 
        requires (physics::are_same_measurement_v<MEAS...>)
    inline constexpr auto make_vector(MEAS&&... measurements) noexcept 
        -> vector<std::common_type_t<MEAS...>, sizeof...(measurements)> {
        
        return { std::forward<std::common_type_t<MEAS...>>(measurements)... };

    }


    template <typename MEAS_TYPE, std::size_t DIM>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    inline constexpr auto make_vector(const std::array<MEAS_TYPE, DIM>& other) noexcept
        -> vector<MEAS_TYPE, DIM> {
        
        return vector<MEAS_TYPE, DIM>(other);

    }
    

    template <typename MEAS_TYPE, std::size_t DIM>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    inline constexpr auto make_random_vector() noexcept
        -> vector<MEAS_TYPE, DIM> {

        vector<MEAS_TYPE, DIM> result;

        for (std::size_t i{}; i < DIM; i++) 
            result.data[i] = std::rand();

        return result;

    }


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


} // namespace scipp::geometry