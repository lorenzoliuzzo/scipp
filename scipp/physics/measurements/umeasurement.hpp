/**
 * @file    physics/measurements/umeasurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the umeasurement struct and its type traits.
 * @date    2023-04-02
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {
            

    /// @brief Struct umeasurement represents a physical uncertaint measurement as two scalar values and a dimentional template meta-structure 
    /// @tparam BASE: The base_quantity of the measurement
    /// @see          measurement
    template <typename BASE_TYPE>
        requires (is_base_v<BASE_TYPE>)
    struct umeasurement {


        // ==============================================
        // aliases
        // ==============================================

            using _t = measurement<BASE_TYPE>; ///< The type of the measurement

            using base_t = BASE_TYPE; ///< The base of the measurement


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

                value{0.0}, uncertainty{0.0}{}


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

                value{other.value}, uncertainty{other.uncertainty}{}


            /// @brief move construct from an umeasurement
            constexpr umeasurement(umeasurement&& other) noexcept :

                value{std::move(other.value)}, uncertainty{std::move(other.uncertainty)}{}



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


            /// @brief Copy assign an umeasurement from another measurement
            constexpr umeasurement& operator=(const measurement<BASE_TYPE>& other) noexcept {
                
                this->value = other.value;
                this->uncertainty = 0.0; 

                return *this;

            }   

            /// @brief Move assign an umeasurement from another measurement
            constexpr umeasurement& operator=(measurement<BASE_TYPE>&& other) noexcept {
                
                this->value = std::move(other.value);
                this->uncertainty = 0.0; 
                
                return *this;
                
            }  


            /// @brief Add this umeasurement and another umeasurement
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            constexpr umeasurement& operator+=(const umeasurement& other) noexcept {

                this->value += other.value;
                this->uncertainty = std::sqrt(std::pow(this->uncertainty, 2) + std::pow(other.uncertainty, 2)); 

                return *this; 

            }

            /// @brief Add this umeasurement and another umeasurement
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            constexpr umeasurement& operator+=(umeasurement&& other) noexcept {

                this->value += std::move(other.value);
                this->uncertainty = std::sqrt(std::pow(this->uncertainty, 2) + std::pow(std::move(other.uncertainty), 2)); 

                return *this; 

            }

            /// @brief Add this umeasurement and a measurement
            constexpr umeasurement& operator+=(const measurement<BASE_TYPE>& other) noexcept {

                this->value += other.value;

                return *this; 

            }

            /// @brief Add this umeasurement and a measurement
            constexpr umeasurement& operator+=(measurement<BASE_TYPE>&& other) noexcept {

                this->value += std::move(other.value);

                return *this; 

            }

            /// @brief Add two umeasurements
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            constexpr umeasurement operator+(const umeasurement& other) const noexcept {
                
                return { this->value + other.value, std::sqrt(std::pow(this->uncertainty, 2) + std::pow(other.uncertainty, 2)) };
            
            }

            /// @brief Add two umeasurements
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            constexpr umeasurement operator+(umeasurement&& other) const noexcept {
                
                return { this->value + std::move(other.value), std::sqrt(std::pow(this->uncertainty, 2) + std::pow(std::move(other.uncertainty), 2)) };
            
            }

            /// @brief Add an umeasurement and a measurement
            constexpr umeasurement operator+(const measurement<BASE_TYPE>& other) const noexcept {
                
                return { this->value + other.value, this->uncertainty };
            
            }

            /// @brief Add an umeasurement and a measurement
            constexpr umeasurement operator+(measurement<BASE_TYPE>&& other) const noexcept {
                
                return { this->value + std::move(other.value), this->uncertainty };
            
            }

            /// @brief Add a measurement and an umeasurement
            friend inline constexpr umeasurement operator+(const measurement<BASE_TYPE>& meas, const umeasurement<BASE_TYPE>& umeas) noexcept {
                
                return { meas.value + umeas.value, umeas.uncertainty };
            
            }

            /// @brief Add a measurement and an umeasurement
            friend inline constexpr umeasurement operator+(measurement<BASE_TYPE>&& meas, umeasurement<BASE_TYPE>&& umeas) noexcept {
                
                return { std::move(meas.value) + std::move(umeas.value), std::move(umeas.uncertainty) };
            
            }


            /// @brief Subtract this umeasurement and another umeasurement
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            constexpr umeasurement& operator-=(const umeasurement& other) noexcept {

                this->value -= other.value;
                this->uncertainty = std::sqrt(std::pow(this->uncertainty, 2) + std::pow(other.uncertainty, 2)); 

                return *this; 

            }

            /// @brief Subtract this umeasurement and another umeasurement
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            constexpr umeasurement& operator-=(umeasurement&& other) noexcept {

                this->value -= std::move(other.value);
                this->uncertainty = std::sqrt(std::pow(this->uncertainty, 2) + std::pow(std::move(other.uncertainty), 2)); 

                return *this; 

            }

            /// @brief Subtract this umeasurement and a measurement
            constexpr umeasurement& operator-=(const measurement<BASE_TYPE>& other) noexcept {

                this->value -= other.value;

                return *this; 

            }

            /// @brief Subtract this umeasurement and a measurement
            constexpr umeasurement& operator-=(measurement<BASE_TYPE>&& other) noexcept {

                this->value -= std::move(other.value);

                return *this; 

            }

            /// @brief Subtract two umeasurements
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            constexpr umeasurement operator-(const umeasurement& other) const noexcept {
                
                return { this->value - other.value, std::sqrt(std::pow(this->uncertainty, 2) + std::pow(other.uncertainty, 2)) };
            
            }

            /// @brief Subtract two umeasurements
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            constexpr umeasurement operator-(umeasurement&& other) const noexcept {
                
                return { this->value - std::move(other.value), std::sqrt(std::pow(this->uncertainty, 2) + std::pow(std::move(other.uncertainty), 2)) };
            
            }

            /// @brief Subtract an umeasurement and a measurement
            constexpr umeasurement operator-(const measurement<BASE_TYPE>& other) const noexcept {
                
                return { this->value - other.value, this->uncertainty };
            
            }

            /// @brief Subtract an umeasurement and a measurement
            constexpr umeasurement operator-(measurement<BASE_TYPE>&& other) const noexcept {
                
                return { this->value - std::move(other.value), this->uncertainty };
            
            }

            /// @brief Subtract a measurement and an umeasurement
            friend inline constexpr umeasurement operator-(const measurement<BASE_TYPE>& meas, const umeasurement<BASE_TYPE>& umeas) noexcept {
                
                return { meas.value - umeas.value, umeas.uncertainty };
            
            }

            /// @brief Subtract a measurement and an umeasurement
            friend inline constexpr umeasurement operator-(measurement<BASE_TYPE>&& meas, umeasurement<BASE_TYPE>&& umeas) noexcept {
                
                return { std::move(meas.value) - std::move(umeas.value), std::move(umeas.uncertainty) };
            
            }


            /// @brief Multiply two umeasurements
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            template <typename UMEAS_TYPE> 
                requires (is_umeasurement_v<UMEAS_TYPE>)
            constexpr auto operator*=(const UMEAS_TYPE& other) noexcept 
                -> math::meta::multiply_t<umeasurement, UMEAS_TYPE>& { 
                
                double result = this->value * other.value;
                double runc1 = this->uncertainty / this->value;
                double runc2 = other.uncertainty / other.value;
                double unc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));

                this->value = result;
                this->uncertainty = std::fabs(result) * unc;

                return *this;

            }

            /// @brief Multiply two umeasurements
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            template <typename UMEAS_TYPE> 
                requires (is_umeasurement_v<UMEAS_TYPE>)
            constexpr auto operator*=(UMEAS_TYPE&& other) noexcept 
                -> math::meta::multiply_t<umeasurement, UMEAS_TYPE>& { 
                
                double result = this->value * std::move(other.value);
                double runc1 = this->uncertainty / this->value;
                double runc2 = std::move(other.uncertainty) / std::move(other.value);
                double unc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));

                this->value = result;
                this->uncertainty = std::fabs(result) * unc;

                return *this;

            }

            /// @brief Multiply an umeasurement and a measurement
            template <typename MEAS_TYPE> 
                requires (is_measurement_v<MEAS_TYPE>)
            constexpr auto operator*=(const MEAS_TYPE& other) noexcept 
                -> math::meta::multiply_t<umeasurement, MEAS_TYPE>& { 
                
                this->value *= other.value;
                this->uncertainty *= std::fabs(other.value);

                return *this;

            }

            /// @brief Multiply an umeasurement and a measurement
            template <typename MEAS_TYPE> 
                requires (is_measurement_v<MEAS_TYPE>)
            constexpr auto operator*=(MEAS_TYPE&& other) noexcept 
                -> math::meta::multiply_t<umeasurement, MEAS_TYPE>& { 
                
                this->value *= std::move(other.value);
                this->uncertainty *= std::fabs(std::move(other.value));

                return *this;

            }

            /// @brief Multiply two umeasurements
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            template <typename UMEAS_TYPE> 
                requires (is_umeasurement_v<UMEAS_TYPE>)
            constexpr auto operator*(const UMEAS_TYPE& other) const noexcept 
                -> math::meta::multiply_t<umeasurement, UMEAS_TYPE> { 
                
                double runc1 = this->uncertainty / this->value;
                double runc2 = other.uncertainty / other.value;
                double tunc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));
                double result = this->value * other.value;

                return { result, std::fabs(result) * tunc };
                
            }

            /// @brief Multiply two umeasurements
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            template <typename UMEAS_TYPE> 
                requires (is_umeasurement_v<UMEAS_TYPE>)
            constexpr auto operator*(UMEAS_TYPE&& other) const noexcept 
                -> math::meta::multiply_t<umeasurement, UMEAS_TYPE> { 
                
                double runc1 = this->uncertainty / this->value;
                double runc2 = std::move(other.uncertainty) / std::move(other.value);
                double tunc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));
                double result = this->value * std::move(other.value);

                return { result, std::fabs(result) * tunc };
                
            }

            /// @brief Multiply an umeasurement with a measurement
            constexpr umeasurement operator*(const measurement<BASE_TYPE>& other) const noexcept {

                return { this->value * other.value, this->uncertainty * std::fabs(other.value) };

            }

            /// @brief Multiply an umeasurement with a measurement
            constexpr umeasurement operator*(measurement<BASE_TYPE>&& other) const noexcept {

                return { this->value * std::move(other.value), this->uncertainty * std::fabs(std::move(other.value)) };

            }

            /// @brief Multiply a measurement with an measurement
            friend inline constexpr umeasurement operator*(const measurement<BASE_TYPE>& meas, const umeasurement& umeas) noexcept {

                return { meas.value * umeas.value, umeas.uncertainty * std::fabs(meas.value) };

            }

            /// @brief Multiply a measurement with an measurement
            friend inline constexpr umeasurement operator*(measurement<BASE_TYPE>&& meas, umeasurement&& umeas) noexcept {

                return { std::move(meas.value) * std::move(umeas.value), std::move(umeas.uncertainty) * std::fabs(std::move(meas.value)) };

            }


            /// @brief Divide two umeasurements
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            template <typename OTHER_BASE_TYPE> 
                requires (is_base_v<OTHER_BASE_TYPE>)
            constexpr auto operator/=(const umeasurement<OTHER_BASE_TYPE>& other) noexcept 
                -> umeasurement<math::meta::divide_t<BASE_TYPE, OTHER_BASE_TYPE>>& { 
                
                double result = this->value / other.value;
                double runc1 = this->uncertainty / this->value;
                double runc2 = other.uncertainty / other.value;
                double unc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));

                this->value = result;
                this->uncertainty = std::fabs(result) * unc;

                return *this;

            }

            /// @brief Divide this umeasurements by an umeasurement
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            template <typename OTHER_BASE_TYPE> 
                requires (is_base_v<OTHER_BASE_TYPE>)
            constexpr auto operator/=(umeasurement<OTHER_BASE_TYPE>&& other) noexcept 
                -> umeasurement<math::meta::divide_t<BASE_TYPE, OTHER_BASE_TYPE>>& { 
                
                double result = this->value / std::move(other.value);
                double runc1 = this->uncertainty / this->value;
                double runc2 = std::move(other.uncertainty) / std::move(other.value);
                double unc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));

                this->value = result;
                this->uncertainty = std::fabs(result) * unc;

                return *this;

            }

            /// @brief Divide this umeasurement by a scalar measurement
            constexpr umeasurement& operator/=(const measurement<BASE_TYPE>& other) noexcept {

                this->value /= other.value;
                this->uncertainty /= std::fabs(other.value);

                return *this;

            }

            /// @brief Divide this umeasurement by a scalar measurement
            constexpr umeasurement& operator/=(measurement<BASE_TYPE>&& other) noexcept {

                this->value /= std::move(other.value);
                this->uncertainty /= std::fabs(std::move(other.value));

                return *this;

            }

            /// @brief Divide two measurements
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            template <typename UMEAS_TYPE> 
                requires (is_umeasurement_v<UMEAS_TYPE>)
            constexpr auto operator/(const UMEAS_TYPE& other) const 
                -> math::meta::divide_t<umeasurement, UMEAS_TYPE> {

                if (other.value == 0.0) 
                    throw std::invalid_argument("Cannot divide umeasurement by a zero umeasurement");

                double result = this->value / other.value;
                double runc1 = this->uncertainty / this->value;
                double runc2 = other.uncertainty / other.value;
                double unc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));

                return { result, std::fabs(result) * unc };
                
            }

            /// @brief Divide two measurements
            /// @note The uncertainty is propagated using the standard propagation of uncertainty formula
            template <typename UMEAS_TYPE> 
                requires (is_umeasurement_v<UMEAS_TYPE>)
            constexpr auto operator/(UMEAS_TYPE&& other) const 
                -> math::meta::divide_t<umeasurement, UMEAS_TYPE> {

                if (other.value == 0.0) 
                    throw std::invalid_argument("Cannot divide umeasurement by a zero umeasurement");

                double result = this->value / std::move(other.value);
                double runc1 = this->uncertainty / this->value;
                double runc2 = std::move(other.uncertainty) / std::move(other.value);
                double unc = std::sqrt(std::pow(runc1, 2) + std::pow(runc2, 2));

                return { result, std::fabs(result) * unc };
                
            }

            /// @brief Divide an umeasurement with a measurement
            constexpr umeasurement operator/(const measurement<BASE_TYPE>& other) const {
                
                if (other.value == 0.0)
                    throw std::invalid_argument("Cannot divide umeasurement by a zero measurement");

                return { this->value / other.value, this->uncertainty / std::fabs(other.value) };

            }

            /// @brief Divide an umeasurement with a measurement
            constexpr umeasurement operator/(measurement<BASE_TYPE>&& other) const {
                
                if (other.value == 0.0)
                    throw std::invalid_argument("Cannot divide umeasurement by a zero measurement");

                return { this->value / std::move(other.value), this->uncertainty / std::fabs(std::move(other.value)) };

            }

            /// @brief Divide a measurement with an measurement
            friend inline constexpr umeasurement operator/(const measurement<BASE_TYPE>& meas, const umeasurement& umeas) {
                
                if (umeas.value == 0.0)
                    throw std::invalid_argument("Cannot divide measurement by a zero umeasurement");

                return { meas.value / umeas.value, umeas.uncertainty * std::fabs(meas.value) / std::pow(umeas.value, 2) };

            }

            /// @brief Divide a measurement with an measurement
            friend inline constexpr umeasurement operator/(measurement<BASE_TYPE>&& meas, umeasurement&& umeas) {
                
                if (umeas.value == 0.0)
                    throw std::invalid_argument("Cannot divide measurement by a zero umeasurement");

                return { std::move(meas.value) / std::move(umeas.value), std::move(umeas.uncertainty) * std::fabs(std::move(meas.value)) / std::pow(std::move(umeas.value), 2) };

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

            /// @brief Check if this measurement is greater than another measurement
            constexpr bool operator>(const umeasurement& other) const noexcept {

                return this->value > other.value; 

            }

            /// @brief Check if this measurement is less than another measurement
            constexpr bool operator<(const umeasurement& other) const noexcept {

                return this->value < other.value; 

            }

            /// @brief Check if this measurement is greater or equal to another measurement
            constexpr bool operator>=(const umeasurement& other) const noexcept {

                return this->value >= other.value; 

            }

            /// @brief Check if this measurement is less or equal to another measurement
            constexpr bool operator<=(const umeasurement& other) const noexcept {

                return this->value <= other.value; 
            
            }


            /// @brief Output operator for an umeasurement
            /// @param os: std::ostream&
            /// @param umeas: umeasurement as l-value const reference
            /// @note if the precision of the umeasurement is 0, the uncertainty is not printed
            /// @note scientific notation is used if the value is greater than 1e4 or less than 1e-4
            friend constexpr std::ostream& operator<<(std::ostream& os, const umeasurement& meas) noexcept { 

                const double abs_value = std::fabs(meas.value);

                // determine number of digits before decimal point in value
                const int n_val = (abs_value >= 1.0) ? 
                                    std::ceil(std::log10(abs_value)) : 
                                    ((abs_value == 0.0) ? 
                                        1 : 
                                        std::floor(std::log10(std::fabs(abs_value))) + 1); 

                // determine number of digits before decimal point in uncertainty
                int n_unc = (meas.uncertainty >= 1.0) ? 
                                    std::ceil(std::log10(meas.uncertainty)) : 
                                    ((meas.uncertainty == 0.0) ? 
                                        1 : 
                                        std::floor(std::log10(std::fabs(meas.uncertainty))) + 1); 
    
                // determine the number of decimal places to show in the uncertainty
                const int prec = (n_unc > n_val) ? 0 : n_val - n_unc; 

                // determine whether scientific notation is needed
                const bool scientific_notation_needed = abs_value >= 1e4 || abs_value <= 1e-4 || 
                                                        meas.uncertainty >= 1e4 || meas.uncertainty <= 1e-4;

                // set the formatting of the output stream
                if (meas.uncertainty == 0.0) {

                    os << std::fixed; 
                    os.precision(n_val); 
                    os << meas.value << ' ' << BASE_TYPE::to_string();

                } else if (scientific_notation_needed) {

                    os << std::scientific; 
                    os.precision(prec - 1); 
                    os << meas.value << " ± ";
                    os.precision(0); 
                    os << meas.uncertainty << ' ' << BASE_TYPE::to_string();

                } else {

                    os << std::fixed;
                    if (meas.uncertainty >= 1.0) 
                        os.precision(0);
                    else 
                        os.precision(std::max(0, std::min(6, -n_unc)) + 1);
                    
                    os << meas.value << " ± " << meas.uncertainty << ' ' << BASE_TYPE::to_string();
                    
                }

                return os; 
                
            }


            /// @brief Input operator for an umeasurement
            friend constexpr std::istream& operator>>(std::istream& is, umeasurement& other) {

                std::string unit; 
                is >> other.value >> other.uncertainty >> unit;

                // Check if the read uncertainty is non-negative
                if (other.uncertainty < 0.0) 
                    throw std::runtime_error("Cannot read an umeasurement with a negative uncertainty");
                
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
                        other.uncertainty *= multiplier;

                    }

                    if (unit != base_t::to_string()) 
                        throw std::runtime_error("Unit mismatch: expected " + base_t::to_string() + ", got " + unit);

                }

                return is; 

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


            /// @brief Get the weight of the measurement
            /// @note The weight is the inverse of the square of the uncertainty
            constexpr double weight() const {

                if (this->uncertainty == 0.0)
                    throw std::runtime_error("Cannot compute the weight of a measurement with zero uncertainty");
                    
                return 1.0 / std::pow(this->uncertainty, 2);

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
    // umeasurement template guidelines
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

        template <typename BASE_TYPE> 
        struct is_umeasurement<umeasurement<BASE_TYPE>> : std::true_type{};


        /// @brief Type trait to check if two measurement types are the same
        template <typename MEAS_TYPE1, typename MEAS_TYPE2> 
            requires (are_umeasurements_v<MEAS_TYPE1, MEAS_TYPE2> && is_same_base_v<typename MEAS_TYPE1::base_t, typename MEAS_TYPE2::base_t>)
        struct is_same_umeasurement : std::true_type {};

        template <typename MEAS_TYPE1, typename MEAS_TYPE2> 
        inline static constexpr bool is_same_umeasurement_v = is_same_umeasurement<MEAS_TYPE1, MEAS_TYPE2>::value; 


        template <typename MEAS_TYPE, typename... OTHER_MEAS_TYPEs> 
        struct are_same_umeasurement : std::conjunction<is_same_umeasurement<MEAS_TYPE, OTHER_MEAS_TYPEs>...> {};
        
        template <typename MEAS_TYPE, typename... MEAS_TYPEs>
        inline static constexpr bool are_same_umeasurement_v = are_same_umeasurement<MEAS_TYPE, MEAS_TYPEs...>::value;



} // namespace physics