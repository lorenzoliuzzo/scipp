/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-10
 * 
 * @copyright Copyright (c) 2023
 */


#ifndef SCIPP_LIBRARY


    #include <cmath>
    #include <cstdint>
    #include <chrono>
    #include <fstream>
    #include <functional>
    #include <iomanip>
    #include <iostream>
    #include <map>
    #include <numeric>
    #include <omp.h>
    #include <stdexcept>
    #include <string>
    #include <thread>
    #include <vector>


    using scalar = double;
    
    #include "math/constants.hpp" // ok

    #include "physics/measurements/units.hpp"
    #include "math/ops/units.hpp"

    #include "physics/measurements/measurement.hpp"
    #include "physics/measurements/types.hpp"

    #include "math/ops/measurement.hpp"

    #include "physics/constants.hpp"


    #include "geometry/vector.hpp"
    // #include "math/ops/vectors.hpp"
    #include "physics/vector_types.hpp"


    #include "math/integral.hpp"    
    // #include "math/statistics.hpp"


    // #include "math/equations.hpp"

    // #include "physics/mass.hpp"
    // #include "physics/gravitational_field.hpp"

    // #include "tools/plotter.hpp"
    // #include "tools/bench.hpp"


    #include "tools/timer.hpp"


#endif