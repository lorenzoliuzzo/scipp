#include "sci++.hpp"


using namespace scipp; 
using namespace physics; 
using namespace physics::units; 


int main() {

    std::cout << "Hello World!" << '\n';

    std::cout << 3.5m * 2. << '\n';
    std::cout << 2. * 3.5m << '\n'; 

    measurement x1(434.5 * Km); 
    x1.print(); 
    x1.print_as(Km); 

    umeasurement x(13.436432 * m, 1434. * nm); 
    umeasurement y(-2.3 * m, 0.05 * m);


    std::cout << "x = " << x << '\n';
    std::cout << "y = " << y << '\n';

    std::cout << math::op::square(x1) << '\n';
    std::cout << math::op::cube(y) << '\n';

    y.print(); 


    return 0;

}
