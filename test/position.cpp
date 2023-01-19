#include "sci++.hpp"

using namespace scipp;
using namespace scipp::physics;
 


int main() {

    position<3> x(3 * m, 5 * m, -32 * m); 


    std::cout << "position: " << x << '\n'; 

    return 0; 

}