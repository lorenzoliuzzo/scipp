/**
 * @file    math/integrals/curvilinear.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 *
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace integrals {


        template <typename FUNCTION_TYPE> 
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::function_t>)
        static constexpr auto curvilinear(const curve<typename FUNCTION_TYPE::arg_t>& gamma,
                                          size_t steps,
                                          double incr_der = 1.e-6) {

            using result_t = functions::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t>;
            result_t result{}; 
            const double N = static_cast<double>(steps);
            // auto d_curve = total_derivative(curve); // @todo
            for (size_t i{}; i < steps; ++i) {

                double t = static_cast<double>(i) / N;
                auto x = gamma(t);
                result += FUNCTION_TYPE::f(x) * op::norm((gamma(t + incr_der) - x) / incr_der);

            }

            return result / N; 

        }


    } // namespace integrals
    

} // namespace scipp::math