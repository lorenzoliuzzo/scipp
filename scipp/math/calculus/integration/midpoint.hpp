/**
 * @file    math/integrals/midpoint.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the midpoint rule for numerical integration.
 * @date    2023-07-16
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        namespace integrals {

            
            /// @brief Midpoint rule for numerical integration
            /// @tparam number of steps
            /// @param function to integrate
            /// @param interval of integration
            template <size_t N, typename FUNCTION, typename DOMAIN>
            static constexpr auto midpoint(const FUNCTION& f, const interval<DOMAIN>& I) {

                op::multiply_t<std::invoke_result_t<FUNCTION, DOMAIN>, DOMAIN> result{};

                const auto h = I.step(N);
                const auto x_range = std::views::iota(0u, N) | std::views::transform(
                    [&](size_t i) {
                        return I.start + (static_cast<double>(i) + 0.5) * h;
                    }
                );

                std::ranges::for_each(x_range,
                    [&](auto x_i) {
                        result += f(x_i) * h;
                    }
                );

                return result;

            }


            /// @brief Midpoint rule for numerical integration
            /// @param function to integrate
            /// @param interval of integration
            /// @param number of steps
            template <typename FUNCTION, typename DOMAIN>
            static constexpr auto midpoint(const FUNCTION& f, const interval<DOMAIN>& I, size_t n) {

                op::multiply_t<std::invoke_result_t<FUNCTION, DOMAIN>, DOMAIN> result{};

                const auto h = I.step(n);
                const auto x_range = std::views::iota(0u, n) | std::views::transform(
                    [&](size_t i) {
                        return I.start + (static_cast<double>(i) + 0.5) * h;
                    }
                );

                std::ranges::for_each(x_range,
                    [&](auto x_i) {
                        result += f(x_i) * h;
                    }
                );

                return result;

            }


            /// @brief Midpoint rule for numerical integration
            /// @tparam std::ratio representing the relative_error seeked
            /// @param function to integrate
            /// @param interval of integration
            template <typename PRECISION, typename FUNCTION, typename DOMAIN>
                requires physics::is_prefix_v<PRECISION>
            static constexpr auto midpoint(const FUNCTION& f, const interval<DOMAIN>& I) noexcept {
                
                static_assert(PRECISION::den > PRECISION::num, "The relative error must be less than 1");

                using result_t = op::multiply_t<std::invoke_result_t<FUNCTION, DOMAIN>, DOMAIN>;
                result_t result{}, prev_result{};

                constexpr size_t INITIAL_STEPS = 16;
                constexpr size_t MAX_ITERATIONS = 1048576; // 2^20
                constexpr double relative_error = static_cast<double>(PRECISION::num) / static_cast<double>(PRECISION::den);
                double error{};

                for (size_t n = INITIAL_STEPS; n < MAX_ITERATIONS; n *= 2) {

                    result = (2.0 * midpoint(f, I, n) + prev_result) / 3.0;

                    // Check if the error is below the threshold
                    error = op::abs((result - prev_result) / result);
                    if (error < relative_error)
                        break;

                    prev_result = result;

                }

                return op::floor(result / relative_error) * relative_error;

            }

        
        } // namespace integrals


    } // namespace calculus


} // namespace scipp::math