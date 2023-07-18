/**
 * @file    scipp/tools/plot.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the plot function.
 * @date    2023-07-16
 * 
 * @copyright Copyright (c) 2023
 */


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::tools {
    

    using namespace scipp::math;

    

    template <size_t N, typename DOMAIN, typename FUNCTION>
    static void plot(const calculus::interval<DOMAIN>& I, 
                     const FUNCTION& f,
                     const std::string& x_label, const std::string& y_label, 
                     const std::string& title = "", const std::string& filename = "") {

        using RANGE = std::invoke_result_t<FUNCTION, DOMAIN>;

        std::vector<double> x_values(N), y_values(N); /// to store the values for the plot

        const auto h = I.step(N);
        const auto x_range = std::views::iota(0u, N) | std::views::transform(
            [&](size_t i) {
                return I.start + (static_cast<double>(i) + 0.5) * h;
            }
        );

        std::ranges::for_each(x_range,
            [&](auto x_i) {

                if constexpr (physics::is_measurement_v<DOMAIN>)
                    x_values.push_back(x_i.value);
                else
                    x_values.push_back(x_i);

                if constexpr (physics::is_measurement_v<RANGE>)
                    y_values.push_back(f(x_i).value);
                else 
                    y_values.push_back(f(x_i));

            }
        );

        plt::figure_size(900, 600);
        plt::grid(true);

        plt::plot(x_values, y_values);

        if constexpr (physics::is_measurement_v<DOMAIN>) {

            plt::xlabel(x_label + " [" + DOMAIN::base_t::to_string() + "]");
            plt::xlim(I.start.value, I.end.value);

        } else {

            plt::xlabel(x_label);
            plt::xlim(I.start, I.end);

        }

        if constexpr (physics::is_measurement_v<RANGE>)
            plt::ylabel(y_label + " [" + RANGE::base_t::to_string() + "]");
        else
            plt::ylabel(y_label);

        if (title != "")
            plt::title(title);

        if (filename != "")
            plt::save(filename);

        plt::show();

    }


    template <typename DOMAIN, typename FUNCTION>
    static void plot(size_t N,
                     const calculus::interval<DOMAIN>& I, 
                     const FUNCTION& f,
                     const std::string& x_label, const std::string& y_label, 
                     const std::string& title = "", const std::string& filename = "") {

        using RANGE = std::invoke_result_t<FUNCTION, DOMAIN>;

        std::vector<double> x_values(N), y_values(N); /// to store the values for the plot

        const auto h = I.step(N);
        const auto x_range = std::views::iota(0u, N) | std::views::transform(
            [&](size_t i) {
                return I.start + (static_cast<double>(i) + 0.5) * h;
            }
        );

        std::ranges::for_each(x_range,
            [&](auto x_i) {

                if constexpr (physics::is_measurement_v<DOMAIN>)
                    x_values.push_back(x_i.value);
                else
                    x_values.push_back(x_i);

                if constexpr (physics::is_measurement_v<RANGE>)
                    y_values.push_back(f(x_i).value);
                else 
                    y_values.push_back(f(x_i));

            }
        );

        plt::figure_size(900, 600);
        plt::grid(true);

        plt::plot(x_values, y_values);

        if constexpr (physics::is_measurement_v<DOMAIN>) {

            plt::xlabel(x_label + " [" + DOMAIN::base_t::to_string() + "]");
            plt::xlim(I.start.value, I.end.value);

        } else {

            plt::xlabel(x_label);
            plt::xlim(I.start, I.end);

        }

        if constexpr (physics::is_measurement_v<RANGE>)
            plt::ylabel(y_label + " [" + RANGE::base_t::to_string() + "]");
        else
            plt::ylabel(y_label);

        if (title != "")
            plt::title(title);

        if (filename != "")
            plt::save(filename);

        plt::show();

    }



    template <typename CURVE>
        requires calculus::is_curve_v<CURVE>
    static void plot(size_t N, 
                     const CURVE& gamma,
                     const std::string& x_label, const std::string& y_label,
                     const std::string& title = "", const std::string& filename = "") {

        std::vector<double> x_values, y_values; /// to store the values for the plot
        x_values.reserve(N);
        y_values.reserve(N);
        
        const auto h = gamma.domain.step(N);
        const auto t_range = std::views::iota(0u, N) | std::views::transform(
            [&](size_t i) {
                return gamma.domain.start + (static_cast<double>(i) + 0.5) * h;
            }
        );

        std::ranges::for_each(t_range,
            [&](auto t_i) {

                const auto point = gamma(t_i);

                // if constexpr (physics::is_measurement_v<decltype(x_i)>)
                //     x_values.push_back(x_i.value);
                // else
                    x_values.emplace_back(val(point[0]).value);

                // if constexpr (physics::is_measurement_v<decltype(y_i)>)
                //     y_values.emplace_back(y_i.value);
                // else 
                    y_values.emplace_back(val(point[1]).value);

            }
        );

        plt::figure_size(900, 900);
        plt::grid(true);

        plt::plot(x_values, y_values);

        plt::xlabel(x_label); 
        plt::ylabel(y_label);

        if (title != "")
            plt::title(title);

        if (filename != "")
            plt::save(filename);

        plt::show();


    }


    // template <typename CURVE>
    // static void plot(size_t N,
    //                  const CURVE& gamma,
    //                  const std::string& x_label, const std::string& y_label, 
    //                  const std::string& title = "", const std::string& filename = "") {

    //     std::vector<double> x_values(N), y_values(N); /// to store the values for the plot

    //     const auto h = gamma.interval.step(N);
    //     const auto t_range = std::views::iota(0u, N) | std::views::transform(
    //         [&](size_t i) {
    //             return I.start + (static_cast<double>(i) + 0.5) * h;
    //         }
    //     );

    //     std::ranges::for_each(t_range,
    //         [&](auto x_i) {

    //             auto point = gamma(x_i);

    //             if constexpr (physics::is_measurement_v<DOMAIN>)
    //                 x_values.push_back(x_i.value);
    //             else
    //                 x_values.push_back(x_i);

    //             if constexpr (physics::is_measurement_v<RANGE>)
    //                 y_values.push_back(f(x_i).value);
    //             else 
    //                 y_values.push_back(f(x_i));

    //         }
    //     );

    //     plt::figure_size(900, 600);
    //     plt::grid(true);

    //     plt::plot(x_values, y_values);

    //     if constexpr (physics::is_measurement_v<DOMAIN>) {

    //         plt::xlabel(x_label + " [" + DOMAIN::base_t::to_string() + "]");
    //         plt::xlim(I.start.value, I.end.value);

    //     } else {

    //         plt::xlabel(x_label);
    //         plt::xlim(I.start, I.end);

    //     }

    //     if constexpr (physics::is_measurement_v<RANGE>)
    //         plt::ylabel(y_label + " [" + RANGE::base_t::to_string() + "]");
    //     else
    //         plt::ylabel(y_label);

    //     if (title != "")
    //         plt::title(title);

    //     if (filename != "")
    //         plt::save(filename);

    //     plt::show();

    // }


} // namespace scipp::tools