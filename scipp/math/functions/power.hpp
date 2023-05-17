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
        struct power<POWER, BASE_TYPE> : unary_function<BASE_TYPE, physics::base_quantity<BASE_TYPE::length * POWER, 
                                                                                          BASE_TYPE::time * POWER,
                                                                                          BASE_TYPE::mass * POWER,
                                                                                          BASE_TYPE::temperature * POWER,
                                                                                          BASE_TYPE::elettric_current * POWER,
                                                                                          BASE_TYPE::substance_amount * POWER,
                                                                                          BASE_TYPE::luminous_intensity * POWER>> {

        
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
        template <size_t POWER, typename PREFIX_TYPE>
            requires (physics::is_prefix_v<PREFIX_TYPE>)
        struct power<POWER, PREFIX_TYPE> : unary_function<PREFIX_TYPE, std::ratio<static_cast<size_t>(std::pow(PREFIX_TYPE::num, POWER)), 
                                                                                  static_cast<size_t>(std::pow(PREFIX_TYPE::den, POWER))>> {


            using result_t = std::ratio<static_cast<size_t>(std::pow(PREFIX_TYPE::num, POWER)), 
                                        static_cast<size_t>(std::pow(PREFIX_TYPE::den, POWER))>; 


            inline static constexpr result_t f(const PREFIX_TYPE&) noexcept {

                return {};

            }       


        };


        /// @brief power an unit of measurement
        template <size_t POWER, typename UNIT_TYPE>
            requires (physics::is_unit_v<UNIT_TYPE>)
        struct power<POWER, UNIT_TYPE> : unary_function<UNIT_TYPE, physics::unit<power_t<POWER, typename UNIT_TYPE::base_t>, power_t<POWER, typename UNIT_TYPE::prefix_t>>> {


            using result_t = physics::unit<power_t<POWER, typename UNIT_TYPE::base_t>, power_t<POWER, typename UNIT_TYPE::prefix_t>>;                                             


            inline static constexpr result_t f(const UNIT_TYPE&) noexcept {

                return {};

            }       


        };


        /// @brief power a measurement
        template <size_t POWER, typename MEAS_TYPE>
            requires (physics::is_measurement_v<MEAS_TYPE>)
        struct power<POWER, MEAS_TYPE> : unary_function<MEAS_TYPE, physics::measurement<power_t<POWER, typename MEAS_TYPE::base_t>, typename MEAS_TYPE::value_t>> {


            using result_t = physics::measurement<power_t<POWER, typename MEAS_TYPE::base_t>, typename MEAS_TYPE::value_t>;                                             


            inline static constexpr result_t f(const MEAS_TYPE& x) noexcept {

                return std::pow(x.value, POWER);

            }       


        };


        /// @brief power a umeasurement
        template <size_t POWER, typename UMEAS_TYPE>
            requires (physics::is_umeasurement_v<UMEAS_TYPE>)
        struct power<POWER, UMEAS_TYPE> : unary_function<UMEAS_TYPE, physics::umeasurement<power_t<POWER, typename UMEAS_TYPE::base_t>>> {


            using result_t = physics::umeasurement<power_t<POWER, typename UMEAS_TYPE::base_t>>;                                             


            inline static constexpr result_t f(const UMEAS_TYPE& x) noexcept {

                return {std::pow(x.value, POWER), x.uncertainty * POWER};

            }       


        };


        /// @brief power a cmeasurement
        template <size_t POWER, typename CMEAS_TYPE>
            requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
        struct power<POWER, CMEAS_TYPE> : unary_function<CMEAS_TYPE, physics::cmeasurement<power_t<POWER, typename CMEAS_TYPE::measurement_t>>> {


            using result_t = physics::cmeasurement<power_t<POWER, typename CMEAS_TYPE::measurement_t>>;


            inline static constexpr result_t f(const CMEAS_TYPE& x) noexcept {

                const auto z = op::log(x);
                return result_t::polar(op::exp(POWER * z.real), POWER * z.imag);

            }


        };


        /// @brief power a vector
        template <size_t POWER, typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        struct power<POWER, VECTOR_TYPE> : unary_function<VECTOR_TYPE, geometry::vector<power_t<POWER, typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>> {


            using result_t = geometry::vector<power_t<POWER, typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>; 


            inline static constexpr result_t f(const VECTOR_TYPE& x) {

                result_t x_pow;
                std::transform(x.data.begin(), x.data.end(), x_pow.data.begin(), [](const auto& x_i) { return op::pow<POWER>(x_i); });
                return x_pow;

            }

        
        };


    } // namespace functions


} // namespace scipp::math