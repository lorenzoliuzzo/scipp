#include "sci++.hpp"


using namespace scipp; 
using namespace physics; 
using namespace physics::units; 


int main() {

    std::cout << "Hello World!" << '\n';

    std::cout << 3.5 / m << '\n';

    measurement x1(434.5 * Km); 
    x1.print(); 
    x1.print_as(Km); 

    umeasurement x(13.5 * m, 0.2 * m); 
    umeasurement y(-2.3 * m, 0.3 * m);


    math::op::square(x1).print();
    math::op::square(y).print();

    y.print(); 


    return 0;

}
