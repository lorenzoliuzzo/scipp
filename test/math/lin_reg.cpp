/**
 * @file    test/math/möbius.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-07-03
 * 
 * @copyright Copyright (c) 2023
 */


#include "scipp"

using namespace scipp;
using namespace math; 
using tools::print; 


int main() {

    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y = {2.0, 4.0, 6.0, 8.0, 10.0};

    linear_regression<double, double> model;
    model.fit(x, y, 1000, 0.6);

    print("slope: ", model.slope);
    print("intercept: ", model.intercept);

    // double xValue = 6.0;
    // double predictedY = model.predict(xValue);

    // std::cout << "Predicted y for x = " << xValue << ": " << predictedY << std::endl;

    return 0;

}