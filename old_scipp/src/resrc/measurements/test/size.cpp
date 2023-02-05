#include "measurements.hpp"

using namespace scipp::measurements;


int main() {

    std::cout << "measurement: " << sizeof(time_m) << '\n'; 

    measurement t3 = 30 * m; 

    (3 * mm).print();
    (3 * ms).print(s);

    std::cout << "Echo: ";
    (30000 * m).print(mm);
    (30000 * m).print(km);
    auto z = 3e6 * mm - 3 * km; 
    z.print(); 

    // auto x = (3000 * m).convert_to(km);
    // x.print(); 

    return 0; 

}

int main2() {

    std::cout << "unit_base: " << sizeof(unit_base) << '\n';     
    std::cout << "unit: " << sizeof(unit<basis::metre>) << '\n';     

    std::cout << "prefix: " << sizeof(prefixes::micro) << '\n'; 
    std::cout << "measurement: " << sizeof(time_m) << '\n'; 

    unit<basis::metre * basis::second> b = m * s; 
    b.print(); 
    std::cout << '\n'; 

    mm.print();
    std::cout << '\n'; 

    time_m t1(4.7654, ps);
    time_m t2(1., ms);
    t1.print(ps); 

    measurement l(25.54, m); 
    std::cout << l << '\n';


    std::cout << t1 * t2 << '\n'; 

    std::cout << 3.567 * m << '\n';


    // measurements2::unit<basis::metre> nm_2(1.e-9);
    // measurements2::measurement<basis::metre> l2(3.86, nm_2);
    // measurements2::measurement<basis::metre> l3(3.5, nm_2);

    // std::cout << "l2: " << l2 << '\n';
    // std::cout << "l3: " << l3 << '\n';
    // std::cout << l2 + l3 << '\n';

    return 0;

}