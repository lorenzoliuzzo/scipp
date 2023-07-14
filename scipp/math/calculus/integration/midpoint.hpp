/**
 * @file    math/integrals/midpoint.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {


        template <size_t STEPS, typename RANGE, typename DOMAIN>
        static constexpr auto midpoint(unary_function<RANGE, DOMAIN>& f, const interval<DOMAIN>& I) noexcept {

            auto result = op::multiply_t<RANGE, DOMAIN>{};

            const auto h = I.step(STEPS);
            const auto x_range = std::views::iota(0u, STEPS) | std::views::transform(
                [&](size_t i) {
                    return I.start + (static_cast<double>(i) + 0.5) * h;
                }
            );

            std::ranges::for_each(x_range,
                [&](auto x_i) {
                    f.var = x_i;
                    result += val(f()) * h;
                }
            );

            return result;

        }


        template <typename RANGE, typename DOMAIN>
        static constexpr auto midpoint(unary_function<RANGE, DOMAIN>& f, const interval<DOMAIN>& I, size_t steps) noexcept {

            auto result = op::multiply_t<RANGE, DOMAIN>{};

            const auto h = I.step(steps);
            const auto x_range = std::views::iota(0u, steps) | std::views::transform(
                [&](size_t i) {
                    return I.start + (static_cast<double>(i) + 0.5) * h;
                }
            );

            std::ranges::for_each(x_range,
                [&](auto x_i) {
                    f.var = x_i;
                    result += val(f()) * h;
                }
            );

            return result;

        }


        template <size_t STEPS, typename RANGE, typename DOMAIN>
        static constexpr auto simpson(unary_function<RANGE, DOMAIN>& f, const interval<DOMAIN>& I) noexcept {

            auto result = op::multiply_t<RANGE, DOMAIN>{};

            const auto h = I.step(STEPS);
            const auto x_range = std::views::iota(0u, STEPS + 1) | std::views::transform(
                [&](size_t i) {
                    return I.start + static_cast<double>(i) * h;
                }
            );

            size_t i = 0;
            std::ranges::for_each(x_range,
                [&](auto x_i) {

                    f.var = x_i;

                    if (x_i == I.start || x_i == I.end)
                        result += val(f()) * h;

                    else if (i % 2 == 0)
                        result += 2.0 * val(f()) * h / 3.0;
                        
                    else
                        result += 4.0 * val(f()) * h / 3.0;
                     
                    i++;

                }
            );

            return result;

        }


        /// @brief Midpoint rule for numerical integration 
        /// @tparam PRECISION std::ratio representing the relative_error of the result
        template <class PRECISION, typename RANGE, typename DOMAIN>
            requires physics::is_prefix_v<PRECISION>
        static constexpr auto midpoint(unary_function<RANGE, DOMAIN>& f, const interval<DOMAIN>& I) noexcept {
            
            using result_t = op::multiply_t<RANGE, DOMAIN>;
            result_t result{}, prev_result{};

            constexpr size_t INITIAL_STEPS = 16;
            constexpr size_t MAX_ITERATIONS = 1048576; // 2^20
            constexpr double relative_error = static_cast<double>(PRECISION::num) / static_cast<double>(PRECISION::den);

            for (size_t n = INITIAL_STEPS; n < MAX_ITERATIONS; n *= 2) {

                result = (2.0 * midpoint(f, I, n) + prev_result) / 3.0;

                // Check if the error is below the threshold
                const double error = op::abs((result - prev_result) / result);
                if (error < relative_error)
                    break;

                prev_result = result;

            }

            return result;

        }


    } // namespace calculus


} // namespace scipp::math