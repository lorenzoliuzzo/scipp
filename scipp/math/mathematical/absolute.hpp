/**
 * @file    math/functions/absolute.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-20
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {



        /// @brief Get the absolute of a number or a measurement
        template <typename T>
            requires (is_number_v<T> || physics::is_measurement_v<T>)
        struct absolute_impl<T> {

            using result_t = T;

            inline static constexpr result_t f(const T& x) {
                    
                return (x < T{}) ? -x : x;

            }       

        };


        // /// @brief Get the absolute of a complex number
        // template <typename CMEAS_TYPE>
        //     requires (math::is_complex_v<CMEAS_TYPE>)
        // struct absolute<CMEAS_TYPE> {

        //     using function_t = unary_function<CMEAS_TYPE, typename CMEAS_TYPE::value_t>;

        //     inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

        //         return op::sqrt(op::sq(x.real) + op::sq(x.imag));

        //     }

        // };


        // /// @brief Get the absolute of a dual number
        // template <typename T>
        //     requires (math::is_dual_v<T>)
        // struct absolute<T> {

        //     using function_t = unary_function<T, T>;

        //     inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

        //         return { op::abs(x.real), x.imag * op::sign(x.real) }; 

        //     }

        // };


        // /// @brief Get the absolute of a vector
        // template <typename VECTOR_TYPE>
        //     requires (geometry::is_vector_v<VECTOR_TYPE>)
        // struct absolute_<VECTOR_TYPE> : unary_function<VECTOR_TYPE, geometry::vector<absolute_t<typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>> {


        //     using result_t = geometry::vector<absolute_t<typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>; 


        //     inline static constexpr result_t f(const VECTOR_TYPE& x) {

        //         result_t x_abs;
        //         std::transform(x.data.begin(), x.data.end(), x_abs.data.begin(), [](const auto& x_i) { return op::abs(x_i); });
        //         return x_abs;

        //     }

        
        // };


    } // namespace functions


} // namespace scipp::math