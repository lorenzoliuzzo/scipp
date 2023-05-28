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
        

        /// @brief divide two physics::base_quantity
        template <typename BASE_TYPE1, typename BASE_TYPE2>
            requires (physics::are_base_v<BASE_TYPE1, BASE_TYPE2>)
        struct divide<BASE_TYPE1, BASE_TYPE2> : binary_function<BASE_TYPE1, BASE_TYPE2, physics::base_quantity<BASE_TYPE1::length - BASE_TYPE2::length, 
                                                                                                               BASE_TYPE1::time - BASE_TYPE2::time,
                                                                                                               BASE_TYPE1::mass - BASE_TYPE2::mass,
                                                                                                               BASE_TYPE1::temperature - BASE_TYPE2::temperature,
                                                                                                               BASE_TYPE1::elettric_current - BASE_TYPE2::elettric_current,
                                                                                                               BASE_TYPE1::substance_amount - BASE_TYPE2::substance_amount,
                                                                                                               BASE_TYPE1::luminous_intensity - BASE_TYPE2::luminous_intensity>> {

        
            using result_t = physics::base_quantity<BASE_TYPE1::length - BASE_TYPE2::length, 
                                                    BASE_TYPE1::time - BASE_TYPE2::time,
                                                    BASE_TYPE1::mass - BASE_TYPE2::mass,
                                                    BASE_TYPE1::temperature - BASE_TYPE2::temperature,
                                                    BASE_TYPE1::elettric_current - BASE_TYPE2::elettric_current,
                                                    BASE_TYPE1::substance_amount - BASE_TYPE2::substance_amount,
                                                    BASE_TYPE1::luminous_intensity - BASE_TYPE2::luminous_intensity>;

            inline static constexpr result_t f(const BASE_TYPE1&, const BASE_TYPE2&) noexcept {

                return {};

            }                                             
            

        };


        /// @brief divide two physics::base_quantity
        template <typename PREFIX_TYPE1, typename PREFIX_TYPE2>
            requires (physics::are_prefix_v<PREFIX_TYPE1, PREFIX_TYPE2>)
        struct divide<PREFIX_TYPE1, PREFIX_TYPE2> : binary_function<PREFIX_TYPE1, PREFIX_TYPE2, std::ratio_divide<PREFIX_TYPE1, PREFIX_TYPE2>> {

        
            using result_t = std::ratio_divide<PREFIX_TYPE1, PREFIX_TYPE2>;


            inline static constexpr result_t f(const PREFIX_TYPE1&, const PREFIX_TYPE2&) noexcept {

                return {};

            }                                             
            

        };


        /// @brief divide an unit of measurement
        template <typename UNIT_TYPE1, typename UNIT_TYPE2>
            requires (physics::are_units_v<UNIT_TYPE1, UNIT_TYPE2>)
        struct divide<UNIT_TYPE1, UNIT_TYPE2> : binary_function<UNIT_TYPE1, UNIT_TYPE2, physics::unit<divide_t<typename UNIT_TYPE1::base_t, typename UNIT_TYPE2::base_t>, 
                                                                                                      divide_t<typename UNIT_TYPE1::prefix_t, typename UNIT_TYPE2::prefix_t>>> {


            using result_t = physics::unit<divide_t<typename UNIT_TYPE1::base_t, typename UNIT_TYPE2::base_t>, 
                                           divide_t<typename UNIT_TYPE1::prefix_t, typename UNIT_TYPE2::prefix_t>>;


            inline static constexpr result_t f(const UNIT_TYPE1&, const UNIT_TYPE2&) noexcept {

                return {};

            }       


        };


        /// @brief divide an unit of measurement
        template <typename SCALAR_TYPE, typename UNIT_TYPE>
            requires (is_number_v<SCALAR_TYPE> && physics::is_unit_v<UNIT_TYPE>)
        struct divide<SCALAR_TYPE, UNIT_TYPE> : binary_function<SCALAR_TYPE, UNIT_TYPE, 
                                                                physics::measurement<typename UNIT_TYPE::base_t, SCALAR_TYPE>> {

            using result_t = physics::measurement<typename UNIT_TYPE::base_t, SCALAR_TYPE>;


            inline static constexpr result_t f(const SCALAR_TYPE& x, const UNIT_TYPE&) noexcept {

                return { x / UNIT_TYPE::mult };

            }       


        };


        /// @brief divide two measurement
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_measurements_v<ARG_TYPE1, ARG_TYPE2>)
        struct divide<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                              physics::measurement<divide_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>, decltype(typename ARG_TYPE1::value_t{} * typename ARG_TYPE2::value_t{})>> {


            using result_t = physics::measurement<divide_t<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>, decltype(typename ARG_TYPE1::value_t{} * typename ARG_TYPE2::value_t{})>; 


            inline static constexpr result_t f(const ARG_TYPE1& x, const ARG_TYPE2& y) {
                
                if (y.value == typename ARG_TYPE2::value_t{})
                    throw std::runtime_error("Division by zero"); 

                return x.value / y.value; 

            }


        };


        /// @brief divide a measurment and a number
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_measurement_v<ARG_TYPE1> && is_number_v<ARG_TYPE2>)
        struct divide<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                                                ARG_TYPE1> {


            using result_t = ARG_TYPE1; 

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) {

                if (y == second_arg_t{})
                    throw std::runtime_error("Division by zero"); 

                return x.value / y; 

            }


        };


        /// @brief divide a number and a measurment
        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (is_number_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        struct divide<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2> {


            using result_t = ARG_TYPE2; 

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) {

                if (y.value == typename ARG_TYPE2::value_t{})
                    throw std::runtime_error("Division by zero");

                return x / y.value; 

            }


        };



    } // namespace functions


} // namespace scipp::math