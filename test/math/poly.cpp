/**
 * @file    test/math/poly.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-04
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"

using namespace scipp;

using namespace tools; 
using namespace math;
using namespace physics;
using namespace physics::units;
using namespace geometry;


int main() {

    std::vector<complex<double>> v = {4.0, 0.0, 1.0};
    auto roots = find_roots<2>(v);
    for (auto& root : roots) {
        print(root);
    }

    return 0; 

}