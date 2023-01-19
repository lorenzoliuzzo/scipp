/**
 * @file    tools.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains a set of tools for the measurements library
 * @date    2023-01-14
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::measurements {


    namespace utilities {


        /**
         * @brief Read a file containing a list of measurements and return a vector of measurements
         * 
         * @param data_file_name: name of the file containing the measurements
         * 
         * @return std::vector<measurement> 
         */
        std::vector<measurement> read_measurements(const std::string& data_file_name) {

            double meas_value;
            std::string meas_unit;
            std::vector<measurement> data;

            std::ifstream file(data_file_name);
            if (!file.is_open()) {

                std::cerr << "Error: unable to open file '" << data_file_name << "'\n";
                exit(EXIT_FAILURE);

            } else while (file >> meas_value >> meas_unit)

                data.emplace_back(measurement(meas_value, unit(meas_unit)));

            file.close();

            return data;

        }


        /**
         * @brief Read a file containing a list of measurements and return a vector of measurements
         * 
         * @param data_file_name: name of the file containing the measurements
         * @param units: unit of the measurements
         * 
         * @return std::vector<measurement> 
         */
        std::vector<measurement> read_measurements(const std::string& data_file_name,  
                                                   const unit& units) {

            double meas_value;
            std::vector<measurement> data;

            std::ifstream file(data_file_name);
            if (!file.is_open()) {

                std::cerr << "Error: unable to open file '" << data_file_name << "'\n";
                exit(EXIT_FAILURE);

            } else while (file >> meas_value)

                data.emplace_back(measurement(meas_value, units));

            file.close();

            return data;
            
        }


        /**
         * @brief Read a file containing a list of umeasurements and return a vector of umeasurements
         * 
         * @param data_file_name: name of the file containing the measurements
         * 
         * @return std::vector<umeasurement> 
         */
        std::vector<umeasurement> read_umeasurements(const std::string& data_file_name) {
                    
            double meas_value;
            double meas_uncertainty;
            std::string meas_unit;
            std::vector<umeasurement> data;

            std::ifstream file(data_file_name);
            if (!file.is_open()) {

                std::cerr << "Error: unable to open file '" << data_file_name << "'\n";
                exit(EXIT_FAILURE);

            } else while (file >> meas_value >> meas_uncertainty >> meas_unit)

                data.emplace_back(umeasurement(meas_value, meas_uncertainty, unit(meas_unit)));

            file.close();

            return data;

        }


        /**
         * @brief Read a file containing a list of umeasurements and return a vector of umeasurements
         * 
         * @param data_file_name: name of the file containing the measurements
         * @param units: unit of the measurements
         * 
         * @return std::vector<umeasurement> 
         */
        std::vector<umeasurement> read_umeasurements(const std::string& data_file_name,  
                                                                       const unit& units) {

            double meas_value;
            double meas_uncertainty;
            std::vector<umeasurement> data;

            std::ifstream file(data_file_name);
            if (!file.is_open()) {

                std::cerr << "Error: unable to open file '" << data_file_name << "'\n";
                exit(EXIT_FAILURE);

            } else while (file >> meas_value >> meas_uncertainty)

                data.emplace_back(umeasurement(meas_value, meas_uncertainty, units));

            file.close();

            return data;
            
        }


        /**
         * @brief Read a file containing a list of umeasurements and return a vector of umeasurements
         * 
         * @param data_file_name: name of the file containing the measurements
         * @param uncertainty: measurement containing the uncertainty of the measurements
         * 
         * @return std::vector<umeasurement> 
         */
        std::vector<umeasurement> read_umeasurements(const std::string& data_file_name,  
                                                                       const measurement& uncertainty) {

            double meas_value;
            std::vector<umeasurement> data;

            std::ifstream file(data_file_name);
            if (!file.is_open()) {

                std::cerr << "Error: unable to open file '" << data_file_name << "'\n";
                exit(EXIT_FAILURE);

            } else while (file >> meas_value)

                data.emplace_back(umeasurement(meas_value, uncertainty.value(), uncertainty.units()));

            file.close();

            return data;

        }


    } // namespace utilities


} // namespace scipp::measurements