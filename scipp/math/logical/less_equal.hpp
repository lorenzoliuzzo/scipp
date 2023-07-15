/**
 * @file    scipp/math/logical/less_equal.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-07-14
 * 
 * @copyright Copyright (c) 2023
 */


    

namespace scipp::math {


    namespace op {


        template <typename T1, typename T2>
        struct less_equal_impl {

            static constexpr bool f(const T1& x, const T2& y) { 

                return x <= y;   
            
            }

        };


        template <typename T1, typename T2>
            requires are_numbers_v<T1, T2>
        struct less_equal_impl<T1, T2> {

            static constexpr bool f(const T1& x, const T2& y) { 

                return (x <= y);   
            
            }

        };


        template <typename T1, typename T2>
            requires (physics::are_measurements_v<T1, T2> && physics::are_same_base_v<typename T1::base_t, typename T2::base_t>)
        struct less_equal_impl<T1, T2> {
            
            static constexpr bool f(const T1& x, const T2& y) {

                return x.value <= y.value;

            }       

        };


    } // namespace op


} // namespace scipp::math