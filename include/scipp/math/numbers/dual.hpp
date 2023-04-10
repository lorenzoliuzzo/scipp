/**
 * @file    math/numbers/dual.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once 


namespace scipp::math {


    template <typename T>
        requires (physics::is_generic_measurement_v<T>)
    struct dual {


        using _t = dual<T>;

        using measurement_t = T;


        measurement_t real, imag;


        constexpr dual() noexcept : 
            
            real{}, imag{} {}


        constexpr dual(const measurement_t& real) noexcept :

            real{real}, imag{} {}

        constexpr dual(measurement_t&& real) noexcept :

            real{std::move(real)}, imag{} {}


        constexpr dual(const measurement_t& real, const measurement_t& imag) noexcept : 
            
            real{real}, imag{imag} {}

        constexpr dual(measurement_t&& real, measurement_t&& imag) noexcept :

            real{std::move(real)}, imag{std::move(imag)} {}


        virtual constexpr ~dual() = default;


        constexpr dual& operator=(const dual& other) noexcept {
            
            this->real = other.real;
            this->imag = other.imag;

            return *this;

        }   

        constexpr dual& operator=(dual&& other) noexcept {
            
            this->real = std::move(other.real);
            this->imag = std::move(other.imag);

            return *this;

        }


        constexpr dual& operator=(const T& real) noexcept {
            
            this->real = real;
            this->imag = T{};

            return *this;

        }


        constexpr dual& operator=(T&& real) noexcept {
            
            this->real = std::move(real);
            this->imag = T{};

            return *this;

        }


        constexpr dual& operator+=(const dual& other) noexcept {
            
            this->real += other.real;
            this->imag += other.imag;

            return *this;

        }

        constexpr dual& operator-=(const dual& other) noexcept {
            
            this->real -= other.real;
            this->imag -= other.imag;

            return *this;
            
        }


        constexpr dual& operator+=(const T& real) noexcept {
            
            this->real += real;
            
            return *this;

        }

        constexpr dual& operator-=(const T& real) noexcept {
            
            this->real -= real;

            return *this;

        }

        constexpr dual& operator+(const dual& other) const noexcept {
            
            dual<T> result; 
            result.real = this->real + other.real;
            result.imag = this->imag + other.imag;

            return result;

        }

        constexpr dual& operator-(const dual& other) const noexcept {
            
            dual<T> result; 
            result.real = this->real - other.real;
            result.imag = this->imag - other.imag;

            return result;

        }


        constexpr dual& operator+(const T& real) const noexcept {
            
            dual<T> result; 
            result.real = this->real + real;

            return result;

        }

        constexpr dual& operator-(const T& real) const noexcept {
            
            dual<T> result; 
            result.real = this->real - real;

            return result;

        }

        constexpr dual operator-() const noexcept {
            
            return {-real, -imag};

        }


        template <typename U>
        constexpr dual<op::measurements_prod_t<T, U>> operator*(const U& other) const noexcept {
                
            return {this->real * other, this->imag * other};
    
        }

        template <typename U>
        constexpr dual<op::measurements_div_t<T, U>> operator/(const U& other) const {

            if (other == 0)
                throw std::runtime_error("Cannot divide a dual number by a zero measurement");

            return {this->real / other, this->imag / other};

        }

        template <typename U>
        friend constexpr dual<op::measurements_prod_t<U, T>> operator*(const U& other, const dual<T>& dual) noexcept {
                
            return {dual.real * other, dual.imag * other};
    
        }

        template <typename U>
        friend constexpr dual<op::measurements_div_t<U, T>> operator/(const U& other, const dual<T>& dual) {    

            if (dual.real == 0)
                throw std::runtime_error("Cannot divide a dual number by a zero measurement");

            return {other / dual.real, -other * dual.imag / op::square(dual.real)};

        }


        template <typename U>
        constexpr dual<op::measurements_prod_t<T, U>> operator*(const dual<U>& other) const noexcept {

            return {this->real * other.real, this->real * other.imag + this->imag * other.real};

        } 

        template <typename U>
        constexpr dual<op::measurements_div_t<T, U>> operator/(const dual<U>& other) const {

            if (other.real == 0)
                throw std::runtime_error("Cannot divide a dual number by a zero measurement");

            return {this->real / other.real, (this->imag * other.real - this->real * other.imag) / op::square(other.real)};

        }


    }; /// struct dual


    template <typename T>
    struct is_dual_measurement : std::false_type {};

    template <typename T>
    struct is_dual_measurement<dual<T>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_dual_measurement_v = is_dual_measurement<T>::value;


} /// namespace scipp::math