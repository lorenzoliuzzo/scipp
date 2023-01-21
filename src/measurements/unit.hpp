/**
 * @file    unit.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the definition and implementation of the units namespace 
 *          with the unit_base class, the unit class
 * @date    2023-01-18
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief measurements namespace contains all the classes and functions of the measurements library
namespace scipp::measurements {

    
    /// @brief units namespace contains all the units of the measurements library
    namespace units {


        /// @brief Namespace containg the SI prefixes
        namespace prefixes {


            constexpr scalar yocto{1.e-24}; //< yocto prefix

            constexpr scalar zepto{1.e-21}; //< zepto prefix

            constexpr scalar atto{1.e-18}; //< atto prefix

            constexpr scalar femto{1.e-15}; //< femto prefix

            constexpr scalar pico{1.e-12}; //< pico prefix

            constexpr scalar nano{1.e-9}; //< nano prefix

            constexpr scalar micro{1.e-6}; //< micro prefix

            constexpr scalar milli{1.e-3}; //< milli prefix

            constexpr scalar centi{1.e-2}; //< centi prefix

            constexpr scalar deci{1.e-1}; //< deci prefix

            constexpr scalar hecto{1.e2}; //< hecto prefix

            constexpr scalar kilo{1.e3}; //< kilo prefix

            constexpr scalar mega{1.e6}; //< mega prefix

            constexpr scalar giga{1.e9}; //< giga prefix
    
            constexpr scalar tera{1.e12}; //< tera prefix

            constexpr scalar peta{1.e15}; //< peta prefix

            constexpr scalar exa{1.e18}; //< exa prefix

            constexpr scalar zetta{1.e21}; //< zetta prefix

            constexpr scalar yotta{1.e24}; //< yotta prefix


            std::map<scalar, char> map = {

                {yocto, 'y'},
                {zepto, 'z'},
                {atto, 'a'},
                {femto, 'f'},
                {pico, 'p'},
                {nano, 'n'},
                {micro, 'u'},
                {milli, 'm'},
                {centi, 'c'},
                {deci, 'd'},
                {hecto, 'h'},
                {kilo, 'k'},
                {mega, 'M'},
                {giga, 'G'},
                {tera, 'T'},
                {peta, 'P'},
                {exa, 'E'},
                {zetta, 'Z'},
                {yotta, 'Y'}

            }; //< Map with the SI prefixes and their corresponding symbols


        } // namespace prefix


        /** 
         * @brief Struct represents an unit of measurement as an union of an unit_base and a scalar prefix
         * @tparam UB: unit_base of the unit
         */
        template <unit_base UB> 
        class unit {


            public: 

                /// @brief Construct a new default unit object
                consteval unit() noexcept : 

                    prefix_{1.} {}


                /**
                 * @brief Construct a new unit object from a scalar prefix 
                 * 
                 * @param prefix: scalar as l-value const reference
                 */
                consteval unit(const scalar& prefix) noexcept : 

                    prefix_{prefix} {}


                /**
                 * @brief Construct a new unit object from a scalar prefix 
                 * 
                 * @param prefix: scalar as r-value reference
                 */
                consteval unit(scalar&& prefix) noexcept : 

                    prefix_{std::move(prefix)} {}


                /**
                 * @brief Copy construct a new unit from another unit object
                 * 
                 * @param other: unit object as l-value const reference
                 */
                consteval unit(const unit& other) noexcept : 

                    prefix_(other.prefix_) {}


                /**
                 * @brief Move construct a new unit from another unit object
                 * 
                 * @param other: unit object as r-value reference
                 */
                consteval unit(unit&& other) noexcept : 

                    prefix_(std::move(other.prefix_)) {}


                /// @brief Default destructor
                ~unit() noexcept = default; 


            // =============================================
            // operators
            // ============================================= 

                /**
                 * @brief Copy assignment operator
                 * 
                 * @param other: unit as l-value const reference
                 * 
                 * @return consteval unit&
                 */
                consteval unit& operator=(const unit& other) noexcept {

                    this->prefix_ = other.prefix_;
 
                    return *this;

                }


                /**
                 * @brief Move assignment operator
                 * 
                 * @param other: unit as r-value reference
                 * 
                 * @return consteval unit& 
                 */
                consteval unit& operator=(unit&& other) noexcept {

                    this->prefix_ = std::move(other.prefix_);

                    return *this;

                }


                /**
                 * @brief Perform a multiplication by multiply the bases and the prefixes
                 * 
                 * @param other: unit as l-value const reference
                 *                      
                 * @return consteval unit
                 */
                template <unit_base UB2>
                consteval unit<UB * UB2> operator*(const unit<UB2>& other) const noexcept { 
                    
                    return { this->prefix_ * other.prefix() }; 
                    
                }


                /**
                 * @brief Perform a multiplication by multiply the bases and the prefixes
                 * 
                 * @param other: unit as r-value reference
                 *                      
                 * @return consteval unit
                 */
                template <unit_base UB2>
                consteval unit<UB * UB2> operator*(unit<UB2>&& other) const noexcept { 
                    
                    return { this->prefix_ * other.prefix() }; 
                    
                }


                /**
                 * @brief Perform a division by divide the bases and the prefixes
                 * 
                 * @param other: unit as l-value const reference
                 *                      
                 * @return consteval unit
                 */
                template <unit_base UB2>
                consteval unit<UB / UB2> operator/(const unit<UB2>& other) const noexcept { 
                    
                    return { this->prefix_ / other.prefix() }; 
                    
                }                


                /**
                 * @brief Perform a division by divide the bases and the prefixes
                 * 
                 * @param other: unit as r-value reference
                 *                      
                 * @return consteval unit
                 */
                template <unit_base UB2>
                consteval unit<UB / UB2> operator/(unit<UB2>&& other) const noexcept { 
                    
                    return { this->prefix_ / other.prefix() }; 
                    
                }          


                /**
                 * @brief Equality operator
                 * 
                 * @param other: unit as l-value const reference
                 * 
                 * @return consteval bool 
                 */
                consteval bool operator==(const unit& other) const noexcept {

                    return this->prefix_ == other.prefix_;

                }


                /**
                 * @brief Inequality operator
                 * 
                 * @param other: unit as l-value const reference
                 * 
                 * @return consteval bool 
                 */
                consteval bool operator!=(const unit& other) const noexcept { 

                    return this->prefix_ != other.prefix_;

                }


            // =============================================
            // setters & getters
            // ============================================= 

                /**
                 * @brief Check if the unit is a base unit or it's prefixed
                 * 
                 * @return constexpr bool 
                 */
                constexpr bool is_prefixed() const noexcept { 
                    
                    return this->prefix_ != 1.;

                }


                /**
                 * @brief Convert a value from the base unit to this unit
                 * 
                 * @param value: scalar as l-value const reference
                 * 
                 * @return constexpr scalar&
                 */
                constexpr scalar convert(const scalar& value) const noexcept { 
                    
                    return value / this->prefix_;
                
                }


                /**
                 * @brief Convert a value from the base unit to this unit
                 * 
                 * @param value: scalar as r-value reference
                 * 
                 * @return consteval scalar 
                 */
                constexpr scalar convert(scalar&& value) noexcept { 
                    
                    return value / this->prefix_;
                
                }


                /**
                 * @brief Convert a value in the current unit to the target unit 
                 * 
                 * @param value: value to convert 
                 * @param units: desired unit unit
                 * 
                 * @return constexpr scalar 
                 * @note the units will only convert if they have the same base unit
                 */
                constexpr scalar convert(const scalar& value, const unit& units) const noexcept { 
                    
                    return value * this->prefix_ / units.prefix();
                
                }


                /**
                 * @brief Convert a value in the current unit to the target unit 
                 * 
                 * @param value: value to convert 
                 * @param units: desired unit unit
                 * 
                 * @return constexpr scalar 
                 * @note the units will only convert if they have the same base unit
                 */
                constexpr scalar convert(scalar&& value, const unit& units) const noexcept { 
                    
                    return value * this->prefix_ / units.prefix();
                
                }


                /**
                * @brief Generate a conversion factor between this unit and another unit 
                * 
                * @param result: desired unit
                * 
                * @return constexpr scalar 
                * @note the units will only convert if they have the same base unit
                */
                consteval scalar convertion_factor(const unit& other) const noexcept { 
                    
                    return this->prefix_ / other.prefix_;
                }


                /**
                 * @brief Get the unit prefix object
                 * 
                 * @return constexpr unit_prefix 
                 */
                constexpr scalar prefix() const noexcept {

                    return prefix_; 

                }


                /**
                 * @brief Get the unit base object
                 * 
                 * @return consteval unit_base& 
                 */
                consteval unit_base base() const noexcept {

                    return UB; 

                }


                /**
                 * @brief Get the unit object
                 * 
                 * @return constexpr unit
                 */
                constexpr const unit& units() const noexcept { 
                    
                    return *this; 
                    
                }


                /**
                 * @brief Get the unit object
                 * 
                 * @return constexpr unit& 
                 */
                constexpr unit& units() noexcept { 
                    
                    return *this; 
                    
                }


                // /**
                //  * @brief Get the unit string
                //  * 
                //  * @return std::string 
                //  */
                // constexpr std::string to_string() const noexcept { 

                //     // std::string unit_string{this->prefix_.to_string()}; 
                //     // unit_string += ; 

                //     return UB.to_string(); 

                // }


                /// @brief Print the unit to the standard output
                constexpr void print() const noexcept {

                    std::cout << UB;

                }

            
            protected:

                scalar prefix_; ///< unit prefix


        }; // class unit
         

    } // namespace units

    
} // namespace scipp::measurements