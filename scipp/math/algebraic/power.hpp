/**
 * @file    math/functions/algebraic/power.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * 
 * @brief   This file contains a collection of power functions implemented in the scipp::math namespace. 
 *          These functions provide various ways to calculate the power of different types of operands, 
 *          including numbers, measurements, complex numbers, vectors, and matrices.
 * 
 * @date    2023-05-28
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <int N, typename T>
        struct power_impl<N, calculus::expr_ptr<T>> {

            using result_t = calculus::expr_ptr<op::power_t<N, T>>;

            inline static constexpr result_t f(const calculus::expr_ptr<T>& x) {

                return std::make_shared<calculus::power_expr<N, T>>(op::pow<N>(x->val), x);

            }

        };


        template <int N, typename T>
        struct power_impl<N, calculus::variable<T>> {

            using result_t = calculus::expr_ptr<op::power_t<N, T>>;

            inline static constexpr result_t f(const calculus::variable<T>& x) {

                return op::pow<N>(x.expr); 

            }

        };


        /// @brief power a physics::base_quantity
        template <int POWER, typename BASE_TYPE>
            requires physics::is_base_v<BASE_TYPE>
        struct power_impl<POWER, BASE_TYPE> {

            using result_t = physics::base_quantity<BASE_TYPE::length * POWER, 
                                                    BASE_TYPE::time * POWER,
                                                    BASE_TYPE::mass * POWER,
                                                    BASE_TYPE::temperature * POWER,
                                                    BASE_TYPE::elettric_current * POWER,
                                                    BASE_TYPE::substance_amount * POWER,
                                                    BASE_TYPE::luminous_intensity * POWER>;

            inline static constexpr result_t f(const BASE_TYPE&) noexcept {

                return {};

            }                                             
            
        };


        /// @brief power a prefix
        template <int POWER, typename PREFIX_TYPE>
            requires physics::is_prefix_v<PREFIX_TYPE>
        struct power_impl<POWER, PREFIX_TYPE> {
            
            using result_t = std::ratio<static_cast<size_t>(std::pow(PREFIX_TYPE::num, POWER)), 
                                        static_cast<size_t>(std::pow(PREFIX_TYPE::den, POWER))>;

            inline static constexpr result_t f(const PREFIX_TYPE&) noexcept {

                return {};

            }       

        };


        /// @brief power an unit of measurement
        template <int POWER, typename UNIT_TYPE>
            requires physics::is_unit_v<UNIT_TYPE>
        struct power_impl<POWER, UNIT_TYPE> {
            
            using result_t = physics::unit<power_t<POWER, typename UNIT_TYPE::base_t>, 
                                           power_t<POWER, typename UNIT_TYPE::prefix_t>>;

            inline static constexpr result_t f(const UNIT_TYPE&) noexcept {

                return {};

            }       

        };


        /// @brief Return the power of a number
        /// @tparam POWER: exponent of the power
        /// @tparam T: number type
        template <int POWER, typename T>
            requires is_number_v<T>
        struct power_impl<POWER, T> {
            
            using result_t = T;

            inline static constexpr result_t f(const T& x) noexcept {

                return std::pow(x, POWER);

            }       

        };


        /// @brief Return the power of a measurement
        /// @tparam POWER: exponent of the power
        /// @tparam T: measurement type
        template <int POWER, typename MEAS_TYPE>
            requires physics::is_measurement_v<MEAS_TYPE>
        struct power_impl<POWER, MEAS_TYPE> {
            
            using result_t = physics::measurement<power_t<POWER, typename MEAS_TYPE::base_t>, typename MEAS_TYPE::value_t>;

            inline static constexpr result_t f(const MEAS_TYPE& x) noexcept {

                return std::pow(x.value, POWER);

            }       

        };


        /// @brief Return the power of a umeasurement
        /// @tparam POWER: exponent of the power
        /// @tparam T: umeasurement type
        template <int POWER, typename UMEAS_TYPE>
            requires physics::is_umeasurement_v<UMEAS_TYPE>
        struct power_impl<POWER, UMEAS_TYPE> {
            
            using result_t = physics::umeasurement<power_t<POWER, typename UMEAS_TYPE::base_t>>;

            inline static constexpr result_t f(const UMEAS_TYPE& x) noexcept {

                return {std::pow(x.value, POWER), x.uncertainty * POWER};

            }       

        };


        // /// @brief Return the power of a complex number
        // /// @tparam POWER: exponent of the power
        // /// @tparam T: complex type
        // template <int POWER, typename T>
        //     requires math::is_complex_v<T>
        // struct power_impl<POWER, T> {
            
        //     using result_t = complex<power_t<POWER, typename T::value_t>>;
            
        //     inline static constexpr result_t f(const T& x) noexcept {

        //         const auto z = op::log(x);
        //         return polar(op::exp(POWER * z.real), POWER * z.imag);

        //     }

        // };


        // /// @brief Return the power of a dual number
        // /// @tparam POWER: exponent of the power
        // /// @tparam T: dual type
        // template <int POWER, typename T>
        //     requires math::is_dual_v<T>
        // struct power_impl<POWER, T> {
            
        //     using result_t = dual<power_t<POWER, typename T::value_t>>;
            
        //     inline static constexpr result_t f(const T& x) noexcept {

        //         const auto pow = op::pow<POWER - 1>(x.real);
        //         return {x.real * pow, x.imag * POWER * pow}; 

        //     }

        // };


        template <int N, typename T>
            requires geometry::is_vector_v<T>
        struct power_impl<N, T> {
            
            using result_t = geometry::vector<power_t<N, typename T::value_t>, T::dim, T::flag>; 

            static constexpr result_t f(const T& x) {

                result_t x_pow;
                std::transform(
                    std::execution::par, 
                    x.data.begin(), x.data.end(), 
                    x_pow.data.begin(), 
                    [](const auto& x_i) { 
                        return pow<N>(x_i); 
                    }
                );

                return x_pow;

            }        


        }; 


    } // namespace op


} // namespace scipp::math