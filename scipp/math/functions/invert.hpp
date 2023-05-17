/**
 * @file    math/functions/invert.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-06
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        /// @brief Invert a physics::base_quantity
        template <typename BASE_TYPE>
            requires (physics::is_base_v<BASE_TYPE>)
        struct invert<BASE_TYPE> : unary_function<BASE_TYPE, physics::base_quantity<-BASE_TYPE::length, 
                                                                                    -BASE_TYPE::time,
                                                                                    -BASE_TYPE::mass,
                                                                                    -BASE_TYPE::temperature,
                                                                                    -BASE_TYPE::elettric_current,
                                                                                    -BASE_TYPE::substance_amount,
                                                                                    -BASE_TYPE::luminous_intensity>> {

        
            using result_t = physics::base_quantity<-BASE_TYPE::length, 
                                                    -BASE_TYPE::time,
                                                    -BASE_TYPE::mass,
                                                    -BASE_TYPE::temperature,
                                                    -BASE_TYPE::elettric_current,
                                                    -BASE_TYPE::substance_amount,
                                                    -BASE_TYPE::luminous_intensity>;

            inline static constexpr result_t f(const BASE_TYPE&) noexcept {

                return {};

            }                                             
            

        };


        /// @brief Invert a prefix
        template <typename PREFIX_TYPE>
            requires (physics::is_prefix_v<PREFIX_TYPE>)
        struct invert<PREFIX_TYPE> : unary_function<PREFIX_TYPE, std::ratio<PREFIX_TYPE::den, PREFIX_TYPE::num>> {


            using result_t = std::ratio<PREFIX_TYPE::den, PREFIX_TYPE::num>; 


            inline static constexpr result_t f(const PREFIX_TYPE&) noexcept {

                return {};

            }       


        };


        /// @brief Invert an unit of measurement
        template <typename UNIT_TYPE>
            requires (physics::is_unit_v<UNIT_TYPE>)
        struct invert<UNIT_TYPE> : unary_function<UNIT_TYPE, physics::unit<invert_t<typename UNIT_TYPE::base_t>, invert_t<typename UNIT_TYPE::prefix_t>>> {


            using result_t = physics::unit<invert_t<typename UNIT_TYPE::base_t>, invert_t<typename UNIT_TYPE::prefix_t>>;                                             


            inline static constexpr result_t f(const UNIT_TYPE&) noexcept {

                return {};

            }       


        };


        /// @brief Invert a number
        template <typename T>
            requires (is_number_v<T>)
        struct invert<T> : unary_function<T, double> {


            using result_t = double;                                             


            inline static constexpr result_t f(const T& x) {

                if (x == T{})
                    throw std::runtime_error("Cannot invert zero");
                    
                return 1.0 / x;

            }       


        };


        /// @brief Invert a measurement
        template <typename MEAS_TYPE>
            requires (physics::is_measurement_v<MEAS_TYPE>)
        struct invert<MEAS_TYPE> : unary_function<MEAS_TYPE, physics::measurement<invert_t<typename MEAS_TYPE::base_t>, decltype(1.0 / typename MEAS_TYPE::value_t{1.0})>> {


            using result_t = physics::measurement<invert_t<typename MEAS_TYPE::base_t>, decltype(1.0 / typename MEAS_TYPE::value_t{1.0})>;                                             


            inline static constexpr result_t f(const MEAS_TYPE& x) {

                return 1.0 / x.value;

            }       


        };


        /// @brief Invert a umeasurement
        template <typename UMEAS_TYPE>
            requires (physics::is_umeasurement_v<UMEAS_TYPE>)
        struct invert<UMEAS_TYPE> : unary_function<UMEAS_TYPE, physics::umeasurement<invert_t<typename UMEAS_TYPE::base_t>>> {


            using result_t = physics::umeasurement<invert_t<typename UMEAS_TYPE::base_t>>;                                             


            inline static constexpr result_t f(const UMEAS_TYPE& x) {

                return {1.0 / x.value, x.uncertainty / std::fabs(x.value) };

            }       


        };


        /// @brief Invert a cmeasurement
        template <typename CMEAS_TYPE>
            requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
        struct invert<CMEAS_TYPE> : unary_function<CMEAS_TYPE, physics::cmeasurement<invert_t<typename CMEAS_TYPE::measurement_t>>> {


            using result_t = physics::cmeasurement<invert_t<typename CMEAS_TYPE::measurement_t>>;


            inline static constexpr result_t f(const CMEAS_TYPE& x) {

                return x * x.conj() / x.norm();

            }


        };


        /// @brief Invert a vector
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        struct invert<VECTOR_TYPE> : unary_function<VECTOR_TYPE, geometry::vector<invert_t<typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>> {


            using result_t = geometry::vector<invert_t<typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>; 


            inline static constexpr result_t f(const VECTOR_TYPE& x) {

                result_t x_inv;
                std::transform(x.data.begin(), x.data.end(), x_inv.data.begin(), [](const auto& x_i) { return op::inv(x_i); });
                return x_inv;

            }

        
        };


    } // namespace functions


} // namespace scipp::math