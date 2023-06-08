/**
 * @file    math/meta/divide.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the divide meta function 
 * @date    2023-05-06
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {


    namespace functions {
        

        /// @brief Divide two base_quantities
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_base_v<ARG_TYPE1, ARG_TYPE2>)
        struct divide<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::base_quantity<ARG_TYPE1::length - ARG_TYPE2::length,
                                                                                            ARG_TYPE1::time - ARG_TYPE2::time,
                                                                                            ARG_TYPE1::mass - ARG_TYPE2::mass,
                                                                                            ARG_TYPE1::temperature - ARG_TYPE2::temperature,
                                                                                            ARG_TYPE1::elettric_current - ARG_TYPE2::elettric_current,
                                                                                            ARG_TYPE1::substance_amount - ARG_TYPE2::substance_amount,
                                                                                            ARG_TYPE1::luminous_intensity - ARG_TYPE2::luminous_intensity>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t&, const function_t::second_arg_t&) noexcept {
                return {};
            }

        };


        /// @brief Divide two prefixes
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_prefix_v<ARG_TYPE1, ARG_TYPE2>)
        struct divide<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, std::ratio_divide<ARG_TYPE1, ARG_TYPE2>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t&, const function_t::second_arg_t&) noexcept {
                return {};
            }

        };


        /// @brief Divide two units of measurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_units_v<ARG_TYPE1, ARG_TYPE2>)
        struct divide<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::unit<divide_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>,
                                                                                   divide_t<typename ARG_TYPE1::prefix_t, typename ARG_TYPE2::prefix_t>>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t&, const function_t::second_arg_t&) noexcept {
                return {};
            }

        };


        /// @brief Divide a number and an unit of measurement
        template <typename SCALAR_TYPE, typename UNIT_TYPE>
            requires (is_number_v<SCALAR_TYPE> && physics::is_unit_v<UNIT_TYPE>)
        struct divide<SCALAR_TYPE, UNIT_TYPE> {

            using function_t = binary_function<SCALAR_TYPE, UNIT_TYPE, physics::measurement<typename UNIT_TYPE::base_t, SCALAR_TYPE>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t&) {
                return { x / UNIT_TYPE::mult };
            }

        };


        /// @brief Divide two numbers
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (are_numbers_v<ARG_TYPE1, ARG_TYPE2>)
        struct divide<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, decltype(ARG_TYPE1{ 1.0 } / ARG_TYPE2{ 1.0 })>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) {
                return x / y;
            }

        };
        

        /// @brief Divide two measurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_measurements_v<ARG_TYPE1, ARG_TYPE2>)
        struct divide<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, physics::measurement<divide_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>, decltype(typename ARG_TYPE1::value_t{} * typename ARG_TYPE2::value_t{})>>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) {
                
                if (y == typename function_t::second_arg_t{})
                    throw std::runtime_error("Division by zero"); 

                return x.value / y.value; 

            }

        };


        /// @brief divide two complex
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (are_complex_v<ARG_TYPE1, ARG_TYPE2>)
        struct divide<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, complex<divide_t<typename ARG_TYPE1::measurement_t, typename ARG_TYPE2::measurement_t>>>;
            
            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) {

                if (y == typename function_t::second_arg_t{})
                    throw std::runtime_error("Division by zero"); 

                return x * op::inv(y); 

            }

        };


        /// @brief divide a measurment and a number
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_measurement_v<ARG_TYPE1> && is_number_v<ARG_TYPE2>)
        struct divide<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) {

                if (y == typename function_t::second_arg_t{})
                    throw std::runtime_error("Division by zero"); 

                return x.value / y; 

            }

        };


        /// @brief divide a number and a measurment
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (is_number_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        struct divide<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2>;


            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) {

                if (y == typename function_t::second_arg_t{})
                    throw std::runtime_error("Division by zero");

                return x / y.value; 

            }

        };


        /// @brief divide a measurment and a number
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (math::is_complex_v<ARG_TYPE1> && is_number_v<ARG_TYPE2>)
        struct divide<ARG_TYPE1, ARG_TYPE2> {

            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) {

                if (y == typename function_t::second_arg_t{})
                    throw std::runtime_error("Division by zero"); 

                return x * op::inv(y); 

            }

        };


        /// @brief divide a number and a measurment
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (is_number_v<ARG_TYPE1> && math::is_complex_v<ARG_TYPE2>)
        struct divide<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2>;


            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) {

                if (y == typename function_t::second_arg_t{})
                    throw std::runtime_error("Division by zero");

                return x * op::inv(y); 

            }

        };


    } // namespace functions


} // namespace scipp::math