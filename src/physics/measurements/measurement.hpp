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


    template <typename BASE, typename = std::enable_if_t<units::is_base_v<BASE>>>
    struct measurement {


        // ==============================================
        // aliases
        // ==============================================

            using type = measurement<BASE>;

            using base = BASE; 


        // ==============================================
        // constructors
        // ==============================================

            consteval measurement() noexcept : 
                
                value{0.0} {}


            constexpr measurement(const scalar& val) noexcept : 
                
                value{val} {}


            template <typename UNITS, typename = std::enable_if_t<units::is_same_base_v<BASE, typename UNITS::base>>>
            constexpr measurement(const scalar& val, const UNITS& unit) noexcept :
            
                value{val * UNITS::mult} {}


        // ==============================================
        // operators
        // ==============================================

            /// @brief Add a measurement to the current measurement
            inline constexpr measurement& operator+=(const measurement& meas) noexcept { 
                
                this->value += meas.value;

                return *this;  
                
            }


            /// @brief Subtract a measurement to the current measurement
            inline constexpr measurement& operator-=(const measurement& meas) noexcept { 
                
                this->value -= meas.value;

                return *this;  

            }

            
            /// @brief Add two measurements
            inline constexpr measurement operator+(const measurement& meas) const noexcept { 
                
                return this->value + meas.value; 
                
            }


            /// @brief Subtract two measurements
            inline constexpr measurement operator-(const measurement& meas) const noexcept { 
                
                return this->value - meas.value; 
                
            }


            /// @brief Get the inverse of a measurement
            inline constexpr measurement operator-() const noexcept {

                return -this->value; 

            }


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
            

            /// @brief Print a measurement to an output stream
            friend inline std::ostream& operator<<(std::ostream& os, const measurement& meas) noexcept { 
                
                return os << meas.value << ' ' << BASE::to_string();
                
            }
            
        
        // ==============================================
        // methods
        // ==============================================

            template <typename UNITS, typename = std::enable_if_t<units::is_same_base_v<BASE, typename UNITS::base>>>
            inline constexpr scalar value_as(const UNITS&) const noexcept { 
                
                return this->value / UNITS::mult; 
                
            }

            
            /// @brief Convert a value from one unit to another 
            template <typename UNITS, typename = std::enable_if_t<units::is_same_base_v<BASE, typename UNITS::base>>>
            inline constexpr measurement convert(const UNITS&) const noexcept {

                return *this / UNITS::mult; 

            }
                
            
            inline constexpr void print(const bool& newline = true) const noexcept {

                std::cout << this->value << ' ' << BASE::to_string() << (newline ? '\n' : ' '); 

            }
            

            template <typename UNITS, typename = std::enable_if_t<units::is_unit_v<UNITS>>>
            inline constexpr void print(const UNITS& units, const bool& newline = true) const noexcept {

                std::cout << this->value_as(units) << ' ' << UNITS::to_string(); 
                if (newline) std::cout << '\n'; 

            }
            

        // ==============================================
        // members
        // ==============================================

            scalar value; 


    }; // struct measurement


    template <typename UNITS, typename = std::enable_if_t<units::is_unit_v<UNITS>>>
    measurement(const scalar&, const UNITS&) -> measurement<typename UNITS::base>;


    /// @brief Multiply a scalar with an unit to get a measurement
    template <typename UNITS, typename = std::enable_if_t<units::is_unit_v<UNITS>>>
    inline constexpr auto operator*(const scalar& val, const UNITS&) noexcept -> measurement<typename UNITS::base> { 
        
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

        // template <typename BASE>
        // struct is_measurement : std::false_type {};

        // template <typename BASE>
        // struct is_measurement<measurement<BASE>> : std::true_type {};

        // template <typename BASE>
        // struct is_measurement<const measurement<BASE>> : std::true_type {};

        // template <typename BASE>
        // inline constexpr bool is_measurement_v = is_measurement<BASE>::value;


} // namespace scipp::physics