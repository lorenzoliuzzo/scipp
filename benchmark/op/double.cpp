/**
 * @file    benchmark/double.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the benchmarking of the scipp::math::op function on the double type.
 *          The benchmarking is done with the Google Benchmark library.
 *          Testing op::add, op::multiply, op::invert, op::square
 * @date    2023-07-17
 *
 * @copyright Copyright (c) 2023
 */


#include <benchmark/benchmark.h>
#include "scipp"

using namespace scipp;
using namespace physics;
using namespace math;

// Define input data for the benchmarks
constexpr double a = 5.0;
constexpr double b = 10.0;

// Benchmark functions
static void BM_Add(benchmark::State& state) {
    for (auto _ : state) {
        auto result = op::add(a, b);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_Multiply(benchmark::State& state) {
    for (auto _ : state) {
        auto result = op::mult(a, b);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_Invert(benchmark::State& state) {
    for (auto _ : state) {
        auto result = op::inv(a);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_Square(benchmark::State& state) {
    for (auto _ : state) {
        auto result = op::square(a);
        benchmark::DoNotOptimize(result);
    }
}


// Register the benchmarks
BENCHMARK(BM_Add);
BENCHMARK(BM_Multiply);
BENCHMARK(BM_Invert);
BENCHMARK(BM_Square);

// Run the benchmark
BENCHMARK_MAIN();