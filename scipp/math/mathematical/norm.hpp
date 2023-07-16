/**
 * @file    math/functions/mathematical/sign.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the sign function
 * @date    2023-07-16
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
            requires is_number_v<T> || physics::is_measurement_v<T>
        struct norm_impl<T> {

            static constexpr T f(const T& other) noexcept {

                return abs(other);

            }

        };


        template <typename T1, typename T2>
        struct norm_impl<std::pair<T1, T2>> {

            static constexpr auto f(const std::pair<T1, T2>& other) noexcept {

                return hypot(other.first, other.second);

            }

        };
        

        template <typename T>
            requires geometry::is_vector_v<T>
        struct norm_impl<T> {

            static constexpr typename T::value_t f(const T& other) noexcept {

                if constexpr (T::dim == 1) 
                    return abs(other.data[0]);

                auto sq_sum = std::accumulate(
                    other.data.begin(), other.data.end(), 
                    typename T::value_t{}, 
                    [](auto& acc, auto& val) { 
                        return acc + square(val); 
                    }
                );

                return sqrt(sq_sum);

            }

        };
        





        // template <typename CMEAS_TYPE>  
        //     requires (math::is_complex_v<CMEAS_TYPE>)
        // struct norm_impl<CMEAS_TYPE> : unary_function<typename CMEAS_TYPE::value_t, CMEAS_TYPE> {

        //     constexpr typename CMEAS_TYPE::value_t f(const CMEAS_TYPE& other) const noexcept override {

        //         return op::sqrt(op::sq(other.real) + op::sq(other.imag));

        //     }

        // };
        

        // /// @brief Get the norm of the vector
        // template <typename VEC_TYPE>
        //     requires (geometry::is_vector_v<VEC_TYPE>)
        // struct norm_impl<VEC_TYPE> : unary_function<typename VEC_TYPE::measurement_t, VEC_TYPE> { 

        //     constexpr typename VEC_TYPE::measurement_t f(const VEC_TYPE& other) const noexcept override {

        //         if constexpr (VEC_TYPE::dim == 1) 
        //             return other.data[0];

        //         square_t<typename VEC_TYPE::measurement_t> result;

        //         for (size_t i{}; i < VEC_TYPE::dim; ++i) 
        //             result += op::sq(other.data[i]);

        //         return op::sqrt(result);

        //     }

        // };


    } // namespace op


} // namespace scipp::math