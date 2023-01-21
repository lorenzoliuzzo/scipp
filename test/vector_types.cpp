#include "sci++.hpp"

using namespace scipp;
using namespace scipp::physics;
 


int main() {


    geometry::vector<basis::metre, 3> b(3 * m, 5 * m, -32 * m);
    std::cout << "vector: " << b << '\n';

    position<3> x(1 * m, 0 * m, 1 * m); 

    position3 y(0 * m, 1 * m, 1 * m);

    std::cout << "position: " << x << '\n'; 
    std::cout << "position3: " << y << '\n'; 
    std::cout << "delta: " << x - y << '\n'; 

    std::cout << "norm: " << norm(x + y) << '\n';
    std::cout << "dot: " << math::op::dot(x, y) << '\n';
    std::cout << "cross: " << math::op::cross(x, y) << '\n';


    return 0; 

}