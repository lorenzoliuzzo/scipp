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
     * @return umeasurement
     */
    umeasurement bench(const std::size_t& n, std::function<void()> func, const unit& time_units = ns) {

        if (n == 0)
            throw std::runtime_error("Error: n must be greater than 0");

        if (time_units.base() != basis::second)
            throw std::runtime_error("Error: time_units must have basis::second as unit_base");

        timer stopwatch;
        std::vector<measurement> times;

        times.reserve(n); 

        for (std::size_t i{}; i < n; ++i) {

            stopwatch.start();
            func();
            stopwatch.stop();
            times.emplace_back(stopwatch.elapsed(time_units));

        }

        return math::statistics::mean(times);

    }


    /**
     * @brief A class for benchmarking an operation or a function or a piece of code
     * 
     * @param n: number of times the operation is repeated
     * @param func: the operation to be benchmarked
     * 
     * @return umeasurement
     */
    umeasurement cpu_bench(const std::size_t& n, std::function<void()> func, const unit& time_units = ns) {

        if (n == 0)
            throw std::runtime_error("Error: n must be greater than 0");

        if (time_units.base() != basis::second)
            throw std::runtime_error("Error: time_units must have basis::second as unit_base");

        cpu_timer stopwatch;
        std::vector<measurement> times;

        times.reserve(n); 

        for (std::size_t i{}; i < n; ++i) {

            stopwatch.start();
            func();
            stopwatch.stop();
            times.emplace_back(stopwatch.elapsed(time_units));

        }

        return math::statistics::mean(times);

    }


} // namespace scipp::tools