/**
 * @file    test/math/variables.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-12
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"

using namespace scipp;

using namespace tools; 
using namespace math; 
using namespace math::differentials;    


int main() {

    double x_val = 2.0;
    double y_val = 3.0;

    // Create independent variable nodes
    ExprPtr<double> x = std::make_shared<IndependentVariableExpr<double>>(x_val);
    ExprPtr<double> y = std::make_shared<IndependentVariableExpr<double>>(y_val);

    // Create dependent variable node with an expression
    ExprPtr<double> z = std::make_shared<DependentVariableExpr<double>>(x * y);

    // Perform forward propagation
    z->update();

    // Print the computed value of z
    std::cout << "z = " << z->val << std::endl;

    // Perform backward propagation to compute gradients
    double dz_dx = 0.0;
    double dz_dy = 0.0;
    z->bind_value(&dz_dx);
    z->propagate(1.0);

    z->bind_value(&dz_dy);
    z->propagate(1.0);

    // Print the gradients
    std::cout << "dz/dx = " << dz_dx << std::endl;
    std::cout << "dz/dy = " << dz_dy << std::endl;

    return 0;
}