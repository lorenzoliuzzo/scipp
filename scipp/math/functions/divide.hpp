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


    } // namespace functions


} // namespace scipp::math