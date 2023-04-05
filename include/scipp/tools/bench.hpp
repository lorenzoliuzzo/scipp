/**
 * @file    tools/bench.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-02
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::tools {


    /**
     * @brief A class for benchmarking an operation or a function or a piece of code
     * 
     * @param n: number of times the operation is repeated
     * @param func: the operation to be benchmarked
     * 
     * @return physics::time_um
     */
    template <std::size_t N>
    physics::time_um bench(const std::function<void(void)>& func) {

        timer stopwatch;
        geometry::vector<physics::time_m, N> times;

        std::transform(std::execution::par,
                       times.data.begin(), times.data.end(), 
                       times.data.begin(),
                       [&stopwatch, &func](const auto&) {
                           stopwatch.start();
                           func();
                           stopwatch.stop();
                           return stopwatch.elapsed();
                        });

        physics::time_m avg_time = math::statistics::average(times);

        return {avg_time, math::statistics::stdev(times, avg_time)};

    }


    /**
     * @brief A class for benchmarking an operation or a function or a piece of code
     * 
     * @param n: number of times the operation is repeated
     * @param func: the operation to be benchmarked
     * 
     * @return physics::time_um
     */
    template <std::size_t N>
    physics::time_um omp_bench(std::function<void()> func) {

        omp_timer stopwatch;
        geometry::vector<physics::time_m, N> times;

        for (std::size_t i{}; i < N; ++i) {

            stopwatch.start();
            func();
            stopwatch.stop();
            times[i] = stopwatch.elapsed();

        }

        return math::statistics::average(times);

    }


    // /**
    //  * @brief A class for benchmarking an operation or a function or a piece of code
    //  * 
    //  * @param n: number of times the operation is repeated
    //  * @param func: the operation to be benchmarked
    //  * 
    //  * @return physics::time_um
    //  */
    // physics::time_um cpu_bench(const std::size_t& n, std::function<void()> func) {

    //     if (n == 0)
    //         throw std::runtime_error("Error: n must be greater than 0");

    //     cpu_timer stopwatch;
    //     geometry::vector<physics::time_m, N> times;

    //     times.reserve(n); 

    //     for (std::size_t i{}; i < n; ++i) {

    //         stopwatch.start();
    //         func();
    //         stopwatch.stop();
    //         times.emplace_back(stopwatch.elapsed());

    //     }

    //     return math::statistics::average(times);

    // }


} // namespace scipp::tools