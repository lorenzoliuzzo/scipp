/**
 * @file    umeasurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-10
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    /// @brief        The umeasurement class is a template class that represents an uncertain measurement of a physical quantity
    /// @tparam BASE: The base of the measurement
    /// @see          base_quantity struct 
    /// @see          measurement struct
    template <typename BASE>
        requires (is_base_v<BASE>)
    struct umeasurement {


        // ==============================================
        // aliases
        // ==============================================

            using type = measurement<BASE>; ///< The type of the measurement

            using base = BASE; ///< The base of the measurement


        // ==============================================
        // members
        // ==============================================

            double value; ///< The value of the measurement

            double uncertainty; ///< The uncertainty of the measurement


        // ==============================================
        // constructors
        // ==============================================

            /// @brief Default constructor
            /// @note The value and the uncertainty are set to 0.0
            constexpr umeasurement() noexcept : 

                value{0.0}, uncertainty{0.0} {}


            /// @brief Construct an umeasurement from a scalar value and a scalar uncertainty
            /// @param val: The value of the measurement
            /// @param unc: The uncertainty of the measurement
            /// @note The uncertainty must be positive
            /// @note The uncertainty is set to 0.0 by default
            constexpr umeasurement(const scalar& val, const scalar& unc = 0.0) {

                if (unc < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");
                
                this->value = val;
                this->uncertainty = unc;
            
            }             


            /// @brief Construct an umeasurement from a scalar value and a scalar uncertainty
            /// @param val: The value of the measurement
            /// @param unc: The uncertainty of the measurement
            /// @note The uncertainty must be positive
            /// @note The uncertainty is set to 0.0 by default
            constexpr umeasurement(scalar&& val, scalar&& unc = 0.0) {

                if (unc < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");
 
                this->value = std::move(val);
                this->uncertainty = std::move(unc);

            }             



            /// @brief Construct an umeasurement from a scalar value, a scalar uncertainty and an unit
            /// @param val: The value of the measurement
            /// @param unc: The uncertainty of the measurement
            /// @param UNITS: The unit of the measurement
            /// @note The uncertainty must be positive
            /// @note The unit must be of the same base of the measurement
            /// @note The value and the uncertainty must be expressed in the same unit
            template <typename UNITS> 
                requires (is_same_base_v<BASE, typename UNITS::base>)
            constexpr umeasurement(const scalar& val, const scalar& unc, const UNITS&) noexcept {

                if (unc < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");

                this->value = val * UNITS::mult; 
                this->uncertainty = unc * UNITS::mult; 

            }


            /// @brief Construct an umeasurement from a scalar value, a scalar uncertainty and an unit
            /// @param val: The value of the measurement
            /// @param unc: The uncertainty of the measurement
            /// @param UNITS: The unit of the measurement
            /// @note The uncertainty must be positive
            /// @note The unit must be of the same base of the measurement
            /// @note The value and the uncertainty must be expressed in the same unit
            template <typename UNITS> 
                requires (is_same_base_v<BASE, typename UNITS::base>)
            constexpr umeasurement(scalar&& val, scalar&& unc, const UNITS&) noexcept {

                if (unc < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");
                
                this->value = std::move(val * UNITS::mult); 
                this->uncertainty = std::move(unc * UNITS::mult); 

            }


            /// @brief Construct an umeasurement from a scalar value, a scalar uncertainty and an unit
            /// @param val: The measurement of the value
            /// @param unc: The measurement of the uncertainty
            /// @note The measurements must be expressed in the same unit
            /// @note The unit prefix that will be inherited is the value's unit prefix
            /// @note The uncertainty measurement is set to 0.0 by default
            constexpr umeasurement(const measurement<BASE>& val, const measurement<BASE>& unc = 0.0) {
                        
                if (unc.value < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");

                this->value = val.value; 
                this->uncertainty = unc.value; 

            }


            /// @brief Construct an umeasurement from a scalar value, a scalar uncertainty and an unit
            /// @param val: The measurement of the value
            /// @param unc: The measurement of the uncertainty
            /// @note The measurements must be expressed in the same unit
            /// @note The unit prefix that will be inherited is the value's unit prefix
            /// @note The uncertainty measurement is set to 0.0 by default
            constexpr umeasurement(measurement<BASE>&& val, measurement<BASE>&& unc = 0.0) {
                        
                if (unc.value < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");

                this->value = std::move(val.value); 
                this->uncertainty = std::move(unc.value); 

            }


            /// @brief Copy construct from an umeasurement
            constexpr umeasurement(const umeasurement& other) noexcept :

                value{other.value}, uncertainty{other.uncertainty} {}


            /// @brief move construct from an umeasurement
            constexpr umeasurement(umeasurement&& other) noexcept :

                value{std::move(other.value)}, uncertainty{std::move(other.uncertainty)} {}



        // ==============================================
        // operators
        // ==============================================

            /// @brief Copy assign an umeasurement from another umeasurement
            constexpr umeasurement& operator=(const umeasurement& other) noexcept {
                
                this->value = other.value;
                this->uncertainty = other.uncertainty; 

                return *this;

            }   


            /// @brief Move assign an umeasurement from another umeasurement
            constexpr umeasurement& operator=(umeasurement&& other) noexcept {
                
                this->value = std::move(other.value);
                this->uncertainty = std::move(other.uncertainty); 
                
                return *this;
                
            }   


            /// @brief Copy assign an umeasurement from another umeasurement
            constexpr umeasurement& operator=(const measurement<BASE>& other) noexcept {
                
                this->value = other.value;
                this->uncertainty = 0.0; 

                return *this;

            }   


            /// @brief Move assign an umeasurement from another umeasurement
            constexpr umeasurement& operator=(measurement<BASE>&& other) noexcept {
                
                this->value = std::move(other.value);
                this->uncertainty = 0.0; 
                
                return *this;
                
            }  


            /// @brief Check if this measurement is equal to another measurement
            constexpr bool operator==(const umeasurement& other) const noexcept {

                return this->value == other.value && this->uncertainty == other.uncertainty; 

            }
            
            
            /// @brief Check if this measurement is equal to another measurement
            constexpr bool operator!=(const umeasurement& other) const noexcept {

                return this->value != other.value && this->uncertainty != other.uncertainty; 

            }


            /// @brief Check if this measurement is equal to another measurement
            constexpr bool operator==(const measurement<BASE>& other) const noexcept {

                return this->value == other.value; 

            }
            
            
            /// @brief Check if this measurement is equal to another measurement
            constexpr bool operator!=(const measurement<BASE>& other) const noexcept {

                return this->value != other.value; 

            }


            /// @brief Add two umeasurements
            /// @param other: umeasurement as a l-value const reference
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            constexpr umeasurement& operator+=(const umeasurement& other) noexcept {

                this->value += other.value;
                this->uncertainty = std::sqrt(std::pow(this->uncertainty, 2) + std::pow(other.uncertainty, 2)); 

                return *this; 

            }


            /// @brief Add two umeasurements
            /// @param other: umeasurement as a l-value const reference
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            constexpr umeasurement operator+(const umeasurement& other) const noexcept {
                
                return { this->value + other.value, std::sqrt(std::pow(this->uncertainty, 2) + std::pow(other.uncertainty, 2)) };
            
            }


            /// @brief Subtract two umeasurements
            /// @param other: umeasurement as a l-value const reference
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            constexpr umeasurement& operator-=(const umeasurement& other) noexcept {

                this->value -= other.value;
                this->uncertainty = std::sqrt(std::pow(this->uncertainty, 2) + std::pow(other.uncertainty, 2)); 

                return *this; 

            }


            /// @brief Subtract two umeasurements
            /// @param other: umeasurement as a l-value const reference
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            constexpr umeasurement operator-(const umeasurement& other) const noexcept {
                
                return { this->value - other.value, std::sqrt(std::pow(this->uncertainty, 2) + std::pow(other.uncertainty, 2)) };
            
            }


            /// @brief Multiply two umeasurements
            /// @param other: umeasurement as a l-value const reference
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            template <typename BASE2> 
                requires (is_base_v<BASE2>)
            constexpr auto operator*=(const umeasurement<BASE2>& other) noexcept 
                -> umeasurement<base_prod_t<BASE, BASE2>>& { 
                
                double runc1 = this->uncertainty / this->value;
                double runc2 = other.uncertainty / other.value;
                double tunc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));
                double result = this->value * other.value;

                this->value = result;
                this->uncertainty = std::fabs(result) * tunc;

                return *this;

            }


            /// @brief Multiply two measurements
            /// @param other: umeasurement as a l-value const reference
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            template <typename BASE2> 
                requires (is_base_v<BASE2>)
            constexpr auto operator*(const umeasurement<BASE2>& other) const noexcept 
                -> umeasurement<base_prod_t<BASE, BASE2>> { 
                
                double runc1 = this->uncertainty / this->value;
                double runc2 = other.uncertainty / other.value;
                double tunc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));
                double result = this->value * other.value;

                return { result, std::fabs(result) * tunc };
                
            }


            /// @brief Divide two umeasurements
            /// @param other: umeasurement as a l-value const reference
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            template <typename BASE2> 
                requires (is_base_v<BASE2>)
            constexpr auto operator/=(const umeasurement<BASE2>& other) noexcept 
                -> umeasurement<base_prod_t<BASE, BASE2>>& { 
                
                double runc1 = this->uncertainty / this->value;
                double runc2 = other.uncertainty / other.value;
                double tunc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));
                double result = this->value / other.value;

                this->value = result;
                this->uncertainty = std::fabs(result) * tunc;

                return *this;

            }


            /// @brief Divide two measurements
            /// @param other: umeasurement as a l-value const reference
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            template <typename BASE2> 
                requires (is_base_v<BASE2>)
            constexpr auto operator/(const umeasurement<BASE2>& other) const 
                -> umeasurement<base_div_t<BASE, BASE2>> {

                if (other.value == 0.0) 
                    throw std::invalid_argument("Cannot divide umeasurement by a zero umeasurement");

                double runc1 = this->uncertainty / this->value;
                double runc2 = other.uncertainty / other.value;
                double tunc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));
                double result = this->value / other.value;

                return { result, std::fabs(result) * tunc };
                
            }


            /// @brief Output operator for a umeasurement
            /// @param os: std::ostream&
            /// @param umeas: umeasurement as l-value const reference
            /// @note if the precision of the umeasurement is 0, the uncertainty is not printed
            /// @note scientific notation is used if the value is greater than 1e4 or less than 1e-4
            friend std::ostream& operator<<(std::ostream& os, const umeasurement& umeas) noexcept { 

                auto abs_value = std::fabs(umeas.value);
                
                // first significative digit positions
                int32_t n_val = ((umeas.uncertainty >= 1) ? 
                                    std::ceil(std::log10(abs_value)) : 
                                    ((abs_value >= 1) ? 
                                        std::ceil(std::log10(abs_value)) : 
                                        std::floor(std::log10(abs_value)))); 

                int32_t n_unc = ((umeas.uncertainty >= 1) ? 
                                    std::ceil(std::log10(umeas.uncertainty)) : 
                                    std::floor(std::log10(umeas.uncertainty))); 

                int32_t prec = (n_unc > n_val) ? 0 : n_val - n_unc; 

                bool scientific_notation_needed = (abs_value >= 1e4) || 
                                                    (abs_value <= 1e-4) || 
                                                    (umeas.uncertainty >= 1e4) || 
                                                    (umeas.uncertainty <= 1e-4);

                // check if the uncertainty needs to be printed
                if (umeas.uncertainty == 0.0) 
                    os << umeas.as_measurement(); 
                
                // check if scientific notation is needed
                if (scientific_notation_needed) {

                    os << std::scientific; 
                    os << std::setprecision(prec) << umeas.value << " ± "; 
                    os << std::setprecision(0) << umeas.uncertainty << ' ' << BASE::to_string();

                } else {

                    os << std::fixed; 

                    if (umeas.uncertainty >= 1.) 
                        os << std::setprecision(0); 
                    else 
                        os << std::setprecision(std::fabs(n_unc)); 
                        
                    os << umeas.value << " ± " << umeas.uncertainty << ' ' << BASE::to_string();

                }

                os << std::defaultfloat << std::setprecision(6);
                
                return os; 
                
            }


            /// @brief measurement convertion operation
            constexpr measurement<BASE> as_measurement() const noexcept {

                return { this->value }; 

            }


            /// @brief Print the measurement to the standard output
            /// @param newline: If true (default case), a newline character is printed at the end of the measurement
            constexpr void print(const bool& newline = true) const noexcept {

                std::cout << *this << (newline ? '\n' : ' ');

            }

            /// @brief Print the umeasurement to the standard output
            /// @param units: The unit in which the value is printed
            /// @param newline: If true (default case), a newline character is printed at the end of the measurement
            /// @note The unit must be of the same base of the measurement

            template <typename UNITS> 
                requires (is_unit_v<UNITS> && is_same_base_v<BASE, typename UNITS::base>)
            constexpr void print(const UNITS& units, const bool& newline = true) const noexcept {

                std::cout << this->value / UNITS::mult << " ± " << this->uncertainty / UNITS::mult << (newline ? '\n' : ' '); 

            }


    }; // struct umeasurement


    template <typename T>
    struct is_umeasurement : std::false_type {}; 

    template <typename BASE> 
        requires (is_base_v<BASE>)
    struct is_umeasurement<umeasurement<BASE>> : std::true_type {};

    template <typename T>
    constexpr bool is_umeasurement_v = is_umeasurement<T>::value;

  
    template <typename... Ts>
    struct are_umeasurements : std::conjunction<is_umeasurement<Ts>...> {};

    template <typename... Ts>
    constexpr bool are_umeasurements_v = are_umeasurements<Ts...>::value;


    template <typename BASE>
        requires (is_base_v<BASE>)
    struct are_same_measurements<umeasurement<BASE>> : std::true_type {};
    
    template <typename BASE1, typename BASE2>
        requires (are_same_base_v<BASE1, BASE2>)
    struct are_same_measurements<umeasurement<BASE1>, umeasurement<BASE2>> : std::true_type {};

    template <typename BASE, typename... Ts>
        requires (are_same_base_v<BASE, typename Ts::base> && ...)
    struct are_same_measurements<umeasurement<BASE>, Ts...> : are_same_measurements<Ts...> {};


} // namespace physics