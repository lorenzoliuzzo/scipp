/**
 * @file    scipp/math/logical/equal.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-07-14
 * 
 * @copyright Copyright (c) 2023
 */


    

namespace scipp::math {


    namespace op {


        template <typename T1, typename T2>
        struct equal_impl {

            static constexpr bool f(const T1& x, const T2& y) { 

                return x == y;   
            
            }

        };


        template <typename T1, typename T2>
            requires are_numbers_v<T1, T2>
        struct equal_impl<T1, T2> {

            static constexpr bool f(const T1& x, const T2& y) { 

                return (x == y);   
            
            }

        };


        template <typename T1, typename T2>
            requires physics::are_base_v<T1, T2>
        struct equal_impl<T1, T2> {
            
            static constexpr bool f(const T1&, const T2&) {

                return physics::are_same_base_v<T1, T2>;

            }                                             
            
        };


        template <typename T1, typename T2>
            requires physics::are_units_v<T1, T2>
        struct equal_impl<T1, T2> {
            
            static constexpr bool f(const T1&, const T2&) {

                return physics::are_same_base_v<T1::base_t, T2::base_t> && std::ratio_equal_v<T1::prefix_t, T2::prefix_t>;

            }                                             
            
        };


        template <typename T1, typename T2>
            requires physics::are_measurements_v<T1, T2>
        struct equal_impl<T1, T2> {
            
            static constexpr bool f(const T1& x, const T2& y) {

                if constexpr (physics::are_same_base_v<T1, T2>)
                    return x.value == y.value;
                
                return false; 

            }       

        };


    } // namespace op


} // namespace scipp::math