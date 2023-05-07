/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file includes all the sci++ library headers files and its standard dependency. 
 * @note    It is also include 'matplotlibcpp' as plotting library
 * @date    2023-04-28
 * 
 * @copyright Copyright (c) 2023
 */


#ifndef SCIPP_LIBRARY
#define SCIPP_LIBRARY 1


    /// ===============================================================
    /// @brief std dependencies
    /// ===============================================================

        #include <algorithm>
        #include <array> /// geometry::vector, geometry::matrix
        #include <concepts> 
        #include <complex>
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
        #include <set>
        #include <string>
        #include <sstream>
        // #include <thread> // maybe not needed
        #include <variant>
        #include <vector>


        #include "external/matplotlibcpp.h"
        namespace plt = matplotlibcpp;


    /// ===============================================================
    /// @brief sci++ library headers
    /// ===============================================================

        /// ---------------------------------------------------------------
        /// @brief scipp traits
        /// ---------------------------------------------------------------

            #include "traits/math.hpp"
            #include "traits/physics.hpp"
            #include "traits/geometry.hpp"

        /// ---------------------------------------------------------------
        /// @brief math/functions
        /// ---------------------------------------------------------------

            #include "math/ops.hpp"

            #include "math/functions/function.hpp"
            #include "math/functions/add.hpp" /// ok
            #include "math/functions/subtract.hpp" /// ok
            #include "math/functions/multiply.hpp" /// @todo vector multiplication among matrix
            #include "math/functions/divide.hpp" 
            #include "math/functions/invert.hpp" /// @done
            #include "math/functions/power.hpp" /// @done
            #include "math/functions/root.hpp" 
            // #include "math/meta/compose.hpp" /// @todo 

        // /// ---------------------------------------------------------------



        // /// ---------------------------------------------------------------
        // /// @brief physics/measurements
        // /// ---------------------------------------------------------------
        
            #include "physics/measurements/base_quantity.hpp" /// @done
            #include "physics/measurements/unit.hpp" /// @ok check if necessary convert() function
        
            #include "physics/measurements/measurement.hpp"
            // #include "physics/measurements/umeasurement.hpp"
            #include "physics/measurements/cmeasurement.hpp"
        //     #include "physics/measurements/scalars.hpp"
            
            #include "physics/measurements/types/units.hpp" 
            #include "physics/measurements/types/measurements.hpp" 

        // /// ---------------------------------------------------------------
            
        //     // #include "math/numbers/dual.hpp"

        // /// ---------------------------------------------------------------

            // #include "math/constants.hpp" 
            // #include "physics/constants.hpp"

        // /// ---------------------------------------------------------------

            #include "geometry/vector.hpp"
            #include "geometry/matrix.hpp"

        // /// ---------------------------------------------------------------

            #include "physics/vector_types.hpp"
        //     // #include "physics/matrix_types.hpp" // @todo

        // /// ---------------------------------------------------------------

        // //     // #include "geometry/vectorial_space.hpp" // @todo
        //     #include "geometry/vectorial_base.hpp"
        

        // /// ---------------------------------------------------------------
        // /// @brief math/polynomials
        // /// ---------------------------------------------------------------

        //     #include "math/polynomials/ruffini.hpp"
        //     #include "math/polynomials/newton_raphson.hpp"
        //     #include "math/polynomials/roots.hpp"
        //     // #include "math/polynomials/durand_kerner.hpp"

        //     #include "math/polynomials/hermite.hpp"
        //     #include "math/polynomials/legendre.hpp"
        //     #include "math/polynomials/chebyshev.hpp"
        //     // #include "math/polynomials/laguerre.hpp"

        // /// ---------------------------------------------------------------

        // //     #include "math/autodiff.hpp"
        // //     #include "math/calculus/derivative.hpp" // @todo


        // /// ---------------------------------------------------------------
        // /// @brief math/calculus
        // /// ---------------------------------------------------------------

        //     #include "math/calculus/interval.hpp"
        //     #include "math/calculus/curve.hpp"

        //     #include "math/calculus/integrals/integrals.hpp"
        //     #include "math/calculus/integrals/gauss.hpp"  

        //     #include "math/calculus/hilbert_space.hpp"

        // /// ---------------------------------------------------------------

        // // //     // #include "math/equations.hpp"

        // /// ---------------------------------------------------------------

        //     // #include "geometry/curve_types.hpp"
        // //     // #include "geometry/line.hpp"
        // //     // #include "geometry/linspace.hpp"

        // /// ---------------------------------------------------------------

        //     #include "math/statistics.hpp"

        // /// ---------------------------------------------------------------

        // /// ---------------------------------------------------------------
        // /// @brief tools
        // /// ---------------------------------------------------------------

            #include "tools/io.hpp"
        //     #include "tools/timer.hpp"
        //     #include "tools/plot.hpp"
        //     // #include "tools/bench.hpp"


#endif