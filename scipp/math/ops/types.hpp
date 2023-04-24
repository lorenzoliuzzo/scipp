/**
 * @file    math/ops/types.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-24
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    
    
    namespace op {


        // ====================================================================================================
        // operations on types
        // ====================================================================================================

            template <typename MEAS_TYPE>   
            struct invert {};

            template <typename MEAS_TYPE>
            using invert_t = typename invert<MEAS_TYPE>::_t;


            template <typename MEAS_TYPE, typename... MEAS_TYPEs>
            struct multiply {};

            template <typename MEAS_TYPE>
            struct multiply<MEAS_TYPE> {

                using _t = MEAS_TYPE;

            };

            template <typename... MEAS_TYPEs>
            using multiply_t = typename multiply<MEAS_TYPEs...>::_t;         


            template <typename MEAS_TYPE, typename... MEAS_TYPEs>
            struct divide {};

            template <typename MEAS_TYPE>
            struct divide<MEAS_TYPE> {

                using _t = MEAS_TYPE;

            };

            template <typename... MEAS_TYPEs>
            using divide_t = typename divide<MEAS_TYPEs...>::_t;         


            template <typename MEAS_TYPE, std::size_t POWER>    
            struct power {};

            template <typename MEAS_TYPE, std::size_t POWER>
            using power_t = typename power<MEAS_TYPE, POWER>::_t;

            template <typename MEAS_TYPE>
            using square_t = power_t<MEAS_TYPE, 2>;

            template <typename MEAS_TYPE>
            using cube_t = power_t<MEAS_TYPE, 3>;


            template <typename MEAS_TYPE, std::size_t POWER>    
            struct root_power {};

            template <typename MEAS_TYPE, std::size_t POWER>
            using root_power_t = typename root_power<MEAS_TYPE, POWER>::_t;

            template <typename MEAS_TYPE>
            using sqrt_t = root_power_t<MEAS_TYPE, 2>;

            template <typename MEAS_TYPE>
            using cbrt_t = root_power_t<MEAS_TYPE, 3>;


    } // namespace op


} // namespace scipp::math