/**
 * @file    physics/measurements/complex.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-03
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once 


namespace scipp::physics {


    /// A measurement of a complex quantity, such as a complex refractive index.
    /// The measurement is represented by a pair of real and imaginary parts.
    template <typename MEAS_TYPE>   
        requires (is_generic_measurement_v<MEAS_TYPE>)
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

                *this /= math::op::sqrt(math::op::square(other.real) + math::op::square(other.imag));

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

                *this /= math::op::sqrt(math::op::square(std::move(other.real)) + math::op::square(std::move(other.imag)));

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
                requires (is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const complex<OTHER_MEAS_TYPE>& other) const noexcept 
                -> complex<math::op::measurements_prod_t<measurement_type, OTHER_MEAS_TYPE>> {
                
                complex<math::op::measurements_prod_t<measurement_type, OTHER_MEAS_TYPE>> result; 
                result.real = this->real * other.real - this->imag * other.imag;
                result.imag = this->real * other.imag + this->imag * other.real;

                return result;

            }


            template <typename OTHER_MEAS_TYPE>
                requires (is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const OTHER_MEAS_TYPE& other) const noexcept 
                -> complex<math::op::measurements_prod_t<measurement_type, OTHER_MEAS_TYPE>> {
                
                complex<math::op::measurements_prod_t<measurement_type, OTHER_MEAS_TYPE>> result; 
                result.real = this->real * other;
                result.imag = this->real * other;

                return result;

            }

            template <typename OTHER_MEAS_TYPE>
                requires (is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(const OTHER_MEAS_TYPE& other) const noexcept 
                -> complex<math::op::measurements_div_t<measurement_type, OTHER_MEAS_TYPE>> {
                
                complex<math::op::measurements_div_t<measurement_type, OTHER_MEAS_TYPE>> result; 
                result.real = this->real / other;
                result.imag = this->real / other;

                return result;

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

            template <typename OTHER_MEAS_TYPE>
                requires (scipp::physics::is_scalar_v<OTHER_MEAS_TYPE>)
            friend constexpr OTHER_MEAS_TYPE norm(const complex<OTHER_MEAS_TYPE>&) noexcept;



    };


    // ==============================================
    // complex type traits
    // ==============================================

        template <typename MEAS_TYPE>
            requires (is_generic_measurement_v<MEAS_TYPE>)
        struct is_complex_measurement<complex<MEAS_TYPE>> : std::true_type{};


//   ///  Return magnitude of @a z.
//   template<typename _Tp> _Tp abs(const complex<_Tp>&);
//   ///  Return phase angle of @a z.
//   template<typename _Tp> _Tp arg(const complex<_Tp>&);
//   ///  Return @a z magnitude squared.
//   template<typename _Tp> _Tp _GLIBCXX20_CONSTEXPR norm(const complex<_Tp>&);

//   ///  Return complex conjugate of @a z.
//   template<typename _Tp>
//     _GLIBCXX20_CONSTEXPR complex<_Tp> conj(const complex<_Tp>&);
//   ///  Return complex with magnitude @a rho and angle @a theta.
//   template<typename _Tp> complex<_Tp> polar(const _Tp&, const _Tp& = 0);

//   // Transcendentals:
//   /// Return complex cosine of @a z.
//   template<typename _Tp> complex<_Tp> cos(const complex<_Tp>&);
//   /// Return complex hyperbolic cosine of @a z.
//   template<typename _Tp> complex<_Tp> cosh(const complex<_Tp>&);
//   /// Return complex base e exponential of @a z.
//   template<typename _Tp> complex<_Tp> exp(const complex<_Tp>&);
//   /// Return complex natural logarithm of @a z.
//   template<typename _Tp> complex<_Tp> log(const complex<_Tp>&);
//   /// Return complex base 10 logarithm of @a z.
//   template<typename _Tp> complex<_Tp> log10(const complex<_Tp>&);
//   /// Return @a x to the @a y'th power.
//   template<typename _Tp> complex<_Tp> pow(const complex<_Tp>&, int);
//   /// Return @a x to the @a y'th power.
//   template<typename _Tp> complex<_Tp> pow(const complex<_Tp>&, const _Tp&);
//   /// Return @a x to the @a y'th power.
//   template<typename _Tp> complex<_Tp> pow(const complex<_Tp>&,
//                                           const complex<_Tp>&);
//   /// Return @a x to the @a y'th power.
//   template<typename _Tp> complex<_Tp> pow(const _Tp&, const complex<_Tp>&);
//   /// Return complex sine of @a z.
//   template<typename _Tp> complex<_Tp> sin(const complex<_Tp>&);
//   /// Return complex hyperbolic sine of @a z.
//   template<typename _Tp> complex<_Tp> sinh(const complex<_Tp>&);
//   /// Return complex square root of @a z.
//   template<typename _Tp> complex<_Tp> sqrt(const complex<_Tp>&);
//   /// Return complex tangent of @a z.
//   template<typename _Tp> complex<_Tp> tan(const complex<_Tp>&);
//   /// Return complex hyperbolic tangent of @a z.
//   template<typename _Tp> complex<_Tp> tanh(const complex<_Tp>&);


} // namespace scipp::physics