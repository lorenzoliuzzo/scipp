#include "sci++.hpp"


using namespace scipp; 
using namespace physics; 
using namespace physics::units; 


int main() {

    std::cout << "Hello World!" << '\n';

    std::cout << 3.5 * m << '\n';

    measurement x1(434.5 * Km); 
    x1.print(); 
    x1.print_as(Km); 

    umeasurement x(13.5 * m, 0.2 * m); 
    umeasurement y(-2.3 * m, 0.3 * m);

    // std::cout << x.value << '\n'; 
    // std::cout << x.uncertainty << '\n'; 

    umeasurement z = x * y; 
    z.print(); 
    z.print(Km2);

    umeasurement w = x + y; 
    w.print();

    geometry::vector<decltype(x), 3> v1(x, y, w); 
    std::cout << v1[0].value << '\n'; 


    // std::cout << sizeof(x) << '\n'; 

    return 0;

}
