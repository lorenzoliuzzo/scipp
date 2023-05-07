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
        requires (math::is_unary_function_v<FUNC_TYPE>)
    void plot(const FUNC_TYPE& func, const math::interval<typename FUNC_TYPE::arg_t>& I, uint points) noexcept {

        std::vector<double> x(points), y(points);
        auto incr = (I.end - I.start) / static_cast<double>(points);
        for (size_t i = 0; i < points; ++i) {
            x[i] = I.start + i * incr;
            y[i] = func(x[i]);
        }

        plt::plot(x, y);

    }

    template <typename FUNC_TYPE>
        requires (math::is_unary_function_v<FUNC_TYPE>)
    void plot(const FUNC_TYPE& func, const math::interval<typename FUNC_TYPE::arg_t>& I, uint points, std::string label) noexcept {

        std::vector<double> x(points), y(points);
        auto incr = (I.end - I.start) / static_cast<double>(points);
        for (size_t i = 0; i < points; ++i) {
            x[i] = I.start + i * incr;
            y[i] = func(x[i]);
        }

        plt::named_plot(label, x, y);

    }

        
} /// namespace scipp::tools