/**
 * @file    measurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the measurement struct and its type traits.
 * @date    2023-04-03
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    /// @brief Struct measurement represents a physical measurement as a double and a dimentional template meta-structure 
    /// @tparam BASE_TYPE: base_quantity of the measurement
    /// @see base_quantity, prefix, unit and their operations in namespace math::op
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

                value{0.0}{}


            /// @brief Construct a measurement from a scalar value
            /// @param val: The value of the measurement
            constexpr measurement(const double& val) noexcept :

                value{val}{}


            /// @brief Construct a measurement from a scalar value
            /// @param val: The value of the measurement
            constexpr measurement(double&& val) noexcept :

                value{std::move(val)}{}


            /// @brief Construct a measurement from a scalar value and an unit
            /// @param val: The value of the measurement
            /// @param UNIT_TYPE: The unit of the measurement
            /// @note The unit must be of the same base of the measurement
            template <typename UNIT_TYPE> 
                requires (is_unit_v<UNIT_TYPE> && is_same_base_v<BASE_TYPE, typename UNIT_TYPE::base>)
            constexpr measurement(const double& val, const UNIT_TYPE&) noexcept :

                value{val * UNIT_TYPE::mult}{}


            /// @brief Construct a measurement from a scalar value and an unit
            /// @param val: The value of the measurement
            /// @param UNIT_TYPE: The unit of the measurement
            /// @note The unit must be of the same base of the measurement
            template <typename UNIT_TYPE> 
                requires (is_unit_v<UNIT_TYPE> && is_same_base_v<BASE_TYPE, typename UNIT_TYPE::base>)
            constexpr measurement(double&& val, const UNIT_TYPE&) noexcept :

                value{std::move(val * UNIT_TYPE::mult)}{}


            /// @brief Construct a measurement from another measurement
            /// @param meas: The measurement to copy
            constexpr measurement(const measurement& other) noexcept :

                value{other.value}{}


            /// @brief Construct a measurement from another measurement
            /// @param meas: The measurement to move
            constexpr measurement(measurement&& other) noexcept :

                value{std::move(other.value)}{}


        // ==============================================
        // operators
        // ==============================================

            constexpr operator double() const noexcept { 
                
                return this->value; 
                
            }


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

            /// @brief Add a measurement to the current measurement
            constexpr measurement& operator+=(measurement&& other) noexcept { 
                
                this->value += std::move(other.value);
                return *this;  
                
            }

            /// @brief Add two measurements
            constexpr measurement operator+(const measurement& other) const noexcept { 
                
                return this->value + other.value; 
                
            }

            /// @brief Add two measurements
            constexpr measurement operator+(measurement&& other) const noexcept { 
                
                return this->value + std::move(other.value); 
                
            }


            /// @brief Subtract a measurement to the current measurement
            constexpr measurement& operator-=(const measurement& other) noexcept { 
                
                this->value -= other.value;
                return *this;  

            }

            /// @brief Subtract a measurement to the current measurement
            constexpr measurement& operator-=(measurement&& other) noexcept { 
                
                this->value -= std::move(other.value);
                return *this;  

            }

            /// @brief Multiply this measurement with a scalar measurement
            constexpr measurement& operator*=(const measurement<units::scalar>& other) noexcept {

                this->value *= other.value; 

                return *this; 

            }

            /// @brief Multiply this measurement with a scalar measurement
            constexpr measurement& operator*=(measurement<units::scalar>&& other) noexcept {

                this->value *= std::move(other.value); 

                return *this; 

            }


            /// @brief Divide this measurement with a scalar measurement
            constexpr measurement& operator/=(const measurement<units::scalar>& other) {

                if (other.value == 0.0) 
                    throw std::invalid_argument("Cannot divide a measurement by zero");

                this->value /= other.value; 

                return *this; 

            }

            /// @brief Divide this measurement with a scalar measurement
            constexpr measurement& operator/=(measurement<units::scalar>&& other) {

                if (other.value == 0.0) 
                    throw std::invalid_argument("Cannot divide a measurement by zero");

                this->value /= std::move(other.value); 

                return *this; 

            }


            /// @brief Subtract two measurements
            constexpr measurement operator-(const measurement& other) const noexcept { 
                
                return this->value - other.value; 
                
            }

            /// @brief Subtract two measurements
            constexpr measurement operator-(measurement&& other) const noexcept { 
                
                return this->value - std::move(other.value); 
                
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

            /// @brief Multiply two measurements
            template <typename OTHER_BASE_TYPE> 
                requires (is_base_v<OTHER_BASE_TYPE>)
            constexpr auto operator*(measurement<OTHER_BASE_TYPE>&& other) const noexcept 
                -> measurement<math::op::base_product_t<BASE_TYPE, OTHER_BASE_TYPE>> { 
                
                return this->value * std::move(other.value); 
                
            }


            /// @brief Divide two measurements
            /// @note The denominator must not be zero
            template <typename OTHER_BASE_TYPE> 
                requires (is_base_v<OTHER_BASE_TYPE>)
            constexpr auto operator/(const measurement<OTHER_BASE_TYPE>& other) const 
                -> measurement<math::op::base_division_t<BASE_TYPE, OTHER_BASE_TYPE>> {

                if (other.value == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by a zero measurement");

                return this->value / other.value; 
                
            }

            /// @brief Divide two measurements
            /// @note The denominator must not be zero
            template <typename OTHER_BASE_TYPE> 
                requires (is_base_v<OTHER_BASE_TYPE>)
            constexpr auto operator/(measurement<OTHER_BASE_TYPE>&& other) const 
                -> measurement<math::op::base_division_t<BASE_TYPE, OTHER_BASE_TYPE>> {

                if (other.value == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by a zero measurement");

                return this->value / std::move(other.value); 
                
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
            

            /// @brief Check if this measurement is equal to another measurement
            constexpr bool operator==(const double& other) const noexcept {

                return this->value == other; 

            }
            
            /// @brief Check if this measurement is equal to another measurement
            constexpr bool operator!=(const double& other) const noexcept {

                return this->value != other; 

            }

            /// @brief Check if this measurement is greater than another measurement
            constexpr bool operator>(const double& other) const noexcept {

                return this->value > other; 

            }


            /// @brief Check if this measurement is less than another measurement
            constexpr bool operator<(const double& other) const noexcept {

                return this->value < other; 

            }

            /// @brief Check if this measurement is greater or equal to another measurement
            constexpr bool operator>=(const double& other) const noexcept {

                return this->value >= other; 

            }

            /// @brief Check if this measurement is less or equal to another measurement
            constexpr bool operator<=(const double& other) const noexcept {

                return this->value <= other; 

            }
            

        // ==============================================
        // friend operators
        // ==============================================

            // /// @brief Multiply a scalar measurement by a measurement
            // friend inline constexpr measurement operator*(const measurement<units::scalar>& scalar, const measurement& meas) noexcept {

            //     return scalar.value * meas.value; 
                
            // }

            // /// @brief Divide a scalar measurement by a measurement
            // friend constexpr auto operator/(const measurement<units::scalar>& scalar, const measurement& meas)
            //     -> measurement<math::op::base_invert_t<BASE_TYPE>> {

            //     if (meas.value == 0.0) 
            //         throw std::runtime_error("Cannot divide a scalar by a zero measurement");

            //     return scalar.value / meas.value; 
                
            // }


            /// @brief Print a measurement to an output stream
            friend inline std::ostream& operator<<(std::ostream& os, const measurement& other) noexcept { 
                
                return os << other.value << ' ' << BASE_TYPE::to_string();
                
            }

            /// @brief Read a measurement from an input stream
            friend std::istream& operator>>(std::istream& is, measurement& other) { 

                std::string unit;
                is >> other.value >> unit;
                
                // Check if the read unit matches the base unit of the measurement type
                if (!unit.empty()) {

                    if (unit.find("[") != std::string::npos) {
                        
                        double multiplier = 1.0;
                        std::string prefix = unit.substr(unit.find("["), unit.find("]") + 1);
                        unit = unit.substr(unit.find("]") + 1);

                        for (const auto& kv : prefix_map) 
                            if (prefix[1] == kv.second) {
                                multiplier = kv.first;
                                break;
                            }

                        other.value *= multiplier;

                    }

                    if (unit != BASE_TYPE::to_string()) 
                        throw std::runtime_error("Unit mismatch: expected " + BASE_TYPE::to_string() + ", got " + unit);

                }

                return is; 
                
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

    // =============================================
    // measurement type traits
    // =============================================
        
        template <typename BASE_TYPE>
            requires (is_base_v<BASE_TYPE>)
        struct is_measurement<measurement<BASE_TYPE>> : std::true_type{};


        template <typename BASE_TYPE>
            requires (is_base_v<BASE_TYPE>)
        struct are_same_measurements<measurement<BASE_TYPE>> : std::true_type{};

        template <typename BASE_TYPE>
            requires (is_base_v<BASE_TYPE>)
        struct are_same_measurements<const measurement<BASE_TYPE>&> : std::true_type{};
        
        template <typename BASE_TYPE>
            requires (is_base_v<BASE_TYPE>)
        struct are_same_measurements<measurement<BASE_TYPE>, const measurement<BASE_TYPE>&> : std::true_type{};

        template <typename BASE_TYPE>
            requires (is_base_v<BASE_TYPE>)
        struct are_same_measurements<const measurement<BASE_TYPE>&, measurement<BASE_TYPE>> : std::true_type{};



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


} // namespace physics