/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file includes all the sci++ library headers files and its standard dependency. 
 * @note    It is also included 'matplotlibcpp' as plotting library and defined the plt:: namespace
 * @date    2023-04-09
 * 
 * @copyright Copyright (c) 2023
 */


#ifndef SCIPP_LIBRARY
#define SCIPP_LIBRARY 1


    #include <algorithm>
    // #include <concepts>
    #include <chrono>
    #include <cmath>
    #include <execution>
    #include <fstream>
    // #include <functional>
    #include <iostream>
    #include <map>
    #include <numeric>
    #include <omp.h>
    #include <ratio>
    #include <string>
    #include <sstream>
    // #include <thread>
    #include <vector>


    #include <external/matplotlibcpp.h>
        namespace plt = matplotlibcpp;


    #include "scipp/physics/measurements/base_quantity.hpp" /// ok
    #include "scipp/math/ops/base_quantity.hpp" /// ok
    #include "scipp/physics/measurements/base_quantity_types.hpp" /// ok

    #include "scipp/physics/measurements/prefix.hpp" /// ok
    #include "scipp/math/ops/prefixes.hpp" /// ok

    #include "scipp/physics/measurements/unit.hpp" /// ok
    #include "scipp/math/ops/units.hpp" /// ok
    #include "scipp/physics/measurements/unit_types.hpp" 

    #include "scipp/physics/measurements/measurement_traits.hpp"
    #include "scipp/math/ops/generic_measurements.hpp" /// ok

    #include "scipp/physics/measurements/measurement.hpp" /// ok
    #include "scipp/math/ops/measurement.hpp" /// ok

    #include "scipp/physics/measurements/umeasurement.hpp" /// ok
    #include "scipp/math/ops/umeasurement.hpp" /// ok

    #include "scipp/physics/measurements/measurement_types.hpp" 

    #include "scipp/math/complex.hpp"
    #include "scipp/math/ops/complex.hpp"

    #include "scipp/math/constants.hpp" 
    #include "scipp/physics/constants.hpp"

    #include "scipp/geometry/linear_algebra/vector.hpp"
    #include "scipp/math/ops/vector.hpp"
    #include "scipp/physics/vector_types.hpp"

    #include "scipp/geometry/linear_algebra/matrix.hpp"
    #include "scipp/math/ops/matrix.hpp"

    // #include "scipp/math/complex_as_mat2.hpp"
    
    #include "scipp/math/functions/function.hpp"
    #include "scipp/math/functions/function_traits.hpp"
    #include "scipp/math/functions/mathematical.hpp"
    #include "scipp/math/functions/derivative.hpp" // @todo

    #include "scipp/math/interval.hpp"
    
    #include "scipp/geometry/curve.hpp"
    #include "scipp/geometry/curve_types.hpp"

    #include "scipp/geometry/line.hpp"
    // #include "scipp/geometry/linspace.hpp"
    // #include "scipp/math/equations.hpp"

    #include "scipp/math/polynomial/hermite.hpp"
    #include "scipp/math/polynomial/lagrange.hpp"
    // #include "scipp/math/polynomial/legendre.hpp" // @todo

    #include "scipp/math/integrals.hpp"    

    #include "scipp/math/statistics.hpp"

    #include "scipp/tools/io.hpp"
    #include "scipp/tools/timer.hpp"
    #include "scipp/tools/bench.hpp"
    // #include "scipp/tools/copy_counter.hpp"

    // #include "scipp/math/interpolation.hpp"

    // #include "scipp/physics/mass.hpp"
    // #include "scipp/physics/gravitational_field.hpp"

    // #include "scipp/math/bessel.hpp"

#endif