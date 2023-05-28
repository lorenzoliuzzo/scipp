/**
 * @file    math/integrals/trapezoid.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace integrals {




        /// @brief Trapezoid rule for numerical integration 
        /// @tparam FUNCTION_TYPE integral function type
        /// @param I interval of integration
        /// @param steps number of steps
        template <typename FUNCTION_TYPE>
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto trapezoid(const interval<typename FUNCTION_TYPE::arg_t>& I, size_t steps = 10000) {
            

            if (is_finite(I.end) && is_finite(I.start)) {
                
                // Regular integration over a finite interval
                const auto h = I.step(steps);
                const auto x_range = std::views::iota(1u, steps) | std::views::transform(
                    [&](size_t i) {
                        return I.start + static_cast<double>(i) * h;
                    }
                );

                auto result = (FUNCTION_TYPE::f(I.start) + FUNCTION_TYPE::f(I.end)) * h / 2.0;
                std::ranges::for_each(x_range,
                    [&](auto x_i) {
                        result += FUNCTION_TYPE::f(x_i) * h;
                    }
                );

                return result;

            } else  
                throw std::runtime_error("Maybe don't use such a poor algorithm to integrate over an infinite interval");

        }



        /// @brief Trapezoid's rule for numerical integration 
        /// @tparam FUNCTION_TYPE integral function type
        /// @tparam PREFIX_TYPE precision of the result
        /// @param I interval of integration
        template <typename FUNCTION_TYPE, typename PREFIX_TYPE, size_t MAX_ITERATIONS = 10000000>
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t> && physics::is_prefix_v<PREFIX_TYPE>)
        static constexpr auto trapezoid(const interval<typename FUNCTION_TYPE::arg_t>& I) {
            
            using result_t = functions::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t>;
            result_t result{}, prev_result{};

            constexpr double relative_error = static_cast<double>(PREFIX_TYPE::num) / static_cast<double>(PREFIX_TYPE::den);
            for (size_t n = 1; n < MAX_ITERATIONS; n *= 2) {

                auto current_result = trapezoid<FUNCTION_TYPE>(I, n);
                result = (2.0 * current_result + prev_result) / 3.0; // Update result using trapezoid's rule sum

                // Check if the error is below the threshold
                const double error = op::abs((result - prev_result) / result);
                if (error < relative_error)
                    break;

                prev_result = result;

            }

            return op::round(result / relative_error) * relative_error;

        }

    } // namespace integrals


} // namespace scipp::math