#include "measurements.hpp"


using namespace scipp::measurements; 


int main() {


    time_m t1(3.676876, ms);

    length_m l1(145653.5, mm); 
    l1.print(); 

    auto v1 = l1 / t1; 
    v1.print(); 

    v1.convert_to(m /s).print(); 
    (l1.convert_to(m) / t1.convert_to(s)).print(); 

    
    return 0; 

}