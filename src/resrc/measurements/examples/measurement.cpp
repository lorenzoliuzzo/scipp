#include "measurements.hpp"


using namespace scipp::measurements;


int main() {

    std::cout << "Hello World!\n";

    std::cout << 3 * m + 4 * mm << '\n'; 

    std::cout << time_m(4.435644) << '\n';

    return 0; 


}