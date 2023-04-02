#pragma once


namespace scipp::math {


    template <typename T> 
    struct complex {


        // ====================================================
        // data members
        // ====================================================
            
            T real;
            T imag;


        // ====================================================
        // constructors
        // ====================================================

            constexpr complex(T real, T imag) noexcept : 
                
                real(real), imag(imag) {}


            constexpr complex(T real) noexcept :

                real(real), imag() {}


            constexpr complex() noexcept :

                real(), imag() {}

            
        // ====================================================
        // operators
        // ====================================================

            constexpr complex<T> operator+(const complex<T> &other) const noexcept {

                return complex<T>(real + other.real, imag + other.imag);
            }


            constexpr complex<T> operator-(const complex<T> &other) const noexcept {

                return complex<T>(real - other.real, imag - other.imag);
            }


            constexpr complex<T> operator*(const complex<T> &other) const noexcept {

                return complex<T>(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
            }


            constexpr complex<T> operator/(const complex<T> &other) const noexcept {

                return complex<T>((real * other.real + imag * other.imag) / (other.real * other.real + other.imag * other.imag), (imag * other.real - real * other.imag) / (other.real * other.real + other.imag * other.imag));
            }


            constexpr complex<T> operator+(const T &other) const noexcept {

                return complex<T>(real + other, imag);
            }


            constexpr complex<T> operator-(const T &other) const noexcept {

                return complex<T>(real - other, imag);
            }


            constexpr complex<T> operator*(const T &other) const noexcept {

                return complex<T>(real * other, imag * other);
            }


            constexpr complex<T> operator/(const T &other) const noexcept {

                return complex<T>(real / other, imag / other);
            }


            constexpr complex<T> operator-() const noexcept {

                return complex<T>(-real, -imag);
            }


            constexpr complex<T> operator+=(const complex<T> &other) noexcept {

                this->real += other.real;
                this->imag += other.imag;

                return *this;
            }


            constexpr complex<T> operator-=(const complex<T> &other) noexcept {

                this->real -= other.real;
                this->imag -= other.imag;

                return *this;
            }


            template <typename U>
            constexpr complex<op::measurements_prod_t<T, U>> operator*(const complex<U> &other) noexcept {
                
                complex<op::measurements_prod_t<T, U>> result;
                result.real = this->real * other.real - this->imag * other.imag;
                result.imag = this->real * other.imag + this->imag * other.real;

                return result;
            }


            template <typename U>
            constexpr complex<op::measurements_div_t<T, U>> operator/(const complex<U> &other) noexcept {

                const auto other_norm2 = other.norm2(); 
                this->real = (this->real * other.real + this->imag * other.imag) / other_norm2; 
                this->imag = (this->imag * other.real - this->real * other.imag) / other_norm2;

                return *this;
            }


            constexpr complex<T> operator+=(const T &other) noexcept {

                this->real += other;

                return *this;
            }


        // ====================================================
        // methods
        // ====================================================

            constexpr T norm() const noexcept {

                return op::sqrt(op::square(this->real) + op::square(this->imag)); 

            }


            constexpr op::measurement_square_t<T> norm2() const noexcept {

                return op::square(this->real) + op::square(this->imag); 

            }


            constexpr complex<T> conj() const noexcept {

                return complex<T>(this->real, -this->imag);

            }


            constexpr complex<T>& normalize() noexcept {

                const auto norm = this->norm();
                this->real /= norm;
                this->imag /= norm;

                return *this;
            }


            constexpr complex<T> normalized() const noexcept {

                const auto norm = this->norm();
                return complex<T>(this->real / norm, this->imag / norm);
            }


            constexpr complex<T> pow(const T &exponent) const noexcept {

                const auto norm = this->norm();
                const auto arg = this->arg();
                const auto new_norm = op::pow(norm, exponent);
                const auto new_arg = arg * exponent;

                return complex<T>(new_norm * op::cos(new_arg), new_norm * op::sin(new_arg));
            }


            constexpr T arg() const noexcept {

                return op::atan(this->imag, this->real);
            }


            constexpr complex<T> exp() const noexcept {

                return complex<T>(op::exp(this->real) * op::cos(this->imag), op::exp(this->real) * op::sin(this->imag));
            }


            constexpr complex<T> log() const noexcept {

                return complex<T>(op::log(this->norm()), this->arg());
            }
            

    }; /// struct complex


} // namespace scipp::math