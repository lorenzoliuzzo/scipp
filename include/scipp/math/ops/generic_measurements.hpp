/**
 * @file    math/ops/measurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-02
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {
    
    
    namespace op {


        template <typename MEAS_TYPE, typename... MEAS_TYPES>
            requires (physics::are_generic_measurements_v<MEAS_TYPE, MEAS_TYPES...>)
        struct measurements_prod { 

            using base = op::base_product_t<typename MEAS_TYPE::base, typename measurements_prod<MEAS_TYPES...>::base>;
            
            using type = std::conditional_t<physics::are_umeasurements_v<MEAS_TYPE, MEAS_TYPES...>,    
                                            physics::umeasurement<base>,
                                            physics::measurement<base>>;
        
        };

        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurements_prod<MEAS_TYPE> {

            using base = typename MEAS_TYPE::base;

            using type = MEAS_TYPE;

        };

        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurements_prod<MEAS_TYPE, double> {

            using base = typename MEAS_TYPE::base;

            using type = MEAS_TYPE;

        };

        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurements_prod<double, MEAS_TYPE> {

            using base = typename MEAS_TYPE::base;

            using type = MEAS_TYPE;

        };

        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurements_prod<MEAS_TYPE, float> {

            using base = typename MEAS_TYPE::base;

            using type = MEAS_TYPE;

        };
        
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurements_prod<MEAS_TYPE, int> {

            using base = typename MEAS_TYPE::base;

            using type = MEAS_TYPE;

        };

        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurements_prod<MEAS_TYPE, uint> {

            using base = typename MEAS_TYPE::base;

            using type = MEAS_TYPE;

        };


        template <typename... Ts>
        using measurements_prod_t = typename measurements_prod<Ts...>::type;


        template <typename MEAS_TYPE1, typename MEAS_TYPE2>
            requires (physics::are_generic_measurements_v<MEAS_TYPE1, MEAS_TYPE2>)
        struct measurements_div { 

            using base = op::base_division_t<typename MEAS_TYPE1::base, typename MEAS_TYPE2::base>;
            
            using type = std::conditional_t<physics::are_umeasurements_v<MEAS_TYPE1, MEAS_TYPE2>,    
                                            physics::umeasurement<base>,
                                            physics::measurement<base>>;
        
            
        };

        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurements_div<MEAS_TYPE, double> {

            using base = typename MEAS_TYPE::base;

            using type = MEAS_TYPE;

        };

        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurements_div<MEAS_TYPE, float> {

            using base = typename MEAS_TYPE::base;

            using type = MEAS_TYPE;

        };
        
        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurements_div<MEAS_TYPE, int> {

            using base = typename MEAS_TYPE::base;

            using type = MEAS_TYPE;

        };

        template <typename MEAS_TYPE>
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurements_div<MEAS_TYPE, uint> {

            using base = typename MEAS_TYPE::base;

            using type = MEAS_TYPE;

        };


        template <typename T1, typename T2>
        using measurements_div_t = typename measurements_div<T1, T2>::type;


        template <typename MEAS_TYPE>
        struct measurement_inv { 

            using base = op::base_invert_t<typename MEAS_TYPE::base>;
            
            using type = std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                            physics::umeasurement<base>, 
                                            physics::measurement<base>>;


        }; 

        template <typename MEAS_TYPE>
        using measurement_inv_t = typename measurement_inv<MEAS_TYPE>::type;


        template <typename MEAS_TYPE, std::size_t POWER>    
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurement_pow { 

            using base = op::base_pow_t<typename MEAS_TYPE::base, POWER>; 
            
            using type = std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                            physics::umeasurement<base>, 
                                            physics::measurement<base>>;

        }; 

        template <typename MEAS_TYPE, std::size_t POWER>
        using measurement_pow_t = typename measurement_pow<MEAS_TYPE, POWER>::type;

        template <typename MEAS_TYPE>
        using measurement_square_t = measurement_pow_t<MEAS_TYPE, 2>;

        template <typename MEAS_TYPE>
        using measurement_cube_t = measurement_pow_t<MEAS_TYPE, 3>;


        template <typename MEAS_TYPE, std::size_t POWER>    
            requires (physics::is_generic_measurement_v<MEAS_TYPE>)
        struct measurement_root { 
            
            using base = op::base_root_t<typename MEAS_TYPE::base, POWER>; 

            using type = std::conditional_t<physics::is_umeasurement_v<MEAS_TYPE>, 
                                            physics::umeasurement<base>, 
                                            physics::measurement<base>>;

        }; 

        template <typename MEAS_TYPE, std::size_t POWER>
        using measurement_root_t = typename measurement_root<MEAS_TYPE, POWER>::type;

        template <typename MEAS_TYPE>
        using measurement_sqrt_t = measurement_root_t<MEAS_TYPE, 2>;

        template <typename MEAS_TYPE>
        using measurement_cbrt_t = measurement_root_t<MEAS_TYPE, 3>;


    } // namespace op


} // namespace scipp::math