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
    #include <fstream>
    #include <iomanip>
    #include <iostream>
    #include <map>
    #include <numeric>
    #include <stdexcept>
    #include <string>
    #include <vector>


    using scalar = double;

    #include "math/constants.hpp"

    #include "measurements/units.hpp"

    using namespace scipp::measurements;

    #include "measurements/measurement.hpp"
    #include "math/measurement_op.hpp"

    #include "measurements/umeasurement.hpp"
    #include "math/umeasurement_op.hpp"

    #include "math/statistics.hpp"

    #include "math/vector.hpp"
    #include "physics/vector_types.hpp"

    #include "physics/constants.hpp"
    // #include "physics/mass.hpp"


    #include "tools/timer.hpp"
    #include "tools/bench.hpp"

    

#endif