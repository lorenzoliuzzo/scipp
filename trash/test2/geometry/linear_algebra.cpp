/**
 * @file    test/linear_algebra.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */


#include "scipp"
#include <cassert>


using namespace scipp; 
using namespace geometry; 
using namespace physics; 
using namespace physics::units; 
using namespace math; 
using namespace tools;


int main() {


    auto mat = make_matrix<position3, 3>(position3(2.0m, 0.0m, 0.0m), position3(0.0m, 1.0m, 0.0m), position3(0.0m, 0.0m, 1.0m));

    print("id3", matrix<position3, 3>::identity());
    print("mat", mat); 
    print("det", mat.determinant());

    vectorial_base base(mat); 
    print("base", base.data);
    // assert(base.is_normalized());


    // auto ld_mat = make_matrix<position3, 3>(position3(0.0m, 2.0m, 0.0m), position3(0.0m, 1.0m, 0.0m), position3(0.0m, 0.0m, 1.0m));
    // vectorial_base base2(ld_mat); 
    // print("base", base2.data);


    auto x = base.from_base(position3(3.0m, 4.0m, 5.5m));
    print("x", x);

    auto y = base.to_base(x);
    print("y", y);


    return 0;

}