/**
 * @file    math/calculus/endpoint.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-24
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace integrals {


        template <typename FUNCTION_TYPE>
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto endpoint_left(const interval<typename FUNCTION_TYPE::arg_t>& I, size_t steps) noexcept {
            
            const auto h = I.step(steps);
            std::array<size_t, steps> indices;
            std::iota(indices.begin(), indices.end(), 0u);

            auto sum = std::transform_reduce(std::execution::par, indices.begin(), indices.end(), 0.0, std::plus<>(),
                [&](auto i) {
                    return FUNCTION_TYPE::f(I.start + static_cast<double>(i) * h);
                }
            );

            return sum * h;
        }


        template <typename FUNCTION_TYPE>
        requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto endpoint_right(const interval<typename FUNCTION_TYPE::arg_t>& I, size_t steps) noexcept {
            
            const auto h = I.step(steps);
            std::array<size_t, steps + 1> indices;
            std::iota(indices.begin(), indices.end(), 1u);

            auto sum = std::transform_reduce(std::execution::par, indices.begin(), indices.end(), 0.0, std::plus<>(),
                [&](auto i) {
                    return FUNCTION_TYPE::f(I.start + static_cast<double>(i) * h);
                }
            );

            return sum * h;

        }


        template <typename FUNCTION_TYPE>
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto endpoint_left(const interval<typename FUNCTION_TYPE::arg_t>& I, double relative_error) noexcept {
            
            auto result = endpoint_left<FUNCTION_TYPE, 1>(I); // Start with a single step
            auto prev_result = result;
            auto prev_prev_result = prev_result;
            double error = 0.0;

            for (size_t steps = 2; ; steps *= 2) {
                result = endpoint_left<FUNCTION_TYPE, steps>(I);
                error = (result - prev_result) / (result - prev_prev_result);

                if (std::abs(error) < relative_error) 
                    break; // Desired relative error achieved

                prev_prev_result = prev_result;
                prev_result = result;
            }

            return result;

        }



        template <typename FUNCTION_TYPE>
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto endpoint_right(const interval<typename FUNCTION_TYPE::arg_t>& I, double relative_error) noexcept {
            
            auto result = endpoint_right<FUNCTION_TYPE, 1>(I); // Start with a single step
            auto prev_result = result;
            auto prev_prev_result = prev_result;
            double error = 0.0;

            for (size_t steps = 2; ; steps *= 2) {
                result = endpoint_right<FUNCTION_TYPE, steps>(I);
                error = (result - prev_result) / (result - prev_prev_result);

                if (std::abs(error) < relative_error) 
                    break; // Desired relative error achieved

                prev_prev_result = prev_result;
                prev_result = result;
            }

            return result;

        }


    } // namespace integrals


} // namespace scipp::math