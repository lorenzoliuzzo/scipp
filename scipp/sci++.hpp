/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file includes all the sci++ library headers files and its standard dependency. 
 * @note    It is also include 'matplotlibcpp' as plotting library
 * @date    2023-04-24
 * 
 * @copyright Copyright (c) 2023
 */


#ifndef SCIPP_LIBRARY
#define SCIPP_LIBRARY 1


    /// ===============================================================
    /// std dependencies
    /// ===============================================================

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
        // #include <omp.h> // maybe not needed
        #include <ratio>
        #include <string>
        #include <sstream>
        // #include <thread> // maybe not needed
        #include <vector>


    /// ===============================================================
    /// sci++ library headers
    /// ===============================================================

    /// ---------------------------------------------------------------

        #include "traits/physics.hpp"
        #include "traits/math.hpp"
        
        #include "math/ops/types.hpp"
        
    /// ---------------------------------------------------------------

        #include "physics/measurements/base_quantity.hpp" 
        #include "math/ops/base_quantity.hpp" 

        #include "physics/measurements/prefix.hpp"
        #include "math/ops/prefix.hpp" 

        #include "physics/measurements/unit.hpp" 
        #include "math/ops/unit.hpp" 

    /// ---------------------------------------------------------------


    /// ---------------------------------------------------------------
        
        #include "physics/measurements/types/units.hpp" 

    /// ---------------------------------------------------------------

        #include "physics/measurements/measurement.hpp"
        #include "math/ops/measurement.hpp"

    /// ---------------------------------------------------------------

        #include "physics/measurements/umeasurement.hpp"

    /// ---------------------------------------------------------------
        
        #include "physics/measurements/types/measurements.hpp" 

    /// ---------------------------------------------------------------
        
        #include "math/numbers/complex.hpp"
        #include "math/ops/complex.hpp"

    /// ---------------------------------------------------------------
       
    //     #include "math/ops/umeasurement.hpp"
        
    /// ---------------------------------------------------------------

        #include "math/numbers/dual.hpp"

    /// ---------------------------------------------------------------

        // #include "math/ops/dual.hpp"

    /// ---------------------------------------------------------------
       
        #include "math/ops/generic_measurements.hpp"

    /// ---------------------------------------------------------------

        #include "math/numbers/constants.hpp" 
        #include "physics/constants.hpp"

    /// ---------------------------------------------------------------

        #include "geometry/vector.hpp"
        #include "math/ops/vector.hpp"
        #include "physics/vector_types.hpp"

    /// ---------------------------------------------------------------

        #include "geometry/matrix.hpp"
        #include "math/ops/matrix.hpp"

    //     // #include "physics/matrix_types.hpp" // @todo

    /// ---------------------------------------------------------------

    //     // #include "geometry/vectorial_space.hpp" // @todo
        #include "geometry/vectorial_base.hpp"
    
    /// ---------------------------------------------------------------

        #include "tools/io.hpp"

    /// ---------------------------------------------------------------

        #include "math/calculus/function.hpp"
        #include "math/calculus/function_traits.hpp"
        #include "math/functions/mathematical.hpp"

    /// ---------------------------------------------------------------

        #include "math/autodiff.hpp"
        #include "math/calculus/derivative.hpp" // @todo

    /// ---------------------------------------------------------------

        #include "math/calculus/interval.hpp"
        #include "math/calculus/curve.hpp"

    /// ---------------------------------------------------------------

        #include "math/calculus/integrals.hpp"  

    /// ---------------------------------------------------------------

    //     // #include "math/equations.hpp"

    /// ---------------------------------------------------------------

        #include "geometry/curve_types.hpp"
        // #include "geometry/line.hpp"
        // #include "geometry/linspace.hpp"

    /// ---------------------------------------------------------------

        #include "math/statistics.hpp"

    /// ---------------------------------------------------------------

    //     #include "math/polynomial/hermite.hpp"

    /// ---------------------------------------------------------------

        #include "tools/timer.hpp"
        #include "tools/bench.hpp"

#endif