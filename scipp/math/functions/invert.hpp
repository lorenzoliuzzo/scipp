/**
 * @file    math/functions/invert.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        /// @brief Invert a physics::base_quantity
        template <typename BASE_TYPE>
            requires (physics::is_base_v<BASE_TYPE>)
        struct invert<BASE_TYPE> {
            
            using function_t = unary_function<BASE_TYPE, physics::base_quantity<-BASE_TYPE::length, 
                                                                                -BASE_TYPE::time,
                                                                                -BASE_TYPE::mass,
                                                                                -BASE_TYPE::temperature,
                                                                                -BASE_TYPE::elettric_current,
                                                                                -BASE_TYPE::substance_amount,
                                                                                -BASE_TYPE::luminous_intensity>>;

            inline static constexpr function_t::result_t f(const function_t::arg_t&) noexcept {

                return {};

            }                                             
            
        };


        /// @brief Invert a prefix
        template <typename PREFIX_TYPE>
            requires (physics::is_prefix_v<PREFIX_TYPE>)
        struct invert<PREFIX_TYPE> {

            using function_t = unary_function<PREFIX_TYPE, std::ratio<PREFIX_TYPE::den, PREFIX_TYPE::num>>;

            inline static constexpr function_t::result_t f(const function_t::arg_t&) noexcept {

                return {};

            }       

        };


        /// @brief Invert an unit of measurement
        template <typename UNIT_TYPE>
            requires (physics::is_unit_v<UNIT_TYPE>)
        struct invert<UNIT_TYPE> {
            
            using function_t = unary_function<UNIT_TYPE, physics::unit<invert_t<typename UNIT_TYPE::base_t>, invert_t<typename UNIT_TYPE::prefix_t>>>;

            inline static constexpr function_t::result_t f(const function_t::arg_t&) noexcept {

                return {};

            }       

        };


        /// @brief Invert a number
        template <typename T>
            requires (is_number_v<T>)
        struct invert<T> {
            
            using function_t = unary_function<T, double>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                if (x == typename function_t::arg_t{})
                    throw std::runtime_error("Cannot invert zero");
                    
                return 1.0 / x;

            }       

        };


        /// @brief Invert a measurement
        template <typename MEAS_TYPE>
            requires (physics::is_measurement_v<MEAS_TYPE>)
        struct invert<MEAS_TYPE> {
            
            using function_t = unary_function<MEAS_TYPE, physics::measurement<invert_t<typename MEAS_TYPE::base_t>, double>>; 

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                if (x == typename function_t::arg_t{})
                    throw std::runtime_error("Cannot invert zero");

                return 1.0 / x.value;

            }       

        };


        /// @brief Invert a umeasurement
        template <typename UMEAS_TYPE>
            requires (physics::is_umeasurement_v<UMEAS_TYPE>)
        struct invert<UMEAS_TYPE> {
            
            using function_t = unary_function<UMEAS_TYPE, physics::umeasurement<invert_t<typename UMEAS_TYPE::base_t>>>;
            
            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                if (x == typename function_t::arg_t{})
                    throw std::runtime_error("Cannot invert zero");

                return {1.0 / x.value, x.uncertainty / std::fabs(x.value) };

            }       

        };


        /// @brief Invert a cmeasurement
        template <typename CMEAS_TYPE>
            requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
        struct invert<CMEAS_TYPE> {
            
            using function_t = unary_function<CMEAS_TYPE, physics::cmeasurement<invert_t<typename CMEAS_TYPE::measurement_t>>>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                if (x == typename function_t::arg_t{})
                    throw std::runtime_error("Cannot invert zero");

                return x * x.conj() / x.norm();

            }

        };


        /// @brief Invert a vector
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        struct invert<VECTOR_TYPE> {
            
            using function_t = unary_function<VECTOR_TYPE, geometry::vector<invert_t<typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                typename function_t::result_t x_inv;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), x_inv.data.begin(), [](const auto& x_i) { return op::inv(x_i); });
                return x_inv;

            }
        
        };


        // /// @brief Invert an unary function
        // template <typename FUNCTION_TYPE>
        //     requires (is_unary_function_v<FUNCTION_TYPE>)
        // struct invert<FUNCTION_TYPE> {
            
        //     using function_t = unary_function<typename FUNCTION_TYPE::arg_t, invert_t<typename FUNCTION_TYPE::result_t>>;

        //     inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

        //         return op::inv(FUNCTION_TYPE::f(x));

        //     }

        // };
        

    } // namespace functions


} // namespace scipp::math