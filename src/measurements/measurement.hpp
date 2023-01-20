/**
 * @file    measurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the definition and implementation of the measurement class,
 *          with all its methods, operators and possible operations.
 * @date    2023-01-19
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief measurements namespace contains all the classes and functions of the measurements library
namespace scipp::measurements {


    /** 
     * @brief measurement class for representing a physical quantity with a numerical value and an unit
     * @see units::unit
     * 
     * @tparam UB: unit_base know at compile-time
     */
    template <unit_base UB>
    class measurement {


        public:

        // =============================================                                                                                         
        // constructors & destructor 
        // =============================================  

            /**
             * @brief Construct a new measurement object
             * 
             * @note The default value is 0
             */
            consteval measurement() noexcept : 
                                            
                value_{0.0} {} 


            /**
             * @brief Construct a new measurement object
             * 
             * @param scal: scalar as l-value const reference
             */
            constexpr measurement(const scalar& scal) noexcept : 
                                            
                value_{scal} {}             


            /**
             * @brief Construct a new measurement object
             * 
             * @param scal: scalar as r-value reference
             */
            constexpr measurement(scalar&& scal) noexcept : 
                                            
                value_{std::move(scal)} {}       


            /**
             * @brief Construct a new measurement object from a value and an unit of measurement
             * 
             * @param scal: scalar as l-value const reference
             * @param units: unit as l-value const reference
             */
            constexpr measurement(const scalar& scal, const unit<UB>& units) noexcept : 
                
                value_{scal * units.prefix()} {}


            /**
             * @brief Construct a new measurement object from a value and an unit of measurement
             * 
             * @param scal: scalar as r-value reference
             * @param units: unit as l-value const reference
             */
            constexpr measurement(scalar&& scal, const unit<UB>& units) noexcept : 
                
                value_{scal * units.prefix()} {}


            /**
             * @brief Construct a new measurement object from a value and an unit of measurement
             * 
             * @param scal: scalar as l-value const reference:
             * @param units: unit as r-value reference
             */
            constexpr measurement(scalar&& scal, unit<UB>&& units) noexcept :

                value_{scal * units.prefix()} {}


            /**
             * @brief Copy constuct a new measurement object from another measurement
             * 
             * @param other: measurement as l-value const reference
             */
            consteval measurement(const measurement& other) noexcept : 
            
                value_{other.value_} {}
                
            
            /**
             * @brief Move construct a new measurement object from another measurement
             * 
             * @param other: measurement as r-value reference
             */
            constexpr measurement(measurement&& other) noexcept :
                
                value_{std::move(other.value_)} {}


            /// @brief Destruct the measurement object
            ~measurement() = default;


        // =============================================                                                                                         
        // operators
        // =============================================  

            /**
             * @brief Copy assign another measurement to this measurement
             * 
             * @param other: measurement as l-value const reference
             * 
             * @return constexpr measurement& 
             */
            constexpr measurement& operator=(const measurement& other) noexcept {

                this->value_ = other.value_;

                return *this;

            }     


            /**
             * @brief Move assign another measurement to this measurement
             * 
             * @param other: measurement as r-value reference
             * 
             * @return constexpr measurement& 
             */
            constexpr measurement& operator=(measurement&& other) noexcept {

                this->value_ = std::move(other.value_);

                return *this;

            }


            /**
             * @brief Add another measurement to this measurement
             * 
             * @param other: measurement as l-value const reference
             * 
             * @return measurement& 
             */
            constexpr measurement& operator+=(const measurement& other) { 

                this->value_ += other.value_; 

                return *this; 
            
            }


            /**
             * @brief Add another measurement to this measurement
             * 
             * @param other: measurement as r-value reference
             * 
             * @return measurement& 
             */
            constexpr measurement& operator+=(measurement&& other) { 

                this->value_ += other.value_; 

                return *this; 
            
            }


            /**
             * @brief Subtract another measurement to this measurement
             * 
             * @param other: measurement l-value const reference
             * 
             * @return measurement& 
             */
            constexpr measurement& operator-=(const measurement& other) { 

                this->value_ -= other.value_; 

                return *this; 
            
            }


            /**
             * @brief Subtract another measurement to this measurement
             * 
             * @param other: measurement as r-value reference
             * 
             * @return measurement& 
             */
            constexpr measurement& operator-=(measurement&& other) { 

                this->value_ -= other.value_; 

                return *this; 

            }


            /**
             * @brief Sum this measurement and another measurement
             * 
             * @param other: measurement as l-value const reference
             * 
             * @return measurement 
             */
            constexpr measurement operator+(const measurement& other) const { 
                
                return { this->value_ + other.value_ };
            
            }


            /**
             * @brief Sum this measurement and another measurement
             * 
             * @param other: measurement as r-value reference
             * 
             * @return measurement 
             */
            constexpr measurement operator+(measurement&& other) const { 
                                
                return { this->value_ + other.value_ };
            
            }


            /**
             * @brief Subtract this measurement and another measurement 
             * 
             * @param other: measurement as l-value const reference
             *  
             * @return constexpr measurement 
             */
            constexpr measurement operator-(const measurement& other) const { 
                
                return { this->value_ - other.value_ };
            
            }


            /**
             * @brief Subtract this measurement and another measurement 
             * 
             * @param other: measurement as r-value reference
             *  
             * @return constexpr measurement 
             */
            constexpr measurement operator-(measurement&& other) const { 

                return { this->value_ - other.value_ };
            
            }
            

            /**
             * @brief Multiply this measurement by another measurement
             * 
             * @param other: measurement as l-value const reference
             * 
             * @return measurement& 
             */
            template <unit_base UB2>
            constexpr measurement<UB * UB2>& operator*=(const measurement<UB2>& other) noexcept { 

                this->value_ *= other.value();

                return *this; 
            
            }


            /**
             * @brief Multiply this measurement by another measurement
             * 
             * @param other: measurement as r-value reference
             * 
             * @return measurement& 
             */
            template <unit_base UB2>
            constexpr measurement<UB * UB2>& operator*=(measurement<UB2>&& other) noexcept { 

                this->value_ *= std::move(other.value());

                return *this; 
            
            }


            /**
             * @brief Divide this measurement by another measurement
             * 
             * @param other: measurement as l-value const reference
             * 
             * @return measurement& 
             */
            template <unit_base UB2>
            constexpr measurement<UB / UB2>& operator/=(const measurement<UB2>& other) { 

                if (other.value() == 0.0)
                    throw std::runtime_error("Cannot divide a measurement by a zero measurement");
                
                else 
                    this->value_ /= other.value();
                
                return *this; 
            
            }


            /**
             * @brief Divide this measurement by another measurement
             * 
             * @param other: measurement as r-value reference
             * 
             * @return measurement& 
             */
            template <unit_base UB2>
            constexpr measurement<UB / UB2>& operator/=(measurement<UB2>&& other) { 
                
                if (other.value() == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by a zero measurement");
                
                else 
                    this->value_ /= std::move(other.value());
                
                return *this; 
            
            }


            /**
             * @brief Multiply this measurement by another measurement
             * 
             * @param other: measurement as l-value const reference
             * 
             * @return constexpr measurement 
             */
            template <unit_base UB2>
            constexpr measurement<UB * UB2> operator*(const measurement<UB2>& other) const noexcept { 
                
                return { this->value_ * other.value() }; 
            
            }


            /**
             * @brief Multiply this measurement by another measurement
             * 
             * @param other: measurement as r-value reference
             * 
             * @return constexpr measurement 
             */
            template <unit_base UB2>
            constexpr measurement<UB * UB2> operator*(measurement<UB2>&& other) const noexcept { 
                
                return { this->value_ * other.value() }; 
            
            }


            /**
             * @brief Divide this measurement by another measurement
             * 
             * @param other: measurement as l-value const reference
             * 
             * @return constexpr measurement 
             */
            template <unit_base UB2>
            constexpr measurement<UB / UB2> operator/(const measurement<UB2>& other) const { 
                
                if (other.value() == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by a zero measurement");
                
                return { this->value_ / other.value() }; 
            
            }


            /**
             * @brief Divide this measurement by another measurement
             * 
             * @param other: measurement as r-value reference
             * 
             * @return constexpr measurement 
             */
            template <unit_base UB2>
            constexpr measurement<UB / UB2> operator/(measurement<UB2>&& other) const { 
                
                if (other.value() == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by a zero measurement");
                
                return { this->value_ / other.value() }; 
            
            }


            /**
             * @brief Multiply this measurement by a scalar
             * 
             * @param scal: scalar as l-value const reference 
             * 
             * @return constexpr measurement& 
             */
            constexpr measurement& operator*=(const scalar& scal) noexcept { 

                this->value_ *= scal;    

                return *this; 
            
            }


            /**
             * @brief Multiply this measurement by a scalar
             * 
             * @param scal: scalar as r-value reference
             * 
             * @return constexpr measurement& 
             */
            constexpr measurement& operator*=(scalar&& scal) noexcept { 

                this->value_ *= scal;    

                return *this; 
            
            }


            /**
             * @brief Divide this measurement by a scalar
             * 
             * @param scal: scalar as l-value const reference
             * 
             * @return constexpr measurement& 
             */
            constexpr measurement& operator/=(const scalar& scal) { 
                
                if (scal == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by 0");
                
                this->value_ /= scal;                    
                
                return *this; 
            
            }


            /**
             * @brief Divide this measurement by a scalar
             * 
             * @param scal: scalar as r-value reference
             * 
             * @return constexpr measurement& 
             */
            constexpr measurement& operator/=(scalar&& scal) { 
                
                if (scal == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by 0");
                
                this->value_ /= scal;                    
                
                return *this; 
            
            }


            /**
             * @brief Multiply this measurement and a scalar
             * 
             * @param scal: scalar as l-value const reference
             * 
             * @return constexpr measurement 
             */
            constexpr measurement operator*(const scalar& scal) const noexcept { 
                
                return { this->value_ * scal }; 
                
            }
            

            /**
             * @brief Multiply this measurement and a scalar
             * 
             * @param scal: scalar as r-value reference
             * 
             * @return constexpr measurement 
             */
            constexpr measurement operator*(scalar&& scal) const noexcept { 
                
                return { this->value_ * scal }; 
                
            }


            /**
             * @brief Divide this measurement and a scalar
             * 
             * @param scal: scalar as l-value const reference
             * 
             * @return constexpr measurement 
             */
            constexpr measurement operator/(const scalar& scal) const { 
                
                if (scal == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by 0");
                
                return { this->value_ / scal }; 
                
            } 


            /**
             * @brief Divide this measurement and a scalar
             * 
             * @param scal: scalar as r-value reference
             * 
             * @return constexpr measurement 
             */
            constexpr measurement operator/(scalar&& scal) const { 
                
                if (scal == 0.0) 
                    throw std::runtime_error("Cannot divide a measurement by 0");
                
                return { this->value_ / scal }; 
                
            } 


            /**
             * @brief Perform a product between a scalar and a measurement
             * 
             * @param scal: scalar as l-value const reference
             * @param meas: measurement as l-value const reference
             * 
             * @return constexpr measurement 
             */
            friend constexpr measurement operator*(const scalar& scal, 
                                                   const measurement& meas) noexcept { 
                                                
                return { scal * meas.value_ }; 
                
            }
            

            /**
             * @brief Perform a product between a scalar and a measurement
             * 
             * @param scal: scalar as r-value reference
             * @param meas: measurement as r-value reference
             * 
             * @return constexpr measurement 
             */
            friend constexpr measurement operator*(scalar&& scal, 
                                                   measurement&& meas) noexcept { 
                                                
                return { scal * meas.value_ }; 
                
            }


            /**
             * @brief Divide a scalar by a measurement
             * 
             * @param scal: scalar as l-value const reference
             * @param meas: measurement as l-value const reference
             * 
             * @return constexpr measurement 
             */
            friend constexpr measurement<UB.inv()> operator/(const scalar& scal, 
                                                             const measurement& meas) { 

                if (meas.value_ == 0.0) 
                    throw std::runtime_error("Cannot divide a scalar by a zero measurement");          
                
                return { scal / meas.value_ }; 
                
            }


            /**
             * @brief Divide a scalar by a measurement
             * 
             * @param scal: scalar as r-value reference
             * @param meas: measurement as r-value reference
             * 
             * @return constexpr measurement 
             */
            friend constexpr measurement<UB.inv()> operator/(scalar&& scal, 
                                                             measurement&& meas) { 

                if (meas.value_ == 0.0) 
                    throw std::runtime_error("Cannot divide a scalar by a zero measurement");          
                
                return { scal / meas.value_ }; 
                
            }

            
            /**
             * @brief Get the opposite of this measurement
             * 
             * @return constexpr measurement 
             */
            constexpr measurement operator-() const noexcept { 
                
                return { -this->value_ }; 
            
            }


            /**
             * @brief Equality operator
             * 
             * @param other: measurement to compare as l-value const reference
             */
            constexpr bool operator==(const measurement& other) const noexcept { 
                
                return this->value_ == other.value_; 
                
            }

            
            /**
             * @brief Inequality operator
             * 
             * @param other: measurement to compare as l-value const reference
             */
            constexpr bool operator!=(const measurement& other) const noexcept { 
                
                return this->value_ != other.value_; 
                
            }
            
            
            /**
             * @brief More than operator
             * 
             * @param other: measurement to compare as l-value const reference
             */
            constexpr bool operator>(const measurement& other) const noexcept { 
                
                return this->value_ > other.value_; 
                
            }

            
            /**
             * @brief Less than operator
             * 
             * @param other: measurement to compare as l-value const reference
             */
            constexpr bool operator<(const measurement& other) const noexcept { 
                
                return this->value_ < other.value_; 
                
            }

            
            /**
             * @brief More than or equal operator
             * 
             * @param other: measurement to compare as l-value const reference
             */
            constexpr bool operator>=(const measurement& other) const noexcept { 
                
                return this->value_ >= other.value_; 
                
            }

            
            /**
             * @brief Less than or equal operator
             * 
             * @param other: measurement to compare as l-value const reference 
             */
            constexpr bool operator<=(const measurement& other) const noexcept { 
                
                return this->value_ <= other.value_;
                
            }       


            /**
             * @brief Equality operator of value
             * 
             * @param scal: scalar as l-value const reference
             */
            constexpr bool operator==(const scalar& scal) const noexcept { 
                
                return this->value_ == scal; 
                
            }

            
            /**
             * @brief Inequality operator of value
             * 
             * @param scal: scalar as l-value const reference
             */
            constexpr bool operator!=(const scalar& scal) const noexcept { 
                
                return this->value_ != scal; 
                
            }
            
            
            /**
             * @brief More than with value
             * 
             * @param scal: scalar as l-value const reference 
             */
            constexpr bool operator>(const scalar& scal) const noexcept { 
                
                return this->value_ > scal; 
                
            }
            
            
            /**
             * @brief Less than with value
             * 
             * @param scal: scalar as l-value const reference 
             */
            constexpr bool operator<(const scalar& scal) const noexcept { 
                
                return this->value_ < scal; 
                
            }
            
            
            /**
             * @brief More than or equal with value
             * 
             * @param scal: scalar as l-value const reference 
             */
            constexpr bool operator>=(const scalar& scal) const noexcept { 
                
                return this->value_ >= scal; 
                
            }
            
            
            /**
             * @brief Less than or equal with value
             * 
             * @param scal: scalar as l-value const reference 
             */
            constexpr bool operator<=(const scalar& scal) const noexcept { 
                
                return this->value_ <= scal; 
                
            }


            /**
             * @brief Output operator for a measurement
             * 
             * @param os: std::ostream&
             * @param meas: measurement as l-value const reference
             * 
             * @return std::ostream&
             *  
             */
            friend std::ostream& operator<<(std::ostream& os, 
                                            const measurement& meas) noexcept { 
                
                double magnitude{std::pow(10, static_cast<int>(std::log10(std::fabs(meas.value_))))};
                if (std::fabs(meas.value_) < 1.) 
                    magnitude /= 10.; 
                auto it = prefixes::map.find(magnitude);

                if (magnitude != 1. && it != prefixes::map.end()) 
                    os << meas.value_ / magnitude << " [" << it->second << ']' << UB;

                else 
                    os << meas.value_ << " " << UB;

                return os; 
                
            }


            /**
             * @brief Output operator for a measurement
             * 
             * @param file: std::ofstream&
             * @param meas: measurement as l-value const reference
             * 
             * @return std::ofstream&
             *  
             */
            friend std::ofstream& operator<<(std::ofstream& file,   
                                             const measurement& meas) noexcept { 
                
                double magnitude{std::pow(10, static_cast<int>(std::log10(std::fabs(meas.value_))))};
                if (std::fabs(meas.value_) < 1.) 
                    magnitude /= 10.; 
                auto it = prefixes::map.find(magnitude);

                if (magnitude != 1. && it != prefixes::map.end()) 
                    file << meas.value_ / magnitude << " [" << it->second << ']' << UB;

                else 
                    file << meas.value_ << " " << UB;

                return file; 
                
            }

            
        // =============================================                                                                                         
        // get methods
        // =============================================  

            /**
             * @brief Get the value of the measurement
             * 
             * @return constexpr const scalar
             */
            constexpr scalar value() const noexcept { 
                
                return this->value_; 
            
            }                        
            
            
            /**
             * @brief Get the value of the measurement
             * 
             * @return constexpr scalar& 
             */
            constexpr scalar& value() noexcept { 
                
                return this->value_; 
            
            }  


            /**
             * @brief Get the value of the measurement
             *
             * @param units: unit as l-value const reference
             * 
             * @return constexpr scalar& 
             */
            constexpr scalar value_as(const unit<UB>& units) const noexcept { 
                
                return units.convert(this->value_); 
            
            }  


            /**
             * @brief Get the unit_base object 
             * 
             * @return constexpr unit_base&
             */
            constexpr unit_base base() const noexcept {

                return UB; 

            }


            /**
             * @brief Get the measurement object
             * 
             * @return constexpr measurement 
             */
            constexpr measurement as_measurement() const noexcept {

                return *this; 

            }


            /**
             * @brief Get the measurement object
             * 
             * @return constexpr measurement&
             */
            constexpr measurement& as_measurement() noexcept {

                return *this; 

            }


            /**
            * @brief Print the measurement
            * 
            * @param prefixed: if set to true it prints the measurement with prefixed units
            */
            void print(const unit<UB>& units = unit<UB>()) const noexcept { 

                if (this->value_ == 0.0)
                    std::cout << this->value_ << " " << UB << '\n';

                else if (units.is_prefixed()) {

                    auto it = prefixes::map.find(units.prefix());
                    if (it != prefixes::map.end()) 
                        std::cout << units.convert(this->value_) << " [" << it->second << ']' << UB << '\n';

                }
                
                else {

                    double magnitude{std::pow(10, static_cast<int>(std::log10(std::fabs(this->value_))))};
                    if (std::fabs(this->value_) < 1.) 
                        magnitude /= 10.; 

                    auto it = prefixes::map.find(magnitude);
                    if (magnitude != 1. && it != prefixes::map.end()) 
                        std::cout << this->value_ / magnitude << " [" << it->second << ']' << UB << '\n';

                }

            }


        protected:

        // =============================================                                                                                         
        // class members & friends
        // =============================================  

            scalar value_; ///< The numerical value of the measurement


    }; 


    /**
     * @brief Construct a measurement multiplying a scalar value and an unit of measurement
     *
     * @param value: scalar as -value reference
     * @param units: unit as l-value const reference
     */
    template <unit_base UB2> 
    constexpr measurement<UB2> operator*(const scalar& value, const unit<UB2>& units) noexcept {

        return { value, units }; 

    }


    /**
     * @brief Construct a measurement multiplying a scalar value and an unit of measurement
     *
     * @param value: scalar as -value reference
     * @param units: unit as l-value const reference
     */
    template <unit_base UB2> 
    constexpr measurement<UB2> operator*(scalar&& value, const unit<UB2>& units) noexcept {

        return { value, units }; 

    }


    /**
     * @brief Construct a measurement multiplying a scalar value and an unit of measurement
     *
     * @param value: scalar as -value reference
     * @param units: unit as l-value const reference
     */
    template <unit_base UB2> 
    constexpr measurement<UB2> operator*(scalar&& value, unit<UB2>&& units) noexcept {

        return { value, units }; 

    }


    using scalar_m = measurement<basis::scalar>;                                                    ///< scalar_m
    using length_m = measurement<basis::metre>;                                                     ///< length_m 
    using time_m = measurement<basis::second>;                                                      ///< time_m 
    using mass_m = measurement<basis::kilogram>;                                                    ///< mass_m 
    using angle_m = measurement<basis::radian>;                                                     ///< angle_m 
    using temperature_m = measurement<basis::Kelvin>;                                               ///< temperature_m
    using current_m = measurement<basis::Ampere>;                                                   ///< current_m
    using luminous_intensity_m = measurement<basis::candela>;                                       ///< luminous_intensity_m
    using mole_m = measurement<basis::mole>;                                                        ///< mole_m

    using speed_m = measurement<basis::metre / basis::second>;                                      ///< speed_m 
    using acceleration_m = measurement<basis::metre / basis::second.square()>;                      ///< acceleration_m 
    using force_m = measurement<basis::kilogram * basis::metre / basis::second.square()>;           ///< force_m 
    using energy_m = measurement<basis::kilogram * basis::metre.square() / basis::second.square()>; ///< energy_m 


} // namespace scipp::measurements