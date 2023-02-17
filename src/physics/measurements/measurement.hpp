/**
 * @file    base.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    /// @brief        The measurement class is a template class that represents a measurement of a physical quantity
    /// @tparam BASE: The base of the measurement
    /// @see          units::unit_base 
    template <typename BASE> requires (units::is_base_v<BASE>)
    struct measurement {


        // ==============================================
        // aliases
        // ==============================================

            using type = measurement<BASE>; ///< The type of the measurement

            using base = BASE; ///< The base of the measurement


        // ==============================================
        // members
        // ==============================================

            scalar value; ///< The value of the measurement


        // ==============================================
        // constructors
        // ==============================================

            /// @brief Default constructor
            constexpr measurement() noexcept : 
                
                value{0.0} {}


            /// @brief Construct a measurement from a scalar value
            /// @param val: The value of the measurement
            constexpr measurement(const scalar& val) noexcept : 
                
                value{val} {}


            /// @brief Construct a measurement from a scalar value
            /// @param val: The value of the measurement
            constexpr measurement(scalar&& val) noexcept : 
                
                value{std::move(val)} {}


            /// @brief Construct a measurement from a scalar value and an unit
            /// @param val: The value of the measurement
            /// @param UNITS: The unit of the measurement
            /// @note The unit must be of the same base of the measurement
            template <typename UNITS> requires (units::is_same_base_v<BASE, typename UNITS::base>)
            constexpr measurement(const scalar& val, const UNITS&) noexcept :
            
                value{val * UNITS::mult} {}


            /// @brief Construct a measurement from a scalar value and an unit
            /// @param val: The value of the measurement
            /// @param UNITS: The unit of the measurement
            /// @note The unit must be of the same base of the measurement
            template <typename UNITS> requires (units::is_same_base_v<BASE, typename UNITS::base>)
            constexpr measurement(scalar&& val, const UNITS&) noexcept :
            
                value{std::move(val * UNITS::mult)} {}


        // ==============================================
        // operators
        // ==============================================

            /// @brief Check if this measurement is equal to another measurement
            inline constexpr bool operator==(const measurement& meas) const noexcept {

                return this->value == meas.value; 

            }
            
            
            /// @brief Check if this measurement is equal to another measurement
            inline constexpr bool operator!=(const measurement& meas) const noexcept {

                return this->value != meas.value; 

            }


            /// @brief Check if this measurement is greater than another measurement
            inline constexpr bool operator>(const measurement& meas) const noexcept {

                return this->value > meas.value; 

            }


            /// @brief Check if this measurement is less than another measurement
            inline constexpr bool operator<(const measurement& meas) const noexcept {

                return this->value < meas.value; 

            }


            /// @brief Check if this measurement is greater or equal to another measurement
            inline constexpr bool operator>=(const measurement& meas) const noexcept {

                return this->value >= meas.value; 

            }


            /// @brief Check if this measurement is less or equal to another measurement
            inline constexpr bool operator<=(const measurement& meas) const noexcept {

                return this->value <= meas.value; 

            }
            

            /// @brief Add a measurement to the current measurement
            inline constexpr measurement& operator+=(const measurement& rhs) noexcept { 
                
                this->value += rhs.value;

                return *this;  
                
            }


            /// @brief Subtract a measurement to the current measurement
            inline constexpr measurement& operator-=(const measurement& rhs) noexcept { 
                
                this->value -= rhs.value;

                return *this;  

            }

            
            /// @brief Add two measurements
            inline constexpr measurement operator+(const measurement& rhs) const noexcept { 
                
                return this->value + rhs.value; 
                
            }


            /// @brief Subtract two measurements
            inline constexpr measurement operator-(const measurement& rhs) const noexcept { 
                
                return this->value - rhs.value; 
                
            }


            /// @brief Negate a measurement
            inline constexpr measurement operator-() const noexcept { 

                return -this->value; 

            }


            /// @brief Multiply two measurements
            template <typename BASE2> requires (units::is_base_v<BASE2>)
            inline constexpr measurement<units::base_prod_t<BASE, BASE2>> operator*(const measurement<BASE2>& other) const noexcept { 
                
                return this->value * other.value; 
                
            }


            /// @brief Divide two measurements
            template <typename BASE2> requires (units::is_base_v<BASE2>)
            inline constexpr measurement<units::base_div_t<BASE, BASE2>> operator/(const measurement<BASE2>& other) const { 

                if (other.value == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by a zero measurement");

                return this->value / other.value; 
                
            }
        

            inline constexpr measurement operator*(const scalar& val) const noexcept {

                return this->value * val; 

            }


            friend inline constexpr measurement operator*(const scalar& val, const measurement& meas) noexcept {

                return val * meas.value; 
                
            }


            inline constexpr measurement operator/(const scalar& val) const {

                if (val == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by zero");

                return this->value / val; 

            }



            friend inline constexpr measurement<units::base_inv_t<BASE>> operator/(const scalar& val, const measurement& meas) {

                if (val == 0.0) 
                    throw std::runtime_error("Cannot divide a scalar by a zero measurement");

                return val / meas.value; 
                
            }


            /// @brief Print a measurement to an output stream
            friend inline constexpr std::ostream& operator<<(std::ostream& os, const measurement& meas) noexcept { 
                
                return os << meas.value << ' ' << BASE::to_string();
                
            }
            
        
        // ==============================================
        // methods
        // ==============================================

            /// @brief  Get the value of the measurement in the specified unit
            /// @param  UNITS: The unit in which the value is returned
            /// @note   The unit must be of the same base of the measurement
            /// @return scalar 
            template <typename UNITS> requires (units::is_same_base_v<BASE, typename UNITS::base>)
            inline constexpr scalar value_as(const UNITS&) const noexcept { 
                
                return this->value / UNITS::mult; 
                
            }

            
            // /// @brief Convert a value from one unit to another 
            // template <typename UNITS> requires (units::is_same_base_v<BASE, typename UNITS::base>)
            // inline constexpr measurement convert(const UNITS&) const noexcept {

            //     return *this / UNITS::mult; 

            // }
                
            
            /// @brief Print the measurement to the standard output
            /// @param newline: If true (default case), a newline character is printed at the end of the measurement
            inline constexpr void print(const bool& newline = true) const noexcept {

                std::cout << this->value << ' ' << BASE::to_string() << (newline ? '\n' : ' '); 

            }
            

            /// @brief Print the measurement to the standard output
            /// @param units: The unit in which the value is printed
            /// @param newline: If true (default case), a newline character is printed at the end of the measurement
            /// @note The unit must be of the same base of the measurement
            template <typename UNITS> requires (units::is_unit_v<UNITS> && units::is_same_base_v<BASE, typename UNITS::base>)
            inline constexpr void print(const UNITS& units, const bool& newline = true) const noexcept {

                std::cout << this->value_as(units) << ' ' << UNITS::to_string() << (newline ? '\n' : ' '); 

            }
            

    }; // struct measurement


    template <typename UNITS> requires (units::is_unit_v<UNITS>)
    measurement(const scalar&, const UNITS&) -> measurement<typename UNITS::base>;


    /// @brief Multiply a scalar with an unit to get a measurement
    template <typename UNITS> requires (units::is_unit_v<UNITS>)
    inline constexpr measurement<typename UNITS::base> operator*(const scalar& val, const UNITS&) noexcept { 
        
        return val * UNITS::mult; 
        
    }


    template <typename T>
    struct is_measurement : std::false_type {};

    template <typename BASE>
    struct is_measurement<measurement<BASE>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_measurement_v = is_measurement<T>::value;


    template <typename... Ts>
    struct are_measurements : std::conjunction<is_measurement<Ts>...> {};

    template <typename... Ts>
    inline constexpr bool are_measurements_v = are_measurements<Ts...>::value;


        
    // template <typename MEAS_TYPE1, typename MEAS_TYPE2> requires (are_measurements_v<MEAS_TYPE1, MEAS_TYPE2>)
    // struct are_same_measurements : units::is_same_base<typename MEAS_TYPE1::base, typename MEAS_TYPE2::base> {};
    

    // template <typename MEAS_TYPE1, typename MEAS_TYPE2> requires (are_measurements_v<MEAS_TYPE1, MEAS_TYPE2>)
    // inline constexpr bool are_same_measurements_v = are_same_measurements<MEAS_TYPE1, MEAS_TYPE2>::value;


    // template <typename T, typename... Ts> requires (are_measurements_v<Ts...>)
    // struct are_same_measurements : are_same_measurements<T, Ts...> {};

        // template <typename MEAS_TYPE1, typename MEAS_TYPE2> requires (are_measurements_v<MEAS_TYPE1, MEAS_TYPE2>)
        // struct measurement_prod {

        //     using type = measurement<units::base_prod_t<typename MEAS_TYPE1::base, typename MEAS_TYPE2::base>>;

        //     using base = units::base_prod_t<typename MEAS_TYPE1::base, typename MEAS_TYPE2::base>;

        // }
        

        // template<typename MEAS_TYPE, typename... MEAS_TYPES>
        // struct measurement_product {

        //     using type = units::base_prod_t<typename MEAS_TYPE::base, typename measurement_product<MEAS_TYPES...>::base>;

        //     using base = typename type::base;

        // };


        // template<typename MEAS_TYPE>
        // struct measurement_product<MEAS_TYPE> {

        //     using type = MEAS_TYPE;

        // };


        // template<typename MEAS_TYPE, typename... MEAS_TYPES>
        // using measurement_prod_t = typename measurement_product<MEAS_TYPE, MEAS_TYPES...>::type;



        template <typename T, typename... Ts>
        struct common_base;

        template <typename T>
        struct common_base<T> {

            using type = typename T::base;

        };      

        template <typename T, typename U, typename... Ts>
        struct common_base<T, U, Ts...> {

            using type = std::conditional_t<units::is_same_base_v<typename T::base, typename U::base>, typename T::base, void>;
        
        };

        template <typename T, typename U>
        struct common_base<T, U> {

            using type = std::conditional_t<units::is_same_base_v<typename T::base, typename U::base>, typename T::base, void>;
        
        };

        template <typename... Ts>
        using common_base_t = typename common_base<Ts...>::type;



} // namespace scipp::physics