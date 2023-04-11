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


    /// std dependencies
    #include <algorithm>
    #include <array>
    #include <concepts> 
    #include <chrono>
    #include <cmath>
    #include <execution>
    #include <fstream> 
    // #include <functional> // maybe not needed
    #include <iostream>
    #include <map> // maybe not needed
    // #include <numeric> // maybe not needed
    #include <omp.h> // maybe not needed
    #include <ratio>
    #include <string>
    #include <sstream>
    // #include <thread> // maybe not needed
    #include <vector>


    /// sci++ library headers
    #include "physics/measurements/base_quantity.hpp" /// ok
    #include "physics/measurements/traits/base_quantity.hpp" /// ok
    #include "math/ops/base_quantity.hpp" /// ok
    #include "physics/measurements/types/base_quantity.hpp" /// ok

    #include "physics/measurements/prefix.hpp" /// ok
    #include "math/ops/prefixes.hpp" /// ok

    #include "physics/measurements/unit.hpp" /// ok
    #include "physics/measurements/traits/unit.hpp" /// ok
    #include "math/ops/units.hpp" /// ok
    #include "physics/measurements/types/unit.hpp" 

    #include "physics/measurements/traits/measurements.hpp" 
    #include "math/ops/generic_measurements.hpp" /// ok

    #include "physics/measurements/measurement.hpp" /// ok
    #include "math/ops/measurement.hpp" /// ok

    #include "physics/measurements/umeasurement.hpp" /// ok
    #include "math/ops/umeasurement.hpp" /// ok

    #include "physics/measurements/types/measurements.hpp" 

    #include "math/numbers/complex.hpp"
    #include "math/numbers/dual.hpp"
    
    // #include "math/ops/complex.hpp"
    #include "math/ops/dual.hpp"

    #include "math/numbers/constants.hpp" 
    #include "physics/constants.hpp"

    #include "geometry/linear_algebra/vector.hpp"
    #include "math/ops/vector.hpp"
    #include "physics/vector_types.hpp"

    #include "geometry/linear_algebra/matrix.hpp"
    #include "math/ops/matrix.hpp"
    // #include "physics/matrix_types.hpp" // @todo

    // #include "geometry/linear_algebra/vectorial_space.hpp" // @todo
    #include "geometry/linear_algebra/vectorial_base.hpp"
    
    #include "math/calculus/function.hpp"
    #include "math/calculus/function_traits.hpp"
    #include "math/functions/mathematical.hpp"
    
    #include "math/calculus/derivative.hpp" // @todo

    #include "math/calculus/interval.hpp"
    
    #include "math/calculus/curve.hpp"
    #include "geometry/curve_types.hpp"

    #include "geometry/line.hpp"
    // #include "geometry/linspace.hpp"
    // #include "math/equations.hpp"

    #include "math/calculus/integrals.hpp"    

    #include "math/polynomial/hermite.hpp"


    #include "math/statistics.hpp"

    #include "tools/io.hpp"
    #include "tools/timer.hpp"
    #include "tools/bench.hpp"


#endif


    /// external dependencies
    // #include <external/matplotlibcpp.h>
    //     namespace plt = matplotlibcpp;