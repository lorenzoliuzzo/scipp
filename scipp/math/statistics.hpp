/**
 * @file    math/statistics.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the definition and implementation of all the descriptive statistics functions
 * @date    2023-03-23
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {

    
    namespace statistics {


        /// @brief Compute the average value of a vector of measurements
        /// @param other: vector of measurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        inline constexpr auto average(const VECTOR_TYPE& other) noexcept {
            
            using value_type = typename VECTOR_TYPE::value_t;

            return std::accumulate(other.data.begin(), other.data.end(), value_type{},
                                [](const value_type& a, const value_type& b) {
                                    return a + b;
                                }) / static_cast<double>(VECTOR_TYPE::dim);
                           
        }
        

        /// @brief Compute the mean value of a vector of umeasurements
        /// @param other: vector of umeasurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE> && physics::is_umeasurement_v<typename VECTOR_TYPE::value_t>)
        constexpr typename VECTOR_TYPE::value_t mean(const VECTOR_TYPE& other) noexcept {

            double weighted_value{};
            double weights{};

            for (const auto& um : other.data) {
                weighted_value += um.value * um.weight(); 
                weights += um.weight();
            }

            return { weighted_value / weights, std::sqrt(1.0 / weights) };

        }

        /// @brief Compute the variance of a vector of measurements
        /// @param other: vector of measurements
        /// @param average: average value of the vector of measurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE> && physics::is_measurement_v<typename VECTOR_TYPE::value_t>)
        constexpr auto variance(const VECTOR_TYPE& other, const typename VECTOR_TYPE::value_t& average) noexcept 
            -> functions::square_t<typename VECTOR_TYPE::value_t> {

            return std::accumulate(other.data.begin(), other.data.end(), functions::square_t<typename VECTOR_TYPE::value_t>(), 
                                    [&average](const functions::square_t<typename VECTOR_TYPE::value_t>& acc, 
                                                            const typename VECTOR_TYPE::value_t& val) { 
                                                                return acc + op::square(val - average); 
                                                            }
                                  ) / static_cast<double>(VECTOR_TYPE::dim);

        }


        /// @brief Compute the variance of a vector of measurements
        /// @param other: vector of measurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        constexpr auto variance(const VECTOR_TYPE& other) noexcept {

            auto avg = average(other);
            return std::accumulate(other.data.begin(), other.data.end(), functions::square_t<typename VECTOR_TYPE::value_t>(), 
                                    [&avg](const functions::square_t<typename VECTOR_TYPE::value_t>& acc, 
                                                            const typename VECTOR_TYPE::value_t& val) { 
                                                                return acc + op::square(val - avg); 
                                                            }
                                  ) / static_cast<double>(VECTOR_TYPE::dim);

        }


        /// @brief Compute the variance of a vector of umeasurements
        /// @param other: vector of umeasurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE> && physics::is_umeasurement_v<typename VECTOR_TYPE::value_t>)
        constexpr auto variance(const VECTOR_TYPE& other) 
            -> functions::square_t<typename VECTOR_TYPE::value_t> {
            
            functions::invert_t<functions::square_t<typename VECTOR_TYPE::value_t>> weights; 
            for (const auto& x : other.data) 
                weights += x.weight(); 
            
            return op::inv(weights);    

        }


        /// @brief Compute the standard deviation of a vector of measurements
        /// @param other: vector of measurements
        /// @param average: average value of the vector of measurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        inline constexpr auto stdev(const VECTOR_TYPE& other, const typename VECTOR_TYPE::value_t& average) noexcept 
            -> physics::measurement<typename VECTOR_TYPE::value_t::base> {

            return op::sqrt(variance(other, average));

        }


        /// @brief Compute the standard deviation of a vector of measurements
        /// @param other: vector of measurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        inline constexpr auto stdev(const VECTOR_TYPE& other) noexcept 
            -> typename VECTOR_TYPE::value_t {

            return op::sqrt(variance(other));

        }


        /// @brief Compute the standard deviation of a vector of measurements
        /// @param other: vector of measurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        inline constexpr auto stdev_mean(const VECTOR_TYPE& other) noexcept 
            -> typename VECTOR_TYPE::value_t {

            return op::sqrt(variance(other)) / static_cast<double>(VECTOR_TYPE::dim);

        }


        /// @brief Compute the median of a vector of measurements
        /// @param other: vector of measurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        constexpr auto median(const VECTOR_TYPE& other) noexcept 
            -> typename VECTOR_TYPE::value_t {

            VECTOR_TYPE copy(other); 
            if (!std::is_sorted(copy.data.begin(), copy.data.end())) 
                std::sort(copy.data.begin(), copy.data.end());

            if (VECTOR_TYPE::dim % 2 != 0) 
                return copy[VECTOR_TYPE::dim / 2];
            else 
                return (copy[VECTOR_TYPE::dim / 2] + copy[(VECTOR_TYPE::dim / 2) - 1]) / 2; 

        }


    } // namespace statistics


} // namespace scipp::math