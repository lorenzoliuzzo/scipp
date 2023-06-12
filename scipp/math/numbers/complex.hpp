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


            constexpr complex(value_t real, value_t imag = value_t{}) noexcept : 
                
                real(std::forward<value_t>(real)), imag(std::forward<value_t>(imag)) {}



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


            friend constexpr std::ostream& operator<<(std::ostream& os, const complex& x) noexcept {

                os << x.real << " + " << x.imag << "i";

                return os;

            }


            constexpr decltype(auto) x() noexcept {

                return this->real;

            }


            constexpr decltype(auto) y() noexcept {

                return this->imag;

            } 


            constexpr auto conj() const noexcept {

                return complex(this->real, -this->imag);

            }


            constexpr auto abs() const noexcept {
                
                return op::abs(*this);

            }


            constexpr auto arg() const noexcept {
                
                return op::atan(this->imag, this->real);

            }


    }; // class complex


} // namespace scipp::physics