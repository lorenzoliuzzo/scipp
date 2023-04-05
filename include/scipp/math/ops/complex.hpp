/**
 * @file    math/ops/complex.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-03
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {
    
    
    namespace op {


        template <typename MEAS_TYPE>
            requires (physics::is_complex_measurement_v<MEAS_TYPE>)
        inline constexpr MEAS_TYPE::measurement_type abs(const MEAS_TYPE& other) noexcept {
            
            return op::sqrt(op::square(other.real) + op::square(other.imag));

        }


        template <typename MEAS_TYPE>
            requires (physics::is_complex_measurement_v<MEAS_TYPE>)
        inline constexpr auto arg(const MEAS_TYPE& other) noexcept {
            
            return op::atan(other.imag / other.real);

        }

        template <typename MEAS_TYPE>
            requires (physics::is_complex_measurement_v<MEAS_TYPE>)
        inline constexpr auto norm(const MEAS_TYPE& other) noexcept {
            
            return op::square(other.real) + op::square(other.imag);

        }


        template <typename MEAS_TYPE>
            requires (physics::is_complex_measurement_v<MEAS_TYPE>)
        inline constexpr auto conj(const MEAS_TYPE& other) noexcept {
            
            return MEAS_TYPE{other.real, -other.imag};

        }


        template <typename MEAS_TYPE1, typename MEAS_TYPE2>
            requires (physics::are_generic_measurements_v<MEAS_TYPE1, MEAS_TYPE2> && physics::is_scalar_v<MEAS_TYPE2>)
        inline constexpr physics::complex<MEAS_TYPE1> polar(const MEAS_TYPE1& rho, const MEAS_TYPE2& theta) noexcept {
            
            return { rho * op::cos(theta), rho * op::sin(theta) };

        }


        /// @brief Get the exponential of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto exp(const physics::complex<MEAS_TYPE>& other) noexcept 
            -> physics::complex<math::op::measurements_div_t<MEAS_TYPE, MEAS_TYPE>> {
            
            return { op::polar(op::exp(other.real), other.imag) };

        }


        /// @brief Get the logarithm of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto log(const physics::complex<MEAS_TYPE>& other) noexcept 
            -> physics::complex<math::op::measurements_div_t<MEAS_TYPE, MEAS_TYPE>> {
            
            return { op::log(op::abs(other)), op::arg(other) };

        }

        /// @brief Get the logarithm in base 10 of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto log10(const physics::complex<MEAS_TYPE>& other) noexcept {
            
            return op::log(other) / op::log10(MEAS_TYPE{10.0});

        }
        

        /// @brief Get the sine of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto sin(const physics::complex<MEAS_TYPE>& other) noexcept 
            -> physics::complex<math::op::measurements_div_t<MEAS_TYPE, MEAS_TYPE>> {
            
            return { op::sin(other.real) * op::cosh(other.imag), op::cos(other.real) * op::sinh(other.imag) };

        }

        /// @brief Get the cosine of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto cos(const physics::complex<MEAS_TYPE>& other) noexcept 
            -> physics::complex<math::op::measurements_div_t<MEAS_TYPE, MEAS_TYPE>> {
            
            return { op::cos(other.real) * op::cosh(other.imag), -op::sin(other.real) * op::sinh(other.imag) };

        }

        /// @brief Get the tangent of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto tan(const physics::complex<MEAS_TYPE>& other) noexcept {
            
            return op::sin(other) / op::cos(other);

        }


        /// @brief Get the sine hyperbolic of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto sinh(const physics::complex<MEAS_TYPE>& other) noexcept 
            -> physics::complex<math::op::measurements_div_t<MEAS_TYPE, MEAS_TYPE>> {
            
            return { op::sinh(other.real) * op::cos(other.imag), op::cosh(other.real) * op::sin(other.imag) };

        }
        
        /// @brief Get the cosine hyperbolic of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto cosh(const physics::complex<MEAS_TYPE>& other) noexcept 
            -> physics::complex<math::op::measurements_div_t<MEAS_TYPE, MEAS_TYPE>> {
            
            return { op::cosh(other.real) * op::cos(other.imag), op::sinh(other.real) * op::sin(other.imag) };

        }

        /// @brief Get the tangent hyperbolic of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto tanh(const physics::complex<MEAS_TYPE>& other) noexcept {
            
            return op::sinh(other) / op::cosh(other);

        }


        /// @brief Get the arcsine of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto asin(const physics::complex<MEAS_TYPE>& other) noexcept 
            -> physics::complex<math::op::measurements_div_t<MEAS_TYPE, MEAS_TYPE>> {

            auto z = op::asinh(MEAS_TYPE(-other.imag, other.real));
            return { z.imag, -z.real };
        
        }


        /// @brief Get the arccosine of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto acos(const physics::complex<MEAS_TYPE>& other) noexcept 
            -> physics::complex<math::op::measurements_div_t<MEAS_TYPE, MEAS_TYPE>> {
            
            auto z = op::asin(other);
            return { M_PI_2 - z.real, -z.imag };

        }


        /// @brief Get the arctangent of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto atan(const physics::complex<MEAS_TYPE>& other) noexcept 
            -> physics::complex<math::op::measurements_div_t<MEAS_TYPE, MEAS_TYPE>> {
                    
            const auto r2 = op::square(other.real);
            const auto x = 1.0 - r2 - op::square(other.imag);

            return { op::atan(MEAS_TYPE(2.0) * other.real / (2.0 * x)), op::log((r2 + op::square(other.imag + 1.0)) / (other.imag - 1.0)) / 4.0 };
                   
        }


        /// @brief Get the arccosine hyperbolic of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto acosh(const physics::complex<MEAS_TYPE>& other) noexcept 
            -> physics::complex<math::op::measurements_div_t<MEAS_TYPE, MEAS_TYPE>> {
            
            return 2.0 * op::log(op::sqrt(0.5 * (other + 1.0)) + op::sqrt(0.5 * (other - 1.0)));

        }

        /// @brief Get the arcsine hyperbolic of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto asinh(const physics::complex<MEAS_TYPE>& other) noexcept 
            -> physics::complex<math::op::measurements_div_t<MEAS_TYPE, MEAS_TYPE>> {
            
            physics::complex<math::op::measurement_square_t<MEAS_TYPE>> z((other.real - other.imag) * (other.real + other.imag) + 1.0, 2.0 * other.real * other.imag);

            return op::log(op::sqrt(z) + other);

        }

        /// @brief Get the arctangent hyperbolic of a scalar complex measurement
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline constexpr auto atanh(const physics::complex<MEAS_TYPE>& other) noexcept 
            -> physics::complex<math::op::measurements_div_t<MEAS_TYPE, MEAS_TYPE>> {
            
            const auto i2 = op::square(other.imag);

            return { op::log((i2 + op::square(1.0 + other.real)) / (i2 + op::square(1.0 - other.real))) / 4.0,
                     op::atan(2.0 * other.imag / (1.0 - i2 - op::square(other.real))) / 2.0 };
                   
        }


        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        inline constexpr auto sqrt(const physics::complex<MEAS_TYPE>& other) noexcept
            -> physics::complex<math::op::measurement_sqrt_t<MEAS_TYPE>> {
    
            if (other.real == MEAS_TYPE()) {

                auto t = op::sqrt(op::abs(other.imag) / 2.0);
                return { t, other.imag < MEAS_TYPE() ? -t : t };

            } else {

                auto t = op::sqrt(2.0 * (op::abs(other) + op::abs(other.real)));

                if (other.real > MEAS_TYPE())
                    return { t / 2.0, other.imag / t };
                else 
                    return { op::abs(other.imag) / t, other.imag < MEAS_TYPE() ? -t / 2.0 : t / 2.0 };
            
            }

        }


        // template <typename MEAS_TYPE>
        //     requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        // inline static constexpr auto pow_impl(const physics::complex<MEAS_TYPE>& x, unsigned n) 
        //     -> complex<math::op::measurement_pow_t<MEAS_TYPE, n>> {

        //     complex<MEAS_TYPE> y = (n % 2) ? x : complex<MEAS_TYPE>(1.0);

        //     while (n >>= 1) {

        //         x *= x;
        //         if (n % 2)
        //             y *= x;

        //     }

        //     return y;

        // }

        // template <typename MEAS_TYPE>
        //     requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        // inline static constexpr auto pow(const physics::complex<MEAS_TYPE>& x, int n) {

        //     return (n < 0) ? 1.0 / op::pow_impl(x, -n) : op::pow_impl(x, static_cast<unsigned>(n));

        // }       


        template <typename MEAS_TYPE, typename SCALAR_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE> && physics::is_scalar_v<MEAS_TYPE>)
        inline static constexpr auto pow(const physics::complex<MEAS_TYPE>& x, const SCALAR_TYPE& y) {
          
            if (x.imag == MEAS_TYPE() && x.real > MEAS_TYPE())
                return op::pow(x.real, y);

            auto z = op::log(x);
            return op::polar<MEAS_TYPE>(op::exp(y * z.real()), y * z.imag());

        }


        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        inline static constexpr auto pow(const physics::complex<MEAS_TYPE>& x, const physics::complex<MEAS_TYPE>& y) {
            
            return (x == MEAS_TYPE()) ? MEAS_TYPE() : op::exp(y * op::log(x));
            
        }


    } // namespace op


} // namespace scipp::math