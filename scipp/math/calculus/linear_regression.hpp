/**
 * @file    math/calculus/interval.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-07-03
 * 
 * @copyright Copyright (c) 2023
 */



/// @brief math namespace contains all the classes and functions of the math library
namespace scipp::math {
    
    
    // Linear Regression struct
    template <typename T1, typename T2>
    struct linear_regression {

        using slope_t = calculus::variable<op::divide_t<T2, T1>>;
        slope_t slope{};

        using intercept_t = calculus::variable<T2>;
        intercept_t intercept{};

        linear_regression() noexcept {}

        void fit(const std::vector<T1>& x, const std::vector<T2>& y, size_t numIterations, double learningRate) {

            size_t numSamples = x.size();
            for (size_t i = 0; i < numIterations; ++i) {

                op::divide_t<T2, T1> sumSlope{};
                T2 sumIntercept{};

                // Calculate gradients
                for (size_t j = 0; j < numSamples; ++j) {
                    intercept_t predictedExpr = this->predict(x[i % numSamples]); 
                    auto [d_slope, d_intercept] = calculus::derivatives(predictedExpr, calculus::wrt(this->slope, this->intercept));
                    sumSlope += d_slope;
                    sumIntercept += d_intercept;
                }

                // Update parameters
                slope -= learningRate * (sumSlope / numSamples);
                intercept -= learningRate * (sumIntercept / numSamples);

            }
        }

        intercept_t predict(T1 xValue) {
            
            return slope * xValue + intercept;

        }

    };


} // namespace scipp::math