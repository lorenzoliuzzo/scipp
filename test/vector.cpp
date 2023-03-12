/**
 * @file    vector.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-05
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp; 
using namespace physics; 
using namespace math; 
using namespace geometry;


int main() {


    base_quantity<0, 1, 0, 0, 0, 0, 0, 0> time_;
    base_quantity<1, 0, 0, 0, 0, 0, 0, 0> length_;

    std::cout << length_.to_string() << '\n';
    std::cout << time_.to_string() << '\n';

    base_quantity<1, -1, 0, 0, 0, 0, 0, 0> speed_;
    std::cout << speed_.to_string() << '\n';

    static_assert(is_same_base_v<base_quantity<1, -1, 0, 0, 0, 0, 0, 0>, base_division_t<decltype(length_), decltype(time_)>>);
    static_assert(has_valid_root_v<base_quantity<2, -4, 0, 0, 0, 0, 0, 0>, 2>);


    // vector<physics::units::metre, 3> v1(1.0m, 0.0m, 0.0m);
    // position3 v2(0.0m, 1.0m, 0.0m);


    // std::cout << op::angle(v1, v2) << '\n';
    // std::cout << op::cross(v1, v2) << '\n';

    // std::cout << op::square(v2) << '\n';

    // v1 += v2;

    // std::cout << v1 << '\n';
    // std::cout << op::normalize(v2) << '\n';
    // std::cout << op::dot(v1, v2) << '\n';
    // std::cout << op::dot(v2, v2) << '\n';
    // std::cout << op::norm(v2) << '\n'; 



    // vector2 v3 = make_vector2<2, length_m>(1.0m, 0.0m);
    // vector2 v4(0.0m, 1.0m);

    // vector2 v5(1.0m, 1.0 * units::s);

    // v3.print(); 
    // v4.print();
    // v5.print();

    // // v4 += v3;
    // // v4.print();

    // v5.get<0>() = 2.0m;
    // v5.get<1>() = 2.0 * units::s;

    // v5.get<0>() = 3;


    // (v5.get<0>() + 3.4m).print(); 
    // v5.print();

    // v5.x().print();
    // v5.y().print();

    // std::cout << sizeof(v5) << '\n';
    // std::cout << sizeof(v5.x()) << '\n';

    // static_assert(have_same_base_v<decltype(v5.y()), time_m>);
    // static_assert(are_measurements_v<time_m>); 
    // static_assert(are_measurements_v<length_m, time_m>); 

    // static_assert(is_omogeneous_v<decltype(v4)>);
    // static_assert(!is_omogeneous_v<decltype(v5)>);

    // vector2 v6(std::array<length_m, 2>{1.0m, 2.0m});
    // v6.print();

    tools::omp_timer timer; 
    // timer.start();
    // timer.stop();
    // std::cout << timer.elapsed() << '\n';


    // timer.start();
    vector2 v6(1.0m, 0.0m);
    vector2 v7(1.0m, -3.40m);
    v6 += v7;
    v6.print();
    // timer.stop();

    // std::cout << timer.elapsed() << '\n';

    // timer.start();
    vector<units::metre, 2> p1(1.0m, 0.0m);
    vector<units::metre, 2> p2(1.0m, -3.40m);
    p1 += p2;
    p1.print();
    // timer.stop();

    // std::cout << timer.elapsed() << '\n';


    std::cout << v6 + v7 << '\n'; 


    vector2<2, length_m, time_m> v8(1.35m, 1. * units::s);
    // std::cout << v8 * 3.246m << '\n';

    
    // std::cout << v8 * 3.53m << '\n';

    // static_assert(physics::measurement_prod_t<length_m, time_m>::base == physics::units::base_product_t<length_m::base, time_m::base>);

    return 0;   


}