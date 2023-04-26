/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file includes all the sci++ library headers files and its standard dependency. 
 * @note    It is also include 'matplotlibcpp' as plotting library
 * @date    2023-04-26
 * 
 * @copyright Copyright (c) 2023
 */


#ifndef SCIPP_LIBRARY
#define SCIPP_LIBRARY 1


    /// ===============================================================
    /// std dependencies
    /// ===============================================================

        #include <algorithm>
        #include <array> /// geometry::vector, geometry::matrix
        #include <concepts> 
        #include <chrono> /// tools::timer
        #include <cmath>
        #include <execution>
        #include <fstream> 
        // #include <functional> // maybe not needed
        #include <iostream> /// tools::io
        #include <map> /// physics::prefix_map
        // #include <numeric> // maybe not needed
        // #include <omp.h> // maybe not needed
        #include <ratio> /// physics::prefix
        #include <string>
        #include <sstream>
        // #include <thread> // maybe not needed
        #include <vector>


    /// ===============================================================
    /// sci++ library headers
    /// ===============================================================

        #include "physics/traits.hpp"
        #include "geometry/traits.hpp"
        #include "math/traits.hpp"

    /// ---------------------------------------------------------------

        #include "math/meta/function.hpp"
        #include "math/meta/mathematical.hpp"

    /// ---------------------------------------------------------------

        #include "math/ops.hpp"

    /// ---------------------------------------------------------------

        #include "physics/measurements/base_quantity.hpp" 
        #include "physics/measurements/unit.hpp" 

    /// ---------------------------------------------------------------
       
        #include "physics/measurements/measurement.hpp"
        // #include "physics/measurements/umeasurement.hpp"
        #include "physics/measurements/cmeasurement.hpp"
        #include "physics/measurements/scalars.hpp"

    /// ---------------------------------------------------------------
        
        #include "physics/measurements/types/units.hpp" 
        #include "physics/measurements/types/measurements.hpp" 

    /// ---------------------------------------------------------------
        
        // #include "math/numbers/dual.hpp"

    /// ---------------------------------------------------------------

        #include "math/constants.hpp" 
        #include "physics/constants.hpp"

    /// ---------------------------------------------------------------

        #include "geometry/vector.hpp"
        #include "geometry/matrix.hpp"

    /// ---------------------------------------------------------------

        #include "physics/vector_types.hpp"
        // #include "physics/matrix_types.hpp" // @todo

    /// ---------------------------------------------------------------

    //     // #include "geometry/vectorial_space.hpp" // @todo
        #include "geometry/vectorial_base.hpp"
    
    /// ---------------------------------------------------------------

    //     #include "math/autodiff.hpp"
    //     #include "math/calculus/derivative.hpp" // @todo

    /// ---------------------------------------------------------------

        #include "math/calculus/interval.hpp"
        #include "math/calculus/curve.hpp"

    /// ---------------------------------------------------------------

        #include "math/calculus/integrals.hpp"  

    /// ---------------------------------------------------------------

    // //     // #include "math/equations.hpp"

    /// ---------------------------------------------------------------

        #include "geometry/curve_types.hpp"
    //     // #include "geometry/line.hpp"
    //     // #include "geometry/linspace.hpp"

    /// ---------------------------------------------------------------

        #include "math/statistics.hpp"

    /// ---------------------------------------------------------------

    // //     #include "math/polynomial/hermite.hpp"

    /// ---------------------------------------------------------------

        #include "tools/io.hpp"
        #include "tools/timer.hpp"
        // #include "tools/bench.hpp"

#endif