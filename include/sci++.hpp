/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-03
 * 
 * @copyright Copyright (c) 2023
 */


// #include <external/complex>


#ifndef SCIPP_LIBRARY
#define SCIPP_LIBRARY 1


    #include <algorithm>
    // #include <concepts>
    // #include <cstdint>
    #include <chrono>
    #include <cmath>
    // #include <complex>
    #include <execution>
    #include <fstream>
    // #include <functional>
    // #include <iomanip>
    #include <iostream>
    #include <map>
    #include <numeric>
    #include <omp.h>
    #include <ratio>
    // #include <stdexcept>
    #include <string>
    #include <sstream>
    // #include <thread>
    // #include <variant>
    #include <vector>


    #include "physics/measurements/base_quantity.hpp" /// ok
    #include "math/ops/base_quantity.hpp" /// ok
    #include "physics/measurements/base_quantity_types.hpp" /// ok

    #include "physics/measurements/prefix.hpp" /// ok
    #include "math/ops/prefixes.hpp" /// ok

    #include "physics/measurements/unit.hpp" /// ok
    #include "math/ops/units.hpp" /// ok
    #include "physics/measurements/unit_types.hpp" 

    #include "physics/measurements/measurement_traits.hpp"
    #include "math/ops/generic_measurements.hpp" /// ok

    #include "physics/measurements/measurement.hpp" /// ok
    #include "math/ops/measurement.hpp" /// ok

    #include "physics/measurements/umeasurement.hpp" /// ok
    #include "math/ops/umeasurement.hpp" /// ok

    #include "physics/measurements/complex.hpp"
    #include "math/ops/complex.hpp"

    #include "physics/measurements/measurement_types.hpp" 


    #include "math/function.hpp"
    // #include "math/equations.hpp"

    #include "math/constants.hpp" 
    #include "physics/constants.hpp"

    #include "geometry/vector.hpp"
    #include "math/ops/vector.hpp"
    #include "physics/vector_types.hpp"

    #include "geometry/matrix.hpp"
    #include "math/ops/matrix.hpp"


    #include "tools/io.hpp"
    #include "tools/timer.hpp"

    #include "math/integral.hpp"    
    #include "math/statistics.hpp"

    #include "tools/bench.hpp"
    #include "tools/copy_counter.hpp"


    // #include "math/interpolation.hpp"
    #include "geometry/linspace.hpp"


    // #include "tools/plotter.hpp"
    #include <external/matplotlibcpp.h>
        namespace plt = matplotlibcpp;



    // #include "physics/mass.hpp"
    // #include "physics/gravitational_field.hpp"



    #include "math/hermite_polynomial.hpp"
    #include "math/bessel.hpp"

#endif