#include "sci++.hpp"


using namespace scipp; 


int main() {


    std::cout << "measurement: " << sizeof(time_m) << '\n'; 
    std::cout << "umeasurement: " << sizeof(time_um) << '\n'; 

    angle_um angle(math::constants::pi / 2, 0.001); 
    angle_um angle_2 = angle * 2.; 

    measurement alpha = angle_2.as_measurement(); 
    measurement alpha2 = 234.4 * rad;

    std::cout << alpha << '\n'; 
    std::cout << alpha2 << '\n'; 

    umeasurement appo1 = angle;
    umeasurement appo2 = math::op::sin(angle_2); 
    umeasurement appo3 = appo1; 

    std::cout << "2alpha: " << angle_2 << '\n'; 
    std::cout << "sin(2*aplha): " << appo1 << '\n'; 
    std::cout << "sin(2alpha): " << appo2 << '\n'; 

    return 0; 

}