/**
 * @file position.cpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief Test file for position.hpp
 * @date 2022-12-19
 * 
 * @copyright Copyright (c) 2023
 */


#include "physics.hpp"

using namespace physics;


int main() {


    position<3> p1(vector3(-5 * m, 0 * m, 0 * m));

    position<3> p2(1.0 * m, 2.5 * m, 3.0 * m);

    position p3(1.0 * m, -2.0 * m, 3.0 * m);

    p1.print(); 

    p2.print();

    p3.print();


    std::cout << (p1 + p2 + p3) / 3. << '\n';
    std::cout << p1.distance(p2) << '\n'; 

    auto dist = (p1 + p2 + p3) / 3.;
    dist.print(); 


    reference_system<3> RS(position(0 * m, 0 * m, 0 * m));

    RS.add({p1, p2, p3});

    for (auto i : RS)
        i.print();

    RS.balance(); 
    std::cout << RS.center() << '\n';


    return 0; 

}