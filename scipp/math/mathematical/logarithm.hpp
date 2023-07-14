/**
 * @file    scipp/math/mathematical/logarithm.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-07-14
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
            requires (is_number_v<T> || physics::is_scalar_measurement_v<T>)
        struct logarithm_impl<T> {

            static constexpr auto f(const T& x) {
                    
                if (x <= 0.0) 
                    throw std::invalid_argument("logarithm of a negative number is not defined");

                return std::log(x);

            }       

        };


        // /// @brief Logarithm of a complex
        // template <typename CMEAS_TYPE>
        //     requires (physics::is_scalar_complex_v<CMEAS_TYPE>)
        // struct logarithm_impl<CMEAS_TYPE> {
            
        //     inline static constexpr function_t::result_t f(const T& x) {

        //         return { op::log(op::abs(x)), x.arg() };

        //     }

        // };


        template <typename T>
            requires (geometry::is_scalar_vector_v<T>)
        struct logarithm_impl<T> {
            
            static constexpr T f(const T& x) {

                T x_exp;
                std::transform(
                    std::execution::par, 
                    x.data.begin(), x.data.end(), 
                    x_exp.data.begin(), 
                    [](const auto& x_i) { 
                        return op::log(x_i); 
                    }
                );

                return x_exp;

            }

        };


    } // namespace op


} // namespace scipp::math