/**
 * @file    math/integrals/midpoint.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace integrals {


        template <typename FUNCTION_TYPE> 
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto midpoint(const curves::interval<typename FUNCTION_TYPE::arg_t>& I, size_t steps = 100000) noexcept {

            auto result = functions::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t>{};

            const auto h = I.step(steps);
            const auto x_range = std::views::iota(0u, steps) | std::views::transform(
                [&](size_t i) {
                    return I.start + (static_cast<double>(i) + 0.5) * h;
                }
            );

            std::ranges::for_each(x_range,
                [&](auto x_i) {
                    result += FUNCTION_TYPE::f(x_i) * h;
                }
            );

            return result;

        }


        /// @todo to fix: it returns twice the correct result 
        /// @brief Midpoint rule for numerical integration 
        /// @tparam FUNCTION_TYPE integral function type
        /// @tparam PREFIX_TYPE precision of the result
        /// @param I curves::interval of integration
        template <typename FUNCTION_TYPE, typename PREFIX_TYPE, size_t MAX_ITERATIONS = 10000>
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t> && physics::is_prefix_v<PREFIX_TYPE>)
        static constexpr auto midpoint(const curves::interval<typename FUNCTION_TYPE::arg_t>& I) {
            
            using result_t = functions::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t>;
            result_t result{}, prev_result{}, current_result{};

            constexpr double relative_error = static_cast<double>(PREFIX_TYPE::num) / static_cast<double>(PREFIX_TYPE::den);
            for (size_t n = 2; n < MAX_ITERATIONS; n *= 2) {

                current_result = midpoint<FUNCTION_TYPE>(I, n);
                result = (2.0 * current_result + prev_result) / 3.0;

                // Check if the error is below the threshold
                const double error = std::abs((result - prev_result) / result);
                if (error < relative_error)
                    break;

                prev_result = result;

            }

            return op::round(result / relative_error) * relative_error;

        }


    } // namespace integrals


} // namespace scipp::math