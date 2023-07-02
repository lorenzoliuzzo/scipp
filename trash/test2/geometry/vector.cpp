/**
 * @file    vector.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-02
 * 
 * @copyright Copyright (c) 2023
 */


#include "scipp"


using namespace scipp; 
using namespace physics; 
using namespace physics::units;
using namespace geometry;
using namespace math;
using namespace tools;


int main() {


    op::measurements_prod_t<double, length_m> a; 
    print(a);

    a = 1.1m * 2.2;
    print(a);   


    position3 v_1(-1.1m); 
    print(v_1); 

    print(v_1 == v_1);

    v_1 *= 2.0;
    print(v_1);

    print(v_1 * 2); 

    auto v0 = position3(1.1m, 2.1m, 3.1m);
    print(v0);
    print(-v0);

    print(v_1 + v0);
    print(v_1 - position3(-3.m)); 

    print("Default position", position3()); 

    auto v1 = position3(1.1m, 2.1m, 3.1m);
    print(v1); 

    vector v2 = position3(1.1m, 2.1m, 3.1m);
    print(v2);

    auto v3 = make_vector(1.1m, 2.1m, 3.1m);
    print(v3);

    vector v4 = make_vector(1.1m, 2.1m, 3.1m);
    print(v4);

    auto v5 = make_vector<length_m>(1.1m, 2.1m, 3.1m);
    print(v5);

    print("sizeof a 2D vector", sizeof(position2));
    print("sizeof a 3D vector", sizeof(position3)); 


    return 0;   


}