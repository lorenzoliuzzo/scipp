/**
 * @file    test/math/möbius.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-07-03
 * 
 * @copyright Copyright (c) 2023
 */


#include "scipp"


using namespace scipp::math::calculus; 


void composition() {

    // Create a sample Möbius map
    möbius_map M(1.0, 2.0, 3.0, 4.0);

    // Decompose the Möbius map into a linear map, an inversion, and another linear map
    auto L1 = linear_map(M.c, M.d);
    auto L2 = linear_map(M.b - (M.a * M.d) / M.c, M.a / M.c);
    auto M_INV = M.inverse();

    // Define a complex number
    std::complex<double> z(2.0, 3.0);

    // Apply the decomposition steps
    std::complex<double> result1 = L1(z);
    std::complex<double> result2 = inversion_map(result1);
    std::complex<double> result3 = L2(result2);

    // Apply the Möbius map directly
    std::complex<double> mobiusResult = M(z);

    // Output the results
    std::cout << "Original complex number: " << z << '\n';
    std::cout << "Mapped complex number using Möbius map: " << mobiusResult << '\n';
    std::cout << "Mapped complex number using decomposition: " << result3 << '\n';
    std::cout << "Inverse of the Möbius map: " << M_INV(mobiusResult) << '\n';

}


int main() {

    composition();

    // constexpr std::complex<double> i = {0.0, 1.0};
    // std::array<std::complex<double>, 3> inputs{ {1.0, 0.0, i} };
    // std::array<std::complex<double>, 3> mapped_values{ {i, 1.0, std::numeric_limits<double>::infinity()} };

    // std::array<std::complex<double>, 4> coefficients = find_mobius_map_coefficients(inputs, mapped_values);

    // std::cout << "Found coefficients: a = " << coefficients[0]
    //           << ", b = " << coefficients[1]
    //           << ", c = " << coefficients[2]
    //           << ", d = " << coefficients[3] << std::endl;

    return 0;

}