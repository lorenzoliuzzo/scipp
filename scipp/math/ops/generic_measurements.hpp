/**
 * @file    math/ops/generic_measurements.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-23
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    
    
    namespace op {


        // ====================================================================================================
        // operations on types
        // ====================================================================================================


            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (physics::is_measurement_v<MEAS_TYPE1> && math::is_complex_v<MEAS_TYPE2>)
            struct multiply<MEAS_TYPE1, MEAS_TYPE2> : complex<op::multiply_t<MEAS_TYPE1, typename MEAS_TYPE2::measurement_t>> {};

            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (math::is_complex_v<MEAS_TYPE1> && physics::is_measurement_v<MEAS_TYPE2>)
            struct multiply<MEAS_TYPE1, MEAS_TYPE2> : complex<op::multiply_t<typename MEAS_TYPE1::measurement_t, MEAS_TYPE2>> {};


            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (physics::is_measurement_v<MEAS_TYPE1> && physics::is_umeasurement_v<MEAS_TYPE2>)
            struct multiply<MEAS_TYPE1, MEAS_TYPE2> : physics::umeasurement<op::base_product_t<typename MEAS_TYPE1::base_t, typename MEAS_TYPE2::base_t>> {};

            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (physics::is_umeasurement_v<MEAS_TYPE1> && physics::is_measurement_v<MEAS_TYPE2>)
            struct multiply<MEAS_TYPE1, MEAS_TYPE2> : physics::umeasurement<op::base_product_t<typename MEAS_TYPE1::base_t, typename MEAS_TYPE2::base_t>> {};


            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (physics::is_umeasurement_v<MEAS_TYPE1> && math::is_complex_v<MEAS_TYPE2>)
            struct multiply<MEAS_TYPE1, MEAS_TYPE2> : complex<op::multiply_t<MEAS_TYPE1, typename MEAS_TYPE2::measurement_t>> {};

            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (math::is_complex_v<MEAS_TYPE1> && physics::is_umeasurement_v<MEAS_TYPE2>)
            struct multiply<MEAS_TYPE1, MEAS_TYPE2> : complex<op::multiply_t<typename MEAS_TYPE1::measurement_t, MEAS_TYPE2>> {};


            template <typename MEAS_TYPE, typename... MEAS_TYPEs>
                requires (physics::are_generic_measurements_v<MEAS_TYPE, MEAS_TYPEs...>)
            struct multiply<MEAS_TYPE, MEAS_TYPEs...> {

                using _t = typename multiply<MEAS_TYPE, typename multiply<MEAS_TYPEs...>::_t>::_t;

            };


            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (physics::is_measurement_v<MEAS_TYPE1> && math::is_complex_v<MEAS_TYPE2>)
            struct divide<MEAS_TYPE1, MEAS_TYPE2> : complex<op::divide_t<MEAS_TYPE1, typename MEAS_TYPE2::measurement_t>> {};

            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (math::is_complex_v<MEAS_TYPE1> && physics::is_measurement_v<MEAS_TYPE2>)
            struct divide<MEAS_TYPE1, MEAS_TYPE2> : complex<op::divide_t<typename MEAS_TYPE1::measurement_t, MEAS_TYPE2>> {};


            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (physics::is_measurement_v<MEAS_TYPE1> && physics::is_umeasurement_v<MEAS_TYPE2>)
            struct divide<MEAS_TYPE1, MEAS_TYPE2> : physics::umeasurement<op::base_product_t<typename MEAS_TYPE1::base_t, typename MEAS_TYPE2::base_t>> {};

            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (physics::is_umeasurement_v<MEAS_TYPE1> && physics::is_measurement_v<MEAS_TYPE2>)
            struct divide<MEAS_TYPE1, MEAS_TYPE2> : physics::umeasurement<op::base_product_t<typename MEAS_TYPE1::base_t, typename MEAS_TYPE2::base_t>> {};


            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (physics::is_umeasurement_v<MEAS_TYPE1> && math::is_complex_v<MEAS_TYPE2>)
            struct divide<MEAS_TYPE1, MEAS_TYPE2> : complex<op::divide_t<MEAS_TYPE1, typename MEAS_TYPE2::measurement_t>> {};

            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (math::is_complex_v<MEAS_TYPE1> && physics::is_umeasurement_v<MEAS_TYPE2>)
            struct divide<MEAS_TYPE1, MEAS_TYPE2> : complex<op::divide_t<typename MEAS_TYPE1::measurement_t, MEAS_TYPE2>> {};


            template <typename MEAS_TYPE, typename... MEAS_TYPEs>
                requires (physics::are_generic_measurements_v<MEAS_TYPE, MEAS_TYPEs...>)
            struct divide<MEAS_TYPE, MEAS_TYPEs...> {

                using _t = typename divide<MEAS_TYPE, typename divide<MEAS_TYPEs...>::_t>::_t;

            };


    } // namespace op


} // namespace scipp::math