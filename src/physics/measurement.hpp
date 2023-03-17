/**
 * @file    measurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-17
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    /// @brief The measurement class is a template class that represents a measurement of a physical quantity
    /// @tparam BASE_TYPE : The base of the measurement
    /// @see base_quantity, unit
    template <typename BASE_TYPE> 
        requires (is_base_v<BASE_TYPE>)
    struct measurement {


        // ==============================================
        // aliases
        // ==============================================

            using type = measurement<BASE_TYPE>; ///< The type of the measurement

            using base = BASE_TYPE; ///< The base of the measurement


        // ==============================================
        // members
        // ==============================================

            double value; ///< The value of the measurement


        // ==============================================
        // static members
        // ==============================================

            inline static constexpr measurement zero = measurement{0.0}; ///< The zero measurement

            inline static constexpr measurement one = measurement{1.0}; ///< The one measurement


        // ==============================================
        // constructors
        // ==============================================

            /// @brief Default constructor
            constexpr measurement() noexcept : 

                value{0.0} {}


            /// @brief Construct a measurement from a scalar value
            /// @param val: The value of the measurement
            constexpr measurement(const double& val) noexcept :

                value{val} {}


            /// @brief Construct a measurement from a scalar value
            /// @param val: The value of the measurement
            constexpr measurement(double&& val) noexcept :

                value{std::move(val)} {}


            /// @brief Construct a measurement from a scalar value and an unit
            /// @param val: The value of the measurement
            /// @param UNIT_TYPE: The unit of the measurement
            /// @note The unit must be of the same base of the measurement
            template <typename UNIT_TYPE> 
                requires (is_unit_v<UNIT_TYPE> && is_same_base_v<BASE_TYPE, typename UNIT_TYPE::base>)
            constexpr measurement(const double& val, const UNIT_TYPE&) noexcept :

                value{val * UNIT_TYPE::mult} {}


            /// @brief Construct a measurement from a scalar value and an unit
            /// @param val: The value of the measurement
            /// @param UNIT_TYPE: The unit of the measurement
            /// @note The unit must be of the same base of the measurement
            template <typename UNIT_TYPE> 
                requires (is_unit_v<UNIT_TYPE> && is_same_base_v<BASE_TYPE, typename UNIT_TYPE::base>)
            constexpr measurement(double&& val, const UNIT_TYPE&) noexcept :

                value{std::move(val * UNIT_TYPE::mult)} {}


            /// @brief Construct a measurement from another measurement
            /// @param meas: The measurement to copy
            constexpr measurement(const measurement& other) noexcept :

                value{other.value} {}


            /// @brief Construct a measurement from another measurement
            /// @param meas: The measurement to move
            constexpr measurement(measurement&& other) noexcept :

                value{std::move(other.value)} {}


        // ==============================================
        // operators
        // ==============================================

            /// @brief Copy assignment operator
            constexpr measurement& operator=(const measurement& other) noexcept {

                this->value = other.value;
                return *this;

            }


            /// @brief Move assignment operator
            constexpr measurement& operator=(measurement&& other) noexcept {

                this->value = std::move(other.value);
                return *this;

            }


            /// @brief Add a measurement to the current measurement
            constexpr measurement& operator+=(const measurement& other) noexcept { 
                
                this->value += other.value;
                return *this;  
                
            }


            /// @brief Subtract a measurement to the current measurement
            constexpr measurement& operator-=(const measurement& other) noexcept { 
                
                this->value -= other.value;
                return *this;  

            }

            
            /// @brief Add two measurements
            constexpr measurement operator+(const measurement& other) const noexcept { 
                
                return this->value + other.value; 
                
            }


            /// @brief Subtract two measurements
            constexpr measurement operator-(const measurement& other) const noexcept { 
                
                return this->value - other.value; 
                
            }


            /// @brief Negate a measurement
            constexpr measurement operator-() const noexcept { 

                return -this->value; 

            }


            /// @brief Multiply two measurements
            template <typename OTHER_BASE_TYPE> 
                requires (is_base_v<OTHER_BASE_TYPE>)
            constexpr auto operator*(const measurement<OTHER_BASE_TYPE>& other) const noexcept 
                -> measurement<math::op::base_product_t<BASE_TYPE, OTHER_BASE_TYPE>> { 
                
                return this->value * other.value; 
                
            }


            /// @brief Divide two measurements
            template <typename OTHER_BASE_TYPE> 
                requires (is_base_v<OTHER_BASE_TYPE>)
            constexpr auto operator/(const measurement<OTHER_BASE_TYPE>& other) const 
                -> measurement<math::op::base_division_t<BASE_TYPE, OTHER_BASE_TYPE>> {

                if (other.value == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by a zero measurement");

                return this->value / other.value; 
                
            }
        

            constexpr measurement& operator*=(const measurement<units::scalar>& other) noexcept {

                this->value *= other.value; 

                return *this; 

            }


            constexpr measurement operator*(const measurement<units::scalar>& other) const noexcept {

                return this->value * other.value; 

            }


            constexpr measurement& operator/=(const measurement<units::scalar>& other) {


                if (other.value == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by zero");

                this->value /= other.value; 

                return *this; 

            }


            constexpr measurement operator/(const measurement<units::scalar>& other) const {

                if (other.value == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by zero");

                return this->value / other.value; 

            }


            /// @brief Check if this measurement is equal to another measurement
            constexpr bool operator==(const measurement& other) const noexcept {

                return this->value == other.value; 

            }
            
            
            /// @brief Check if this measurement is equal to another measurement
            constexpr bool operator!=(const measurement& other) const noexcept {

                return this->value != other.value; 

            }


            /// @brief Check if this measurement is greater than another measurement
            constexpr bool operator>(const measurement& other) const noexcept {

                return this->value > other.value; 

            }


            /// @brief Check if this measurement is less than another measurement
            constexpr bool operator<(const measurement& other) const noexcept {

                return this->value < other.value; 

            }


            /// @brief Check if this measurement is greater or equal to another measurement
            constexpr bool operator>=(const measurement& other) const noexcept {

                return this->value >= other.value; 

            }


            /// @brief Check if this measurement is less or equal to another measurement
            constexpr bool operator<=(const measurement& other) const noexcept {

                return this->value <= other.value; 

            }
            

        // ==============================================
        // friend operators
        // ==============================================

            friend constexpr measurement operator*(const double& scalar, const measurement& meas) noexcept {

                return scalar * meas.value; 
                
            }


            /// @brief Divide a scalar by a measurement
            /// @param scalar: The scalar value as lvalue const reference
            /// @param meas: The measurement as lvalue const reference
            friend constexpr auto operator/(const double& scalar, const measurement& meas)
                -> measurement<math::op::base_invert_t<BASE_TYPE>> {

                if (meas.value == 0.0) 
                    throw std::runtime_error("Cannot divide a scalar by a zero measurement");

                return scalar / meas.value; 
                
            }


            /// @brief Print a measurement to an output stream
            friend constexpr std::ostream& operator<<(std::ostream& os, const measurement& other) noexcept { 
                
                return os << other.value << ' ' << BASE_TYPE::to_string();
                
            }
            
        
        // ==============================================
        // methods
        // ==============================================

            /// @brief  Get the value of the measurement in the specified unit
            /// @param  UNIT_TYPE: The unit in which the value is returned
            /// @note   The unit must be of the same base of the measurement
            template <typename UNIT_TYPE> 
                requires (is_unit_v<UNIT_TYPE> && is_same_base_v<BASE_TYPE, typename UNIT_TYPE::base>)
            constexpr double value_as(const UNIT_TYPE&) const noexcept { 
                
                return this->value / UNIT_TYPE::mult; 
                
            }
                        
            
            /// @brief Print the measurement to the standard output
            /// @param newline: If true (default case), a newline character is printed at the end of the measurement
            constexpr void print(const bool& newline = true) const noexcept {

                std::cout << this->value << ' ' << BASE_TYPE::to_string() << (newline ? '\n' : ' '); 

            }
            

            /// @brief Print the measurement to the standard output
            /// @param units: The unit in which the value is printed
            /// @param newline: If true (default case), a newline character is printed at the end of the measurement
            /// @note The unit must be of the same base of the measurement

            template <typename UNIT_TYPE> 
                requires (is_unit_v<UNIT_TYPE> && is_same_base_v<BASE_TYPE, typename UNIT_TYPE::base>)
            constexpr void print_as(const UNIT_TYPE& units, const bool& newline = true) const noexcept {

                std::cout << this->value_as(units) << ' ' << UNIT_TYPE::to_string() << (newline ? '\n' : ' '); 

            }
            

    }; // struct measurement


    // =============================================
    // measurement template guidelines
    // =============================================
        
        template <typename UNIT_TYPE> 
            requires (is_unit_v<UNIT_TYPE>)
        measurement(const double&, const UNIT_TYPE&) 
            -> measurement<typename UNIT_TYPE::base>;

        template <typename UNIT_TYPE> 
            requires (is_unit_v<UNIT_TYPE>)
        measurement(double&&, const UNIT_TYPE&) 
            -> measurement<typename UNIT_TYPE::base>;


    // =================================================================
    // measurement construction from operations with double and units 
    // =================================================================

        /// @brief Multiply a double with an unit to get a measurement
        template <typename UNIT_TYPE> 
            requires (is_unit_v<UNIT_TYPE>)
        constexpr auto operator*(const double& val, const UNIT_TYPE&) noexcept
            -> measurement<typename UNIT_TYPE::base> { 
            
            return val * UNIT_TYPE::mult; 
            
        }
        
        /// @brief Multiply a double with an unit to get a measurement
        template <typename UNIT_TYPE> 
            requires (is_unit_v<UNIT_TYPE>)
        constexpr auto operator*(double&& val, const UNIT_TYPE&) noexcept
            -> measurement<typename UNIT_TYPE::base> { 
            
            return val * UNIT_TYPE::mult; 
            
        }
        
        /// @brief Divide a double with an unit to get a measurement
        template <typename UNIT_TYPE> 
            requires (is_unit_v<UNIT_TYPE>)
        constexpr auto operator/(const double& val, const UNIT_TYPE&) noexcept
            -> measurement<math::op::base_invert_t<typename UNIT_TYPE::base>> { 
            
            return val / UNIT_TYPE::mult; 
            
        }
    
        /// @brief Divide a double with an unit to get a measurement
        template <typename UNIT_TYPE> 
            requires (is_unit_v<UNIT_TYPE>)
        constexpr auto operator/(double&& val, const UNIT_TYPE&) noexcept
            -> measurement<math::op::base_invert_t<typename UNIT_TYPE::base>> { 
            
            return val / UNIT_TYPE::mult; 
            
        }


    // =============================================
    // measurement type traits
    // =============================================
        
        template <typename T>
        struct is_measurement : std::false_type {};

        template <typename BASE_TYPE>
            requires (is_base_v<BASE_TYPE>)
        struct is_measurement<measurement<BASE_TYPE>> : std::true_type {};

        template <typename MEAS_TYPE>
        constexpr bool is_measurement_v = is_measurement<MEAS_TYPE>::value;


        template <typename... MEAS_TYPES>
        struct are_measurements : std::conjunction<is_measurement<MEAS_TYPES>...> {};

        template <typename... MEAS_TYPES>
        constexpr bool are_measurements_v = are_measurements<MEAS_TYPES...>::value;




    // =============================================
    // measurement type operations
    // =============================================

        template <typename MEAS_TYPE, typename... MEAS_TYPES>
        struct measurements_prod { 
            
            using type = MEAS_TYPE; 
        
        };

        template <typename BASE_TYPE>
            requires (is_base_v<BASE_TYPE>)
        struct measurements_prod<measurement<BASE_TYPE>> { 
            
            using type = measurement<BASE_TYPE>; 
        
        };


        template <typename MEAS_TYPE, typename... MEAS_TYPES>
            requires (are_measurements_v<MEAS_TYPE, MEAS_TYPES...>)
        struct measurements_prod<MEAS_TYPE, MEAS_TYPES...> {
            
            using type = measurement<math::op::base_product_t<typename MEAS_TYPE::base, typename measurements_prod<MEAS_TYPES...>::type::base>>;
        
        }; 

        template <typename... Ts>
        using measurements_prod_t = typename measurements_prod<Ts...>::type;


        template <typename MEAS1, typename MEAS2>
            requires (are_measurements_v<MEAS1, MEAS2>)
        struct measurements_div { 
            
            using type = measurement<math::op::base_division_t<typename MEAS1::base, typename MEAS2::base>>; 
            
        };

        template <typename T1, typename T2>
        using measurements_div_t = typename measurements_div<T1, T2>::type;


        template <typename T>
        using measurement_square_t = measurements_prod_t<T, T>;

        template <typename T>
        using measurement_cube_t = measurements_prod_t<measurement_square_t<T>, T>;


        template <typename T>
        struct measurements_inv { 
            
            using type = T; 

        }; 

        template <typename BASE>
            requires (is_base_v<BASE>)
        struct measurements_inv<measurement<BASE>> { 
            
            using type = measurement<math::op::base_invert_t<BASE>>; 

        };

        template <typename... Ts>
        using measurements_inv_t = typename measurements_inv<Ts...>::type;


        template <typename T, int>
        struct measurement_pow { 
            
            using type = T; 

        }; 

        template <typename BASE_TYPE, int POWER>
            requires (is_base_v<BASE_TYPE>)
        struct measurement_pow<measurement<BASE_TYPE>, POWER> { 
            
            using type = measurement<math::op::base_pow_t<BASE_TYPE, POWER>>; 

        };


} // namespace physics