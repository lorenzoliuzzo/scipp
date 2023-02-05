/**
 * @file    bench.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2022-12-11
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once

#include <functional>


namespace scipp::tools {


    /**
     * @brief A class for benchmarking an operation or a function or a piece of code
     * 
     * @param n: number of times the operation is repeated
     * @param func: the operation to be benchmarked
     * 
     * @return time_um
     */
    time_um bench(const std::size_t& n, std::function<void()> func) {

        if (n == 0)
            throw std::runtime_error("Error: n must be greater than 0");

        timer stopwatch;
        std::vector<time_m> times;

        times.reserve(n); 

        for (std::size_t i{}; i < n; ++i) {

            stopwatch.start();
            func();
            stopwatch.stop();
            times.emplace_back(stopwatch.elapsed());

        }

        return math::statistics::mean(times);

    }


    /**
     * @brief A class for benchmarking an operation or a function or a piece of code
     * 
     * @param n: number of times the operation is repeated
     * @param func: the operation to be benchmarked
     * 
     * @return time_um
     */
    time_um cpu_bench(const std::size_t& n, std::function<void()> func) {

        if (n == 0)
            throw std::runtime_error("Error: n must be greater than 0");

        cpu_timer stopwatch;
        std::vector<time_m> times;

        times.reserve(n); 

        for (std::size_t i{}; i < n; ++i) {

            stopwatch.start();
            func();
            stopwatch.stop();
            times.emplace_back(stopwatch.elapsed());

        }

        return math::statistics::mean(times);

    }


    /**
     * @brief A class for benchmarking an operation or a function or a piece of code
     * 
     * @param n: number of times the operation is repeated
     * @param func: the operation to be benchmarked
     * 
     * @return time_um
     */
    time_um omp_bench(const std::size_t& n, std::function<void()> func) {

        if (n == 0)
            throw std::runtime_error("Error: n must be greater than 0");

        omp_timer stopwatch;
        std::vector<time_m> times;

        times.reserve(n); 

        for (std::size_t i{}; i < n; ++i) {

            stopwatch.start();
            func();
            stopwatch.stop();
            times.emplace_back(stopwatch.elapsed());

        }

        return math::statistics::mean(times);

    }

} // namespace scipp::tools