/**
 * @file    measurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-08-09
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    /// @brief        The measurement class is a template class that represents a measurement of a physical quantity
    /// @tparam BASE: The base of the measurement
    /// @see          units::unit_base 
    template <typename BASE> 
        requires (is_base_v<BASE>)
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
            template <typename UNITS> 
                requires (is_unit_v<UNITS> && is_same_base_v<BASE, typename UNITS::base>)
            constexpr measurement(const scalar& val, const UNITS&) noexcept :

                value{val * UNITS::mult} {}


            /// @brief Construct a measurement from a scalar value and an unit
            /// @param val: The value of the measurement
            /// @param UNITS: The unit of the measurement
            /// @note The unit must be of the same base of the measurement
            template <typename UNITS> 
                requires (is_unit_v<UNITS> && is_same_base_v<BASE, typename UNITS::base>)
            constexpr measurement(scalar&& val, const UNITS&) noexcept :

                value{std::move(val * UNITS::mult)} {}


        // ==============================================
        // operators
        // ==============================================

            /// @brief Check if this measurement is equal to another measurement
            constexpr bool operator==(const measurement& meas) const noexcept {

                return this->value == meas.value; 

            }
            
            
            /// @brief Check if this measurement is equal to another measurement
            constexpr bool operator!=(const measurement& meas) const noexcept {

                return this->value != meas.value; 

            }


            /// @brief Check if this measurement is greater than another measurement
            constexpr bool operator>(const measurement& meas) const noexcept {

                return this->value > meas.value; 

            }


            /// @brief Check if this measurement is less than another measurement
            constexpr bool operator<(const measurement& meas) const noexcept {

                return this->value < meas.value; 

            }


            /// @brief Check if this measurement is greater or equal to another measurement
            constexpr bool operator>=(const measurement& meas) const noexcept {

                return this->value >= meas.value; 

            }


            /// @brief Check if this measurement is less or equal to another measurement
            constexpr bool operator<=(const measurement& meas) const noexcept {

                return this->value <= meas.value; 

            }
            

            /// @brief Add a measurement to the current measurement
            constexpr measurement& operator+=(const measurement& rhs) noexcept { 
                
                this->value += rhs.value;
                return *this;  
                
            }


            /// @brief Subtract a measurement to the current measurement
            constexpr measurement& operator-=(const measurement& rhs) noexcept { 
                
                this->value -= rhs.value;
                return *this;  

            }

            
            /// @brief Add two measurements
            constexpr measurement operator+(const measurement& rhs) const noexcept { 
                
                return this->value + rhs.value; 
                
            }


            /// @brief Subtract two measurements
            constexpr measurement operator-(const measurement& rhs) const noexcept { 
                
                return this->value - rhs.value; 
                
            }


            /// @brief Negate a measurement
            constexpr measurement operator-() const noexcept { 

                return -this->value; 

            }


            /// @brief Multiply two measurements
            template <typename BASE2> 
                requires (is_base_v<BASE2>)
            constexpr auto operator*(const measurement<BASE2>& other) const noexcept 
                -> measurement<base_prod_t<BASE, BASE2>> { 
                
                return this->value * other.value; 
                
            }


            /// @brief Divide two measurements
            template <typename BASE2> 
                requires (is_base_v<BASE2>)
            constexpr auto operator/(const measurement<BASE2>& other) const 
                -> measurement<base_div_t<BASE, BASE2>> {

                if (other.value == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by a zero measurement");

                return this->value / other.value; 
                
            }
        

            constexpr measurement operator*(const scalar& val) const noexcept {

                return this->value * val; 

            }


            constexpr measurement operator/(const scalar& val) const {

                if (val == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by zero");

                return this->value / val; 

            }


            friend constexpr measurement operator*(const scalar& val, const measurement& meas) noexcept {

                return val * meas.value; 
                
            }


            /// @brief Divide a scalar by a measurement
            /// @param val: The scalar value as lvalue const reference
            /// @param meas: The measurement as lvalue const reference
            /// @return measurement<base_inv_t<BASE>>
            friend constexpr auto operator/(const scalar& val, const measurement& meas)
                -> measurement<base_inv_t<BASE>> {

                if (val == 0.0) 
                    throw std::runtime_error("Cannot divide a scalar by a zero measurement");

                return val / meas.value; 
                
            }


            /// @brief Print a measurement to an output stream
            friend constexpr std::ostream& operator<<(std::ostream& os, const measurement& meas) noexcept { 
                
                return os << meas.value << ' ' << BASE::to_string();
                
            }
            
        
        // ==============================================
        // methods
        // ==============================================

            /// @brief  Get the value of the measurement in the specified unit
            /// @param  UNITS: The unit in which the value is returned
            /// @note   The unit must be of the same base of the measurement
            /// @return scalar 
            template <typename UNITS> 
                requires (is_unit_v<UNITS> && is_same_base_v<BASE, typename UNITS::base>)
            constexpr scalar value_as(const UNITS&) const noexcept { 
                
                return this->value / UNITS::mult; 
                
            }
                        
            
            /// @brief Print the measurement to the standard output
            /// @param newline: If true (default case), a newline character is printed at the end of the measurement
            constexpr void print(const bool& newline = true) const noexcept {

                std::cout << this->value << ' ' << BASE::to_string() << (newline ? '\n' : ' '); 

            }
            

            /// @brief Print the measurement to the standard output
            /// @param units: The unit in which the value is printed
            /// @param newline: If true (default case), a newline character is printed at the end of the measurement
            /// @note The unit must be of the same base of the measurement

            template <typename UNITS> 
                requires (is_unit_v<UNITS> && is_same_base_v<BASE, typename UNITS::base>)
            constexpr void print_as(const UNITS& units, const bool& newline = true) const noexcept {

                std::cout << this->value_as(units) << ' ' << UNITS::to_string() << (newline ? '\n' : ' '); 

            }
            

    }; // struct measurement


    template <typename UNITS> 
        requires (is_unit_v<UNITS>)
    measurement(const scalar&, const UNITS&) 
        -> measurement<typename UNITS::base>;


    /// @brief Multiply a scalar with an unit to get a measurement
    template <typename UNITS> 
        requires (is_unit_v<UNITS>)
    constexpr auto operator*(const scalar& val, const UNITS&) noexcept
        -> measurement<typename UNITS::base> 
    { 
        
        return val * UNITS::mult; 
        
    }
    

    template <typename T>
    struct is_measurement : std::false_type {};

    template <typename BASE>
    struct is_measurement<measurement<BASE>> : std::true_type {};

    template <typename T>
    constexpr 
    bool is_measurement_v = is_measurement<T>::value;


    template <typename... Ts>
    struct are_measurements : std::conjunction<is_measurement<Ts>...> {};

    template <typename... Ts>
    constexpr 
    bool are_measurements_v = are_measurements<Ts...>::value;


    template <typename T, typename... Ts>
    struct are_same_measurements : std::false_type {};


    template <typename BASE>
    struct are_same_measurements<measurement<BASE>> : std::true_type {};

    
    template <typename BASE1, typename BASE2>
        requires (are_same_base_v<BASE1, BASE2>)
    struct are_same_measurements<measurement<BASE1>, measurement<BASE2>> : std::true_type {};


    template <typename T, typename... Ts>
    constexpr
    bool are_same_measurements_v = are_same_measurements<T, Ts...>::value;


} // namespace physics