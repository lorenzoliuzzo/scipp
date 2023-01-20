#include "measurements.hpp"

using namespace scipp::measurements;


int main() {


    time_um t1(1.0, 0.1, s);

    time_um t2(34.32, 2.54, s);
    time_um t3(6.63 * s, 1.4 * s);

    std::cout << t1 << '\n';
    std::cout << t2 << '\n';    
    std::cout << t3 << '\n';

    t3.print();

    std::cout << t2 + t3 << '\n';


    return 0;

}