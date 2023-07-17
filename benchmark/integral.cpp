#include <benchmark/benchmark.h>
#include "scipp"

using namespace scipp;
using namespace scipp::physics; 
using namespace scipp::math;
using namespace scipp::math::calculus;
using tools::print; 


 main() {

    variable<measurement<base::length>> x = 2.0 * units::m;

    variable<measurement<base::length>> y = -3.0 * x; 

    variable<measurement<base::area>> z = x * x; 
    

    auto dy_dx = derivatives(y, wrt(x)); 
    auto [dz_dx, dz_dy, dz_dz] = derivatives(z, wrt(x, y, z));