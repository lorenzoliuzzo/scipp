/**
 * @file    math/complex.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-03
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once 


namespace scipp::math {


    /// A measurement of a complex quantity, such as a complex refractive index.
    /// The measurement is represented by a pair of real and imaginary parts.
    template <typename MEAS_TYPE>   
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    struct complex {


        // ==============================================
        // aliases
        // ==============================================

            using type = complex<MEAS_TYPE>;

            using measurement_type = MEAS_TYPE; 

            using base = typename MEAS_TYPE::base;


        // ==============================================
        // members
        // ==============================================

            measurement_type real;

            measurement_type imag;


        // ==============================================
        // constructors
        // ==============================================

            constexpr complex() noexcept :
                
                real{}, imag{} {}


            constexpr complex(const complex& other) noexcept :

                real(other.real), imag(other.imag) {}


            constexpr complex(complex&& other) noexcept :

                real(std::move(other.real)), imag(std::move(other.imag)) {}


            constexpr complex(const measurement_type& real, const measurement_type& imag) noexcept : 
                
                real(real), imag(imag) {}


            constexpr complex(const measurement_type& real) noexcept :

                real(real), imag{} {}


            constexpr complex(measurement_type&& real, measurement_type&& imag) noexcept : 
                
                real(std::move(real)), imag(std::move(imag)) {}


            constexpr complex(measurement_type&& real) noexcept :

                real(std::move(real)), imag{} {}


        // ==============================================
        // operators
        // ==============================================

            constexpr complex& operator=(const complex& other) noexcept {

                this->real = other.real;
                this->imag = other.imag;

                return *this;

            }


            constexpr complex& operator=(complex&& other) noexcept {

                this->real = std::move(other.real);
                this->imag = std::move(other.imag);

                return *this;

            }


            constexpr complex& operator+=(const complex& other) noexcept {

                this->real += other.real;
                this->imag += other.imag;

                return *this;

            }

            constexpr complex& operator+=(complex&& other) noexcept {

                this->real += std::move(other.real);
                this->imag += std::move(other.imag);

                return *this;

            }


            constexpr complex& operator-=(const complex& other) noexcept {

                this->real -= other.real;
                this->imag -= other.imag;

                return *this;

            }

            constexpr complex& operator-=(complex&& other) noexcept {

                this->real -= std::move(other.real);
                this->imag -= std::move(other.imag);

                return *this;

            }


            template <typename SCALAR_TYPE>
                requires (scipp::physics::is_scalar_v<SCALAR_TYPE>)
            constexpr complex& operator*=(const complex<SCALAR_TYPE>& other) noexcept {

                this->real *= other.real; 
                this->real -= this->imag * other.imag; 
                this->imag *= other.real; 
                this->imag += this->real * other.imag;

                return *this;

            }

            template <typename SCALAR_TYPE>
                requires (scipp::physics::is_scalar_v<SCALAR_TYPE>)
            constexpr complex& operator*=(complex<SCALAR_TYPE>&& other) noexcept {

                this->real *= std::move(other.real); 
                this->real -= this->imag * std::move(other.imag); 
                this->imag *= std::move(other.real); 
                this->imag += this->real * std::move(other.imag);

                return *this;

            }

            template <typename SCALAR_TYPE>
                requires (scipp::physics::is_scalar_v<SCALAR_TYPE>)
            constexpr complex& operator*=(const SCALAR_TYPE& other) noexcept {

                this->real *= other; 
                this->imag *= other; 
                
                return *this;

            }

            template <typename SCALAR_TYPE>
                requires (scipp::physics::is_scalar_v<SCALAR_TYPE>)
            constexpr complex& operator*=(SCALAR_TYPE&& other) noexcept {

                this->real *= std::move(other); 
                this->imag *= std::move(other); 

                return *this;

            }


            template <typename SCALAR_TYPE>
                requires (scipp::physics::is_scalar_v<SCALAR_TYPE>)
            constexpr complex& operator/=(const complex<SCALAR_TYPE>& other) {

                if (other == 0.0) 
                    throw std::runtime_error("Cannot divide a complex measurment by zero.");

                this->real *= other.real; 
                this->real += this->imag * other.imag; 
                this->imag *= other.real;
                this->imag -= this->real * other.imag; 

                *this /= op::sqrt(op::square(other.real) + op::square(other.imag));

                return *this;

            }

            template <typename SCALAR_TYPE>
                requires (scipp::physics::is_scalar_v<SCALAR_TYPE>)
            constexpr complex& operator/=(complex<SCALAR_TYPE>&& other) {

                if (other == 0.0) 
                    throw std::runtime_error("Cannot divide a complex measurment by zero.");

                this->real *= std::move(other.real); 
                this->real += this->imag * std::move(other.imag); 
                this->imag *= std::move(other.real);
                this->imag -= this->real * std::move(other.imag); 

                *this /= op::sqrt(op::square(std::move(other.real)) + op::square(std::move(other.imag)));

                return *this;

            }

            template <typename SCALAR_TYPE>
                requires (scipp::physics::is_scalar_v<SCALAR_TYPE>)
            constexpr complex& operator/=(const SCALAR_TYPE& other) {

                if (other == 0.0) 
                    throw std::runtime_error("Cannot divide a complex measurment by zero.");

                this->real /= other; 
                this->imag /= other; 
                
                return *this;

            }

            template <typename SCALAR_TYPE>
                requires (scipp::physics::is_scalar_v<SCALAR_TYPE>)
            constexpr complex& operator/=(SCALAR_TYPE&& other) {

                if (other == 0.0) 
                    throw std::runtime_error("Cannot divide a complex measurment by zero.");

                this->real /= std::move(other); 
                this->imag /= std::move(other); 

                return *this;

            }


            constexpr complex operator-() const noexcept {

                complex result; 
                result.real = -this->real;
                result.imag = -this->imag;

                return result;

            }


            constexpr complex operator+(const complex& other) const noexcept {

                complex result; 
                result.real = this->real + other.real;
                result.imag = this->imag + other.imag;

                return result;

            }

            constexpr complex operator-(const complex& other) const noexcept {

                complex result; 
                result.real = this->real - other.real;
                result.imag = this->imag - other.imag;

                return result;

            }


            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const complex<OTHER_MEAS_TYPE>& other) const noexcept 
                -> complex<op::measurements_prod_t<measurement_type, OTHER_MEAS_TYPE>> {
                
                complex<op::measurements_prod_t<measurement_type, OTHER_MEAS_TYPE>> result; 
                result.real = this->real * other.real - this->imag * other.imag;
                result.imag = this->real * other.imag + this->imag * other.real;

                return result;

            }


            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const OTHER_MEAS_TYPE& other) const noexcept 
                -> complex<op::measurements_prod_t<measurement_type, OTHER_MEAS_TYPE>> {
                
                complex<op::measurements_prod_t<measurement_type, OTHER_MEAS_TYPE>> result; 
                result.real = this->real * other;
                result.imag = this->real * other;

                return result;

            }

            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(const OTHER_MEAS_TYPE& other) const noexcept 
                -> complex<op::measurements_div_t<measurement_type, OTHER_MEAS_TYPE>> {
                
                complex<op::measurements_div_t<measurement_type, OTHER_MEAS_TYPE>> result; 
                result.real = this->real / other;
                result.imag = this->real / other;

                return result;

            }


            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            friend constexpr auto operator*(const OTHER_MEAS_TYPE& other, const complex<MEAS_TYPE>& other_c) noexcept 
                -> complex<op::measurements_prod_t<OTHER_MEAS_TYPE, MEAS_TYPE>> {
                
                complex<op::measurements_prod_t<measurement_type, OTHER_MEAS_TYPE>> result; 
                result.real = other * other_c.real;
                result.imag = other * other_c.real;

                return result;

            }

            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            friend constexpr auto operator/(const OTHER_MEAS_TYPE& other, const complex<MEAS_TYPE>& other_c) noexcept 
                -> complex<op::measurements_div_t<OTHER_MEAS_TYPE, MEAS_TYPE>> {

                return complex<OTHER_MEAS_TYPE>(other) / other_c;

            }


            constexpr bool operator==(const complex& other) const noexcept {

                return (this->real == other.real) && (this->imag == other.imag);

            }

            constexpr bool operator!=(const complex& other) const noexcept {

                return !(*this == other);

            }


            friend constexpr std::ostream& operator<<(std::ostream& os, const complex& other) noexcept {


                os << '(' << other.real << " " << other.imag << ')'; 

                return os;

            }


        // ==============================================
        // methods
        // ==============================================


    };


    // ==============================================
    // complex type traits
    // ==============================================

        template <typename T>
        struct is_complex_measurement : std::false_type{};

        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct is_complex_measurement<complex<MEAS_TYPE>> : std::true_type{};

        template <typename T>
        inline constexpr bool is_complex_measurement_v = is_complex_measurement<T>::value;


        static_assert(is_complex_measurement_v<complex<physics::measurement<physics::units::metre>>>);


} // namespace scipp::math