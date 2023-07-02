/**
 * @file    test/traits.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-06
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"


using namespace scipp;
using namespace tools; 
using namespace physics;
using namespace geometry;
using namespace math;


int main() {

    auto p1 = position3(1.0m, 2.0m, 3.0m);
    auto p2 = vector<complex<length_m>, 3, false>(complex<length_m>(1.0m, -1.0m), complex<length_m>(2.0m), complex<length_m>(3.0m));
    auto p3 = row_vector<time_m, 3>(1.0 * units::s, 2.0 * units::s, 3.0 * units::s);

    static_assert(are_same_vectors_v<decltype(p1), position3>);
    static_assert(are_same_base_v<decltype(p2)::base_t, position3::base_t>);
    static_assert(is_vector_v<decltype(p2)>); 

    static_assert(is_column_vector_v<decltype(p1)>);
    static_assert(is_row_vector_v<decltype(p3)>);
    // auto f = functions::multiply<decltype(p1), decltype(p2)>{};

    print(p1); 
    print(p2);
    print(op::mult(p1, p3));
    print(op::mult(p3, p1));
    print(p1 * 1.0m); 

    print(p1 + p1);
    print(p1 + p2);

    


    return 0;

}


