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
         * @param vec: vector of measurements
         * 
         * @return measurement 
         */
        measurement median(const std::vector<measurement>& vec) {

            std::size_t N{vec.size()}; 
            if (N == 0) 
                throw std::invalid_argument("Can't operate a descriptive statistic funtion on an empty vector"); 

            std::vector<measurement> copy{vec}; 
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
        umeasurement mean(const std::vector<measurement>& vec) {

            std::size_t N{vec.size()}; 
            if (N == 0) 
                throw std::invalid_argument("Can't operate a descriptive statistic funtion on an empty vector"); 
            
            measurement average = std::accumulate(vec.begin(), vec.end(), measurement(0., vec[0].units())) / N;
            
            measurement sigma_sq(0., vec[0].units().square());

            for (auto x : vec) 
                sigma_sq += square(x - average).as_measurement(); 

            return umeasurement(average, sqrt(sigma_sq / (N * (N - 1))));                 

        }


        /**
         * @brief Compute the mean value of a vector of umeasurements.
         * @note The uncertainty is computed as the standard deviation of mean (sdom)
         * 
         * @param vec: vector of umeasurements
         * 
         * @return umeasurement
         */
        umeasurement mean(const std::vector<umeasurement>& vec) {

            std::size_t N{vec.size()}; 
            if (N == 0) 
                throw std::invalid_argument("Can't operate a descriptive statistic funtion on an empty vector"); 
            
            measurement average = std::accumulate(vec.begin(), vec.end(), umeasurement(0., 0., vec[0].units())).as_measurement() / N;
            measurement sigma_sq(0., vec[0].units().square());

            for (auto x : vec) 
                sigma_sq += square(x - average).as_measurement(); 

            return umeasurement(average, sqrt(sigma_sq / (N * (N - 1))));                 

        }


        /**
         * @brief Compute the weighted mean of a vector of measurements
         * 
         * @param vec 
         * 
         * @return umeasurement 
         */
        umeasurement wmean(const std::vector<umeasurement>& vec) {

            if (vec.size() == 0) 
                throw std::invalid_argument("Can't operate a descriptive statistic funtion on an empty vector"); 
            
            measurement weighted(0., vec[0].units().inv());
            measurement weights(0., vec[0].units().inv().square());

            for (const umeasurement& x : vec) {
                weighted += x.as_measurement() * x.weight(); 
                weights += x.weight();
            }

            return umeasurement(weighted / weights, sqrt(weights.inv()));

        }


        /**
         * @brief Compute the variance of a vector of measurements
         * 
         * @param vec: vector of measurements
         * 
         * @return measurement 
         */
        measurement variance(const std::vector<measurement>& vec) {

            measurement average(mean(vec).as_measurement());
            measurement sigma_sq(0., vec[0].units().square()); 

            for (const measurement& x : vec) 
                sigma_sq += square(x - average); 

            return sigma_sq / vec.size();

        }

    
        /**
         * @brief Compute the weighted variance of a vector of measurements
         * 
         * @param vec 
         * 
         * @return measurement 
         */
        measurement wvariance(const std::vector<umeasurement>& vec) {

            if (vec.size() == 0) 
                throw std::invalid_argument("Can't operate a descriptive statistic funtion on an empty vector"); 
            
            measurement weights(0., vec[0].units().inv().square());
            for (const umeasurement& x : vec) 
                weights += x.weight(); 
            
            return weights.inv(); 

        }


        /**
         * @brief Compute the standard deviation of a vector of measurements
         * 
         * @param vec: vector of measurements
         * 
         * @return measurement 
         */
        inline measurement sd(const std::vector<measurement>& vec) { 
            
            return sqrt(variance(vec)); 
        
        }


        /**
         * @brief Compute the standard error of the mean of a vector of measurements
         * 
         * @param vec: vector of measurements
         * 
         * @return measurement 
         */
        inline measurement sdom(const std::vector<measurement>& vec) { 
            
            return sqrt(variance(vec) / (vec.size() - 1)); 
        
        }


        /**
         * @brief Compute the weighted standard deviation of a vector of measurements
         * 
         * @param vec 
         * 
         * @return measurement 
         */
        inline measurement wsd(const std::vector<umeasurement>& vec) {

            return sqrt(wvariance(vec));
        
        }


        measurement chi(const std::vector<measurement>& vec, 
                        const std::vector<measurement>& expected) {

            if (vec.size() != expected.size()) 
                throw std::invalid_argument("Can't operate a chi square funtion on vectors of different size"); 
            
            measurement accu = measurement(0., vec[0].units()); 
            for (std::size_t i{}; i < vec.size(); ++i) 
                accu += square((vec[i] - expected[i])) / expected[i]; 
            
            return accu; 

        }         


        measurement chi(const std::vector<umeasurement>& vec, 
                        const std::vector<umeasurement>& expected) {

            if (vec.size() != expected.size()) 
                throw std::invalid_argument("Can't operate a chi square funtion on vectors of different size"); 
            
            measurement accu = measurement(0., vec[0].units()); 
            for (std::size_t i{}; i < vec.size(); ++i) 
                accu += (square((vec[i] - expected[i])) / expected[i]).as_measurement(); 
            
            return accu; 

        }     


        inline measurement chi_r(const std::vector<measurement>& v, 
                                 const std::vector<measurement>& expected, 
                                 const int& gdl) {

            return chi(v, expected) / gdl; 

        }


    } // namespace statistics


} // namespace scipp::math