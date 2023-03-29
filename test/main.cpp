#include "sci++.hpp"


using namespace scipp; 
using namespace physics; 
using namespace physics::units; 
using namespace math;
using namespace geometry; 


int main() {


    std::cout << "Hello World!" << '\n';

    std::cout << 3.5m * 2. << '\n';
    std::cout << 2. * 3.5m << '\n'; 

    measurement x1(434.5 * km); 
    x1.print(); 
    x1.print_as(km); 

    umeasurement x(13.436432 * m, 1434. * nm); 
    umeasurement y(-2.3 * m, 0.05 * m);


    std::cout << "x = " << x << '\n';
    std::cout << "y = " << y << '\n';

    std::cout << op::square(x1) << '\n';
    std::cout << op::cube(y) << '\n';

    std::cout << op::pow<3>(x) << '\n';

    umeasurement z(3.54, 32.3, m); 

    z.print(); 


    std::cout << std::acos(0.0) << '\n'; 


    return 0;

}
