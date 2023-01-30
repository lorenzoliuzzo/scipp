/**
 * @file    sci++.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-01-20
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
    #include <vector>


    using scalar = double;
    
    #include "math/constants.hpp"

    #include "measurements/unit_base.hpp"    
    #include "math/op/unit_base_op.hpp"
    #include "measurements/unit.hpp"
    #include "math/op/unit_op.hpp"
    #include "measurements/units_types.hpp"

    #include "measurements/measurement.hpp"
    #include "math/op/measurement_op.hpp"
    #include "measurements/umeasurement.hpp"
    #include "math/op/umeasurement_op.hpp"

    #include "measurements/measurements_types.hpp"

    #include "meta_measurements/base.hpp"
    #include "meta_measurements/prefix.hpp"
    #include "meta_measurements/unit.hpp"
    

    #include "geometry/vector.hpp"
    #include "math/op/vector_op.hpp"

    #include "physics/vector_types.hpp"
    #include "physics/constants.hpp"

    #include "math/statistics.hpp"

    #include "math/equations.hpp"
    #include "math/integral.hpp"

    #include "physics/mass.hpp"
    #include "physics/gravitational_field.hpp"


    #include "tools/timer.hpp"
    #include "tools/bench.hpp"
    // #include "tools/plotter.hpp"
    

#endif