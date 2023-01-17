/**
 * @file    timer.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2022-12-11
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once

#include <chrono>


namespace scipp::tools {


    /// @brief Class for timing the execution of a generic function/process
    class timer {

        
        public:

        // =============================================
        // constructor and destructor
        // =============================================   

            /// @brief Construct a new timer object
            timer() noexcept {}


            /// @brief Default destructor
            ~timer() = default;

        
        // =============================================
        // timer methods
        // =============================================   


            inline void start() noexcept {

                start_ = std::chrono::high_resolution_clock::now();

            }


            inline void stop() noexcept {

                stop_ = std::chrono::high_resolution_clock::now();

            }


            time_measurement elapsed() const {

                return std::chrono::duration_cast<std::chrono::nanoseconds>(stop_ - start_).count() * ns;
            
            }             


        protected: 

            // =============================================
            // class members
            // =============================================     

            std::chrono::time_point<std::chrono::high_resolution_clock> start_, stop_;


    }; // class timer


    /// @brief Class for timing the execution of a generic function/process
    class cpu_timer {

        
        public:

        // =============================================
        // constructor and destructor
        // =============================================   

            /// @brief Construct a new cpu_timer object
            cpu_timer() noexcept {}


            /// @brief Default destructor
            ~cpu_timer() = default;

        
        // =============================================
        // cpu_timer methods
        // =============================================   


            constexpr void start() noexcept {

                start_ = __builtin_ia32_rdtsc();

            }


            constexpr void stop() noexcept {

                stop_ = __builtin_ia32_rdtsc();

            }


            constexpr uint64_t cpu_cycles() const noexcept {

                return stop_ - start_;

            }


            constexpr time_measurement elapsed() const {

                return (stop_ - start_) / (1.8 * GHz);
            
            }             


        protected: 

            // =============================================
            // class members
            // =============================================     

            uint64_t start_, stop_;


    }; // class cpu_timer


} // namespace scipp::tools