/**
 * @file    math/calculus/curves/line.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-09
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {

    
    namespace curves {


        template <typename T>
        struct line : curve<T, T::dim> {


            using _t = line<T>;

            using value_t = T;

            using param_t = double;


            value_t origin;

            value_t direction;         


            constexpr line(value_t A, value_t dir) noexcept : 
                
                origin(std::forward<value_t>(A)), direction(std::forward<value_t>(dir)) {}



            inline constexpr value_t operator()(param_t t) const noexcept {

                return origin + t * direction;

            }


        }; // struct line



        template <typename T>
            requires (is_number_v<T> || physics::is_generic_measurement_v<T>)
        struct line<T> : curve<T, 1> {


            using _t = line<T>;

            using value_t = T;

            using param_t = double;


            value_t origin;

            value_t direction;         


            constexpr line(value_t A, value_t dir) noexcept : 
                
                origin(std::forward<value_t>(A)), direction(std::forward<value_t>(dir)) {}



            inline constexpr value_t operator()(param_t t) const noexcept {

                return origin + t * direction;

            }


        }; // struct line

        
    } // namespace curves


} // namespace scipp::math