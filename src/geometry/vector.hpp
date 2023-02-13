/**
 * @file    geometry/vector.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-11
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::geometry {


    /// @brief The vector class is a template class that represents a vector in a n-dimensional space
    /// @tparam DIM: The dimension of the vector
    /// @tparam MEAS_TYPES: The types of the measurements of the vector components
    /// @see physics::measurement
    template <std::size_t DIM, typename... MEAS_TYPES> requires (physics::are_measurements_v<MEAS_TYPES...>) 
    struct vector2 {

        
        // ===========================================================
        // aliases
        // ===========================================================

            using type = vector2<DIM, MEAS_TYPES...>; ///< The type of the vector


        // ===========================================================
        // members
        // ===========================================================

            std::tuple<MEAS_TYPES...> data_; ///< The data of the vector


            inline static constexpr std::size_t dimension = DIM; ///< The dimension of the vector


        // ===========================================================
        // constructors
        // ===========================================================

            /// @brief Construct a default vector 
            inline constexpr vector2() noexcept = default;
            

            /// @brief Construct a new vector from a pack of measurements
            /// @param measurements: list of all the vector components
            /// @note The number of components must be the same as the dimesion of the vector
            //  && are_same_measurements_v<ARGS..., MEAS_TYPES...>)
            constexpr vector2(MEAS_TYPES&&... measurements) noexcept : 
                
                data_{std::forward<MEAS_TYPES>(measurements)...} {}


            /// @brief Construct a new vector from a std::tuple of measurements
            /// @param measurements: std::tuple<MEAS_TYPES...> as l-value const reference
            /// @note The number of components must be the same as the dimesion of the vector
            constexpr vector2(const std::tuple<MEAS_TYPES...>& measurements) noexcept requires (std::tuple_size<std::tuple<MEAS_TYPES...>>() == DIM) : 
                
                data_{measurements} {}


            /// @brief Construct a new vector from a std::tuple of measurements
            /// @param measurements: std::tuple<MEAS_TYPES...> as r-value reference
            /// @note The number of components must be the same as the dimesion of the vector
            constexpr vector2(std::tuple<MEAS_TYPES...>&& measurements) noexcept requires (std::tuple_size<std::tuple<MEAS_TYPES...>>() == DIM) : 
                
                data_{std::move(measurements)} {}


            /// @brief Construct a new vector from a std::array of measurements
            /// @param measurements: std::array<MEAS_TYPES, DIM> as l-value const reference
            /// @note The number of components must be the same as the dimesion of the vector
            constexpr vector2(const std::array<physics::common_base_t<MEAS_TYPES...>, DIM>& measurements) noexcept requires (physics::have_same_base_v<MEAS_TYPES...>) : 
                
                data_{measurements} {}


            /// @brief Construct a new vector from a vector object
            /// @param other: vector as l-value const reference
            constexpr vector2(const vector2& other) noexcept : 
                
                data_{other.data_} {}


            /// @brief Construct a new vector from a vector object
            /// @param other: vector as r-value reference
            constexpr vector2(vector2&& other) noexcept : 
                
                data_{std::move(other.data_)} {}


        // ===========================================================
        // operators
        // ===========================================================

            /// @brief Copy assignment operator
            /// @param other: vector as l-value const reference
            inline constexpr vector2& operator=(const vector2& other) noexcept {

                this->data_ = other.data_;

                return *this;

            }


            /// @brief Move assignment operator
            /// @param other: vector as r-value reference
            inline constexpr vector2& operator=(vector2&& other) noexcept {

                this->data_ = std::move(other.data_);

                return *this;

            }


            /// @brief Equality operator
            /// @param other: vector as l-value const reference
            inline constexpr bool operator==(const vector2& other) const noexcept {

                return this->data_ == other.data_;

            }


            /// @brief Inequality operator
            /// @param other: vector as l-value const reference
            inline constexpr bool operator!=(const vector2& other) const noexcept {

                return this->data_ != other.data_;

            }


            /// @brief Print the vector to an output stream
            /// @param os: std::ostream as l-value reference
            /// @param vec: vector as l-value const reference
            friend inline constexpr std::ostream& operator<<(std::ostream& os, const vector2& vec) noexcept {

                os << "(\t"; 
                std::apply([&os](const auto&... measurements) { ((os << measurements << "\t"), ...); }, vec.data_);
                os << ")\n";

                return os;

            }
            
        
        // ===========================================================
        // methods
        // ===========================================================

            /// @brief Get a const reference to the i-th element of the vector
            /// @tparam INDEX: std::size_t
            /// @return const std::tuple_element_t<INDEX, std::tuple<MEAS_TYPES...>>&
            template <std::size_t INDEX> requires (INDEX < DIM)
            inline constexpr auto get() const noexcept -> const std::tuple_element_t<INDEX, std::tuple<MEAS_TYPES...>>& {

                return std::get<INDEX>(this->data_);

            }


            /// @brief Get a reference to the i-th element of the vector
            /// @tparam INDEX: std::size_t
            /// @return std::tuple_element_t<INDEX, std::tuple<MEAS_TYPES...>>&
            template <std::size_t INDEX> requires (INDEX < DIM)
            inline constexpr auto get() noexcept -> std::tuple_element_t<INDEX, std::tuple<MEAS_TYPES...>>& {

                return std::get<INDEX>(this->data_);

            }


            /// @brief Get the vector components
            /// @return const std::tuple<MEAS_TYPES...>&
            inline constexpr const std::tuple<MEAS_TYPES...>& data() const noexcept {

                return this->data_;

            }


            /// @brief Get the vector components
            /// @return std::tuple<MEAS_TYPES...>&
            inline constexpr std::tuple<MEAS_TYPES...>& data() noexcept {

                return this->data_;

            }


            /// @brief Get the first element of the vector
            /// @return const std::tuple_element_t<0, std::tuple<MEAS_TYPES...>>&
            inline constexpr auto x() const noexcept -> const std::tuple_element_t<0, std::tuple<MEAS_TYPES...>>& {

                return std::get<0>(this->data_);

            }


            /// @brief Get the first element of the vector
            /// @return std::tuple_element_t<0, std::tuple<MEAS_TYPES...>>&
            inline constexpr auto x() noexcept -> std::tuple_element_t<0, std::tuple<MEAS_TYPES...>>& {

                return std::get<0>(this->data_);

            }


            /// @brief Get the second element of the vector
            /// @return const std::tuple_element_t<1, std::tuple<MEAS_TYPES...>>&
            inline constexpr auto y() const noexcept requires (DIM >= 1) {

                return std::get<1>(this->data_);

            }


            /// @brief Get the second element of the vector
            /// @return std::tuple_element_t<1, std::tuple<MEAS_TYPES...>>&
            inline constexpr auto y() noexcept requires (DIM >= 1) {

                return std::get<1>(this->data_);

            }


            /// @brief Get the third element of the vector
            /// @return const std::tuple_element_t<2, std::tuple<MEAS_TYPES...>>&
            inline constexpr auto z() const noexcept requires (DIM >= 2) {

                return std::get<2>(this->data_);

            }


            /// @brief Get the third element of the vector
            /// @return std::tuple_element_t<2, std::tuple<MEAS_TYPES...>>&
            inline constexpr auto z() noexcept requires (DIM >= 2) {

                return std::get<2>(this->data_);

            }


            /// @brief Get the forth element of the vector
            /// @return const std::tuple_element_t<3, std::tuple<MEAS_TYPES...>>&
            inline constexpr auto w() const noexcept requires (DIM >= 3) {

                return std::get<3>(this->data_);

            }


            /// @brief Get the forth element of the vector
            /// @return std::tuple_element_t<3, std::tuple<MEAS_TYPES...>>&
            inline constexpr auto w() noexcept requires (DIM >= 3) {

                return std::get<3>(this->data_);

            }


            /// @brief Print the vector components
            inline constexpr void print() const noexcept {

                std::cout << "(\t";
                std::apply([](const auto&... args) { ((std::cout << args << '\t'), ...); }, this->data_);
                std::cout << ")\n";

            }
           

    }; // struct vector2


    template <typename... MEAS_TYPES> requires (scipp::physics::are_measurements_v<MEAS_TYPES...>)
    vector2(MEAS_TYPES&&... measurements) -> vector2<sizeof...(measurements), MEAS_TYPES...>;


    template <typename... MEAS_TYPES> requires (scipp::physics::are_measurements_v<MEAS_TYPES...>)
    vector2(const vector2<sizeof...(MEAS_TYPES), MEAS_TYPES...>&) -> vector2<sizeof...(MEAS_TYPES), MEAS_TYPES...>;


    template <typename... MEAS_TYPES> requires (scipp::physics::are_measurements_v<MEAS_TYPES...>)
    vector2(vector2<sizeof...(MEAS_TYPES), MEAS_TYPES...>&&) -> vector2<sizeof...(MEAS_TYPES), MEAS_TYPES...>;


    template <typename... MEAS_TYPES> requires (scipp::physics::are_measurements_v<MEAS_TYPES...>)
    vector2(const std::tuple<MEAS_TYPES...>&) -> vector2<sizeof...(MEAS_TYPES), MEAS_TYPES...>;


    template <typename... MEAS_TYPES> requires (scipp::physics::are_measurements_v<MEAS_TYPES...>)
    vector2(std::tuple<MEAS_TYPES...>&&) -> vector2<sizeof...(MEAS_TYPES), MEAS_TYPES...>;


    template <std::size_t DIM, typename MEAS_TYPE> requires (scipp::physics::is_measurement_v<MEAS_TYPE>)
    vector2(const std::array<MEAS_TYPE, DIM>&) -> vector2<DIM, MEAS_TYPE>;


    template <std::size_t DIM, typename MEAS_TYPE> requires (scipp::physics::is_measurement_v<MEAS_TYPE>)
    vector2(std::array<MEAS_TYPE, DIM>&) -> vector2<DIM, MEAS_TYPE>;


    template <std::size_t DIM, typename MEAS_TYPE> requires (scipp::physics::is_measurement_v<MEAS_TYPE>)
    vector2(std::array<MEAS_TYPE, DIM>&&) -> vector2<DIM, MEAS_TYPE>;

    
    template <typename... MEAS_TYPES> requires (scipp::physics::are_measurements_v<MEAS_TYPES...>)
    inline constexpr auto make_vector2(MEAS_TYPES&&... measurements) noexcept -> vector2<sizeof...(MEAS_TYPES), MEAS_TYPES...> {
        
        return {std::forward<MEAS_TYPES>(measurements)...};

    }


    template <size_t DIM, typename... MEAS_TYPES> requires (scipp::physics::are_measurements_v<MEAS_TYPES...> && (DIM == sizeof...(MEAS_TYPES)))
    inline constexpr auto make_vector2(MEAS_TYPES&&... measurements) noexcept -> vector2<DIM, MEAS_TYPES...> {
        
        return {std::forward<MEAS_TYPES>(measurements)...};

    }


    template <typename T>
    struct is_vector2 : std::false_type {};

    template <std::size_t DIM, typename... MEAS_TYPES> requires (physics::are_measurements_v<MEAS_TYPES...>)
    struct is_vector2<vector2<DIM, MEAS_TYPES...>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_vector2_v = is_vector2<T>::value;


    template <typename... Ts>
    struct are_vectors2 : std::conjunction<is_vector2<Ts>...> {};

    template <typename... Ts>
    inline constexpr bool are_vectors2_v = are_vectors2<Ts...>::value;


    // template <typename... Ts>
    // struct are_same_vectors2 : std::false_type {};

    // template <typename T, typename... Ts>
    // struct are_same_vectors2<T, Ts...> : std::conjunction<are_vectors2<Ts>, ...> {};

    // template <typename... Ts>
    // inline constexpr bool are_same_vectors2_v = are_same_vectors2<Ts...>::value;


    template <typename... VECTORS>
    struct is_omogeneous : std::false_type {};

    template <std::size_t DIM, typename... MEAS_TYPES> requires (physics::are_measurements_v<MEAS_TYPES...>)
    struct is_omogeneous<vector2<DIM, MEAS_TYPES...>> : physics::have_same_base<MEAS_TYPES...> {};

    template <typename... VECTORS>
    inline constexpr bool is_omogeneous_v = is_omogeneous<VECTORS...>::value;


    template <typename BASE, std::size_t DIM>
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
            inline constexpr vector() noexcept = default;
            

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


            /// @brief Print the vector to an output stream
            friend std::ostream& operator<<(std::ostream& os, const vector& vec) noexcept {

                os << "(\t";
                for (std::size_t i{}; i < DIM; ++i) 
                    os << vec[i] << "\t\t";
                os << ")\n";

                return os;

            }
            
        
        // ===========================================================
        // methods
        // ===========================================================

            /// @brief Get the begin() const iterator
            /// @return constexpr value_type& const 
            inline constexpr value_type& begin() const noexcept {

                return this->data_.begin();

            }


            /// @brief Get the begin() iterator
            /// @return constexpr value_type&
            inline constexpr value_type& begin() noexcept {

                return this->data_.begin();

            }


            /// @brief Get the end() iterator
            /// @return constexpr value_type&
            inline constexpr value_type& end() const noexcept {

                return this->data_.end();

            }


            /// @brief Get the end() iterator
            /// @return constexpr value_type&
            inline constexpr value_type& end() noexcept {

                return this->data_.end();

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
            constexpr void print() const noexcept {
                
                std::cout << "( ";
                for (std::size_t i{}; i < DIM; ++i) 
                    std::cout << this->data_[i] << ((i < DIM - 1) ? ", " : " )\n"); 

            }


            template <typename UNITS, typename = std::enable_if_t<physics::units::is_unit_v<UNITS>>>
            constexpr void print(const UNITS& units) const noexcept {
                
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


    template <typename T>
    struct is_vector : std::false_type {};

    template <typename BASE, std::size_t DIM> requires (physics::units::is_base_v<BASE> && (DIM > 0))
    struct is_vector<vector<BASE, DIM>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_vector_v = is_vector<T>::value;


    template <typename... VECTORS>
    struct are_vectors : std::false_type {};

    template <typename... BASES, size_t DIM>
    struct are_vectors<vector<BASES, DIM>...> : std::true_type {};

    template <typename... VECTORS>
    inline constexpr bool are_vectors_v = are_vectors<VECTORS...>::value;


    template <typename... VECTORS>
    struct common_base;

    template <typename VECTOR>
    struct common_base<VECTOR> {
        using type = typename VECTOR::base;
    };

    template <typename VECTOR, typename... VECTORS>
    struct common_base<VECTOR, VECTORS...> {

        static_assert(are_vectors_v<VECTOR, VECTORS...>, "All types must be vectors");

        using type = std::common_type_t<typename VECTOR::base, typename common_base<VECTORS...>::type>;
    
    };

    template <typename... VECTORS>
    using common_base_t = typename common_base<VECTORS...>::type;


    template <typename... VECTORS>
    struct common_dimention;

    template <typename VECTOR>
    struct common_dimention<VECTOR> {
        static constexpr size_t value = VECTOR::dimension;
    };

    template <typename VECTOR, typename... VECTORS>
    struct common_dimention<VECTOR, VECTORS...> {

        static_assert(are_vectors_v<VECTOR, VECTORS...>, "All types must be vectors");

        static constexpr size_t value = std::min({VECTOR::dimension, common_dimention<VECTORS...>::value});
    
    };

    template <typename... VECTORS>
    inline constexpr size_t common_dimention_v = common_dimention<VECTORS...>::value;



} // namespace scipp::geometry