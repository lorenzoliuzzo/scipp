#include "benchmark/cppbenchmark.h"

#include "measurements.hpp"


using namespace scipp::measurements; 


BENCHMARK("measurement multiplication", const measurement<basis::metre>& a, const measurement<basis::kilogram>& b)
{
    a * b; 
}

BENCHMARK_MAIN()