/**
 * @file    umeasurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the definition and implementation of the umeasurement class,
 *          with all its methods, operators and possible operations.
 * @date    2023-01-19
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief measurements namespace contains all the classes and functions of the measurements library
namespace scipp::measurements {
    

    /** 
     * @brief A class for representing a physical quantity with a numerical value, an uncertanty and an unit
     * @see units::unit  
     *   
     * @tparam UNIT_BASE: unit_base know at compile-time
     */
    template <unit_base UB>
    class umeasurement {     
        

        public: 

        // =============================================                                                                                         
        // constructors & destructor 
        // =============================================  

            /**
             * @brief Construct a new umeasurement object
             * 
             * @note The default value is 0
             * @note The default uncertainty is 0
             */
            consteval umeasurement() noexcept : 
                                            
                value_{0.0}, 
                uncertainty_{0.0} {} 


            /**
             * @brief Construct a new umeasurement object from a value and an uncertainty
             * 
             * @param value: scalar as l-value const reference
             * @param uncertainty: scalar as l-value const reference
             *
             * @note The uncertainty must be non-negative
             * @note The uncertainty must be expressed as a base_unit
             * @note The uncertainty is set to zero by default
             */
            constexpr umeasurement(const scalar& value, const scalar& uncertainty = 0.0) {

                if (uncertainty < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");
                
                else {

                    this->value_ = value;
                    this->uncertainty_ = uncertainty;

                }
            
            }             


            /**
             * @brief Construct a new umeasurement object from a value and an uncertainty
             * 
             * @param value: scalar as l-value const reference
             * @param uncertainty: scalar as r-value reference
             *
             * @note The uncertainty must be non-negative
             * @note The uncertainty must be expressed as a base_unit
             * @note The uncertainty is set to zero by default
             */
            constexpr umeasurement(const scalar& value, scalar&& uncertainty = 0.0) {

                if (uncertainty < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");
                
                else {

                    this->value_ = value;
                    this->uncertainty_ = uncertainty;

                }
            
            }     


            /**
             * @brief Construct a new umeasurement object from a value and an uncertainty
             * 
             * @param value: scalar as r-value reference
             * @param uncertainty: scalar as r-value reference
             *
             * @note The uncertainty must be non-negative
             * @note The uncertainty must be expressed as a base_unit
             * @note The uncertainty is set to zero by default
             */
            constexpr umeasurement(scalar&& value, scalar&& uncertainty = 0.0) {

                if (uncertainty < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");
                
                else {

                    this->value_ = std::move(value);
                    this->uncertainty_ = std::move(uncertainty);
                
                }
            
            }             


            /**
             * @brief Construct a new umeasurement object from a value, an uncertainty and an unit
             * 
             * @param value: scalar as l-value const reference
             * @param uncertainty: scalar as l-value const reference
             * @param units: unit as l-value const reference
             * 
             * @note The uncertainty must be non-negative
             * @note Both value and uncertainty must be expressed as the same unit of the measurement
             */
            constexpr umeasurement(const scalar& value, 
                                   const scalar& uncertainty, 
                                   const unit<UB>& units) {

                if (uncertainty < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");

                else {

                    this->value_ = value * units.prefix(); 
                    this->uncertainty_ = uncertainty * units.prefix(); 
                
                }
                        
            }


            /**
             * @brief Construct a new umeasurement object from a value, an uncertainty and an unit
             * 
             * @param value: scalar as r-value reference
             * @param uncertainty: scalar as r-value reference
             * @param units: unit as r-value reference
             * 
             * @note The uncertainty must be non-negative
             * @note Both value and uncertainty must be expressed as the same unit of the measurement
             */
            constexpr umeasurement(scalar&& value, 
                                   scalar&& uncertainty, 
                                   unit<UB>&& units) {

                if (uncertainty < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");

                else {

                    this->value_ = std::move(value * units.prefix()); 
                    this->uncertainty_ = std::move(uncertainty * units.prefix()); 
                
                }
                        
            }


            /**
             * @brief Construct a new umeasurement object from a measurement and an uncertainty
             * 
             * @param other: measurement as a l-value const reference
             * @param uncertainty: scalar as a l-value const reference
             * 
             * @note The uncertainty must be non-negative
             * @note The uncertainty must be expressed as a base_unit
             * @note The uncertainty is set to zero by default
             */
            constexpr umeasurement(const measurement<UB>& other, 
                                   const scalar& uncertainty = 0.0) {

                if (uncertainty < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");

                else {

                    this->value_ = other.value(); 
                    this->uncertainty_ = uncertainty; 
                
                }

            }     


            /**
             * @brief Construct a new umeasurement object from a measurement and an uncertainty
             * 
             * @param other: measurement as a r-value reference
             * @param uncertainty: scalar as a r-value reference
             * 
             * @note The uncertainty must be non-negative
             * @note The uncertainty must be expressed as a base_unit
             * @note The uncertainty is set to zero by default
             */
            constexpr umeasurement(measurement<UB>&& other, 
                                   scalar&& uncertainty = 0.0) {

                if (uncertainty < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");

                else {

                    this->value_ = std::move(other.value()); 
                    this->uncertainty_ = std::move(uncertainty); 
                
                }

            }     


            /**
             * @brief Construct a new umeasurement object from two measurements
             * 
             * @param value: measurement as l-value const reference 
             * @param uncertainty: measurement as l-value const reference
             * 
             * @note The uncertainty value must be non-negative
             */
            constexpr umeasurement(const measurement<UB>& value, 
                                   const measurement<UB>& uncertainty) {
                        
                if (uncertainty.value() < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");

                else {

                    this->value_ = value.value(); 
                    this->uncertainty_ = uncertainty.value(); 
                
                }

            }


            /**
             * @brief Construct a new umeasurement object from two measurements
             * 
             * @param value: measurement as r-value reference 
             * @param uncertainty: measurement as r-value reference
             * 
             * @note The uncertainty value must be non-negative
             */
            constexpr umeasurement(measurement<UB>&& value, 
                                   measurement<UB>&& uncertainty) {
                        
                if (uncertainty.value() < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");

                else {

                    this->value_ = std::move(value.value()); 
                    this->uncertainty_ = std::move(uncertainty.value()); 
                
                }

            }


            /**
             * @brief Copy construct a new umeasurement object
             * 
             * @param other: umeasurement as a l-value const reference
             */
            constexpr umeasurement(const umeasurement& other) noexcept :

                value_{other.value_},
                uncertainty_{other.uncertainty_} {}


            /**
             * @brief Move construct a new umeasurement object
             * 
             * @param other: umeasurement as a r-value reference
             */
            constexpr umeasurement(umeasurement&& other) noexcept :

                value_{std::move(other.value_)},
                uncertainty_{std::move(other.uncertainty_)} {}


            /// @brief default destructor
            ~umeasurement() = default;
            

        // =============================================                                                                                         
        // operators
        // =============================================  

            /**
             * @brief Copy assign an umeasurement from another umeasurement
             * 
             * @param other: umeasurement as a l-value const reference
             * 
             * @return uncertai_measurement& 
             */
            constexpr umeasurement& operator=(const umeasurement& other) noexcept {
                
                this->value_ = other.value_;
                this->uncertainty_ = other.uncertainty_; 

                return *this;

            }   


            /**
             * @brief Move assign an umeasurement from another umeasurement
             * 
             * @param other: umeasurement as a r-value reference
             * 
             * @return uncertai_measurement& 
             */
            constexpr umeasurement& operator=(umeasurement&& other) noexcept {
                
                this->value_ = std::move(other.value_);
                this->uncertainty_ = std::move(other.uncertainty_); 
                
                return *this;
                
            }   


            /**
             * @brief Compute a product and calculate the new uncertainties using the root sum of squares(rss) method
             * 
             * @param other: umeasurement as a l-value const reference
             *  
             * @return umeasurement 
             */
            template <unit_base UB2>
            constexpr umeasurement<UB * UB2> operator*(const umeasurement<UB2>& other) const noexcept {

                scalar tval1 = this->uncertainty_ / this->value_;
                scalar tval2 = other.uncertainty() / other.value();
                scalar nunc = std::sqrt(std::pow(tval1, 2) + std::pow(tval2, 2));
                scalar nval = this->value_ * other.value();

                return { nval, std::fabs(nval) * nunc };

            }
    

            /**
             * @brief Compute a product and calculate the new uncertainties using the root sum of squares(rss) method
             * 
             * @param other: umeasurement as a r-value reference
             *  
             * @return umeasurement 
             */
            template <unit_base UB2>
            constexpr umeasurement<UB * UB2> operator*(umeasurement<UB2>&& other) const noexcept {

                scalar tval1 = this->uncertainty_ / this->value_;
                scalar tval2 = other.uncertainty() / other.value();
                scalar ntol = std::sqrt(std::pow(tval1, 2) + std::pow(tval2, 2));
                scalar nval = this->value_ * other.value();

                return { nval, std::fabs(nval) * ntol };

            }


            /**
             * @brief Compute a division and calculate the new uncertainties using the root sum of squares(rss) method
             * 
             * @param other: umeasurement as a l-value const reference
             * 
             * @return constexpr umeasurement 
             */
            template <unit_base UB2>
            constexpr umeasurement<UB / UB2> operator/(const umeasurement<UB2>& other) const {
                
                if (other.value_ == 0.0) 
                    throw std::invalid_argument("Cannot divide umeasurement by a zero umeasurement");

                scalar tval1 = this->uncertainty_ / this->value_;
                scalar tval2 = other.uncertainty() / other.value();
                scalar ntol = std::sqrt(std::pow(tval1, 2) + std::pow(tval2, 2));
                scalar nval = this->value_ / other.value();

                return { nval, std::fabs(nval) * ntol };
            
            }


            /**
             * @brief Compute a division and calculate the new uncertainties using the root sum of squares(rss) method
             * 
             * @param other: umeasurement as a r-value reference
             * 
             * @return constexpr umeasurement 
             */
            template <unit_base UB2>
            constexpr umeasurement<UB / UB2> operator/(umeasurement<UB2>&& other) const {
                
                if (other.value_ == 0.0) 
                    throw std::invalid_argument("Cannot divide umeasurement by a zero umeasurement");

                scalar tval1 = this->uncertainty_ / this->value_;
                scalar tval2 = other.uncertainty() / other.value();
                scalar ntol = std::sqrt(std::pow(tval1, 2) + std::pow(tval2, 2));
                scalar nval = this->value_ / other.value();

                return { nval, std::fabs(nval) * ntol };
            
            }


            /**
             * @brief Compute an addition and calculate the new uncertainties using the root sum of squares(rss) method
             * 
             * @param other: umeasurement as a l-value const reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement operator+(const umeasurement& other) const noexcept {
                
                return { this->value_ + other.value(), std::sqrt(std::pow(this->uncertainty_, 2) + std::pow(other.uncertainty(), 2)) };
            
            }


            /**
             * @brief Compute an addition and calculate the new uncertainties using the root sum of squares(rss) method
             * 
             * @param other: umeasurement as a r-value reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement operator+(umeasurement&& other) const noexcept {
                
                return { this->value_ + other.value(), std::sqrt(std::pow(this->uncertainty_, 2) + std::pow(other.uncertainty(), 2)) };
            
            }


            /**
             * @brief Return the opposite of this umeasurement
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement operator-() const noexcept {

                return { -this->value_, this->uncertainty_ };
            
            }


            /**
             * @brief Compute a subtraction and calculate the new uncertainties using the root sum of squares(rss) method
             * 
             * @param other: umeasurement as a l-value const reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement operator-(const umeasurement& other) const noexcept {
                
                return { this->value_ - other.value(), std::sqrt(std::pow(this->uncertainty_, 2) + std::pow(other.uncertainty(), 2)) };
            
            }


            /**
             * @brief Compute a subtraction and calculate the new uncertainties using the root sum of squares(rss) method
             * 
             * @param other: umeasurement as a r-value reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement operator-(umeasurement&& other) const noexcept {
                
                return { this->value_ - other.value(), std::sqrt(std::pow(this->uncertainty_, 2) + std::pow(other.uncertainty(), 2)) };
            
            }
            

            /**
             * @brief Compute a product and calculate the new uncertainties using the simple method for uncertainty propagation
             * 
             * @param other: umeasurement as a l-value const reference
             * 
             * @return umeasurement 
             */
            template <unit_base UB2>
            constexpr umeasurement<UB * UB2> simple_product(const umeasurement<UB2>& other) const noexcept {
                
                scalar ntol = this->uncertainty_ / std::fabs(this->value_) + other.uncertainty() / std::fabs(other.value());
                scalar nval = this->value_ * other.value();

                return { nval, std::fabs(nval) * ntol };
            
            }

            
            /**
             * @brief Compute a product and calculate the new uncertainties using the simple method for uncertainty propagation
             * 
             * @param other: umeasurement as a r-value reference
             * 
             * @return umeasurement 
             */
            template <unit_base UB2>
            constexpr umeasurement<UB * UB2> simple_product(umeasurement<UB2>&& other) const noexcept {
                
                scalar ntol = this->uncertainty_ / std::fabs(this->value_) + other.uncertainty() / std::fabs(other.value());
                scalar nval = this->value_ * other.value();

                return { nval, std::fabs(nval) * ntol };
            
            }


            /**
             * @brief Compute a division and calculate the new uncertainties using simple method for uncertainty propagation
             * 
             * @param other: umeasurement as a l-value const reference
             * 
             * @return constexpr umeasurement 
             */
            template <unit_base UB2>
            constexpr umeasurement<UB / UB2> simple_divide(const umeasurement<UB2>& other) const {
                
                if (other.value() == 0.0) 
                    throw std::invalid_argument("Cannot divide umeasurement by a zero umeasurement");

                scalar ntol = this->uncertainty_ / std::fabs(this->value_) + other.uncertainty() / std::fabs(other.value());
                scalar nval = this->value_ / other.value();

                return { nval, std::fabs(nval) * ntol };
            
            }


            /**
             * @brief Compute a division and calculate the new uncertainties using simple method for uncertainty propagation
             * 
             * @param other: umeasurement as a r-value reference
             * 
             * @return constexpr umeasurement 
             */
            template <unit_base UB2>
            constexpr umeasurement<UB / UB2> simple_divide(umeasurement<UB2>&& other) const {
                
                if (other.value_ == 0.0) 
                    throw std::invalid_argument("Cannot divide umeasurement by a zero umeasurement");

                scalar ntol = this->uncertainty_ / std::fabs(this->value_) + other.uncertainty() / std::fabs(other.value());
                scalar nval = this->value_ / other.value();

                return { nval, std::fabs(nval) * ntol };
            
            }


            /**
             * @brief Compute an addition and calculate the new uncertainties using the simple uncertainty summation method
             * 
             * @param other: umeasurement as a l-value const reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement simple_add(const umeasurement& other) const noexcept {

                return { this->value_ + other.value(), this->uncertainty_ + other.uncertainty() };
            
            }


            /**
             * @brief Compute an addition and calculate the new uncertainties using the simple uncertainty summation method
             * 
             * @param other: umeasurement as a r-value reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement simple_add(umeasurement&& other) const noexcept {

                return { this->value_ + other.value(), this->uncertainty_ + other.uncertainty() };
            
            }
            

            /**
             * @brief Compute a subtraction and calculate the new uncertainties using the simple uncertainty summation method
             * 
             * @param other: umeasurement as a l-value const reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement simple_subtract(const umeasurement& other) const noexcept {
                
                return { this->value_ - other.value(), this->uncertainty_ + other.uncertainty() };
            
            }


            /**
             * @brief Compute a subtraction and calculate the new uncertainties using the simple uncertainty summation method
             * 
             * @param other: umeasurement as a r-value reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement simple_subtract(umeasurement&& other) const noexcept {
                
                return { this->value_ - other.value(), this->uncertainty_ + other.uncertainty() };
            
            }


            /**
             * @brief Copy assign an umeasurement from a measurement
             * 
             * @param other: umeasurement as a l-value const reference
             * 
             * @return uncertai_measurement& 
             */
            constexpr umeasurement& operator=(const measurement<UB>& other) noexcept {
                
                this->value_ = other.value_;
                this->uncertainty_ = 0.0; 

                return *this;

            }   


            /**
             * @brief Move assign an umeasurement from a measurement
             * 
             * @param other: umeasurement as a r-value reference
             * 
             * @return uncertai_measurement& 
             */
            constexpr umeasurement& operator=(measurement<UB>&& other) noexcept {
                
                this->value_ = std::move(other.value_);
                this->uncertainty_ = 0.0; 

                return *this;
                
            }   


            /**
             * @brief Compute a product with a measurement, equivalent to umeasurement multiplication with 0 uncertainty
             * 
             * @param other: measurement as a l-value const reference
             *  
             * @return umeasurement 
             */
            template <unit_base UB2>
            constexpr umeasurement<UB * UB2> operator*(const measurement<UB2>& other) const noexcept {
                
                return { this->value_ * other.value(), std::fabs(other.value()) * this->uncertainty_ };
            
            }


            /**
             * @brief Compute a product with a measurement, equivalent to umeasurement multiplication with 0 uncertainty
             * 
             * @param other: measurement as a r-value reference
             *  
             * @return umeasurement 
             */
            template <unit_base UB2>
            constexpr umeasurement<UB * UB2> operator*(measurement<UB2>&& other) const noexcept {
                
                return { this->value_ * other.value(), std::fabs(other.value()) * this->uncertainty_ };
            
            }


            /**
             * @brief Compute a division with a measurement, equivalent to umeasurement division with 0 uncertainty
             * 
             * @param other: measurement as a l-value const reference 
             * 
             * @return constexpr umeasurement 
             */
            template <unit_base UB2>
            constexpr umeasurement<UB / UB2> operator/(const measurement<UB2>& other) const {
                
                if (other.value() == 0.0) 
                    throw std::invalid_argument("Cannot divide umeasurement by a zero measurement");

                return { this->value_ / other.value(), this->uncertainty_ / std::fabs(other.value()) };
            
            }


            /**
             * @brief Compute a division with a measurement, equivalent to umeasurement division with 0 uncertainty
             * 
             * @param other: measurement as a r-value reference 
             * 
             * @return constexpr umeasurement 
             */
            template <unit_base UB2>
            constexpr umeasurement<UB / UB2> operator/(measurement<UB2>&& other) const {
                
                if (other.value() == 0.0) 
                    throw std::invalid_argument("Cannot divide umeasurement by a zero measurement");

                return { this->value_ / other.value(), this->uncertainty_ / std::fabs(other.value()) };
            
            }


            /**
             * @brief Compute an addition with a measurement and calculate the new uncertainties using the simple uncertainty summation method
             * 
             * @param other: measurement as a l-value const reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement operator+(const measurement<UB>& other) const noexcept {

                return { this->value_ + other.value(), this->uncertainty_ };
            
            }


            /**
             * @brief Compute an addition with a measurement and calculate the new uncertainties using the simple uncertainty summation method
             * 
             * @param other: measurement as a r-value reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement operator+(measurement<UB>&& other) const noexcept {

                return { this->value_ + other.value(), this->uncertainty_ };
            
            }

            
            /**
             * @brief Compute a subtraction with a measurement and calculate the new uncertainties using the simple uncertainty summation method
             * 
             * @param other: measurement as a l-value const reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement operator-(const measurement<UB>& other) const noexcept {

                return { this->value_ - other.value(), this->uncertainty_ };
            
            }


            /**
             * @brief Compute a subtraction with a measurement and calculate the new uncertainties using the simple uncertainty summation method
             * 
             * @param other: measurement as a r-value reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement operator-(measurement<UB>&& other) const noexcept {

                return { this->value_ - other.value(), this->uncertainty_ };
            
            }

   
            /**
             * @brief Compute a product with a scalar and calculate the new uncertainties using the simple uncertainty multiplication method
             * 
             * @param val: the scalar as a l-value const reference
             * 
             * @return umeasurement 
             */
            constexpr umeasurement operator*(const scalar& val) const noexcept { 
                
                return { val * this->value_, std::fabs(val) * this->uncertainty_ }; 
            
            }


            /**
             * @brief Compute a product with a scalar and calculate the new uncertainties using the simple uncertainty multiplication method
             * 
             * @param val: the scalar as a r-value reference
             * 
             * @return umeasurement 
             */
            constexpr umeasurement operator*(scalar&& val) const noexcept { 
                
                return { val * this->value_, std::fabs(val) * this->uncertainty_ }; 
            
            }


            /**
             * @brief Divide this umeasurement with a scalar
             * 
             * @param val: the scalar to divide with as a l-value const reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement operator/(const scalar& val) const {

                if (val == 0.0) 
                    throw std::invalid_argument("Cannot divide umeasurement by 0");

                return { this->value_ / val, this->uncertainty_ / std::fabs(val) };
            
            }


            /**
             * @brief Divide this umeasurement with a scalar
             * 
             * @param val: the scalar to divide with as a r-value reference
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement operator/(scalar&& val) const {

                if (val == 0.0) 
                    throw std::invalid_argument("Cannot divide umeasurement by 0");

                return { this->value_ / val, this->uncertainty_ / std::fabs(val) };
            
            }


            // /**
            //  * @brief Equality operator between umeasurement and measurement
            //  * 
            //  * @param other: measurement to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator==(const measurement& other) const noexcept {
                
            //     if (this->uncertainty_ == 0.0) 
            //         return this->value_ == other.value_as(this->units_); 
                
            //     else 
            //         return (other.value_as(this->units_) >= (this->value_ - this->uncertainty_) && other.value_as(this->units_) <= (this->value_ + this->uncertainty_));
            
            // }


            // /**
            //  * @brief Equality operator
            //  * 
            //  * @param other: umeasurement to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator==(const umeasurement& other) const noexcept { 
                
            //     return this->simple_subtract(other) == measurement(0.0, this->units_); 
                
            // }


            // /**
            //  * @brief Inequality operator between umeasurement and measurement
            //  * 
            //  * @param other: measurement to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator!=(const measurement& other) const noexcept { 
                
            //     return !operator==(other); 
                
            // }


            // /**
            //  * @brief Inequality operator
            //  * 
            //  * @param other: umeasurement to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator!=(const umeasurement& other) const noexcept { 
                
            //     return !operator==(other); 
                
            // }

            
            // /**
            //  * @brief More than operator
            //  * 
            //  * @param other: umeasurement to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator>(const umeasurement& other) const noexcept { 
                
            //     return this->value_ > other.value_as(this->units_); 
                
            // }

            
            // /**
            //  * @brief More than operator
            //  * 
            //  * @param other: measurement to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator>(const measurement& other) const noexcept { 
                
            //     return this->value_ > other.value_as(this->units_); 
                
            // }


            // /** 
            //  * @brief More than operator
            //  * 
            //  * @param val: scalar to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator>(const scalar& val) const noexcept { 
                
            //     return this->value_ > val; 
                
            // }

            
            // /**
            //  * @brief Less than operator
            //  * 
            //  * @param other: umeasurement to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator<(const umeasurement& other) const noexcept { 
                
            //     return this->value_ < other.value_as(this->units_); 
                
            // }
            
            
            // /**
            //  * @brief Less than operator
            //  * 
            //  * @param other: measurement to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator<(const measurement& other) const noexcept { 
                
            //     return this->value_ < other.value_as(this->units_); 
                
            // }

            
            // /**
            //  * @brief Less than operator
            //  * 
            //  * @param val: scalar to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator<(const scalar& val) const noexcept { 
                
            //     return this->value_ < val; 
                
            // }

            
            // /**
            //  * @brief More than or equal operator
            //  * 
            //  * @param other: umeasurement to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator>=(const umeasurement& other) const noexcept {
                
            //     return this->simple_subtract(other).value_ >= 0.0;
            
            // }


            // /**
            //  * @brief More than or equal operator
            //  * 
            //  * @param other: measurement to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator>=(const measurement& other) const noexcept {
                
            //     return this->value_ >= other.value_as(this->units_); 
            
            // }


            // /**
            //  * @brief More than or equal operator
            //  * 
            //  * @param val: scalar to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator>=(const scalar& val) const noexcept { 

            //     return this->value_ >= val; 
                
            // }


            // /**
            //  * @brief Less than or equal operator
            //  * 
            //  * @param other: umeasurement to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator<=(const umeasurement& other) const noexcept {
                
            //     return this->simple_subtract(other).value_ <= 0.0; 
            
            // }


            // /**
            //  * @brief Less than or equal operator
            //  * 
            //  * @param other: measurement to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator<=(const measurement& other) const noexcept {
                
            //     return (this->value_ <= other.value_as(this->units_)); 
            
            // }


            // /**
            //  * @brief Less than or equal operator
            //  * 
            //  * @param val: scalar to compare as l-value const reference
            //  * 
            //  * @return bool
            //  */
            // constexpr bool operator<=(const scalar& val) const noexcept { 

            //     return this->value_ <= val; 
                
            // }

            
            // /**
            //  * @brief Perform a product between a measurement and an umeasurement
            //  * 
            //  * @param meas: measurement as l-value const reference
            //  * @param umeas: umeasurement
            //  *  
            //  * @return umeasurement 
            //  */
            // friend inline umeasurement operator*(const measurement& meas, 
            //                                      const umeasurement& umeas) noexcept { 
                                
            //     return umeas.operator*(meas); 
                            
            // }


            // /**
            //  * @brief Perform a product between a scalar and an umeasurement
            //  * 
            //  * @param value: scalar
            //  * @param umeas: umeasurement
            //  * 
            //  * @return umeasurement 
            //  */
            // friend inline umeasurement operator*(const scalar& value, 
            //                               const umeasurement& umeas) noexcept { 
                                
            //     return umeas.operator*(value); 
                            
            // }


            // /**
            //  * @brief Perform a division between a measurement and an umeasurement
            //  * 
            //  * @param meas: measurement
            //  * @param umeas: umeasurement
            //  *  
            //  * @return constexpr umeasurement 
            //  */
            // friend constexpr umeasurement operator/(const measurement& meas, 
            //                                                  const umeasurement& umeas) {
                                                        
            //     if (umeas.value_ == 0.0) 
            //         throw std::runtime_error("Cannot divide a measurement by a zero umeasurement");

            //     scalar ntol = umeas.uncertainty_ / umeas.value_;
            //     scalar nval = meas.value() / umeas.value_;

            //     return umeasurement(nval, std::fabs(nval * ntol), meas.units() / umeas.units_);
            
            // }


            // /**
            //  * @brief Perform a division between a scalar and an umeasurement
            //  * 
            //  * @param value: scalar
            //  * @param umeas: umeasurement
            //  * 
            //  * @return constexpr umeasurement 
            //  */
            // friend constexpr umeasurement operator/(const scalar& v1, 
            //                                                  const umeasurement& umeas) {

            //     if (umeas.value_ == 0.0) 
            //         throw std::runtime_error("Cannot divide a scalar by a zero umeasurement");

            //     scalar ntol = umeas.uncertainty_ / umeas.value_;
            //     scalar nval = v1 / umeas.value_;
            //     return umeasurement(nval, std::fabs(nval * ntol), umeas.units_.inv());
            
            // }

            
            // /**
            //  * @brief Perform a sum between a measurement and an umeasurement
            //  * 
            //  * @param meas: measurement as l-value const reference
            //  * @param umeas: umeasurement
            //  *  
            //  * @return constexpr umeasurement 
            //  */
            // friend constexpr umeasurement operator+(const measurement& meas, 
            //                                                  const umeasurement& umeas) {
                
            //     if (meas.units().base_ != umeas.units_.base_) 
            //         throw std::invalid_argument("Cannot sum measurement and umeasurement with different unit bases");

            //     scalar cval = umeas.units_.convertion_factor(meas.units());
            //     scalar ntol = umeas.uncertainty_ * cval;

            //     return umeasurement(meas.value() + cval * umeas.value_, ntol, meas.units());
            
            // }


            // /**
            //  * @brief Perform a subtraction between a measurement and an umeasurement
            //  * 
            //  * @param meas: measurement 
            //  * @param umeas: umeasurement
            //  *  
            //  * @return constexpr umeasurement 
            //  */
            // friend constexpr umeasurement operator-(const measurement& meas, 
            //                                                  const umeasurement& umeas) {

            //     if (meas.units().base_ != umeas.units_.base_) 
            //         throw std::invalid_argument("Cannot sum measurement and umeasurement with different unit bases");

            //     scalar cval = umeas.units_.convertion_factor(meas.units());
            //     scalar ntol = umeas.uncertainty_ * cval;

            //     return umeasurement(meas.value() - cval * umeas.value_, ntol, meas.units());
            
            // }


            // /**
            //  * @brief Equality operator between a measurement and an umeasurement
            //  * 
            //  * @param meas: measurement
            //  * @param umeas: umeasurement
            //  * 
            //  * @return bool
            //  */
            // friend constexpr bool operator==(const measurement<UB>& meas, 
            //                                  const umeasurement& umeas) noexcept { 
                
            //     return umeas == meas; 
            
            // }


            // /**
            //  * @brief Inequality operator between a measurement and an umeasurement
            //  * 
            //  * @param meas: measurement
            //  * @param umeas: umeasurement
            //  * 
            //  * @return bool
            //  */
            // friend constexpr bool operator!=(const measurement<UB>& meas, 
            //                                  const umeasurement& umeas) noexcept { 
                
            //     return umeas != meas; 
            
            // }
            

            // /**
            //  * @brief More operator between a measurement and an umeasurement
            //  * 
            //  * @param meas: measurement
            //  * @param umeas: umeasurement
            //  * 
            //  * @return bool
            //  */
            // friend constexpr bool operator>(const measurement<UB>& meas, 
            //                                 const umeasurement& umeas) noexcept { 
                
            //     return meas.value() > umeas.value_; 
            
            // }
            

            // /**
            //  * @brief Less operator between a measurement and an umeasurement
            //  * 
            //  * @param meas: measurement
            //  * @param umeas: umeasurement
            //  * 
            //  * @return bool
            //  */
            // friend constexpr bool operator<(const measurement<UB>& meas, 
            //                                 const umeasurement& umeas) noexcept { 
                
            //     return meas.value() < umeas.value_; 
            
            // }
            

            // /**
            //  * @brief More or equal operator between a measurement and an umeasurement
            //  * 
            //  * @param meas: measurement
            //  * @param umeas: umeasurement
            //  * 
            //  * @return bool
            //  */
            // friend constexpr bool operator>=(const measurement<UB>& meas, 
            //                                  const umeasurement& umeas) noexcept { 
                
            //     return (meas > umeas) ? true : (umeas == meas); 
            
            // }
            

            // /**
            // * @brief Less or equal operator between a measurement and an umeasurement
            // * 
            // * @param meas: measurement
            // * @param umeas: umeasurement
            // * 
            // * @return bool
            // * 
            // */
            // friend constexpr bool operator<=(const measurement<UB>& meas, 
            //                                  const umeasurement& umeas) noexcept { 
                
            //     return (meas < umeas) ? true : (umeas == meas); 
            
            // }


            /**
             * @brief Output operator for a umeasurement
             * 
             * @param os: std::ostream&
             * @param meas: umeasurement as l-value const reference
             * 
             * @note if the precision of the umeasurement is 0, the uncertainty is not printed
             * @note scientific notation is used if the value is greater than 1e4 or less than 1e-4
             * 
             * @return std::ostream&
             */
            friend std::ostream& operator<<(std::ostream& os, const umeasurement& umeas) noexcept { 

                scalar abs_value = std::fabs(umeas.value_);
                
                // first significative digit positions
                int32_t n_val = ((umeas.uncertainty_ >= 1) ? 
                                    std::ceil(std::log10(abs_value)) : 
                                    ((abs_value >= 1) ? 
                                        std::ceil(std::log10(abs_value)) : 
                                        std::floor(std::log10(abs_value)))); 

                int32_t n_unc = ((umeas.uncertainty_ >= 1) ? 
                                    std::ceil(std::log10(umeas.uncertainty_)) : 
                                    std::floor(std::log10(umeas.uncertainty_))); 

                int32_t prec = (n_unc > n_val) ? 0 : n_val - n_unc; 

                bool scientific_notation_needed = (abs_value >= 1e4) || 
                                                    (abs_value <= 1e-4) || 
                                                    (umeas.uncertainty_ >= 1e4) || 
                                                    (umeas.uncertainty_ <= 1e-4);

                // check if the uncertainty needs to be printed
                if (umeas.uncertainty_ == 0.0) 
                    os << umeas.as_measurement(); 
                
                // check if scientific notation is needed
                if (scientific_notation_needed) {

                    os << std::scientific; 
                    os << std::setprecision(prec) << "(" << umeas.value_ << " ± "; 
                    os << std::setprecision(0) << umeas.uncertainty_ << ") " << UB;

                } else {

                    os << std::fixed; 

                    if (umeas.uncertainty_ >= 1.) 
                        os << std::setprecision(0); 
                    else 
                        os << std::setprecision(std::fabs(n_unc)); 
                        
                    os << "(" << umeas.value_ << " ± " << umeas.uncertainty_ << ") " << UB;

                }

                os << std::defaultfloat << std::setprecision(6);
                
                return os; 
                
            }


        // =============================================                                                                                         
        // set & get methods
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
             * @brief Get the value of the measurement
             *
             * @param units: unit as l-value const reference
             * 
             * @return constexpr scalar& 
             */
            constexpr scalar value_as(const unit<UB>& units) noexcept { 
                
                return units.convert(this->value_); 
            
            }  


            /**
             * @brief Cast to a measurement
             * 
             * @return measurement 
             */
            constexpr measurement<UB> as_measurement() const noexcept { 
                
                return { this->value_ };
                
            }


            /**
             * @brief Get the uncertainty of the measurement
             * 
             * @return constexpr const scalar
             */
            constexpr scalar uncertainty() const noexcept { 
                
                return this->uncertainty_; 
            
            }                        
            
            
            /**
             * @brief Get the uncertainty of the measurement
             * 
             * @return constexpr scalar& 
             */
            constexpr scalar& uncertainty() noexcept { 
                
                return this->uncertainty_; 
            
            }  


            /**
             * @brief Get the uncertainty of measurement
             *
             * @param units: unit as l-value const reference
             * 
             * @return constexpr scalar& 
             */
            constexpr scalar& uncertainty_as(const unit<UB>& units) const noexcept { 
                
                return units.convert(this->uncertainty_); 
            
            }  


            /**
             * @brief Get the uncertainty of measurement
             *
             * @param units: unit as l-value const reference
             * 
             * @return constexpr scalar
             */
            constexpr scalar uncertainty_as(const unit<UB>& units) noexcept { 
                
                return units.convert(this->uncertainty_); 
            
            }  


            /**
             * @brief Get the relative uncertainty of the measurement
             * 
             * @return constexpr scalar
             */
            constexpr scalar relative_uncertainty() const noexcept { 
                
                return this->uncertainty_ / this->value_;

            }


            // /**
            //  * @brief Get the weight of the measurement
            //  * 
            //  * @return constexpr measurement 
            //  */
            // constexpr measurement<UB.square().inv()> weight() const {
                    
            //     return 1. / math::op::square(this->uncertainty_as_measurement());

            // }


            /**
             * @brief Get the uncertainty as a separate measurement
             * 
             * @return constexpr measurement 
             */
            constexpr measurement<UB> uncertainty_as_measurement() const noexcept { 
                
                return { this->uncertainty_ }; 
            
            }


            /**
             * @brief Get the umeasurement object
             * 
             * @return constexpr umeasurement 
             */
            constexpr umeasurement as_umeasurement() const noexcept {

                return *this; 

            }


            /**
             * @brief Get the umeasurement object
             * 
             * @return constexpr umeasurement&
             */
            constexpr umeasurement& as_umeasurement() noexcept {

                return *this; 

            }


            /**
            * @brief Print the measurement to a ostream
            * 
            * @param newLine: bool
            * 
            * @return void
            */
            void print() const noexcept { 

                std::cout << *this << '\n';

            }


        private:

        // =============================================                                                                                         
        // class members
        // =============================================  

            scalar value_; ///< the numerical value of the measurement
            
            scalar uncertainty_; ///< the uncertainty of the measurement


    }; // class umeasurement
    

} // namespace scipp::measurements