#include "measurements.hpp"


using namespace scipp::measurements; 



int main() {


    std::cout << "double: " << sizeof(double) << '\n';
    std::cout << "unit_base: " << sizeof(unit_base) << '\n'; 
    std::cout << "unit_prefix: " << sizeof(unit_prefix) << '\n'; 
    std::cout << "unit: " << sizeof(unit) << '\n'; 
    // std::cout << "measurement: " << sizeof(measurement) << '\n'; 
    std::cout << "time_meas: " << sizeof(time_m) << '\n'; 

    measurement<basis::metre> l1(3, m);

    time_m t1(3, km); 


    
    return 0; 

}