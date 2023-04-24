/**
 * @file    math/meta.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-24
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace meta {


        // ===================================================
        // invert a type
        // ===================================================

            template <typename T>   
            struct invert {};

            template <typename T>
            using invert_t = typename invert<T>::_t;


            template <typename BASE_TYPE>
                requires (physics::is_base_v<BASE_TYPE>)
            struct invert<BASE_TYPE> {

                using _t = physics::base_quantity<-BASE_TYPE::length, 
                                                  -BASE_TYPE::time,
                                                  -BASE_TYPE::mass,
                                                  -BASE_TYPE::temperature,
                                                  -BASE_TYPE::elettric_current,
                                                  -BASE_TYPE::substance_amount,
                                                  -BASE_TYPE::luminous_intensity>;                                             

            };


            template <typename PREFIX_TYPE>
                requires (physics::is_prefix_v<PREFIX_TYPE>)
            struct invert<PREFIX_TYPE> {

                using _t = std::ratio<PREFIX_TYPE::den, PREFIX_TYPE::num>; 

            };


            template <typename UNIT_TYPE>
                requires (physics::is_unit_v<UNIT_TYPE>)
            struct invert<UNIT_TYPE> {

                using _t = physics::unit<invert_t<typename UNIT_TYPE::base_t>, invert_t<typename UNIT_TYPE::prefix_t>>;                                             

            };


            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            struct invert<MEAS_TYPE> {

                using _t = physics::measurement<invert_t<typename MEAS_TYPE::base_t>>;                                             

            };


            template <typename UMEAS_TYPE>
                requires (physics::is_umeasurement_v<UMEAS_TYPE>)
            struct invert<UMEAS_TYPE> {

                using _t = physics::umeasurement<invert_t<typename UMEAS_TYPE::base_t>>;                                             

            };


            template <typename CMEAS_TYPE>
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct invert<CMEAS_TYPE> {

                using _t = physics::cmeasurement<invert_t<typename CMEAS_TYPE::measurement_t>>;                                             

            };


            template <typename VEC_TYPE>
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct invert<VEC_TYPE> {

                using _t = geometry::vector<invert_t<typename VEC_TYPE::measurement_t>, VEC_TYPE::dim>;                                             

            };
            

        // ===================================================
        // multiply types
        // ===================================================

            template <typename T, typename... Ts>
            struct multiply {

                using _t = typename multiply<T, typename multiply<Ts...>::_t>::_t;

            };

            template <typename T>
            struct multiply<T> {

                using _t = T;

            };

            template <typename... Ts>
            using multiply_t = typename multiply<Ts...>::_t;  


            template <typename BASE_TYPE1, typename BASE_TYPE2>
                requires (physics::are_base_v<BASE_TYPE1, BASE_TYPE2>)
            struct multiply<BASE_TYPE1, BASE_TYPE2> {

                using _t = physics::base_quantity<BASE_TYPE1::length + BASE_TYPE2::length, 
                                                  BASE_TYPE1::time + BASE_TYPE2::time,
                                                  BASE_TYPE1::mass + BASE_TYPE2::mass,
                                                  BASE_TYPE1::temperature + BASE_TYPE2::temperature,
                                                  BASE_TYPE1::elettric_current + BASE_TYPE2::elettric_current,
                                                  BASE_TYPE1::substance_amount + BASE_TYPE2::substance_amount,
                                                  BASE_TYPE1::luminous_intensity + BASE_TYPE2::luminous_intensity>;                                             

            };


            template <typename PREFIX_TYPE1, typename PREFIX_TYPE2>
                requires (physics::are_prefix_v<PREFIX_TYPE1, PREFIX_TYPE2>)
            struct multiply<PREFIX_TYPE1, PREFIX_TYPE2> {

                using _t = std::ratio_multiply<PREFIX_TYPE1, PREFIX_TYPE2>; 

            };


            template <typename UNIT_TYPE1, typename UNIT_TYPE2>
                requires (physics::are_units_v<UNIT_TYPE1, UNIT_TYPE2>)
            struct multiply<UNIT_TYPE1, UNIT_TYPE2> {

                using _t = physics::unit<multiply_t<typename UNIT_TYPE1::base_t, typename UNIT_TYPE2::base_t>, 
                                         multiply_t<typename UNIT_TYPE1::prefix_t, typename UNIT_TYPE2::prefix_t>>;                                             

            };


            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (physics::are_measurements_v<MEAS_TYPE1, MEAS_TYPE2>)
            struct multiply<MEAS_TYPE1, MEAS_TYPE2> {

                using _t = physics::measurement<multiply_t<typename MEAS_TYPE1::base_t, typename MEAS_TYPE2::base_t>>;                                             

            };


            template <typename UMEAS_TYPE1, typename UMEAS_TYPE2>
                requires (physics::are_umeasurements_v<UMEAS_TYPE1, UMEAS_TYPE2>)
            struct multiply<UMEAS_TYPE1, UMEAS_TYPE2> {

                using _t = physics::umeasurement<multiply_t<typename UMEAS_TYPE1::base_t, typename UMEAS_TYPE2::base_t>>;                                             

            };


            template <typename CMEAS_TYPE1, typename CMEAS_TYPE2>
                requires (physics::are_cmeasurements_v<CMEAS_TYPE1, CMEAS_TYPE2>)
            struct multiply<CMEAS_TYPE1, CMEAS_TYPE2> {
                
                using _t = physics::cmeasurement<multiply_t<typename CMEAS_TYPE1::measurement_t, typename CMEAS_TYPE2::measurement_t>>;                                             

            };


            template <typename CMEAS_TYPE, typename MEAS_TYPE>
                requires (physics::is_cmeasurement_v<CMEAS_TYPE> && physics::is_measurement_v<MEAS_TYPE>)
            struct multiply<CMEAS_TYPE, MEAS_TYPE> {

                using _t = physics::cmeasurement<multiply_t<typename CMEAS_TYPE::measurement_t, MEAS_TYPE>>;                                             

            };


            template <typename MEAS_TYPE, typename CMEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE> && physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct multiply<MEAS_TYPE, CMEAS_TYPE> {

                using _t = physics::cmeasurement<multiply_t<MEAS_TYPE, typename CMEAS_TYPE::measurement_t>>;                                             

            };


            template <typename CMEAS_TYPE, typename UMEAS_TYPE>
                requires (physics::is_cmeasurement_v<CMEAS_TYPE> && physics::is_umeasurement_v<UMEAS_TYPE>)
            struct multiply<CMEAS_TYPE, UMEAS_TYPE> {

                using _t = physics::cmeasurement<multiply_t<typename CMEAS_TYPE::measurement_t, UMEAS_TYPE>>;                                             

            };


            template <typename UMEAS_TYPE, typename CMEAS_TYPE>
                requires (physics::is_umeasurement_v<UMEAS_TYPE> && physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct multiply<UMEAS_TYPE, CMEAS_TYPE> {

                using _t = physics::cmeasurement<multiply_t<UMEAS_TYPE, typename CMEAS_TYPE::measurement_t>>;                                             

            };


            template <typename MEAS_TYPE, typename UMEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE> && physics::is_umeasurement_v<UMEAS_TYPE>)
            struct multiply<MEAS_TYPE, UMEAS_TYPE> {

                using _t = physics::umeasurement<multiply_t<MEAS_TYPE, typename UMEAS_TYPE::base_t>>;                                             

            };


            template <typename UMEAS_TYPE, typename MEAS_TYPE>
                requires (physics::is_umeasurement_v<UMEAS_TYPE> && physics::is_measurement_v<MEAS_TYPE>)
            struct multiply<UMEAS_TYPE, MEAS_TYPE> {

                using _t = physics::umeasurement<multiply_t<typename UMEAS_TYPE::base_t, MEAS_TYPE>>;                                             

            };


        // ===================================================
        // divide type
        // ===================================================

            template <typename T1, typename T2>
            struct divide {};

            template <typename T1, typename T2>
            using divide_t = typename divide<T1, T2>::_t;  


            template <typename BASE_TYPE1, typename BASE_TYPE2>
                requires (physics::are_base_v<BASE_TYPE1, BASE_TYPE2>)
            struct divide<BASE_TYPE1, BASE_TYPE2> {

                using _t = physics::base_quantity<BASE_TYPE1::length - BASE_TYPE2::length, 
                                                  BASE_TYPE1::time - BASE_TYPE2::time,
                                                  BASE_TYPE1::mass - BASE_TYPE2::mass,
                                                  BASE_TYPE1::temperature - BASE_TYPE2::temperature,
                                                  BASE_TYPE1::elettric_current - BASE_TYPE2::elettric_current,
                                                  BASE_TYPE1::substance_amount - BASE_TYPE2::substance_amount,
                                                  BASE_TYPE1::luminous_intensity - BASE_TYPE2::luminous_intensity>;                                             

            };


            template <typename PREFIX_TYPE1, typename PREFIX_TYPE2>
                requires (physics::are_prefix_v<PREFIX_TYPE1, PREFIX_TYPE2>)
            struct divide<PREFIX_TYPE1, PREFIX_TYPE2> {

                using _t = std::ratio_divide<PREFIX_TYPE1, PREFIX_TYPE2>; 

            };


            template <typename UNIT_TYPE1, typename UNIT_TYPE2>
                requires (physics::are_units_v<UNIT_TYPE1, UNIT_TYPE2>)
            struct divide<UNIT_TYPE1, UNIT_TYPE2> {

                using _t = physics::unit<divide_t<typename UNIT_TYPE1::base_t, typename UNIT_TYPE2::base_t>, 
                                         divide_t<typename UNIT_TYPE1::prefix_t, typename UNIT_TYPE2::prefix_t>>;                                             

            };


            template <typename MEAS_TYPE1, typename MEAS_TYPE2>
                requires (physics::are_measurements_v<MEAS_TYPE1, MEAS_TYPE2>)
            struct divide<MEAS_TYPE1, MEAS_TYPE2> {

                using _t = physics::measurement<divide_t<typename MEAS_TYPE1::base_t, typename MEAS_TYPE2::base_t>>;                                             

            };


            template <typename UMEAS_TYPE1, typename UMEAS_TYPE2>
                requires (physics::are_umeasurements_v<UMEAS_TYPE1, UMEAS_TYPE2>)
            struct divide<UMEAS_TYPE1, UMEAS_TYPE2> {

                using _t = physics::umeasurement<divide_t<typename UMEAS_TYPE1::base_t, typename UMEAS_TYPE2::base_t>>;                                             

            };


            template <typename CMEAS_TYPE1, typename CMEAS_TYPE2>
                requires (physics::are_cmeasurements_v<CMEAS_TYPE1, CMEAS_TYPE2>)
            struct divide<CMEAS_TYPE1, CMEAS_TYPE2> {

                using _t = physics::cmeasurement<divide_t<typename CMEAS_TYPE1::measurement_t, typename CMEAS_TYPE2::measurement_t>>;                                             

            };


            template <typename CMEAS_TYPE, typename MEAS_TYPE>
                requires (physics::is_cmeasurement_v<CMEAS_TYPE> && physics::is_measurement_v<MEAS_TYPE>)
            struct divide<CMEAS_TYPE, MEAS_TYPE> {

                using _t = physics::cmeasurement<divide_t<typename CMEAS_TYPE::measurement_t, MEAS_TYPE>>;                                             

            };


            template <typename MEAS_TYPE, typename CMEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE> && physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct divide<MEAS_TYPE, CMEAS_TYPE> {

                using _t = physics::cmeasurement<divide_t<MEAS_TYPE, typename CMEAS_TYPE::measurement_t>>;                                             

            };


            template <typename CMEAS_TYPE, typename UMEAS_TYPE>
                requires (physics::is_cmeasurement_v<CMEAS_TYPE> && physics::is_umeasurement_v<UMEAS_TYPE>)
            struct divide<CMEAS_TYPE, UMEAS_TYPE> {

                using _t = physics::cmeasurement<divide_t<typename CMEAS_TYPE::measurement_t, UMEAS_TYPE>>;                                             

            };


            template <typename UMEAS_TYPE, typename CMEAS_TYPE>
                requires (physics::is_umeasurement_v<UMEAS_TYPE> && physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct divide<UMEAS_TYPE, CMEAS_TYPE> {

                using _t = physics::cmeasurement<divide_t<UMEAS_TYPE, typename CMEAS_TYPE::measurement_t>>;                                             

            };


            template <typename MEAS_TYPE, typename UMEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE> && physics::is_umeasurement_v<UMEAS_TYPE>)
            struct divide<MEAS_TYPE, UMEAS_TYPE> {
                
                using _t = physics::umeasurement<divide_t<MEAS_TYPE, typename UMEAS_TYPE::base_t>>;                                             

            };


            template <typename UMEAS_TYPE, typename MEAS_TYPE>
                requires (physics::is_umeasurement_v<UMEAS_TYPE> && physics::is_measurement_v<MEAS_TYPE>)
            struct divide<UMEAS_TYPE, MEAS_TYPE> {

                using _t = physics::umeasurement<divide_t<typename UMEAS_TYPE::base_t, MEAS_TYPE>>;                                             

            };


        // ===================================================
        // take the power of a type
        // ===================================================

            template <typename T, std::size_t POWER>    
            struct power {};

            template <typename T, std::size_t POWER>
            using power_t = typename power<T, POWER>::_t;

            template <typename T>
            using square_t = power_t<T, 2>;

            template <typename T>
            using cube_t = power_t<T, 3>;


            template <typename BASE_TYPE, std::size_t POWER>
                requires (physics::is_base_v<BASE_TYPE>)
            struct power<BASE_TYPE, POWER> {

                using _t = physics::base_quantity<static_cast<int>(BASE_TYPE::length * POWER), 
                                                  static_cast<int>(BASE_TYPE::time * POWER),
                                                  static_cast<int>(BASE_TYPE::mass * POWER),
                                                  static_cast<int>(BASE_TYPE::temperature * POWER),
                                                  static_cast<int>(BASE_TYPE::elettric_current * POWER),
                                                  static_cast<int>(BASE_TYPE::substance_amount * POWER),
                                                  static_cast<int>(BASE_TYPE::luminous_intensity * POWER)>;

            };


            /// @brief Struct to compute the power of an std::ratio
            template <typename PREFIX_TYPE, std::size_t POWER>
                requires (physics::is_prefix_v<PREFIX_TYPE>)
            struct power<PREFIX_TYPE, POWER> {

                static constexpr auto value = std::pow(PREFIX_TYPE::num, POWER);
                static constexpr auto denom_pow = std::pow(PREFIX_TYPE::den, POWER);
                static constexpr std::size_t denom = denom_pow;
                static_assert(value <= std::numeric_limits<std::size_t>::max() / denom, "Overflow in constant expression");

                using _t = std::ratio<static_cast<std::size_t>(value), denom>;

            };

            template <typename UNIT_TYPE, std::size_t POWER>
                requires (physics::is_unit_v<UNIT_TYPE>)
            struct power<UNIT_TYPE, POWER> {

                using _t = physics::unit<power_t<typename UNIT_TYPE::base_t, POWER>, 
                                         power_t<typename UNIT_TYPE::prefix_t, POWER>>;

            };
        

            template <typename MEAS_TYPE, std::size_t POWER>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            struct power<MEAS_TYPE, POWER> {

                using _t = physics::measurement<power_t<typename MEAS_TYPE::base_t, POWER>>;

            };


            template <typename UMEAS_TYPE, std::size_t POWER>
                requires (physics::is_umeasurement_v<UMEAS_TYPE>)
            struct power<UMEAS_TYPE, POWER> {

                using _t = physics::umeasurement<power_t<typename UMEAS_TYPE::base_t, POWER>>;

            };


            template <typename CMEAS_TYPE, std::size_t POWER>
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct power<CMEAS_TYPE, POWER> {

                using _t = physics::cmeasurement<power_t<typename CMEAS_TYPE::measurement_t, POWER>>;

            };
    

        // ===================================================
        // take the root of a type
        // ===================================================

            template <typename T, std::size_t POWER>    
            struct root {};

            template <typename T, std::size_t POWER>
            using root_t = typename root<T, POWER>::_t;

            template <typename T>
            using sqrt_t = root_t<T, 2>;

            template <typename T>
            using cbrt_t = root_t<T, 3>;


            template <typename BASE_TYPE, std::size_t POWER>
                requires (physics::is_base_v<BASE_TYPE>)
            struct root<BASE_TYPE, POWER> {

                using _t = physics::base_quantity<static_cast<int>(BASE_TYPE::length / POWER), 
                                                  static_cast<int>(BASE_TYPE::time / POWER),
                                                  static_cast<int>(BASE_TYPE::mass / POWER),
                                                  static_cast<int>(BASE_TYPE::temperature / POWER),
                                                  static_cast<int>(BASE_TYPE::elettric_current / POWER),
                                                  static_cast<int>(BASE_TYPE::substance_amount / POWER),
                                                  static_cast<int>(BASE_TYPE::luminous_intensity / POWER)>;

            };


            template <typename PREFIX_TYPE, std::size_t POWER>
                requires (physics::is_prefix_v<PREFIX_TYPE>)
            struct root<PREFIX_TYPE, POWER> {

                static constexpr auto num_pow = std::pow(PREFIX_TYPE::num, 1. / POWER);
                static_assert(num_pow <= std::numeric_limits<std::size_t>::max(), "Overflow in constant expression");
                static constexpr auto denom_pow = std::pow(PREFIX_TYPE::den, 1. / POWER);

                using _t = std::ratio<static_cast<std::size_t>(num_pow), static_cast<std::size_t>(denom_pow)>;

            };
            

            template <typename UNIT_TYPE, std::size_t POWER>
                requires (physics::is_unit_v<UNIT_TYPE>)
            struct root<UNIT_TYPE, POWER> {

                using _t = physics::unit<root_t<typename UNIT_TYPE::base_t, POWER>, 
                                         root_t<typename UNIT_TYPE::prefix_t, POWER>>;

            };


            template <typename MEAS_TYPE, std::size_t POWER>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            struct root<MEAS_TYPE, POWER> {

                using _t = physics::measurement<root_t<typename MEAS_TYPE::base_t, POWER>>;

            };


            template <typename UMEAS_TYPE, std::size_t POWER>
                requires (physics::is_umeasurement_v<UMEAS_TYPE>)
            struct root<UMEAS_TYPE, POWER> {

                using _t = physics::umeasurement<root_t<typename UMEAS_TYPE::base_t, POWER>>;

            };


            template <typename CMEAS_TYPE, std::size_t POWER>
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct root<CMEAS_TYPE, POWER> {

                using _t = physics::cmeasurement<root_t<typename CMEAS_TYPE::measurement_t, POWER>>;

            };


    }
    

} // namespace scipp::math