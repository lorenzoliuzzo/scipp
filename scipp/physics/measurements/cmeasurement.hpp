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
        requires (is_measurement_v<MEAS_TYPE> || is_umeasurement_v<MEAS_TYPE>)
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


            inline static constexpr std::size_t dim = 2;


        // ==============================================
        // constructors
        // ==============================================

            constexpr cmeasurement() noexcept :
                
                real{}, imag{} {}


            constexpr cmeasurement(const cmeasurement& other) noexcept :

                real(other.real), imag(other.imag) {}


            constexpr cmeasurement(cmeasurement&& other) noexcept :

                real(std::move(other.real)), imag(std::move(other.imag)) {}


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


            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> && is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr cmeasurement& operator*=(const cmeasurement<OTHER_MEAS_TYPE>& other) noexcept {

                this->real *= other.real; 
                this->real -= this->imag * other.imag; 
                this->imag *= other.real; 
                this->imag += this->real * other.imag;

                return *this;

            }

            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> && is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr cmeasurement& operator*=(cmeasurement<OTHER_MEAS_TYPE>&& other) noexcept {

                this->real *= std::move(other.real); 
                this->real -= this->imag * std::move(other.imag); 
                this->imag *= std::move(other.real); 
                this->imag += this->real * std::move(other.imag);

                return *this;

            }

            template <typename SCALAR_TYPE>
                requires (is_scalar_v<SCALAR_TYPE>)
            constexpr cmeasurement& operator*=(const SCALAR_TYPE& other) noexcept {

                this->real *= other; 
                this->imag *= other; 
                
                return *this;

            }

            template <typename SCALAR_TYPE>
                requires (is_scalar_v<SCALAR_TYPE>)
            constexpr cmeasurement& operator*=(SCALAR_TYPE&& other) noexcept {

                this->real *= std::move(other); 
                this->imag *= std::move(other); 

                return *this;

            }


            template <typename SCALAR_TYPE>
                requires (is_scalar_v<SCALAR_TYPE>)
            constexpr cmeasurement& operator/=(const cmeasurement<SCALAR_TYPE>& other) {

                if (other == measurement_t::zero) 
                    throw std::runtime_error("Cannot divide a cmeasurement measurment by zero.");

                this->real *= other.real; 
                this->real += this->imag * other.imag; 
                this->imag *= other.real;
                this->imag -= this->real * other.imag; 

                *this /= math::op::sqrt(math::op::square(other.real) + math::op::square(other.imag));

                return *this;

            }

            template <typename SCALAR_TYPE>
                requires (is_scalar_v<SCALAR_TYPE>)
            constexpr cmeasurement& operator/=(cmeasurement<SCALAR_TYPE>&& other) {

                if (other == measurement_t::zero) 
                    throw std::runtime_error("Cannot divide a cmeasurement measurment by zero.");

                this->real *= std::move(other.real); 
                this->real += this->imag * std::move(other.imag); 
                this->imag *= std::move(other.real);
                this->imag -= this->real * std::move(other.imag); 

                *this /= math::op::sqrt(math::op::square(std::move(other.real)) + math::op::square(std::move(other.imag)));

                return *this;

            }

            template <typename SCALAR_TYPE>
                requires (is_scalar_v<SCALAR_TYPE>)
            constexpr cmeasurement& operator/=(const SCALAR_TYPE& other) {

                if (other == measurement_t::zero) 
                    throw std::runtime_error("Cannot divide a cmeasurement measurment by zero.");

                this->real /= other; 
                this->imag /= other; 
                
                return *this;

            }

            template <typename SCALAR_TYPE>
                requires (is_scalar_v<SCALAR_TYPE>)
            constexpr cmeasurement& operator/=(SCALAR_TYPE&& other) {

                if (other == measurement_t::zero) 
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
            constexpr auto operator*(const cmeasurement<OTHER_MEAS_TYPE>& other) const noexcept 
                -> cmeasurement<math::meta::multiply_t<measurement_t, OTHER_MEAS_TYPE>> {
                
                cmeasurement<math::meta::multiply_t<measurement_t, OTHER_MEAS_TYPE>> result; 
                result.real = this->real * other.real - this->imag * other.imag;
                result.imag = this->real * other.imag + this->imag * other.real;

                return result;

            }


            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const OTHER_MEAS_TYPE& other) const noexcept 
                -> cmeasurement<math::meta::multiply_t<measurement_t, OTHER_MEAS_TYPE>> {
                
                cmeasurement<math::meta::multiply_t<measurement_t, OTHER_MEAS_TYPE>> result; 
                result.real = this->real * other;
                result.imag = this->real * other;

                return result;

            }

            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(const OTHER_MEAS_TYPE& other) const noexcept 
                -> cmeasurement<math::meta::divide_t<measurement_t, OTHER_MEAS_TYPE>> {
                
                cmeasurement<math::meta::divide_t<measurement_t, OTHER_MEAS_TYPE>> result; 
                result.real = this->real / other;
                result.imag = this->real / other;

                return result;

            }


            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE>)
            friend constexpr cmeasurement<math::meta::multiply_t<OTHER_MEAS_TYPE, MEAS_TYPE>> operator*(const OTHER_MEAS_TYPE& other, const cmeasurement<MEAS_TYPE>& other_c) noexcept {
                
                cmeasurement<math::meta::multiply_t<measurement_t, OTHER_MEAS_TYPE>> result; 
                result.real = other * other_c.real;
                result.imag = other * other_c.imag;

                return result;

            }

            template <typename OTHER_MEAS_TYPE>
                requires (is_measurement_v<OTHER_MEAS_TYPE> || is_umeasurement_v<OTHER_MEAS_TYPE>)
            friend constexpr auto operator/(const OTHER_MEAS_TYPE& other, const cmeasurement<MEAS_TYPE>& other_c) noexcept 
                -> cmeasurement<math::meta::divide_t<OTHER_MEAS_TYPE, MEAS_TYPE>> {

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


    }; // class cmeasurement


    template <typename MEAS_TYPE>
    struct is_cmeasurement<cmeasurement<MEAS_TYPE>> : std::true_type{};


} // namespace scipp::physics