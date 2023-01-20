#include "sci++.hpp"

using namespace scipp;
using namespace scipp::physics;
 


int main() {


    vector<basis::metre, 3> b(3 * m, 5 * m, -32 * m);
    std::cout << "vector: " << b << '\n';

    position<3> x(3 * m, 5 * m, -32 * m); 

    position3 p(3 * m, 5 * m, 34.654 * m);


    std::cout << "position: " << x << '\n'; 
    std::cout << "position3: " << p << '\n'; 
    std::cout << "delta: " << x - p << '\n'; 
    std::cout << "norm: " << norm(x + p) << '\n';


    return 0; 

}