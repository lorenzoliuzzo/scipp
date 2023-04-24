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
        inline constexpr auto average(const VECTOR_TYPE& other) noexcept 
            -> physics::measurement<typename VECTOR_TYPE::measurement_t::base> {
            
            return std::accumulate(other.data.begin(), other.data.end(), typename VECTOR_TYPE::measurement_t()) / static_cast<physics::scalar_m>(VECTOR_TYPE::dim); 

        }


        /// @brief Compute the mean value of a vector of umeasurements
        /// @param other: vector of umeasurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE> && physics::is_umeasurement_v<typename VECTOR_TYPE::measurement_t>)
        constexpr typename VECTOR_TYPE::measurement_t mean(const VECTOR_TYPE& other) noexcept {

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
            requires (geometry::is_vector_v<VECTOR_TYPE> && physics::is_measurement_v<typename VECTOR_TYPE::measurement_t>)
        constexpr auto variance(const VECTOR_TYPE& other, const typename VECTOR_TYPE::measurement_t& average) noexcept 
            -> op::square_t<typename VECTOR_TYPE::measurement_t> {

            return std::accumulate(other.data.begin(), other.data.end(), op::square_t<typename VECTOR_TYPE::measurement_t>(), 
                                    [&average](const op::square_t<typename VECTOR_TYPE::measurement_t>& acc, 
                                                            const typename VECTOR_TYPE::measurement_t& val) { 
                                                                return acc + op::square(val - average); 
                                                            }
                                  ) / static_cast<physics::scalar_m>(VECTOR_TYPE::dim);

        }


        /// @brief Compute the variance of a vector of measurements
        /// @param other: vector of measurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE> && physics::is_measurement_v<typename VECTOR_TYPE::measurement_t>)
        constexpr auto variance(const VECTOR_TYPE& other) noexcept 
            -> op::square_t<typename VECTOR_TYPE::measurement_t> {

            auto avg = average(other);
            return std::accumulate(other.data.begin(), other.data.end(), op::square_t<typename VECTOR_TYPE::measurement_t>(), 
                                    [&avg](const op::square_t<typename VECTOR_TYPE::measurement_t>& acc, 
                                                            const typename VECTOR_TYPE::measurement_t& val) { 
                                                                return acc + op::square(val - avg); 
                                                            }
                                  ) / static_cast<physics::scalar_m>(VECTOR_TYPE::dim);

        }


        /// @brief Compute the variance of a vector of umeasurements
        /// @param other: vector of umeasurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE> && physics::is_umeasurement_v<typename VECTOR_TYPE::measurement_t>)
        constexpr auto variance(const VECTOR_TYPE& other) 
            -> physics::measurement<op::base_square_t<typename VECTOR_TYPE::measurement_t::base>> {
            
            op::invert_t<physics::measurement<op::base_square_t<typename VECTOR_TYPE::measurement_t::base>>> weights; 
            for (const auto& x : other.data) 
                weights += x.weight(); 
            
            return op::inv(weights);    

        }


        /// @brief Compute the standard deviation of a vector of measurements
        /// @param other: vector of measurements
        /// @param average: average value of the vector of measurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        inline constexpr auto stdev(const VECTOR_TYPE& other, const typename VECTOR_TYPE::measurement_t& average) noexcept 
            -> physics::measurement<typename VECTOR_TYPE::measurement_t::base> {

            return op::sqrt(variance(other, average));

        }


        /// @brief Compute the standard deviation of a vector of measurements
        /// @param other: vector of measurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        inline constexpr auto stdev(const VECTOR_TYPE& other) noexcept 
            -> physics::measurement<typename VECTOR_TYPE::measurement_t::base> {

            return op::sqrt(variance(other));

        }


        /// @brief Compute the standard deviation of a vector of measurements
        /// @param other: vector of measurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        inline constexpr typename VECTOR_TYPE::measurement_t stdev_mean(const VECTOR_TYPE& other) noexcept {

            return op::sqrt(variance(other)) / static_cast<physics::scalar_m>(VECTOR_TYPE::dim);

        }


        /// @brief Compute the median of a vector of measurements
        /// @param other: vector of measurements
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        constexpr typename VECTOR_TYPE::measurement_t median(const VECTOR_TYPE& other) noexcept {

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