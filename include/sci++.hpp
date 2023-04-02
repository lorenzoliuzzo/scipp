/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-02
 * 
 * @copyright Copyright (c) 2023
 */


#ifndef SCIPP_LIBRARY


    #include <algorithm>
    #include <cmath>
    // #include <concepts>
    // #include <cstdint>
    // #include <complex>
    #include <chrono>
    #include <execution>
    #include <fstream>
    // #include <functional>
    // #include <iomanip>
    #include <iostream>
    #include <map>
    #include <numeric>
    // #include <omp.h>namespace plt = matplotlibcpp; 

    #include <ratio>
    // #include <stdexcept>
    #include <string>
    #include <sstream>
    // #include <thread>
    // #include <variant>
    #include <vector>


    #include <external/matplotlibcpp.h>
        namespace plt = matplotlibcpp; 


    #include "physics/measurements/base_quantity.hpp" /// ok
    #include "math/ops/base_quantities.hpp" /// ok

    #include "physics/measurements/prefix.hpp" /// ok
    #include "math/ops/prefixes.hpp" /// ok

    #include "physics/measurements/unit.hpp" /// ok
    #include "math/ops/units.hpp" /// ok
    #include "physics/measurements/unit_types.hpp" 

    #include "physics/measurements/measurement.hpp" /// ok
    #include "physics/measurements/umeasurement.hpp" /// ok
    #include "physics/measurements/measurement_types.hpp" 
    #include "math/ops/measurements.hpp" /// ok

    #include "math/constants.hpp" 
    #include "physics/constants.hpp"

    #include "geometry/vector.hpp"
    #include "math/ops/vectors.hpp"
    #include "physics/vector_types.hpp"

    #include "geometry/matrix.hpp"
    #include "math/ops/matrices.hpp"


    // #include "physics/measurements/complex_measurement.hpp"

    #include "math/integral.hpp"    

    #include "math/statistics.hpp"
    // #include "math/interpolation.hpp"
    #include "geometry/linspace.hpp"

    // #include "math/equations.hpp"

    // #include "physics/mass.hpp"
    // #include "physics/gravitational_field.hpp"

    // #include "tools/plotter.hpp"
    // #include "tools/bench.hpp"

    #include "tools/io.hpp"
    #include "tools/timer.hpp"
    #include "tools/copy_counter.hpp"

    #include "math/hermite_polynomial.hpp"


#endif