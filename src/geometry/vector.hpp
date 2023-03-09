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


    template <typename MEAS, std::size_t DIM>
        requires (physics::is_measurement_v<MEAS> || physics::is_umeasurement_v<MEAS>)
    struct vector {

        
        // ===========================================================
        // aliases
        // ===========================================================
            
            using measurement_type = MEAS;

            using data_type = std::array<measurement_type, DIM>;

            using type = vector<MEAS, DIM>;


        // ===========================================================
        // members
        // ===========================================================

            inline static constexpr std::size_t dimension = DIM;

            std::array<measurement_type, DIM> data_;


        // ===========================================================
        // constructors
        // ===========================================================

            /// @brief Construct a default vector 
            constexpr vector() noexcept = default;
            

            /**
             * @brief Construct a new vector from a pack of measurements
             * 
             * @param vec: list of all the vector components
             * 
             * @note The number of components must be the same as the dimesion of the vector
             */
            template <typename... MEAS2>
                requires (physics::are_measurements_v<MEAS2...> && physics::are_same_measurements_v<measurement_type, MEAS2...>)
            constexpr vector(const MEAS2&... measurements) noexcept 
                requires (sizeof...(measurements) == DIM) : 
                
                data_{std::forward<measurement_type>(measurements)...} {}


            /**
             * @brief Construct a new vector from a pack of measurements
             * 
             * @param vec: list of all the vector components
             * 
             * @note The number of components must be the same as the dimesion of the vector
             */
            template <typename... MEAS2>
                requires (physics::are_measurements_v<MEAS2...> && physics::are_same_measurements_v<measurement_type, MEAS2...>)
            constexpr vector(MEAS2&&... measurements) noexcept 
                requires (sizeof...(measurements) == DIM) : 
                
                data_{std::forward<measurement_type>(std::move(measurements))...} {}


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


        // ===========================================================
        // operators
        // ===========================================================

            /**
             * @brief Access the i-th element of the vector
             * 
             * @param index: std::size_t
             * 
             * @return constexpr measurement_type
             * 
             * @note: index must be in the range [0, DIM)
             */
            constexpr const measurement_type& operator[](const std::size_t& index) const { 
                
                if (index >= DIM) 
                    throw std::out_of_range("Cannot access a vector with an index out of range");
                    
                return this->data_[index]; 
                
            }


            /**
             * @brief Access the i-th element of the vector
             * 
             * @param index: std::size_t 
             * 
             * @return constexpr measurement_type& 
             * 
             * @note: index must be in the range [0, DIM)
             */
            constexpr measurement_type& operator[](const std::size_t& index) 
        { 
                
                if (index >= DIM) 
                    throw std::out_of_range("Cannot access a vector with an index out of range");

                return this->data_[index]; 
                
            }


            /**
             * @brief Equality operator
             * 
             * @param other: vector as l-value const reference
             */
            constexpr bool operator==(const vector& other) const noexcept 
            {

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
            constexpr bool operator!=(const vector& other) const noexcept 
            {

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
            constexpr vector& operator=(const vector& other) 
            noexcept 
            {

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
            constexpr vector& operator=(vector&& other) 
            noexcept 
            {
                
                this->data_ = std::move(other.data_); 

                return *this; 

            }


            /// @brief Print the vector to an output stream
            friend std::ostream& operator<<(std::ostream& os, const vector& vec) 
            noexcept 
            {

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
            /// @return constexpr measurement_type& const 
            constexpr measurement_type& begin() const noexcept 
            {

                return this->data_.begin();

            }


            /// @brief Get the begin() iterator
            /// @return constexpr measurement_type&
            constexpr measurement_type& begin() 
            noexcept 
            {

                return this->data_.begin();

            }


            /// @brief Get the end() iterator
            /// @return constexpr measurement_type&
            constexpr measurement_type& end() const noexcept 
            {

                return this->data_.end();

            }


            /// @brief Get the end() iterator
            /// @return constexpr measurement_type&
            constexpr measurement_type& end() 
            noexcept 
            {

                return this->data_.end();

            }


            /**
             * @brief Get the vector components
             * 
             * @return const std::array<measurement_type, DIM>&: vector components
             */
            constexpr std::array<measurement_type, DIM>& data() 
            noexcept 
            {

                return this->data_;

            }


            /**
             * @brief Get the vector components
             * 
             * @return const std::array<measurement_type, DIM>&: vector components
             */
            constexpr const std::array<measurement_type, DIM>& data() const noexcept 
            {

                return this->data_;

            }


            /// @brief Print the vector components
            constexpr void print() const noexcept 
            {
                
                std::cout << "( ";
                for (std::size_t i{}; i < DIM; ++i) 
                    std::cout << this->data_[i] << ((i < DIM - 1) ? ", " : " )\n"); 

            }


            template <typename UNITS, typename = std::enable_if_t<physics::is_unit_v<UNITS>>>
            constexpr void print(const UNITS& units) const noexcept 
            {
                
                std::cout << "( ";
                for (std::size_t i{}; i < DIM; ++i) 
            {

                    this->data_[i].print(units, false); 
                    std::cout << ((i < DIM - 1) ? ", " : " )\n"); 

                }

            }
            

    }; // struct vector


    template <typename T, typename... MEAS>
    vector(const MEAS&... measurements) -> vector<T, sizeof...(measurements)>; 

    template <typename T, typename... MEAS>
    vector(MEAS&&... measurements) -> vector<T, sizeof...(measurements)>; 


    template <typename T>
    struct is_vector : std::false_type {};

    template <typename BASE, std::size_t DIM> 
        requires (physics::is_base_v<BASE> && (DIM > 0))
    struct is_vector<vector<BASE, DIM>> : std::true_type {};

    template <typename T>
    constexpr bool is_vector_v = is_vector<T>::value;


    template <typename... VECTORS>
    struct are_vectors : std::false_type {};

    template <typename... BASES, size_t DIM>
    struct are_vectors<vector<BASES, DIM>...> : std::true_type {};

    template <typename... VECTORS>
    constexpr bool are_vectors_v = are_vectors<VECTORS...>::value;


} // namespace scipp::geometry