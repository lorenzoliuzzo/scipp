/**
 * @file    math/numbers/complex.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the complex struct and its type traits.
 * @date    2023-06-08
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::math {


    template <typename T>   
        requires (is_number_v<T> || physics::is_measurement_v<T> || physics::is_umeasurement_v<T>)  
    struct complex<T> {


        // ==============================================
        // aliases
        // ==============================================

            using _t = complex<T>;

            using value_t = T; 


        // ==============================================
        // members
        // ==============================================

            value_t real;

            value_t imag;


            inline static constexpr size_t dim = 2;


            inline static constexpr complex zero = complex{0.0}; ///< The zero measurement

            inline static constexpr complex one = complex{1.0}; ///< The one measurement

            inline static constexpr complex i = complex{0.0, 1.0}; ///< The one measurement


        // ==============================================
        // constructors
        // ==============================================

            constexpr complex() noexcept :
                
                real{}, imag{} {}


            constexpr complex(const complex& other) noexcept :

                real(other.real), imag(other.imag) {}


            constexpr complex(complex&& other) noexcept :

                real(std::move(other.real)), imag(std::move(other.imag)) {}


            constexpr complex(const value_t& real) noexcept :

                real(real), imag{} {}
                

            constexpr complex(value_t&& real) noexcept :

                real(std::move(real)), imag{} {}


            constexpr complex(const value_t& real, const value_t& imag) noexcept : 
                
                real(real), imag(imag) {}


            constexpr complex(value_t&& real, value_t&& imag) noexcept : 
                
                real(std::move(real)), imag(std::move(imag)) {}



        // ==============================================
        // operators with complex
        // ==============================================

            constexpr bool operator==(const complex& other) const noexcept {

                return (this->real == other.real) && (this->imag == other.imag);

            }

            constexpr bool operator!=(const complex& other) const noexcept {

                return !(*this == other);

            }


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


            constexpr decltype(auto) x() noexcept {

                return this->real;

            }

            // constexpr value_t x() noexcept {

            //     return this->real;

            // }


            constexpr value_t y() const noexcept {

                return this->imag;

            }         

            constexpr value_t y() noexcept {

                return this->imag;

            }         


            constexpr complex conj() const noexcept {

                return { this->real, -this->imag };

            }

            constexpr complex conj() noexcept {

                return { this->real, -this->imag };

            }

            constexpr auto abs() const noexcept {
                
                return op::abs(*this);

            }

            constexpr auto arg() const noexcept {
                
                return op::atan(this->imag, this->real);

            }


            inline static constexpr complex cartesian(const value_t& x, const value_t& y) noexcept {

                return { x, y };

            }
            
            template <typename SCALAR_TYPE>
                requires (is_number_v<SCALAR_TYPE> || physics::is_scalar_measurement_v<SCALAR_TYPE> || physics::is_scalar_umeasurement_v<SCALAR_TYPE>)
            inline static constexpr complex polar(const value_t& rho, const SCALAR_TYPE& theta) noexcept {

                return { rho * op::cos(theta), rho * op::sin(theta) };

            }


    }; // class complex


} // namespace scipp::physics