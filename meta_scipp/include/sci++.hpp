/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-31
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
    
    #include "math/constants.hpp"

    #include "physics/units/base.hpp" 
    #include "math/ops/unit_base.hpp"

    #include "physics/units/prefix.hpp"
    #include "math/ops/prefix.hpp"

    #include "physics/units/unit.hpp"
    #include "math/ops/unit.hpp"
    #include "physics/units/types.hpp"

    #include "physics/measurement.hpp"
    #include "math/ops/measurement.hpp"
    #include "physics/measurements_types.hpp"

    #include "math/integral.hpp"



    // #include "math/op/measurement_op.hpp"
    // #include "measurements/umeasurement.hpp"
    // #include "math/op/umeasurement_op.hpp"

    // #include "measurements/measurements_types.hpp"

    // #include "meta_measurements/base.hpp"
    // #include "meta_measurements/prefix.hpp"
    // #include "meta_measurements/unit.hpp"
    // #include "meta_measurements/measurement.hpp"
    // #include "meta_measurements/types.hpp"
    

    // #include "geometry/vector.hpp"
    // #include "math/op/vector_op.hpp"

    // #include "physics/vector_types.hpp"
    // #include "physics/constants.hpp"

    // #include "math/statistics.hpp"

    // #include "math/equations.hpp"
    // #include "math/integral.hpp"

    // #include "physics/mass.hpp"
    // #include "physics/gravitational_field.hpp"

    // #include "tools/plotter.hpp"
    // #include "tools/bench.hpp"


    #include "tools/timer.hpp"


#endif