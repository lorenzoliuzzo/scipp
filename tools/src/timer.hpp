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


            time_measurement elapsed(const unit& units = s) const {

                if (units.base_ != basis::second) 
                    throw std::invalid_argument("Wrong unit, the unit_base must be second");

                time_measurement ns_elapsed(std::chrono::duration_cast<std::chrono::nanoseconds>(stop_ - start_).count(), ns);

                return ns_elapsed.convert_to(units);
            
            }             


        protected: 

            // =============================================
            // class members
            // =============================================     

            std::chrono::time_point<std::chrono::high_resolution_clock> start_, stop_;


    }; // class timer


} // namespace scipp::tools