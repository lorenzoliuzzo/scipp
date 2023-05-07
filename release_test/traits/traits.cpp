/**
 * @file    test/traits.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-06
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp;

int main() {


    using namespace physics;
    using namespace geometry;
    using namespace math;


    auto B1 = base_quantity<1, 0, 0, 0, 0, 0, 0>{};
    std::cout << B1.to_string() << '\n';

    auto B2 = base_quantity<0, 1, 0, 0, 0, 0, 0>{};
    std::cout << B2.to_string() << '\n';

    auto B3 = functions::invert_t<decltype(B2)>{};
    std::cout << B3.to_string() << '\n';

    auto P1 = op::inv(std::kilo{});
    static_assert(is_prefix_v<decltype(P1)>);

    std::cout << static_cast<double>(P1.num) / static_cast<double>(P1.den) << '\n';

    static_assert(is_same_prefix_v<std::milli, functions::invert_t<std::kilo>>);
    static_assert(is_same_prefix_v<std::milli, decltype(P1)>);


    static_assert(functions::is_unary_function_v<functions::invert<std::milli>>);



    return 0; 
    
}