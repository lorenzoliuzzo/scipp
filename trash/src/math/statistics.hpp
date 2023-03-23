/**
 * @file    statistics.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the definition and implementation of all the descriptive statistics functions for the measurements library
 * @date    2023-01-02
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {

    
    namespace statistics {


        /**
         * @brief Compute the median of a vector of measurements
         * 
         * @param other: vector of measurements
         * 
         * @return measurement 
         */
        template <unit_base UB>
        measurement<UB> median(const std::vector<measurement<UB>>& other) {

            std::size_t N{other.size()}; 
            if (N == 0) 
                throw std::invalid_argument("Can't operate a descriptive statistic function on an empty vector"); 

            std::vector<measurement<UB>> copy{other}; 
            if (!std::is_sorted(copy.begin(), copy.end())) 
                std::sort(copy.begin(), copy.end());

            if (N % 2 != 0) 
                return copy[N / 2];
            else 
                return (copy[N / 2] + copy[(N / 2) - 1]) / 2; 

        }



        /**
         * @brief Compute the mean value of a vector of measurements
         * @note The uncertainty is computed as the standard deviation of mean (sdom)
         * 
         * @param vec: vector of measurements
         * 
         * @return umeasurement
         */
        template <unit_base UB>
        constexpr umeasurement<UB> mean(const std::vector<measurement<UB>>& vec) {

            std::size_t N{vec.size()}; 
            if (N == 0) 
                throw std::invalid_argument("Can't operate a descriptive statistic function on an empty vector"); 
            
            measurement<UB> average = std::accumulate(vec.begin(), vec.end(), measurement<UB>()) / N;
            measurement<math::op::square(UB)> sigma_sq;
            

            #pragma omp parallel for
            for (const measurement<UB>& x : vec) 
                #pragma omp critical
                sigma_sq += op::square(x - average); 

            return { average, op::sqrt(sigma_sq / (N * (N - 1))) };                 

        }


        /**
         * @brief Compute the mean value of a vector of umeasurements.
         * @note The uncertainty is computed as the standard deviation of mean (sdom)
         * 
         * @param vec: vector of umeasurements
         * 
         * @return umeasurement
         */
        template <unit_base UB>
        constexpr umeasurement<UB> mean(const std::vector<umeasurement<UB>>& vec) {

            std::size_t N{vec.size()}; 
            if (N < 2) 
                throw std::invalid_argument("Can't operate a descriptive statistic function on an empty vector"); 
            
            measurement<UB> average = std::accumulate(vec.begin(), vec.end(), umeasurement<UB>(0.)).as_measurement() / N;
            measurement<math::op::square(UB)> sigma_sq;

            #pragma omp parallel for
            for (auto x : vec) 
                #pragma omp critical
                sigma_sq += op::square(x - average); 

            return { average, op::sqrt(sigma_sq / (N * (N - 1))) };                 

        }


        /**
         * @brief Compute the weighted mean of a vector of measurements
         * 
         * @param vec 
         * 
         * @return umeasurement 
         */
        template <unit_base UB>
        constexpr umeasurement<UB> wmean(const std::vector<umeasurement<UB>>& vec) {

            if (vec.size() == 0) 
                throw std::invalid_argument("Can't operate a descriptive statistic function on an empty vector"); 
            
            measurement<math::op::inv(UB)> weighted;
            measurement<math::op::square(math::op::inv(UB))> weights;

            for (const umeasurement<UB>& x : vec) {
                weighted += x.as_measurement() * x.weight(); 
                weights += x.weight();
            }

            return { weighted / weights, op::sqrt(op::inv(weights)) };

        }


        /**
         * @brief Compute the variance of a vector of measurements
         * 
         * @param vec: vector of measurements
         * 
         * @return measurement 
         */
        template <unit_base UB>
        constexpr measurement<UB> variance(const std::vector<measurement<UB>>& vec) {

            measurement<UB> average = average(vec);
            measurement<math::op::square(UB)> sigma_sq; 

            for (const measurement<UB>& x : vec) 
                sigma_sq += op::square(x - average); 

            return sigma_sq / vec.size();

        }

    
        /**
         * @brief Compute the weighted variance of a vector of measurements
         * 
         * @param vec 
         * 
         * @return measurement 
         */
        template <unit_base UB>
        constexpr measurement<UB> wvariance(const std::vector<umeasurement<UB>>& vec) {

            if (vec.size() == 0) 
                throw std::invalid_argument("Can't operate a descriptive statistic function on an empty vector"); 
            
            measurement<math::op::square(math::op::inv(UB))> weights; 
            for (const umeasurement<UB>& x : vec) 
                weights += x.weight(); 
            
            return op::inv(weights); 

        }


        /**
         * @brief Compute the standard deviation of a vector of measurements
         * 
         * @param vec: vector of measurements
         * 
         * @return measurement 
         */
        template <unit_base UB>
        constexpr measurement<UB> sd(const std::vector<measurement<UB>>& vec) { 
            
            return op::sqrt(variance(vec)); 
        
        }


        /**
         * @brief Compute the standard error of the mean of a vector of measurements
         * 
         * @param vec: vector of measurements
         * 
         * @return measurement 
         */
        template <unit_base UB>
        constexpr measurement<UB> sdom(const std::vector<measurement<UB>>& vec) { 
            
            return op::sqrt(variance(vec) / (vec.size() - 1)); 
        
        }


        /**
         * @brief Compute the weighted standard deviation of a vector of measurements
         * 
         * @param vec 
         * 
         * @return measurement 
         */
        template <unit_base UB>
        constexpr measurement<UB> wsd(const std::vector<measurement<UB>>& vec) { 

            return op::sqrt(wvariance(vec));
        
        }


        // measurement chi(const std::vector<measurement>& vec, 
        //                 const std::vector<measurement>& expected) {

        //     if (vec.size() != expected.size()) 
        //         throw std::invalid_argument("Can't operate a chi square function on vectors of different size"); 
            
        //     measurement accu = measurement(0., vec[0].units()); 
        //     for (std::size_t i{}; i < vec.size(); ++i) 
        //         accu += square((vec[i] - expected[i])) / expected[i]; 
            
        //     return accu; 

        // }         


        // measurement chi(const std::vector<umeasurement>& vec, 
        //                 const std::vector<umeasurement>& expected) {

        //     if (vec.size() != expected.size()) 
        //         throw std::invalid_argument("Can't operate a chi square function on vectors of different size"); 
            
        //     measurement accu = measurement(0., vec[0].units()); 
        //     for (std::size_t i{}; i < vec.size(); ++i) 
        //         accu += (square((vec[i] - expected[i])) / expected[i]).as_measurement(); 
            
        //     return accu; 

        // }     


        // inline measurement chi_r(const std::vector<measurement>& v, 
        //                          const std::vector<measurement>& expected, 
        //                          const int& gdl) {

        //     return chi(v, expected) / gdl; 

        // }


    } // namespace statistics


} // namespace scipp::math