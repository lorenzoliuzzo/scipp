/**
 * @file    umeasurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-17
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
    template <typename BASE_TYPE>
        requires (is_base_v<BASE_TYPE>)
    struct umeasurement {


        // ==============================================
        // aliases
        // ==============================================

            using type = measurement<BASE_TYPE>; ///< The type of the measurement

            using base = BASE_TYPE; ///< The base of the measurement


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
            constexpr umeasurement(const double& val, const double& unc = 0.0) {

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
            constexpr umeasurement(double&& val, double&& unc = 0.0) {

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
            template <typename UNIT_TYPE> 
                requires (is_same_base_v<BASE_TYPE, typename UNIT_TYPE::base>)
            constexpr umeasurement(const double& val, const double& unc, const UNIT_TYPE&) {

                if (unc < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");

                this->value = val * UNIT_TYPE::mult; 
                this->uncertainty = unc * UNIT_TYPE::mult; 

            }


            /// @brief Construct an umeasurement from a scalar value, a scalar uncertainty and an unit
            /// @param val: The value of the measurement
            /// @param unc: The uncertainty of the measurement
            /// @param UNITS: The unit of the measurement
            /// @note The uncertainty must be positive
            /// @note The unit must be of the same base of the measurement
            /// @note The value and the uncertainty must be expressed in the same unit
            template <typename UNIT_TYPE> 
                requires (is_same_base_v<BASE_TYPE, typename UNIT_TYPE::base>)
            constexpr umeasurement(double&& val, double&& unc, const UNIT_TYPE&) {

                if (unc < 0.0) 
                    throw std::invalid_argument("Cannot instantiate an umeasurement with a negative uncertainty");
                
                this->value = std::move(val * UNIT_TYPE::mult); 
                this->uncertainty = std::move(unc * UNIT_TYPE::mult); 

            }


            /// @brief Construct an umeasurement from a scalar value, a scalar uncertainty and an unit
            /// @param val: The measurement of the value
            /// @param unc: The measurement of the uncertainty
            /// @note The measurements must be expressed in the same unit
            /// @note The unit prefix that will be inherited is the value's unit prefix
            /// @note The uncertainty measurement is set to 0.0 by default
            constexpr umeasurement(const measurement<BASE_TYPE>& val, const measurement<BASE_TYPE>& unc = 0.0) {
                        
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
            constexpr umeasurement(measurement<BASE_TYPE>&& val, measurement<BASE_TYPE>&& unc = 0.0) {
                        
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
            constexpr umeasurement& operator=(const measurement<BASE_TYPE>& other) noexcept {
                
                this->value = other.value;
                this->uncertainty = 0.0; 

                return *this;

            }   


            /// @brief Move assign an umeasurement from another umeasurement
            constexpr umeasurement& operator=(measurement<BASE_TYPE>&& other) noexcept {
                
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
            constexpr bool operator==(const measurement<BASE_TYPE>& other) const noexcept {

                return this->value == other.value; 

            }
            
            
            /// @brief Check if this measurement is equal to another measurement
            constexpr bool operator!=(const measurement<BASE_TYPE>& other) const noexcept {

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
            template <typename OTHER_BASE_TYPE> 
                requires (is_base_v<OTHER_BASE_TYPE>)
            constexpr auto operator*=(const umeasurement<OTHER_BASE_TYPE>& other) noexcept 
                -> umeasurement<math::op::base_product_t<BASE_TYPE, OTHER_BASE_TYPE>>& { 
                
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
            template <typename OTHER_BASE_TYPE> 
                requires (is_base_v<OTHER_BASE_TYPE>)
            constexpr auto operator*(const umeasurement<OTHER_BASE_TYPE>& other) const noexcept 
                -> umeasurement<math::op::base_product_t<BASE_TYPE, OTHER_BASE_TYPE>> { 
                
                double runc1 = this->uncertainty / this->value;
                double runc2 = other.uncertainty / other.value;
                double tunc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));
                double result = this->value * other.value;

                return { result, std::fabs(result) * tunc };
                
            }


            /// @brief Divide two umeasurements
            /// @param other: umeasurement as a l-value const reference
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            template <typename OTHER_BASE_TYPE> 
                requires (is_base_v<OTHER_BASE_TYPE>)
            constexpr auto operator/=(const umeasurement<OTHER_BASE_TYPE>& other) noexcept 
                -> umeasurement<math::op::base_product_t<BASE_TYPE, OTHER_BASE_TYPE>>& { 
                
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
            template <typename OTHER_BASE_TYPE> 
                requires (is_base_v<OTHER_BASE_TYPE>)
            constexpr auto operator/(const umeasurement<OTHER_BASE_TYPE>& other) const 
                -> umeasurement<math::op::base_division_t<BASE_TYPE, OTHER_BASE_TYPE>> {

                if (other.value == 0.0) 
                    throw std::invalid_argument("Cannot divide umeasurement by a zero umeasurement");

                double runc1 = this->uncertainty / this->value;
                double runc2 = other.uncertainty / other.value;
                double tunc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));
                double result = this->value / other.value;

                return { result, std::fabs(result) * tunc };
                
            }


            friend constexpr umeasurement operator*(const double& val, const umeasurement& meas) noexcept {

                return { val * meas.value, std::fabs(val) * meas.uncertainty };
                
            }


            /// @brief Divide a scalar by a umeasurement
            /// @param val: The scalar value as lvalue const reference
            /// @param meas: The umeasurement as lvalue const reference
            /// @return umeasurement<math::op::base_invert_t<BASE_TYPE>>
            friend constexpr auto operator/(const double& val, const umeasurement& meas)
                -> umeasurement<math::op::base_invert_t<BASE_TYPE>> {

                if (meas.value == 0.0) 
                    throw std::runtime_error("Cannot divide a scalar by a zero umeasurement");

                return { val / meas.value, std::fabs(val) * meas.uncertainty / std::pow(meas.value, 2) };
                
            }


            /// @brief Output operator for a umeasurement
            /// @param os: std::ostream&
            /// @param umeas: umeasurement as l-value const reference
            /// @note if the precision of the umeasurement is 0, the uncertainty is not printed
            /// @note scientific notation is used if the value is greater than 1e4 or less than 1e-4
            friend std::ostream& operator<<(std::ostream& os, const umeasurement& meas) noexcept { 

                double abs_value = std::fabs(meas.value);
                
                // first significative digit positions
                int n_val = ((meas.uncertainty >= 1) ? 
                                    std::ceil(std::log10(abs_value)) : 
                                    ((abs_value >= 1) ? 
                                        std::ceil(std::log10(abs_value)) : 
                                        std::floor(std::log10(abs_value)))); 

                int n_unc = ((meas.uncertainty >= 1) ? 
                                    std::ceil(std::log10(meas.uncertainty)) : 
                                    std::floor(std::log10(meas.uncertainty))); 

                int prec = (n_unc > n_val) ? 0 : n_val - n_unc; 

                bool scientific_notation_needed = abs_value >= 1e4 || abs_value <= 1e-4 || 
                                                  meas.uncertainty >= 1e4 || meas.uncertainty <= 1e-4;

                // check if the uncertainty needs to be printed
                if (meas.uncertainty == 0.0) 
                    os << meas.as_measurement(); 
                
                // check if scientific notation is needed
                else if (scientific_notation_needed) {

                    os << std::scientific; 
                    os << std::setprecision(prec - 1) << meas.value << " ± "; 
                    os << std::setprecision(0) << meas.uncertainty << ' ' << BASE_TYPE::to_string();

                } else {

                    os << std::fixed; 

                    if (meas.uncertainty >= 1.) 
                        os << std::setprecision(0); 
                    else 
                        os << std::setprecision(std::fabs(n_unc)); 
                        
                    os << meas.value << " ± " << meas.uncertainty << ' ' << BASE_TYPE::to_string();

                }

                os << std::defaultfloat << std::setprecision(6);
                
                return os; 
                
            }


        // ==============================================
        // methods
        // ==============================================

            /// @brief  Get the value of the measurement in the specified unit
            /// @param  UNITS: The unit in which the value is returned
            /// @note   The unit must be of the same base of the measurement
            template <typename UNIT_TYPE> 
                requires (is_unit_v<UNIT_TYPE> && is_same_base_v<BASE_TYPE, typename UNIT_TYPE::base>)
            constexpr double value_as(const UNIT_TYPE&) const noexcept { 
                
                return this->value / UNIT_TYPE::mult; 
                
            }


            /// @brief  Get the uncertainty of the measurement in the specified unit
            /// @param  UNITS: The unit in which the uncertainty is returned
            /// @note   The unit must be of the same base of the measurement
            template <typename UNIT_TYPE> 
                requires (is_unit_v<UNIT_TYPE> && is_same_base_v<BASE_TYPE, typename UNIT_TYPE::base>)
            constexpr double uncertainty_as(const UNIT_TYPE&) const noexcept { 
                
                return this->uncertainty / UNIT_TYPE::mult; 
                
            }


            /// @brief Get the value as measurement 
            constexpr measurement<BASE_TYPE> as_measurement() const noexcept {

                return { this->value }; 

            }


            /// @brief Get the uncertainty as measurement 
            constexpr measurement<BASE_TYPE> uncertainty_as_measurement() const noexcept {

                return { this->uncertainty }; 

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
            template <typename UNIT_TYPE> 
                requires (is_unit_v<UNIT_TYPE> && is_same_base_v<BASE_TYPE, typename UNIT_TYPE::base>)
            constexpr void print_as(const UNIT_TYPE&, const bool& newline = true) const noexcept {

                std::cout << this->value / UNIT_TYPE::mult << " ± " << this->uncertainty / UNIT_TYPE::mult << (newline ? '\n' : ' '); 

            }


    }; // struct umeasurement


    // =============================================
    // measurement template guidelines
    // =============================================

        template <typename UNIT_TYPE> 
            requires (is_unit_v<UNIT_TYPE>)
        umeasurement(const double&, const double&, const UNIT_TYPE&) 
            -> umeasurement<typename UNIT_TYPE::base>;

        template <typename UNIT_TYPE> 
            requires (is_unit_v<UNIT_TYPE>)
        umeasurement(double&&, double&&, const UNIT_TYPE&) 
            -> umeasurement<typename UNIT_TYPE::base>;


    // =============================================
    // umeasurement type traits
    // =============================================

        template <typename T>
        struct is_umeasurement : std::false_type {}; 

        template <typename BASE_TYPE> 
            requires (is_base_v<BASE_TYPE>)
        struct is_umeasurement<umeasurement<BASE_TYPE>> : std::true_type {};

        template <typename T>
        constexpr bool is_umeasurement_v = is_umeasurement<T>::value;

    
        template <typename... Ts>
        struct are_umeasurements : std::conjunction<is_umeasurement<Ts>...> {};

        template <typename... Ts>
        constexpr bool are_umeasurements_v = are_umeasurements<Ts...>::value;


    // =============================================
    // measurements type traits
    // =============================================

        /// @brief Type trait to check if a type is a measurement or an umeasurement
        template <typename T>
        struct is_generic_measurement : std::false_type {};

        template <typename BASE_TYPE>
        struct is_generic_measurement<measurement<BASE_TYPE>> : std::true_type {};

        template <typename BASE_TYPE>
        struct is_generic_measurement<umeasurement<BASE_TYPE>> : std::true_type {};

        template <typename MEAS_TYPE>
        constexpr bool is_generic_measurement_v = is_generic_measurement<MEAS_TYPE>::value;


        /// @brief Type trait to check if some types are measurements or umeasurements
        template <typename... Ts>
        struct are_generic_measurements : std::false_type {};

        template <typename MEAS_TYPE>
        struct are_generic_measurements<MEAS_TYPE> : is_generic_measurement<MEAS_TYPE> {};

        template <typename MEAS_TYPE, typename... MEAS_TYPEs>
        struct are_generic_measurements<MEAS_TYPE, MEAS_TYPEs...> : std::conjunction<is_generic_measurement<MEAS_TYPE>, are_generic_measurements<MEAS_TYPEs...>> {};

        template <typename... MEAS_TYPEs>
        constexpr bool are_generic_measurements_v = are_generic_measurements<MEAS_TYPEs...>::value;


        /// @brief Check if all the measurements are of the same base
        template <typename T, typename... Ts>
        struct are_same_measurements : std::false_type {};

        template <typename BASE_TYPE>
            requires (is_base_v<BASE_TYPE>)
        struct are_same_measurements<measurement<BASE_TYPE>> : std::true_type {};

        template <typename BASE_TYPE>
            requires (is_base_v<BASE_TYPE>)
        struct are_same_measurements<umeasurement<BASE_TYPE>> : std::true_type {};

        template <typename MEAS_TYPE, typename... MEAS_TYPEs>
            requires (are_generic_measurements_v<MEAS_TYPE, MEAS_TYPEs...>)
        struct are_same_measurements<MEAS_TYPE, MEAS_TYPE, MEAS_TYPEs...> : are_same_measurements<MEAS_TYPE, MEAS_TYPEs...> {};

        template <typename MEAS_TYPE, typename... MEAS_TYPEs>
        constexpr bool are_same_measurements_v = are_same_measurements<MEAS_TYPE, MEAS_TYPEs...>::value;


} // namespace physics