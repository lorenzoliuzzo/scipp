/**
 * @file    tools/io.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-28
 * 
 * @copyright Copyright (c) 2023
 */


/// @brief physics namespace contains all the classes and functions of the physics library
namespace scipp::tools {


    template <typename FUNC_TYPE>
        requires (math::functions::is_unary_function_v<typename FUNC_TYPE::function_t>)
    void plot(const math::curves::interval<typename FUNC_TYPE::function_t::arg_t>& I, size_t points) noexcept {

        std::vector<double> x(points), y(points);
        const auto h = I.step(points);

        for (size_t i = 0; i < points; ++i) {
            auto x_i = I.start + i * h;
            y[i] = FUNC_TYPE::f(x_i).value;
            x[i] = x_i.value;
        }

        plt::plot(x, y);
        plt::show(); 

    }


    // template <typename FUNC_TYPE>
    //     requires (math::functions::is_unary_function_v<FUNC_TYPE>)
    // void plot(const FUNC_TYPE& func, const math::interval<typename FUNC_TYPE::arg_t>& I, uint points, std::string label) noexcept {

    //     std::vector<double> x(points), y(points);
    //     auto incr = (I.end - I.start) / static_cast<double>(points);
    //     for (size_t i = 0; i < points; ++i) {
    //         x[i] = I.start + i * incr;
    //         y[i] = func(x[i]);
    //     }

    //     plt::named_plot(label, x, y);

    // }

        
} /// namespace scipp::tools