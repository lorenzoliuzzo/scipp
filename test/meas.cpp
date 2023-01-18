#include "sci++.hpp"


using namespace scipp; 


int main() {


    std::cout << "measurement: " << sizeof(time_m) << '\n'; 
    std::cout << "umeasurement: " << sizeof(time_um) << '\n'; 

    angle_um angle(math::constants::pi / 2, 0.001); 
    angle_um angle_2 = angle * 2.; 

    umeasurement appo1 = math::op::sin(angle * 2.);
    umeasurement appo2 = math::op::sin(angle_2); 

    std::cout << "2alpha: " << angle_2 << '\n'; 
    std::cout << "sin(2*aplha): " << appo1 << '\n'; 
    std::cout << "sin(2alpha): " << appo2 << '\n'; 

    return 0; 

}