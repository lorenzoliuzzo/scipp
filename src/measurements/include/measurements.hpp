/**
 * @file    measurements.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains all the headers of the measurements library
 * @date    2023-01-18
 * 
 * @copyright Copyright (c) 2023
 */


#define SCIPP_MEASUREMENTS_HPP

    
    using scalar = double;


    #include <cmath>
    #include <cstdint>
    #include <fstream>
    #include <iomanip>
    #include <iostream>
    #include <map>
    #include <stdexcept>
    #include <string>
    #include <vector>


    #include "units.hpp"
    #include "measurement.hpp"
    #include "umeasurement.hpp"
    // #include "utilities".hpp"