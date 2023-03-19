#include "sci++.hpp"


using namespace scipp; 
using namespace physics; 
using namespace physics::units; 
using namespace math;
using namespace geometry; 


int main() {


    std::cout << "Hello World!" << '\n';

    std::cout << 3.5m * 2. << '\n';
    std::cout << 2. * 3.5m << '\n'; 

    measurement x1(434.5 * km); 
    x1.print(); 
    x1.print_as(km); 

    umeasurement x(13.436432 * m, 1434. * nm); 
    umeasurement y(-2.3 * m, 0.05 * m);


    std::cout << "x = " << x << '\n';
    std::cout << "y = " << y << '\n';

    std::cout << op::square(x1) << '\n';
    std::cout << op::cube(y) << '\n';

    std::cout << op::pow<3>(x) << '\n';

    umeasurement z(3.54, 32.3, m); 

    z.print(); 


    std::cout << std::acos(0.0) << '\n'; 

    auto m1 = make_matrix(make_vector(x, y), make_vector(z, x));
    m1.print(); 

    // std::cout << op::inv(make_vector(x, y)) << '\n'; 
    // std::cout << op::pow<3>(make_vector(x, y)) << '\n'; 


    op::base_product_t<metre, metre, second, radian, kilogram> x2;
    std::cout << x2.to_string() << '\n';


    std::conditional_t<physics::are_measurements_v<umeasurement<metre>, umeasurement<second>>,
                       physics::measurement<op::base_product_t<metre, second>>, 
                       physics::umeasurement<op::base_product_t<metre, second>>> x3(3.24, 0.43);

    std::cout << x3 << '\n'; // prints 3.24 +/- 0.43

    op::measurements_multiply_t<umeasurement<metre>, umeasurement<second>> x4(3.24, 0.43);
    std::cout << x4 << '\n';
    

    static_assert(are_generic_measurements_v<measurement<metre>, umeasurement<second>>);
    static_assert(are_generic_measurements_v<measurement<metre>, measurement<second>>);
    static_assert(are_generic_measurements_v<umeasurement<metre>, umeasurement<second>>);
    static_assert(are_generic_measurements_v<umeasurement<metre>, measurement<second>>);

    // static_assert(are_measurements_v<umeasurement<metre>, umeasurement<second>>);
    // static_assert(are_measurements_v<umeasurement<metre>, measurement<second>>);


    std::cout << norm(make_vector(x, y)) << '\n';

    std::cout << position3() << '\n';
    std::cout << uposition2() << '\n';
    std::cout << uposition2().y() << '\n';

    static_assert(are_same_measurements_v<decltype(x), decltype(y), decltype(z)>);
    std::cout << uposition3(x, y, z) << '\n';    
    


    measurement appo = 3.4 * m; 
    std::cout << appo << '\n';

    std::cout << op::square(appo) << '\n';
    op::square(appo).print_as(mm * mm);


    return 0;

}
