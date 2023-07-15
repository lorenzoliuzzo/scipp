/**
 * @file    scipp/math/mathematical/exponential.hpp
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
        struct exponential_impl<T> {

            inline static constexpr auto f(const T& x) noexcept {
                    
                return std::exp(x);

            }       

        };


        template <typename T>
            requires geometry::is_scalar_vector_v<T>
        struct exponential_impl<T> {
            
            inline static constexpr auto f(const T& x) noexcept {

                T x_exp;
                std::transform(
                    std::execution::par, 
                    x.data.begin(), x.data.end(), 
                    x_exp.data.begin(), 
                    [](const auto& x_i) { 
                        return op::exp(x_i); 
                    }
                );

                return x_exp;

            }
        
        };



        // /// @brief Exponential of a complex
        // template <typename CMEAS_TYPE>
        //     requires (physics::is_scalar_complex_v<CMEAS_TYPE>)
        // struct exponential_impl<CMEAS_TYPE> {
            
        //     inline static constexpr auto f(const T& x) noexcept {

        //         return polar(std::exp(x.real), x.imag);

        //     }

        // };


    } // namespace op


} // namespace scipp::math