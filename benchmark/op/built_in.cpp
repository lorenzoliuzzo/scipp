/**
 * @file    benchmark/double.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the benchmarking of the built-in function on the double type.
 *          The benchmarking is done with the Google Benchmark library.
 *          Testing +, *, /, pow
 * @date    2023-07-17
 *
 * @copyright Copyright (c) 2023
 */


#include <benchmark/benchmark.h>

#include <cmath>


// Define input data for the benchmarks
constexpr double a = 5.0;
constexpr double b = 10.0;


// Benchmark functions
static void BM_Add(benchmark::State& state) {
    for (auto _ : state) {
        auto result = a + b;
        benchmark::DoNotOptimize(result);
    }
}

static void BM_Multiply(benchmark::State& state) {
    for (auto _ : state) {
        auto result = a * b;
        benchmark::DoNotOptimize(result);
    }
}

static void BM_Invert(benchmark::State& state) {
    for (auto _ : state) {
        auto result = 1.0 / a;
        benchmark::DoNotOptimize(result);
    }
}

static void BM_Square(benchmark::State& state) {
    for (auto _ : state) {
        auto result = std::pow(a, 2);
        benchmark::DoNotOptimize(result);
    }
}


BENCHMARK(BM_Add);
BENCHMARK(BM_Multiply);
BENCHMARK(BM_Invert);
BENCHMARK(BM_Square);

// Run the benchmark
BENCHMARK_MAIN();
