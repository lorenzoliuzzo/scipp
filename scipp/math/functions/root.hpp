/**
 * @file    math/functions/power.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-06
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        /// @brief power a physics::base_quantity
        template <size_t POWER, typename BASE_TYPE>
            requires (physics::is_base_v<BASE_TYPE>)
        struct root<POWER, BASE_TYPE> : unary_function<BASE_TYPE, physics::base_quantity<BASE_TYPE::length / POWER, 
                                                                                          BASE_TYPE::time / POWER,
                                                                                          BASE_TYPE::mass / POWER,
                                                                                          BASE_TYPE::temperature / POWER,
                                                                                          BASE_TYPE::elettric_current / POWER,
                                                                                          BASE_TYPE::substance_amount / POWER,
                                                                                          BASE_TYPE::luminous_intensity / POWER>> {

        
            using result_t = physics::base_quantity<BASE_TYPE::length / POWER, 
                                                    BASE_TYPE::time / POWER,
                                                    BASE_TYPE::mass / POWER,
                                                    BASE_TYPE::temperature / POWER,
                                                    BASE_TYPE::elettric_current / POWER,
                                                    BASE_TYPE::substance_amount / POWER,
                                                    BASE_TYPE::luminous_intensity / POWER>;


            inline static constexpr result_t f(const BASE_TYPE&) noexcept {

                return {};

            }                                             
            

        };


        /// @brief power a prefix
        template <size_t POWER, typename PREFIX_TYPE>
            requires (physics::is_prefix_v<PREFIX_TYPE>)
        struct root<POWER, PREFIX_TYPE> : unary_function<PREFIX_TYPE, std::ratio<static_cast<size_t>(std::pow(PREFIX_TYPE::num, 1.0 / POWER)), 
                                                                                  static_cast<size_t>(std::pow(PREFIX_TYPE::den, 1.0 / POWER))>> {

            
            using result_t = std::ratio<static_cast<size_t>(std::pow(PREFIX_TYPE::num, 1.0 / POWER)), 
                                        static_cast<size_t>(std::pow(PREFIX_TYPE::den, 1.0 / POWER))>; 


            inline static constexpr result_t f(const PREFIX_TYPE&) noexcept {

                return {};

            }       


        };


        /// @brief power an unit of measurement
        template <size_t POWER, typename UNIT_TYPE>
            requires (physics::is_unit_v<UNIT_TYPE>)
        struct root<POWER, UNIT_TYPE> : unary_function<UNIT_TYPE, physics::unit<root_t<POWER, typename UNIT_TYPE::base_t>, root_t<POWER, typename UNIT_TYPE::prefix_t>>> {


            using result_t = physics::unit<root_t<POWER, typename UNIT_TYPE::base_t>, root_t<POWER, typename UNIT_TYPE::prefix_t>>;                                             


            inline static constexpr result_t f(const UNIT_TYPE&) noexcept {

                return {};

            }       


        };


        /// @brief power a number
        template <size_t POWER, typename T>
            requires (is_number_v<T>)
        struct root<POWER, T> : unary_function<T, T> {


            using result_t = T;

            inline static constexpr result_t f(const T& x) noexcept {

                return std::pow(x, 1.0 / POWER);

            }       


        };


        /// @brief power a measurement
        template <size_t POWER, typename MEAS_TYPE>
            requires (physics::is_measurement_v<MEAS_TYPE>)
        struct root<POWER, MEAS_TYPE> : unary_function<MEAS_TYPE, physics::measurement<root_t<POWER, typename MEAS_TYPE::base_t>, typename MEAS_TYPE::value_t>> {


            using result_t = physics::measurement<root_t<POWER, typename MEAS_TYPE::base_t>, typename MEAS_TYPE::value_t>;                                             


            inline static constexpr result_t f(const MEAS_TYPE& x) noexcept {

                return std::pow(x.value, 1.0 / POWER);

            }       


        };


        /// @brief power a umeasurement
        template <size_t POWER, typename UMEAS_TYPE>
            requires (physics::is_umeasurement_v<UMEAS_TYPE>)
        struct root<POWER, UMEAS_TYPE> : unary_function<UMEAS_TYPE, physics::umeasurement<root_t<POWER, typename UMEAS_TYPE::base_t>>> {


            using result_t = physics::umeasurement<root_t<POWER, typename UMEAS_TYPE::base_t>>;                                             


            inline static constexpr result_t f(const UMEAS_TYPE& x) noexcept {

                return {std::pow(x.value, POWER), x.uncertainty * POWER};

            }       


        };


        /// @brief power a complex
        template <size_t POWER, typename CMEAS_TYPE>
            requires (math::is_complex_v<CMEAS_TYPE>)
        struct root<POWER, CMEAS_TYPE> : unary_function<CMEAS_TYPE, complex<root_t<POWER, typename CMEAS_TYPE::value_t>>> {


            using result_t = complex<root_t<POWER, typename CMEAS_TYPE::value_t>>;


            inline static constexpr result_t f(const CMEAS_TYPE& x) noexcept {

                return result_t::polar(op::rt<POWER>(x.abs()), x.arg() / POWER);
            }


        };


        /// @brief power a vector
        template <size_t POWER, typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        struct root<POWER, VECTOR_TYPE> : unary_function<VECTOR_TYPE, geometry::vector<root_t<POWER, typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>> {


            using result_t = geometry::vector<root_t<POWER, typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>; 


            inline static constexpr result_t f(const VECTOR_TYPE& x) {

                result_t x_pow;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), x_pow.data.begin(), [](const auto& x_i) { return op::pow<POWER>(x_i); });
                return x_pow;

            }

        
        };


    } // namespace functions


} // namespace scipp::math