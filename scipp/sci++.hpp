/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file includes all the sci++ library headers files and its standard dependency. 
 * @date    2023-06-12
 * 
 * @copyright Copyright (c) 2023
 */


#ifndef SCIPP_LIBRARY
#define SCIPP_LIBRARY 1


    /// ===============================================================
    /// @brief std dependencies
    /// ===============================================================

        // #include <algorithm>
        #include <array> /// geometry::vector, geometry::matrix
        #include <concepts> /// traits
        #include <chrono> /// tools::timer
        #include <cmath> /// math::functions
        #include <execution> /// math::functions, math::integrals
        #include <fstream> /// tools::io
        // #include <functional> // maybe not needed
        #include <iostream> /// tools::io
        #include <iterator>
        #include <map> /// physics::prefix_map
        // #include <numeric> // maybe not needed
        // #include <omp.h> // maybe not needed
        #include <random> /// math::statistics
        #include <ranges> /// math::integrals
        #include <ratio> /// physics::prefix, tools::io
        // #include <set>
        #include <string> /// tools::io
        #include <sstream> /// tools::io
        #include <type_traits>
        // #include <thread> // maybe not needed
        // #include <vector>


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
            
            #include "math/functions/types/unary.hpp"
            #include "math/functions/types/binary.hpp"
            #include "math/functions/types/ternary.hpp"
            #include "math/functions/types/nary.hpp"
            #include "math/functions/types/operations.hpp"
            #include "math/functions/types/operators.hpp"

            #include "math/functions/logical/equal.hpp"
            // #include "math/functions/logical/greater.hpp"
            // #include "math/functions/logical/less.hpp"

            #include "math/functions/algebraic/add.hpp" /// @ok
            #include "math/functions/algebraic/negate.hpp"

            #include "math/functions/algebraic/multiply.hpp" /// @todo umeasurements
            #include "math/functions/algebraic/invert.hpp" 

            #include "math/functions/algebraic/power.hpp" /// @ok
            #include "math/functions/algebraic/root.hpp" 

            #include "math/functions/mathematical/compose.hpp"
            #include "math/functions/mathematical/sign.hpp"
            #include "math/functions/mathematical/modulo.hpp"
            #include "math/functions/mathematical/exponential.hpp" /// @ok, @todo matrices
            #include "math/functions/mathematical/logarithm.hpp"
            #include "math/functions/mathematical/trigonometric.hpp"
            #include "math/functions/mathematical/hyperbolic.hpp"

            #include "math/functions/numerical/round.hpp"
            

        /// ---------------------------------------------------------------
        /// @brief physics/measurements
        /// ---------------------------------------------------------------
        
            #include "physics/measurements/base_quantity.hpp" 
            #include "physics/measurements/unit.hpp" 
        
            #include "physics/measurements/measurement.hpp"
            #include "physics/measurements/umeasurement.hpp"
            
            #include "physics/measurements/types/units.hpp" 
            #include "physics/measurements/types/measurements.hpp" 

            
        /// ---------------------------------------------------------------
        /// @brief math/numbers
        /// ---------------------------------------------------------------
        
            #include "math/numbers/complex.hpp" 
            #include "math/numbers/dual.hpp" 

            #include "math/numbers/constants.hpp" 
            #include "physics/constants.hpp"


        /// ---------------------------------------------------------------
        /// @brief geometry/linear_algebra
        /// ---------------------------------------------------------------

            #include "geometry/vector.hpp"
            #include "geometry/matrix.hpp"

            #include "physics/vector_types.hpp"
            // #include "physics/matrix_types.hpp" // @todo

            // #include "geometry/vectorial_base.hpp"
        

        /// ---------------------------------------------------------------
        /// @brief math/polynomials
        /// ---------------------------------------------------------------

            #include "math/polynomials/polynomial.hpp"
            #include "math/polynomials/ruffini.hpp"
            #include "math/polynomials/newton_root.hpp"
        //     #include "math/polynomials/roots.hpp"
        //     // #include "math/polynomials/durand_kerner.hpp"

        //     #include "math/polynomials/hermite.hpp"
        //     #include "math/polynomials/legendre.hpp"
        //     #include "math/polynomials/chebyshev.hpp"
        //     // #include "math/polynomials/laguerre.hpp"

        /// ---------------------------------------------------------------

        // //     #include "math/autodiff.hpp"
        // //     #include "math/calculus/derivative.hpp" // @todo


        /// ---------------------------------------------------------------
        /// @brief math/calculus
        /// ---------------------------------------------------------------

            #include "math/calculus/curves/interval.hpp"
            #include "math/calculus/curves/line.hpp"
            #include "math/calculus/curves/circumference.hpp"
            #include "math/calculus/curves/ellipse.hpp"
            #include "math/calculus/curves/sphere.hpp"

            #include "math/calculus/integrals/rectangle.hpp"
            #include "math/calculus/integrals/trapezoid.hpp"
            #include "math/calculus/integrals/midpoint.hpp"
            #include "math/calculus/integrals/endpoint.hpp"
            #include "math/calculus/integrals/simpson.hpp"
            #include "math/calculus/integrals/curvilinear.hpp"
            #include "math/calculus/integrals/gauss.hpp"  

        //     #include "math/calculus/hilbert_space.hpp"

        /// ---------------------------------------------------------------

        // // //     // #include "math/equations.hpp"

        /// ---------------------------------------------------------------

        // //     // #include "geometry/linspace.hpp"

        /// ---------------------------------------------------------------

            #include "math/statistics.hpp"

        /// ---------------------------------------------------------------

        /// ---------------------------------------------------------------
        /// @brief tools
        /// ---------------------------------------------------------------

            #include "tools/io.hpp"
            #include "tools/timer.hpp"
            #include "tools/plot.hpp"
        //     #include "tools/bench.hpp"


#endif