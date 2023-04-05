/**
 * @file    geometry/linspace.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-01
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::geometry {



    /// @brief Create a linearly spaced vector
    /// @param start The starting value of the sequence
    /// @param stop The end value of the sequence
    /// @param num The number of samples to generate
    template <std::size_t DIM, typename MEAS_TYPE>
        requires physics::is_measurement_v<MEAS_TYPE>
    static constexpr vector<MEAS_TYPE, DIM> linspace(const MEAS_TYPE& start, const MEAS_TYPE& stop) noexcept {

        const MEAS_TYPE step = (stop - start) / static_cast<physics::scalar_m>(DIM - 1.0);
        std::array<MEAS_TYPE, DIM> result;

        for (std::size_t i{}; i < DIM; ++i)
            result[i] = start + static_cast<physics::scalar_m>(i) * step;

        return result;

    };

    
    template <std::size_t DIM, typename VECTOR_TYPE>
        requires is_vector_v<VECTOR_TYPE>
    static constexpr matrix<VECTOR_TYPE, DIM> linspace(const VECTOR_TYPE& start, const VECTOR_TYPE& stop) noexcept {

        const VECTOR_TYPE step = (stop - start) / static_cast<physics::scalar_m>(DIM - 1.0);
        std::array<VECTOR_TYPE, DIM> result;

        for (std::size_t i{}; i < DIM; ++i)
            result[i] = start + static_cast<physics::scalar_m>(i) * step;

        return result;

    };


    template <std::size_t DIM, typename SEGMENT_TYPE>
        requires is_segment_v<SEGMENT_TYPE>
    static constexpr auto linspace(const SEGMENT_TYPE& other) noexcept {

        return linspace<DIM>(other.start, other.end);

    };


    template <std::size_t DIM, typename CIRCLE_TYPE>
        // requires is_circle_v<CIRCLE_TYPE>
    static constexpr matrix<typename CIRCLE_TYPE::point_type, DIM> linspace(const CIRCLE_TYPE& other) noexcept {

        std::array<typename CIRCLE_TYPE::point_type, DIM> result;
        const auto t = linspace<DIM>(0.0, 2.0 * math::constants::pi);
        for (std::size_t i{}; i < DIM; ++i)
            result[i] = other(t[i]);

        return result;

    };

    
    template <std::size_t DIM, typename SPHERE_TYPE>
        requires is_sphere_v<SPHERE_TYPE>
    static constexpr matrix<typename SPHERE_TYPE::point_type, DIM> linspace(const SPHERE_TYPE& other) noexcept {

        // const auto phi = linspace<static_cast<unsigned int>(DIM / 10)>(static_cast<physics::scalar_m>(0.5), static_cast<physics::scalar_m>(2.0 * math::constants::pi));
        // const auto theta = linspace<static_cast<unsigned int>(DIM / 10)>(static_cast<physics::scalar_m>(0.5), static_cast<physics::scalar_m>(math::constants::pi));

        // for (std::size_t i{}; i < static_cast<unsigned int>(DIM / 10); ++i)
        //     for (std::size_t j{}; j < static_cast<unsigned int>(DIM / 10); ++j)
        //         result[i * static_cast<unsigned int>(DIM / 10) + j] = other(phi[j], theta[i]);

        //         // ] = other(phi[j], theta[i]);

        // return result;

        std::array<typename SPHERE_TYPE::point_type, DIM> result;

        for (std::size_t i{}; i < DIM; ++i)
            result[i] = other(math::op::acos(static_cast<physics::scalar_m>(1. - 2. * (static_cast<double>(i) + 0.5) / DIM)), math::constants::pi * (1. + std::sqrt(5.)) * (static_cast<double>(i) + 0.5));

        return result;


        // physics::scalar_m ga = (3.0 - std::sqrt(5.)) * math::constants::pi; 
        // auto theta = ga * linspace<DIM>(0.0, 1.0);
        // auto z = linspace<DIM, physics::scalar_m>(1.0 / static_cast<physics::scalar_m>(DIM) - 1.0, 1.0 - 1.0 / static_cast<physics::scalar_m>(DIM));
        // auto radius = math::op::sqrt(geometry::vector<physics::scalar_m, DIM>(1.0) - math::op::square(z));

        // for (std::size_t i{}; i < DIM; ++i)
        //     result[i] = typename SPHERE_TYPE::point_type(radius[i] * math::op::cos(theta[i]), radius[i] * math::op::sin(theta[i]), z[i]);


    // # Create a list of golden angle increments along tha range of number of points                                           
    // theta = ga * np.arange(num_points)

    // # Z is a split into a range of -1 to 1 in order to create a unit circle                                                  
    // z = np.linspace(1/num_points-1, 1-1/num_points, num_points)

    // # a list of the radii at each height step of the unit circle                                                             
    // radius = np.sqrt(1 - z * z)

    // # Determine where xy fall on the sphere, given the azimuthal and polar angles                                            
    // y = radius * np.sin(theta)
    // x = radius * np.cos(theta)



    //     std::array<typename SPHERE_TYPE::point_type, DIM> result;
    //     physics::scalar_m theta, phi;
    //     std::size_t M_phi;

    //     auto a = 4.0 * math::constants::pi * math::op::square(other.radius) / static_cast<physics::scalar_m>(DIM); 
    //     auto d = math::op::sqrt(a);
    //     auto M_theta = std::round(math::constants::pi / d);
    //     auto d_theta = math::constants::pi / M_theta; 
    //     auto d_phi = a / d_theta;


    //     // for (std::size_t m{}; m < M_theta - static_cast<physics::scalar_m>(1.0); ++m) {

    //     for (std::size_t m{}; m < M_theta; ++m) {

    //         theta = math::constants::pi * (m + 0.5) / M_theta;
    //         M_phi = std::round(2 * math::constants::pi * math::op::sin(theta) / d_phi);

    //         for (std::size_t n{}; n < (M_phi - 1); ++n) {

    //             phi = 2 * math::constants::pi * n / M_phi;
    //             result[n + m * M_phi] = other(phi, theta);
    //         }
            
    //     }

        return result;

    };


}