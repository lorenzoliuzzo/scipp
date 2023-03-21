/**
 * @file    geometry/row_vector.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-15
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::geometry {


    /// @brief The row_vector class is a template class that represents a row vector in a n-dimensional space
    /// @tparam DIM: The dimension of the vector
    /// @tparam MEAS_TYPES: The types of the measurements of the vector components
    /// @see physics::measurement
    template <std::size_t DIM, typename... MEAS_TYPES> 
        requires (physics::are_measurements_v<MEAS_TYPES...>) 
    struct row_vector {

        
        // ===========================================================
        // aliases
        // ===========================================================

            using type = row_vector<DIM, MEAS_TYPES...>; ///< The type of the vector
            

        // ===========================================================
        // members
        // ===========================================================

            std::tuple<MEAS_TYPES...> data_; ///< The data of the vector


            inline static constexpr std::size_t dim = DIM; ///< The dimension of the vector


        // ===========================================================
        // constructors
        // ===========================================================

            /// @brief Construct a default vector 
            constexpr row_vector() noexcept = default;
            

            /// @brief Construct a new vector from a pack of measurements
            /// @param measurements: list of all the vector components
            /// @note The number of components must be the same as the dimesion of the vector
            constexpr row_vector(MEAS_TYPES&&... measurements) noexcept 

                : data_{std::forward<MEAS_TYPES>(measurements)...} {}


            /// @brief Construct a new vector from a vector object
            /// @param other: vector as l-value const reference
            constexpr row_vector(const row_vector& other) noexcept 

                : data_{other.data_} {}


            /// @brief Construct a new vector from a vector object
            /// @param other: vector as r-value reference
            constexpr row_vector(row_vector&& other) noexcept 

                : data_{std::move(other.data_)} {}


        // ===========================================================
        // operators
        // ===========================================================

            /// @brief Copy assignment operator
            /// @param other: vector as l-value const reference
            constexpr row_vector& operator=(const row_vector& other) noexcept {

                this->data_ = other.data_;
                return *this;

            }


            /// @brief Move assignment operator
            /// @param other: vector as r-value reference
            constexpr row_vector& operator=(row_vector&& other) noexcept {

                this->data_ = std::move(other.data_);
                return *this;

            }


            /// @brief Equality operator
            /// @param other: vector as l-value const reference
            constexpr bool operator==(const row_vector& other) const noexcept {

                return this->data_ == other.data_;

            }


            /// @brief Inequality operator
            /// @param other: vector as l-value const reference
            constexpr bool operator!=(const row_vector& other) const noexcept {

                return this->data_ != other.data_;

            }


            /// @brief Increment the vector by another vector
            /// @param other: geometry::row_vector<DIM, MEAS_TYPES...> as l-value const reference
            /// @return geometry::row_vector<DIM, MEAS_TYPES...>&
            constexpr row_vector<DIM, MEAS_TYPES...>& operator+=(const row_vector& other) noexcept {

                std::apply([&](auto&... lhs_components) { 
                    std::apply([&](auto&... rhs_components) { 

                        ((lhs_components += rhs_components), ...);

                    }, other.data_);
                }, this->data_);

                return *this;

            }


            /// @brief Decrement the vector by another vector
            /// @param other: geometry::row_vector<DIM, MEAS_TYPES...> as l-value const reference
            /// @return geometry::row_vector<DIM, MEAS_TYPES...>&
            constexpr row_vector<DIM, MEAS_TYPES...>& operator-=(const row_vector& other) noexcept {

                std::apply([&](auto&... lhs_components) { 
                    std::apply([&](auto&... rhs_components) { 

                        ((lhs_components -= rhs_components), ...);

                    }, other.data_);
                }, this->data_);

                return *this;

            }


            // /// @brief Multiply the vector by a measurement
            // /// @param other: physics::measurement as l-value const reference
            // /// @return geometry::row_vector<DIM, MEAS_TYPES... * measurement>&
            // /// @note this not use the std::apply function because it is not possible to multiply a tuple of measurements
            // template <typename MEAS_TYPE> 
            //     requires (physics::is_measurement_v<MEAS_TYPE>)
            // constexpr    auto operator*(const MEAS_TYPE& other)
            // const noexcept 
            //     -> row_vector<DIM, physics::multiply_each_t<MEAS_TYPE, MEAS_TYPES...>>
            // {

            //     row_vector<DIM, physics::multiply_each_t<MEAS_TYPE, MEAS_TYPES...>> result;


            //     // auto [this_components...] = this->data_;
            //     // auto [result_components...] = result.data_;

            //     // ((result_components = this_components * other), ...);

            //     return result;

            // }


            /// @brief Print the vector to an output stream
            /// @param os: std::ostream as l-value reference
            /// @param vec: vector as l-value const reference
            friend constexpr std::ostream& operator<<(std::ostream& os, const row_vector& vec) noexcept {

                os << "(\t"; 
                std::apply([&os](const auto&... measurements) { ((os << measurements << "\t"), ...); }, vec.data_);
                os << ")\n";
                return os;

            }
            

            /// @brief Print the vector to an output stream
            /// @param os: std::ostream as l-value reference
            /// @param vec: vector as l-value const reference
            friend constexpr std::ofstream& operator<<(std::ofstream& os, const row_vector& vec) noexcept {

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
            template <std::size_t INDEX> 
                requires (INDEX < DIM)
            constexpr auto get() const noexcept 
                -> const std::tuple_element_t<INDEX, std::tuple<MEAS_TYPES...>>& {

                return std::get<INDEX>(this->data_);

            }


            /// @brief Get a reference to the i-th element of the vector
            /// @tparam INDEX: std::size_t
            /// @return std::tuple_element_t<INDEX, std::tuple<MEAS_TYPES...>>&
            template <std::size_t INDEX> 
                requires (INDEX < DIM)
            constexpr auto get() noexcept 
                -> std::tuple_element_t<INDEX, std::tuple<MEAS_TYPES...>>& {

                return std::get<INDEX>(this->data_);

            }


            /// @brief Get the first element of the vector
            /// @return const std::tuple_element_t<0, std::tuple<MEAS_TYPES...>>&
            constexpr auto x() const noexcept {

                return std::get<0>(this->data_);

            }


            /// @brief Get the first element of the vector
            /// @return std::tuple_element_t<0, std::tuple<MEAS_TYPES...>>&
            constexpr auto x() noexcept {

                return std::get<0>(this->data_);

            }


            /// @brief Get the second element of the vector
            /// @return const std::tuple_element_t<1, std::tuple<MEAS_TYPES...>>&
            constexpr auto y() const noexcept 
                requires (DIM >= 1) {

                return std::get<1>(this->data_);

            }


            /// @brief Get the second element of the vector
            /// @return std::tuple_element_t<1, std::tuple<MEAS_TYPES...>>&
            constexpr auto y() noexcept 
                requires (DIM >= 1) {

                return std::get<1>(this->data_);

            }


            /// @brief Get the third element of the vector
            /// @return const std::tuple_element_t<2, std::tuple<MEAS_TYPES...>>&
            constexpr auto z() const noexcept 
                requires (DIM >= 2) {

                return std::get<2>(this->data_);

            }


            /// @brief Get the third element of the vector
            /// @return std::tuple_element_t<2, std::tuple<MEAS_TYPES...>>&
            constexpr auto z() noexcept 
                requires (DIM >= 2) {

                return std::get<2>(this->data_);

            }


            /// @brief Get the forth element of the vector
            /// @return const std::tuple_element_t<3, std::tuple<MEAS_TYPES...>>&
            constexpr auto w() const noexcept 
                requires (DIM >= 3) {

                return std::get<3>(this->data_);

            }


            /// @brief Get the forth element of the vector
            /// @return std::tuple_element_t<3, std::tuple<MEAS_TYPES...>>&
            constexpr auto w() noexcept 
                requires (DIM >= 3) {

                return std::get<3>(this->data_);

            }


            /// @brief Get the vector components
            /// @return const std::tuple<MEAS_TYPES...>&
            constexpr const std::tuple<MEAS_TYPES...>& data() const noexcept {

                return this->data_;

            }


            /// @brief Get the vector components
            /// @return std::tuple<MEAS_TYPES...>&
            constexpr std::tuple<MEAS_TYPES...>& data() noexcept {

                return this->data_;

            }


            /// @brief Print the vector components
            constexpr void print() const noexcept {

                std::cout << "(\t";
                std::apply([](const auto&... args) { ((std::cout << args << '\t'), ...); }, this->data_);
                std::cout << ")\n";

            }
           

    }; // struct row_vector


    // /// @brief traspose a column vector into a row vector
    // /// @tparam DIM: std::size_t
    // /// @tparam MEAS_TYPES: typename...
    // /// @param vec: column_vector<DIM, MEAS_TYPES...> as l-value const reference
    // /// @return row_vector<DIM, MEAS_TYPES...>
    // template <std::size_t DIM, typename MEAS_TYPE>
    //     requires (physics::is_measurement_v<MEAS_TYPE> || physics::is_umeasurement_v<MEAS_TYPE>)
    // constexpr auto transpose(const vector<MEAS_TYPE, DIM>& vec) noexcept
    //     -> row_vector<DIM, MEAS_TYPE> {

    //     row_vector<DIM, MEAS_TYPE> result;

    //     std::apply([&](const auto&... components) { 
    //         std::apply([&](auto&... result_components) { 

    //             ((result_components = components), ...);

    //         }, result.data_);
    //     }, vec.data);

    //     return result;

    // }


    // template <std::size_t DIM, typename... MEAS_TYPES>
    //     requires (physics::are_measurements_v<MEAS_TYPES>)
    // constexpr auto operator+(const row_vector<DIM, MEAS_TYPES...>& lhs, const row_vector<DIM, MEAS_TYPES...>& rhs) noexcept 
    //     -> row_vector<DIM, physics::add_each_t<MEAS_TYPES...>> {

    //     row_vector<DIM, physics::add_each_t<MEAS_TYPES...>> result;

    //     std::apply([&](const auto&... lhs_components) { 
    //         std::apply([&](const auto&... rhs_components) { 
    //             std::apply([&](auto&... result_components) { 

    //                 ((result_components = lhs_components + rhs_components), ...);

    //             }, result.data_);
    //         }, rhs.data_);
    //     }, lhs.data_);

    //     return result;

    // }



} // namespace scipp::geometry