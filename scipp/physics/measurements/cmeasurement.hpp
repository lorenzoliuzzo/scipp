/**
 * @file    physics/measurements/cmeasurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the cmeasurement struct and its type traits.
 * @date    2023-04-03
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::physics {


    template <typename MEAS_TYPE>   
        requires (math::is_number_v<MEAS_TYPE> || is_measurement_v<MEAS_TYPE> || is_umeasurement_v<MEAS_TYPE>)  
    struct cmeasurement {


        // ==============================================
        // aliases
        // ==============================================

            using _t = cmeasurement<MEAS_TYPE>;

            using measurement_t = MEAS_TYPE; 

            using base_t = typename MEAS_TYPE::base_t;


        // ==============================================
        // members
        // ==============================================

            measurement_t real;

            measurement_t imag;


            inline static constexpr size_t dim = 2;


            inline static constexpr cmeasurement zero = cmeasurement{0.0}; ///< The zero measurement

            inline static constexpr cmeasurement one = cmeasurement{1.0}; ///< The one measurement

            inline static constexpr cmeasurement i = cmeasurement{0.0, 1.0}; ///< The one measurement


        // ==============================================
        // constructors
        // ==============================================

            constexpr cmeasurement() noexcept :
                
                real{}, imag{} {}


            constexpr cmeasurement(const cmeasurement& other) noexcept :

                real(other.real), imag(other.imag) {}


            constexpr cmeasurement(cmeasurement&& other) noexcept :

                real(std::move(other.real)), imag(std::move(other.imag)) {}


            constexpr cmeasurement(double&& real) noexcept :

                real(std::move(real)), imag{} {}


            constexpr cmeasurement(const double& real) noexcept :

                real(real), imag{} {}


            constexpr cmeasurement(double&& real, double&& imag) noexcept :

                real(std::move(real)), imag{std::move(imag)} {}


            constexpr cmeasurement(const double& real, const double& imag) noexcept :

                real(real), imag{imag} {}


            constexpr cmeasurement(const measurement_t& real, const measurement_t& imag) noexcept : 
                
                real(real), imag(imag) {}


            constexpr cmeasurement(const measurement_t& real) noexcept :

                real(real), imag{} {}


            constexpr cmeasurement(measurement_t&& real, measurement_t&& imag) noexcept : 
                
                real(std::move(real)), imag(std::move(imag)) {}


            constexpr cmeasurement(measurement_t&& real) noexcept :

                real(std::move(real)), imag{} {}


        // ==============================================
        // operators with cmeasurement
        // ==============================================

            constexpr bool operator==(const cmeasurement& other) const noexcept {

                return (this->real == other.real) && (this->imag == other.imag);

            }

            constexpr bool operator!=(const cmeasurement& other) const noexcept {

                return !(*this == other);

            }


            constexpr cmeasurement& operator=(const cmeasurement& other) noexcept {

                this->real = other.real;
                this->imag = other.imag;

                return *this;

            }

            constexpr cmeasurement& operator=(cmeasurement&& other) noexcept {

                this->real = std::move(other.real);
                this->imag = std::move(other.imag);

                return *this;

            }


            constexpr cmeasurement& operator+=(const cmeasurement& other) noexcept {

                this->real += other.real;
                this->imag += other.imag;

                return *this;

            }

            constexpr cmeasurement& operator+=(cmeasurement&& other) noexcept {

                this->real += std::move(other.real);
                this->imag += std::move(other.imag);

                return *this;

            }


            constexpr cmeasurement& operator-=(const cmeasurement& other) noexcept {

                this->real -= other.real;
                this->imag -= other.imag;

                return *this;

            }

            constexpr cmeasurement& operator-=(cmeasurement&& other) noexcept {

                this->real -= std::move(other.real);
                this->imag -= std::move(other.imag);

                return *this;

            }


            template <typename SCALAR_MEAS_TYPE>
                requires (is_scalar_measurement_v<SCALAR_MEAS_TYPE> || is_scalar_umeasurement_v<SCALAR_MEAS_TYPE>)
            constexpr cmeasurement& operator*=(const cmeasurement<SCALAR_MEAS_TYPE>& other) noexcept {

                this->real *= other.real; 
                this->real -= this->imag * other.imag; 
                this->imag *= other.real; 
                this->imag += this->real * other.imag;

                return *this;

            }

            template <typename SCALAR_MEAS_TYPE>
                requires (is_scalar_measurement_v<SCALAR_MEAS_TYPE> || is_scalar_umeasurement_v<SCALAR_MEAS_TYPE>)
            constexpr cmeasurement& operator*=(cmeasurement<SCALAR_MEAS_TYPE>&& other) noexcept {

                this->real *= std::move(other.real); 
                this->real -= this->imag * std::move(other.imag); 
                this->imag *= std::move(other.real); 
                this->imag += this->real * std::move(other.imag);

                return *this;

            }

            template <typename NUMBER_TYPE>
                requires (math::is_number_v<NUMBER_TYPE>)
            constexpr cmeasurement& operator*=(const NUMBER_TYPE& other) noexcept {

                this->real *= other; 
                this->imag *= other; 
                
                return *this;

            }

            template <typename NUMBER_TYPE>
                requires (math::is_number_v<NUMBER_TYPE>)
            constexpr cmeasurement& operator*=(NUMBER_TYPE&& other) noexcept {

                this->real *= std::move(other); 
                this->imag *= std::move(other); 

                return *this;

            }


            template <typename SCALAR_MEAS_TYPE>
                requires (is_scalar_measurement_v<SCALAR_MEAS_TYPE> || is_scalar_umeasurement_v<SCALAR_MEAS_TYPE>)
            constexpr cmeasurement& operator/=(const cmeasurement<SCALAR_MEAS_TYPE>& other) {

                if (other == SCALAR_MEAS_TYPE::zero) 
                    throw std::runtime_error("Cannot divide a cmeasurement measurment by zero.");

                this->real *= other.real; 
                this->real += this->imag * other.imag; 
                this->imag *= other.real;
                this->imag -= this->real * other.imag; 

                *this /= math::op::sqrt(math::op::square(other.real) + math::op::square(other.imag));

                return *this;

            }

            template <typename SCALAR_MEAS_TYPE>
                requires (is_scalar_measurement_v<SCALAR_MEAS_TYPE> || is_scalar_umeasurement_v<SCALAR_MEAS_TYPE>)
            constexpr cmeasurement& operator/=(cmeasurement<SCALAR_MEAS_TYPE>&& other) {

                if (other == SCALAR_MEAS_TYPE::zero) 
                    throw std::runtime_error("Cannot divide a cmeasurement measurment by zero.");

                this->real *= std::move(other.real); 
                this->real += this->imag * std::move(other.imag); 
                this->imag *= std::move(other.real);
                this->imag -= this->real * std::move(other.imag); 

                *this /= math::op::sqrt(math::op::square(std::move(other.real)) + math::op::square(std::move(other.imag)));

                return *this;

            }


            template <typename NUMBER_TYPE>
                requires (math::is_number_v<NUMBER_TYPE>)
            constexpr cmeasurement& operator/=(const NUMBER_TYPE& other) {

                if (other == NUMBER_TYPE{}) 
                    throw std::runtime_error("Cannot divide a cmeasurement measurment by zero.");

                this->real /= other; 
                this->imag /= other; 
                
                return *this;

            }


            template <typename NUMBER_TYPE>
                requires (math::is_number_v<NUMBER_TYPE>)
            constexpr cmeasurement& operator/=(NUMBER_TYPE&& other) {

                if (other == NUMBER_TYPE{}) 
                    throw std::runtime_error("Cannot divide a cmeasurement measurment by zero.");

                this->real /= std::move(other); 
                this->imag /= std::move(other); 

                return *this;

            }


            constexpr cmeasurement operator-() const noexcept {

                cmeasurement result; 
                result.real = -this->real;
                result.imag = -this->imag;

                return result;

            }


            constexpr cmeasurement operator+(const cmeasurement& other) const noexcept {

                cmeasurement result; 
                result.real = this->real + other.real;
                result.imag = this->imag + other.imag;

                return result;

            }

            constexpr cmeasurement operator-(const cmeasurement& other) const noexcept {

                cmeasurement result; 
                result.real = this->real - other.real;
                result.imag = this->imag - other.imag;

                return result;

            }


            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const cmeasurement<OTHER_MEAS_TYPE>& other) const noexcept {

                return math::op::mult(*this, other);

            }


            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const OTHER_MEAS_TYPE& other) const noexcept 
                -> cmeasurement<math::functions::multiply_t<measurement_t, OTHER_MEAS_TYPE>> {
                
                cmeasurement<math::functions::multiply_t<measurement_t, OTHER_MEAS_TYPE>> result; 
                result.real = this->real * other;
                result.imag = this->real * other;

                return result;

            }

            template <typename OTHER_CMEAS_TYPE>
                requires (is_cmeasurement_v<OTHER_CMEAS_TYPE>)
            constexpr auto operator/(const OTHER_CMEAS_TYPE& other) const 
                -> math::functions::divide_t<cmeasurement, OTHER_CMEAS_TYPE> {
                
                auto denom = math::op::norm(other);
                if (denom == OTHER_CMEAS_TYPE::measurement_t::zero) 
                    throw std::runtime_error("Division by zero!");

                return ((*this) * other.conj()) / denom;

            }

            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE> || math::is_number_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(const OTHER_MEAS_TYPE& other) const 
                -> math::functions::divide_t<cmeasurement, OTHER_MEAS_TYPE> {
                
                if (other == OTHER_MEAS_TYPE{})
                    throw std::runtime_error("Division by zero!");

                math::functions::divide_t<cmeasurement, OTHER_MEAS_TYPE> result; 
                result.real = this->real / other;
                result.imag = this->real / other;

                return result;

            }


            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE> || math::is_number_v<OTHER_MEAS_TYPE>)
            friend constexpr cmeasurement<math::functions::multiply_t<OTHER_MEAS_TYPE, MEAS_TYPE>> operator*(const OTHER_MEAS_TYPE& other, const cmeasurement<MEAS_TYPE>& other_c) noexcept {
                
                cmeasurement<math::functions::multiply_t<measurement_t, OTHER_MEAS_TYPE>> result; 
                result.real = other * other_c.real;
                result.imag = other * other_c.imag;

                return result;

            }

            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE>)
            friend constexpr auto operator/(const OTHER_MEAS_TYPE& other, const cmeasurement<MEAS_TYPE>& other_c) noexcept 
                -> cmeasurement<math::functions::divide_t<OTHER_MEAS_TYPE, MEAS_TYPE>> {

                return cmeasurement<OTHER_MEAS_TYPE>(other) / other_c;

            }


            friend constexpr std::ostream& operator<<(std::ostream& os, const cmeasurement& other) noexcept {


                os << '(' << other.real << " " << other.imag << ')'; 

                return os;

            }



            constexpr measurement_t x() const noexcept {

                return this->real;

            }

            constexpr measurement_t x() noexcept {

                return this->real;

            }


            constexpr measurement_t y() const noexcept {

                return this->imag;

            }         

            constexpr measurement_t y() noexcept {

                return this->imag;

            }         


            constexpr cmeasurement conj() const noexcept {

                return { this->real, -this->imag };

            }

            constexpr cmeasurement conj() noexcept {

                return { this->real, -this->imag };

            }

            constexpr auto abs() const noexcept {
                
                return math::op::abs(*this);

            }

            constexpr auto arg() const noexcept {
                
                return math::op::atan(this->imag, this->real);

            }


            inline static constexpr cmeasurement cartesian(const measurement_t& x, const measurement_t& y) noexcept {

                return { x, y };

            }
            
            template <typename SCALAR_MEAS_TYPE>
                requires (is_scalar_measurement_v<SCALAR_MEAS_TYPE> || is_scalar_umeasurement_v<SCALAR_MEAS_TYPE>)
            inline static constexpr cmeasurement polar(const measurement_t& rho, const SCALAR_MEAS_TYPE& theta) noexcept {

                return { rho * math::op::cos(theta), rho * math::op::sin(theta) };

            }


    }; // class cmeasurement


} // namespace scipp::physics