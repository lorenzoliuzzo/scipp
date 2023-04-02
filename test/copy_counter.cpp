#include "sci++.hpp"


using namespace scipp;
using namespace tools; 


int main() {


    copy_counter<physics::length_m> a;
    copy_counter<physics::length_m> b(a);
    copy_counter<physics::length_m> c = a;
    copy_counter<physics::length_m> d;
    d = a;
   
    print("copy_count", copy_counter<physics::length_m>::copy_count); 
    print("move_count", copy_counter<physics::length_m>::move_count); 
    print("destructor_count", copy_counter<physics::length_m>::destructor_count); 
   
    copy_counter<physics::length_m>::reset();
   
    copy_counter<physics::length_m> e(std::move(a));
    copy_counter<physics::length_m> f;
    f = std::move(b);
   
    print("copy_count", copy_counter<physics::length_m>::copy_count); 
    print("move_count", copy_counter<physics::length_m>::move_count); 
    print("destructor_count", copy_counter<physics::length_m>::destructor_count); 
    
    return 0;

}
   