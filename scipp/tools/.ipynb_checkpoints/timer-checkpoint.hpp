/**
 * @file    tools/timer.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-03-30
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::tools {


    /// @brief Class for timing the execution of a generic function/process
    class timer {

        
        public:

        // =============================================
        // constructor and destructor
        // =============================================   

            /// @brief Construct a new timer object
            timer() noexcept = default;


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


            inline physics::time_m elapsed() noexcept {

                return physics::time_m(static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(stop_ - start_).count()), physics::units::ns);
            
            }             


        protected: 

            // =============================================
            // class members
            // =============================================     

            std::chrono::time_point<std::chrono::high_resolution_clock> start_, stop_;


    }; // class timer


/*
    /// @brief Class for timing the execution of a generic function/process
    class omp_timer {

        
        public:

        // =============================================
        // constructor and destructor
        // =============================================   

            /// @brief Default destructor
            ~omp_timer() = default;

        
        // =============================================
        // omp_timer methods
        // =============================================   


            inline void start() {

                start_ = omp_get_wtime();

            }


            inline void stop() {

                stop_ = omp_get_wtime();

            }


            constexpr physics::time_m elapsed() {

                return physics::time_m(stop_ - start_);
            
            }             


        protected: 

            // =============================================
            // class members
            // =============================================     

            double start_, stop_;


    }; // class timer
*/
    

} // namespace scipp::tools