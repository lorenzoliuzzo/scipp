/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file includes all the sci++ library headers files and its standard dependency. 
 * @note    It is also include 'matplotlibcpp' as plotting library
 * @date    2023-04-10
 * 
 * @copyright Copyright (c) 2023
 */


#ifndef SCIPP_LIBRARY
#define SCIPP_LIBRARY 1


    /// STD dependencies
    #include <algorithm>
    #include <array>
    #include <concepts> 
    #include <chrono>
    #include <cmath>
    #include <execution>
    #include <fstream> 
    #include <functional> // maybe not needed
    #include <iostream>
    #include <map>
    #include <numeric>
    #include <ratio>
    #include <string>
    #include <sstream>
    #include <thread> // maybe not needed
    #include <vector>


    /// external dependencies
    #include <omp.h> // maybe not needed
    #include <external/matplotlibcpp.h>
        namespace plt = matplotlibcpp;


    /// sci++ library headers
    #include "scipp/physics/measurements/base_quantity.hpp" /// ok
    #include "scipp/physics/measurements/traits/base_quantity.hpp" /// ok
    #include "scipp/math/ops/base_quantity.hpp" /// ok
    #include "scipp/physics/measurements/types/base_quantity.hpp" /// ok

    #include "scipp/physics/measurements/prefix.hpp" /// ok
    #include "scipp/math/ops/prefixes.hpp" /// ok

    #include "scipp/physics/measurements/unit.hpp" /// ok
    #include "scipp/physics/measurements/traits/unit.hpp" /// ok
    #include "scipp/math/ops/units.hpp" /// ok
    #include "scipp/physics/measurements/types/unit.hpp" 

    #include "scipp/physics/measurements/traits/measurements.hpp" 
    #include "scipp/math/ops/generic_measurements.hpp" /// ok

    #include "scipp/physics/measurements/measurement.hpp" /// ok
    #include "scipp/math/ops/measurement.hpp" /// ok

    #include "scipp/physics/measurements/umeasurement.hpp" /// ok
    #include "scipp/math/ops/umeasurement.hpp" /// ok

    #include "scipp/physics/measurements/types/measurements.hpp" 

    #include "scipp/math/numbers/complex.hpp"
    #include "scipp/math/ops/complex.hpp"
    #include "scipp/math/numbers/dual.hpp"
    #include "scipp/math/ops/dual.hpp"

    #include "scipp/math/numbers/constants.hpp" 
    #include "scipp/physics/constants.hpp"

    #include "scipp/geometry/linear_algebra/vector.hpp"
    #include "scipp/math/ops/vector.hpp"
    #include "scipp/physics/vector_types.hpp"

    #include "scipp/geometry/linear_algebra/matrix.hpp"
    #include "scipp/math/ops/matrix.hpp"
    #include "scipp/geometry/linear_algebra/vectorial_base.hpp"

    // #include "scipp/math/complex_as_mat2.hpp"
    
    #include "scipp/math/calculus/function.hpp"
    #include "scipp/math/calculus/function_traits.hpp"
    #include "scipp/math/functions/mathematical.hpp"

    #include "scipp/math/node.hpp"
    
    #include "scipp/math/calculus/derivative.hpp" // @todo
    // #include "scipp/math/interpolation.hpp" // @todo

    #include "scipp/math/calculus/interval.hpp"
    
    #include "scipp/math/calculus/curve.hpp"
    #include "scipp/geometry/curve_types.hpp"

    #include "scipp/geometry/line.hpp"
    // #include "scipp/geometry/linspace.hpp"
    // #include "scipp/math/equations.hpp"

    #include "scipp/math/calculus/integrals.hpp"    

    #include "scipp/math/polynomials/hermite.hpp"
    // #include "scipp/math/functions/bessel.hpp" // @todo
    // #include "scipp/math/polynomials/lagrange.hpp" // @todo
    // #include "scipp/math/polynomials/legendre.hpp" // @todo


    #include "scipp/math/statistics.hpp"

    #include "scipp/tools/io.hpp"
    #include "scipp/tools/timer.hpp"
    #include "scipp/tools/bench.hpp"
    // #include "scipp/tools/copy_counter.hpp"


    // #include "scipp/physics/mass.hpp"
    // #include "scipp/physics/gravitational_field.hpp"


#endif