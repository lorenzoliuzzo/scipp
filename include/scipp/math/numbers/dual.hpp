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


    template <typename MEAS_TYPE>
        requires (physics::is_generic_measurement_v<MEAS_TYPE>)
    struct dual {


        // ==============================================
        // aliases
        // ==============================================

            using _t = dual<MEAS_TYPE>;

            using measurement_t = MEAS_TYPE;


        // ==============================================
        // members
        // ==============================================

            measurement_t real; 

            measurement_t imag;


        // ==============================================
        // constructors
        // ==============================================

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


            constexpr ~dual() = default;


        // ==============================================
        // operators with duals
        // ==============================================

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


            constexpr dual& operator+=(const dual& other) noexcept {
                
                this->real += other.real;
                this->imag += other.imag;

                return *this;

            }

            constexpr dual& operator+=(dual&& other) noexcept {
                
                this->real += std::move(other.real);
                this->imag += std::move(other.imag);

                return *this;

            }


            constexpr dual& operator-=(const dual& other) noexcept {
                
                this->real -= other.real;
                this->imag -= other.imag;

                return *this;
                
            }

            constexpr dual& operator-=(dual&& other) noexcept {
                
                this->real -= std::move(other.real);
                this->imag -= std::move(other.imag);

                return *this;
                
            }


            constexpr dual& operator+(const dual& other) const noexcept {
                
                dual<measurement_t> result; 
                result.real = this->real + other.real;
                result.imag = this->imag + other.imag;

                return result;

            }

            constexpr dual& operator+(dual&& other) const noexcept {
                
                dual<measurement_t> result; 
                result.real = this->real + std::move(other.real);
                result.imag = this->imag + std::move(other.imag);

                return result;

            }


            constexpr dual& operator-(const dual& other) const noexcept {
                
                dual<measurement_t> result; 
                result.real = this->real - other.real;
                result.imag = this->imag - other.imag;

                return result;

            }

            constexpr dual& operator-(dual&& other) const noexcept {
                
                dual<measurement_t> result; 
                result.real = this->real - std::move(other.real);
                result.imag = this->imag - std::move(other.imag);

                return result;

            }


            constexpr dual operator-() const noexcept {
                
                return {-real, -imag};

            }


            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const dual<OTHER_MEAS_TYPE>& other) const noexcept 
                -> dual<op::measurements_prod_t<measurement_t, OTHER_MEAS_TYPE>> {

                return {this->real * other.real, this->real * other.imag + this->imag * other.real};

            } 

            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(dual<OTHER_MEAS_TYPE>&& other) const noexcept 
                -> dual<op::measurements_prod_t<measurement_t, OTHER_MEAS_TYPE>> {

                return {this->real * std::move(other.real), this->real * std::move(other.imag) + this->imag * std::move(other.real)};

            } 


            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(const dual<OTHER_MEAS_TYPE>& other) const
                -> dual<op::measurements_div_t<measurement_t, OTHER_MEAS_TYPE>> {

                if (other.real == 0)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {this->real / other.real, (this->imag * other.real - this->real * other.imag) / op::square(other.real)};

            }

            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(dual<OTHER_MEAS_TYPE>&& other) const
                -> dual<op::measurements_div_t<measurement_t, OTHER_MEAS_TYPE>> {

                if (other.real == 0)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {this->real / std::move(other.real), (this->imag * std::move(other.real) - this->real * std::move(other.imag)) / op::square(std::move(other.real))};

            }
            

        // ==============================================
        // operators with measurement_t
        // ==============================================

            constexpr dual& operator=(const measurement_t& real) noexcept {
                
                this->real = real;
                this->imag = measurement_t{};

                return *this;

            }

            constexpr dual& operator=(measurement_t&& real) noexcept {
                
                this->real = std::move(real);
                this->imag = measurement_t{};

                return *this;

            }


            constexpr dual& operator+=(const measurement_t& real) noexcept {
                
                this->real += real;
                
                return *this;

            }

            constexpr dual& operator+=(measurement_t&& real) noexcept {
                
                this->real += std::move(real);
                
                return *this;

            }


            constexpr dual& operator-=(const measurement_t& real) noexcept {
                
                this->real -= real;

                return *this;

            }

            constexpr dual& operator-=(measurement_t&& real) noexcept {
                
                this->real -= std::move(real);

                return *this;

            }


            constexpr dual& operator+(const measurement_t& real) const noexcept {
                
                dual<measurement_t> result; 
                result.real = this->real + real;

                return result;

            }

            constexpr dual& operator+(measurement_t&& real) const noexcept {
                
                dual<measurement_t> result; 
                result.real = this->real + std::move(real);

                return result;

            }


            constexpr dual& operator-(const measurement_t& real) const noexcept {
                
                dual<measurement_t> result; 
                result.real = this->real - real;

                return result;

            }

            constexpr dual& operator-(measurement_t&& real) const noexcept {
                
                dual<measurement_t> result; 
                result.real = this->real - std::move(real);

                return result;

            }


            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_measurement_v<OTHER_MEAS_TYPE> && physics::is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*=(const OTHER_MEAS_TYPE& other) noexcept 
                -> dual<op::measurements_prod_t<measurement_t, OTHER_MEAS_TYPE>>& {
                
                this->real *= other;
                this->imag *= other;

                return *this;
        
            }

            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_measurement_v<OTHER_MEAS_TYPE> && physics::is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*=(OTHER_MEAS_TYPE&& other) noexcept 
                -> dual<op::measurements_prod_t<measurement_t, OTHER_MEAS_TYPE>>& {
                
                this->real *= std::move(other);
                this->imag *= std::move(other);

                return *this;
        
            }

            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_measurement_v<OTHER_MEAS_TYPE> && physics::is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/=(const OTHER_MEAS_TYPE& other) noexcept 
                -> dual<op::measurements_div_t<measurement_t, OTHER_MEAS_TYPE>>& {

                if (other == 0)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");
                
                this->real /= other;
                this->imag /= other;

                return *this;
        
            }

            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_measurement_v<OTHER_MEAS_TYPE> && physics::is_scalar_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/=(OTHER_MEAS_TYPE&& other) noexcept 
                -> dual<op::measurements_div_t<measurement_t, OTHER_MEAS_TYPE>>& {

                if (other == 0)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");
                
                this->real /= std::move(other);
                this->imag /= std::move(other);

                return *this;
        
            }


            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(const OTHER_MEAS_TYPE& other) const noexcept 
                -> dual<op::measurements_prod_t<measurement_t, OTHER_MEAS_TYPE>> {
                    
                return {this->real * other, this->imag * other};
        
            }

            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator*(OTHER_MEAS_TYPE&& other) const noexcept 
                -> dual<op::measurements_prod_t<measurement_t, OTHER_MEAS_TYPE>> {
                    
                return {this->real * std::move(other), this->imag * std::move(other)};
        
            }


            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(const OTHER_MEAS_TYPE& other) const 
                -> dual<op::measurements_div_t<measurement_t, OTHER_MEAS_TYPE>> {

                if (other == 0)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {this->real / other, this->imag / other};

            }

            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            constexpr auto operator/(OTHER_MEAS_TYPE&& other) const 
                -> dual<op::measurements_div_t<measurement_t, OTHER_MEAS_TYPE>> {

                if (other == 0)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {this->real / std::move(other), this->imag / std::move(other)};

            }


            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            friend constexpr auto operator*(const OTHER_MEAS_TYPE& other, const dual<measurement_t>& other_dual) noexcept 
                -> dual<op::measurements_prod_t<OTHER_MEAS_TYPE, measurement_t>> {
                    
                return {other_dual.real * other, other_dual.imag * other};
        
            }

            template <typename OTHER_MEAS_TYPE>
                requires (physics::is_generic_measurement_v<OTHER_MEAS_TYPE>)
            friend constexpr auto operator/(const OTHER_MEAS_TYPE& other, const dual<measurement_t>& other_dual) 
                -> dual<op::measurements_div_t<OTHER_MEAS_TYPE, measurement_t>> {

                if (other_dual.real == 0)
                    throw std::runtime_error("Cannot divide a dual number by a zero measurement");

                return {other / other_dual.real, -other * other_dual.imag / op::square(other_dual.real)};

            }


    }; /// struct dual


    template <typename T>
    struct is_dual_measurement : std::false_type {};

    template <typename MEAS_TYPE>
    struct is_dual_measurement<dual<MEAS_TYPE>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_dual_measurement_v = is_dual_measurement<T>::value;


    template <typename... MEAS_TYPES>
    struct are_dual_measurements : std::conjunction<is_dual_measurement<MEAS_TYPES>...>{};

    template <typename... MEAS_TYPES>
    inline constexpr bool are_dual_measurements_v = are_dual_measurements<MEAS_TYPES...>::value;


} /// namespace scipp::math