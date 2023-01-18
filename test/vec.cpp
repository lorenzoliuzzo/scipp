#include "sci++.hpp"

using namespace scipp; 


int main() {

    geometry::linear_algebra::vector<basis::metre, 3> vec(3 * m, 4 * km, 5 * cm); 

    vec.print(); 

    return 0; 

}