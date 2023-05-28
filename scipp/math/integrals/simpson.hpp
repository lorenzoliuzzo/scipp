/**
 * @file    math/integrals/simpson.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace integrals {


        /// @brief Simpson's rule for numerical integration 
        /// @tparam FUNCTION_TYPE integral function type
        /// @param I interval of integration
        /// @param steps number of steps
        template <typename FUNCTION_TYPE>
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        static constexpr auto simpson(const interval<typename FUNCTION_TYPE::arg_t>& I, size_t steps = 10000) {
            

            if (is_finite(I.end) && is_finite(I.start)) {
                
                using result_t = functions::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t>;
                result_t result{}; 

                const auto h = I.step(steps);
                const auto x_range = std::views::iota(0u, steps + 1) | std::views::transform(
                    [&](size_t i) {
                        return I.start + static_cast<double>(i) * h;
                    }
                );

                size_t i = 0;
                std::ranges::for_each(x_range,
                    [&](auto x_i) {
                        if (x_i == I.start || x_i == I.end)
                            result += FUNCTION_TYPE::f(x_i) * h;
                        else if (i % 2 == 0)
                            result += 2 * FUNCTION_TYPE::f(x_i) * h;
                        else
                            result += 4 * FUNCTION_TYPE::f(x_i) * h;

                        i++;
                    }
                );

                result /= 3.0;

                return result;

            } else  
                throw std::runtime_error("Maybe don't use such a poor algorithm to integrate over an infinite interval");

        }


        /// @brief Simpson's rule for numerical integration 
        /// @tparam FUNCTION_TYPE integral function type
        /// @tparam PREFIX_TYPE precision of the result
        /// @param I interval of integration
        template <typename FUNCTION_TYPE, typename PREFIX_TYPE, size_t MAX_ITERATIONS = 10000000>
            requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t> && physics::is_prefix_v<PREFIX_TYPE>)
        static constexpr auto simpson(const interval<typename FUNCTION_TYPE::arg_t>& I) {
            
            using result_t = functions::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t>;
            result_t result{}, prev_result{}, current_result{};

            constexpr double relative_error = static_cast<double>(PREFIX_TYPE::num) / static_cast<double>(PREFIX_TYPE::den);
            for (size_t n = 1; n < MAX_ITERATIONS; n *= 2) {

                current_result = simpson<FUNCTION_TYPE>(I, n);
                result = (2.0 * current_result + prev_result) / 3.0; 

                const double error = std::abs((result - prev_result) / result);
                if (error < relative_error)
                    break;

                prev_result = result;

            }

            return op::round(result / relative_error) * relative_error;

        }


        // template <typename FUNCTION_TYPE> 
        //     requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t>)
        // static constexpr auto simpson(const interval<typename FUNCTION_TYPE::arg_t>& I, size_t steps) noexcept 

        //     const auto h = (I.end - I.start) / static_cast<double>(steps);
        //     auto result = functions::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t>{};
        //     auto x = I.start;
        //     for (size_t i = 0; i < steps - 1; i += 2) {
        //         const auto x1 = x;
        //         const auto x2 = x + h;
        //         const auto x_mid = (x1 + x2) / 2.0;
        //         result += (FUNCTION_TYPE::f(x1) + 4.0 * FUNCTION_TYPE::f(x_mid) + FUNCTION_TYPE::f(x2)) * (h / 3.0);
        //         x += 2 * h;
        //     }

        //     return result;


            // const auto h = (I.end - I.start) / static_cast<double>(steps);
            // std::vector<size_t> indices(steps + 1);
            // std::iota(indices.begin(), indices.end(), 0u);

            // auto result = functions::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t>{};
            // for (size_t i = 0; i < steps - 1; i += 2) {
            //     const auto x1 = I.start + static_cast<double>(indices[i]) * h;
            //     const auto x2 = I.start + static_cast<double>(indices[i + 1]) * h;
            //     const auto x_mid = (x1 + x2) / 2.0;
            //     result += (FUNCTION_TYPE::f(x1) + 4.0 * FUNCTION_TYPE::f(x_mid) + FUNCTION_TYPE::f(x2)) * (h / 3.0);
            // }

            // return result;

        // std::vector<size_t> indices(steps + 1);
        // std::iota(indices.begin(), indices.end(), 0u);

        // std::vector<double> x_values(steps + 1);
        // std::transform(indices.begin(), indices.end(), x_values.begin(), [&](auto i) {
        //     return I.start + static_cast<double>(i) * h;
        // });

        // std::vector<double> f_values(steps + 1);
        // std::transform(x_values.begin(), x_values.end(), f_values.begin(), FUNCTION_TYPE::f);

        // std::vector<double> terms(steps + 1);
        // std::transform(x_values.begin(), x_values.end(), f_values.begin(), terms.begin(), [&](auto x, auto f) {
        //     return f * (static_cast<int>(x / h) % 2 == 0 ? 2.0 : 4.0);
        // });

        // return std::accumulate(terms.begin(), terms.end(), 0.0) * (h / 3.0);


        // auto indices = std::views::iota(0u, steps + 1);

        // auto x_values = indices | std::views::transform([&](auto i) {
        //     return I.start + static_cast<double>(i) * h;
        // });

        // auto f_values = x_values | std::views::transform(FUNCTION_TYPE::f);

        // auto terms = std::views::zip(x_values, f_values) | std::views::transform([&](auto x, auto f) {
        //     return f * (static_cast<int>(x / h) % 2 == 0 ? 2.0 : 4.0);
        // });

        // return std::ranges::accumulate(terms, 0.0) * (h / 3.0);
    
        // std::vector<size_t> indices(steps + 1);
        // std::iota(indices.begin(), indices.end(), 0u);

        // std::vector<double> values(steps);
        // std::transform(indices.begin(), indices.end() - 1, values.begin(), [&](auto i) {
        //     const auto x1 = I.start + static_cast<double>(indices[i]) * h;
        //     const auto x2 = I.start + static_cast<double>(indices[i + 1]) * h;
        //     const auto x_mid = (x1 + x2) / 2.0;
        //     return FUNCTION_TYPE::f(x1) + 4.0 * FUNCTION_TYPE::f(x_mid) + FUNCTION_TYPE::f(x2);
        // });

        // return std::reduce(values.begin(), values.end(), 0.0, std::plus<>()) * (h / 3.0);

        // std::vector<size_t> indices(steps + 1);
        // std::iota(indices.begin(), indices.end(), 0u);

        // return std::views::iota(2u, steps, 2u)
        //     | std::views::transform([&](auto i) {
        //         const auto x1 = I.start + static_cast<double>(indices[i - 2]) * h;
        //         const auto x2 = I.start + static_cast<double>(indices[i]) * h;
        //         const auto x_mid = (x1 + x2) / 2.0;
        //         return FUNCTION_TYPE::f(x1) + 4.0 * FUNCTION_TYPE::f(x_mid) + FUNCTION_TYPE::f(x2);
        //     })
        //     | std::ranges::reduce(std::plus<>())
        //     * (h / 3.0);


            // return std::transform_reduce(indices | std::views::drop(2) | std::views::take(steps - 2),
            //     indices | std::views::drop(2),
            //     0.0,
            //     [&](auto i1, auto i2) {
            //         const auto x1 = I.start + static_cast<double>(i1) * h;
            //         const auto x2 = I.start + static_cast<double>(i2) * h;
            //         const auto x_mid = (x1 + x2) / 2.0;
            //         return (FUNCTION_TYPE::f(x1) + 4.0 * FUNCTION_TYPE::f(x_mid) + FUNCTION_TYPE::f(x2)) * h / 6.0;
            //     }
            // );

        

// template <typename FUNCTION_TYPE>
// static constexpr auto simpson_recursive(const interval<typename FUNCTION_TYPE::arg_t>& I, const double h, const size_t n, const size_t depth) noexcept 
//     -> functions::multiply_t<typename FUNCTION_TYPE::result_t, typename FUNCTION_TYPE::arg_t> {
    
//     const auto x1 = I.start;
//     const auto x2 = I.start + h;
//     const auto x_mid = (x1 + x2) / 2.0;

//     const auto sum = FUNCTION_TYPE::f(x1) + 4.0 * FUNCTION_TYPE::f(x_mid) + FUNCTION_TYPE::f(x2);
//     const auto integral = sum * (h / 6.0);

//     if (depth > 0) {
//         const auto interval_left = interval<typename FUNCTION_TYPE::arg_t>(I.start, x_mid);
//         const auto interval_right = interval<typename FUNCTION_TYPE::arg_t>(x_mid, I.end);
//         const auto integral_left = simpson_recursive<FUNCTION_TYPE>(interval_left, h / 2.0, n / 2, depth - 1);
//         const auto integral_right = simpson_recursive<FUNCTION_TYPE>(interval_right, h / 2.0, n / 2, depth - 1);
//         return integral + integral_left + integral_right;
//     }

//     return integral;
// }


//         /// @brief Rectangle rule for numerical integration 
//         /// @tparam FUNCTION_TYPE integral function type
//         /// @tparam PREFIX_TYPE precision of the result
//         /// @param I interval of integration
//         template <typename FUNCTION_TYPE, typename PREFIX_TYPE, size_t MAX_ITERATIONS = 1000>
//             requires (functions::is_unary_function_v<typename FUNCTION_TYPE::_t> && physics::is_prefix_v<PREFIX_TYPE>)
//         static constexpr auto simpson(const interval<typename FUNCTION_TYPE::arg_t>& I) noexcept {

//             constexpr double relative_error = static_cast<double>(PREFIX_TYPE::num) / static_cast<double>(PREFIX_TYPE::den);

//             auto h = (I.end - I.start);
//             size_t n = 1;

//             auto result = FUNCTION_TYPE::f((I.start + I.end) / 2.0) * h;
//             auto prev_result = result;

//             while (true) {

//                 n *= 2;

//                 const auto sum = simpson<FUNCTION_TYPE>(I, n);        
//                 result = (4.0 * sum - prev_result) / 3.0; // Update result using Simpson's rule sum

//                 // Check if the error is below the threshold
//                 const double error = (result - prev_result) / result;
//                 if (std::abs(error) < relative_error)
//                     break;

//                 prev_result = result;
//             }

//             return op::round(result / relative_error) * relative_error;

//         }

    } // namespace integrals


} // namespace scipp::math