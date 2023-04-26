/**
 * @file    math/function/mathematical.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-26
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace meta {

        // ===================================================
        // invert a type
        // ===================================================

            template <typename T>   
            struct invert;

            template <typename T>
            struct inv_impl;

            template <typename T>
            using invert_t = typename invert<T>::_t;


            // @brief Invert a physics::base_quantity
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


            /// @brief Invert a prefix
            template <typename PREFIX_TYPE>
                requires (physics::is_prefix_v<PREFIX_TYPE>)
            struct invert<PREFIX_TYPE> {

                using _t = std::ratio<PREFIX_TYPE::den, PREFIX_TYPE::num>; 

            };

            template <typename PREFIX_TYPE>
                requires (physics::is_prefix_v<PREFIX_TYPE>)
            struct inv_impl<PREFIX_TYPE> : unary_function<invert_t<PREFIX_TYPE>, PREFIX_TYPE> {

                constexpr invert_t<PREFIX_TYPE> f(const PREFIX_TYPE&) const noexcept override {

                    return {};  

                }

            };


            /// @brief Invert an unit of measurement
            template <typename UNIT_TYPE>
                requires (physics::is_unit_v<UNIT_TYPE>)
            struct invert<UNIT_TYPE> {

                using _t = physics::unit<invert_t<typename UNIT_TYPE::base_t>, invert_t<typename UNIT_TYPE::prefix_t>>;                                             

            };

            template <typename UNIT_TYPE>
                requires (physics::is_unit_v<UNIT_TYPE>)
            struct inv_impl<UNIT_TYPE> : unary_function<invert_t<UNIT_TYPE>, UNIT_TYPE> {

                constexpr invert_t<UNIT_TYPE> f(const UNIT_TYPE&) const noexcept override {

                    return {};  

                }

            };


            /// @brief Invert a measurement
            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            struct invert<MEAS_TYPE> {

                using _t = physics::measurement<invert_t<typename MEAS_TYPE::base_t>>;                                             

            };

            template <typename MEAS_TYPE>  
                requires (physics::is_measurement_v<MEAS_TYPE>)
            struct inv_impl<MEAS_TYPE> : unary_function<invert_t<MEAS_TYPE>, MEAS_TYPE> {

                constexpr invert_t<MEAS_TYPE> f(const MEAS_TYPE& x) const override {

                    if (x == MEAS_TYPE::zero) 
                        throw std::domain_error("Cannot invert a zero measurement"); 

                    return 1. / x.value; 

                }

            };


            template <typename UMEAS_TYPE>
                requires (physics::is_umeasurement_v<UMEAS_TYPE>)
            struct invert<UMEAS_TYPE> {

                using _t = physics::umeasurement<invert_t<typename UMEAS_TYPE::base_t>>;                                             

            };


            /// @brief Invert a cmeasurement
            template <typename CMEAS_TYPE>
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct invert<CMEAS_TYPE> {

                using _t = physics::cmeasurement<invert_t<typename CMEAS_TYPE::measurement_t>>;                                             

            };

            template <typename CMEAS_TYPE>  
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct inv_impl<CMEAS_TYPE> : unary_function<invert_t<CMEAS_TYPE>, CMEAS_TYPE> {

                constexpr invert_t<CMEAS_TYPE> f(const CMEAS_TYPE& x) const override {

                    if (x == CMEAS_TYPE::zero) 
                        throw std::domain_error("Cannot invert a zero cmeasurement"); 

                    return 1. / x; 

                }

            };


            /// @brief Invert a vector
            template <typename VEC_TYPE>
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct invert<VEC_TYPE> {

                using _t = geometry::vector<invert_t<typename VEC_TYPE::measurement_t>, VEC_TYPE::dim>;                                             

            };
            
            template <typename VEC_TYPE>  
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct inv_impl<VEC_TYPE> : unary_function<invert_t<VEC_TYPE>, VEC_TYPE> {

                constexpr invert_t<VEC_TYPE> f(const VEC_TYPE& other) const override {

                    using measurement_t = typename VEC_TYPE::measurement_t;

                    invert_t<VEC_TYPE> result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) {
                        if (other[i] == measurement_t::zero) 
                            throw std::domain_error("Cannot invert a vector because one of its component is zero"); 
                        result[i] = 1. / other[i];
                    }

                    return result;

                }

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


            // @brief Multiply two physics::base_quantity types
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


            template <typename VEC_TYPE, typename MEAS_TYPE>
                requires (geometry::is_vector_v<VEC_TYPE> && physics::is_generic_measurement_v<MEAS_TYPE>)
            struct multiply<VEC_TYPE, MEAS_TYPE> {

                using _t = geometry::vector<multiply_t<typename VEC_TYPE::measurement_t, MEAS_TYPE>, VEC_TYPE::dim>;                                             

            };


            template <typename MEAS_TYPE, typename VEC_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && geometry::is_vector_v<VEC_TYPE>)
            struct multiply<MEAS_TYPE, VEC_TYPE> {

                using _t = geometry::vector<multiply_t<MEAS_TYPE, typename VEC_TYPE::measurement_t>, VEC_TYPE::dim>;                                             

            };


            template <typename T, typename NUMBER_TYPE>
                requires ((physics::is_generic_measurement_v<T> || geometry::is_vector_v<T>) && 
                          is_number_v<NUMBER_TYPE>)
            struct multiply<T, NUMBER_TYPE> {

                using _t = T; 

            };

            template <typename NUMBER_TYPE, typename T>
                requires (is_number_v<NUMBER_TYPE> && 
                          (physics::is_generic_measurement_v<T> || geometry::is_vector_v<T>))
            struct multiply<NUMBER_TYPE, T> {

                using _t = T; 
                
            };


        // ===================================================
        // divide type
        // ===================================================

            template <typename T1, typename T2>
            struct divide;

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


            template <typename VEC_TYPE, typename MEAS_TYPE>
                requires (geometry::is_vector_v<VEC_TYPE> && physics::is_generic_measurement_v<MEAS_TYPE>)
            struct divide<VEC_TYPE, MEAS_TYPE> {

                using _t = geometry::vector<divide_t<typename VEC_TYPE::measurement_t, MEAS_TYPE>, VEC_TYPE::dim>;                                             

            };


            template <typename MEAS_TYPE, typename VEC_TYPE>
                requires (physics::is_generic_measurement_v<MEAS_TYPE> && geometry::is_vector_v<VEC_TYPE>)
            struct divide<MEAS_TYPE, VEC_TYPE> {

                using _t = geometry::vector<divide_t<MEAS_TYPE, typename VEC_TYPE::measurement_t>, VEC_TYPE::dim>;                                             

            };


            template <typename T, typename NUMBER_TYPE>
                requires ((physics::is_generic_measurement_v<T> || geometry::is_vector_v<T>) && 
                          is_number_v<NUMBER_TYPE>)
            struct divide<T, NUMBER_TYPE> {

                using _t = T; 

            };

            template <typename NUMBER_TYPE, typename T>
                requires (is_number_v<NUMBER_TYPE> && 
                          (physics::is_generic_measurement_v<T> || geometry::is_vector_v<T>))
            struct divide<NUMBER_TYPE, T> {

                using _t = invert_t<T>; 
                
            };


        // ===================================================
        // take the power of a type
        // ===================================================

            template <typename T, uint POWER>    
            struct pow;

            template <typename T, uint POWER>
            struct pow_impl;


            template <typename T, uint POWER>
            using pow_t = typename pow<T, POWER>::_t;


            /// @brief Power of an physics::base_quantity
            template <typename BASE_TYPE, uint POWER>
                requires (physics::is_base_v<BASE_TYPE>)
            struct pow<BASE_TYPE, POWER> {

                using _t = physics::base_quantity<static_cast<int>(BASE_TYPE::length * POWER), 
                                                  static_cast<int>(BASE_TYPE::time * POWER),
                                                  static_cast<int>(BASE_TYPE::mass * POWER),
                                                  static_cast<int>(BASE_TYPE::temperature * POWER),
                                                  static_cast<int>(BASE_TYPE::elettric_current * POWER),
                                                  static_cast<int>(BASE_TYPE::substance_amount * POWER),
                                                  static_cast<int>(BASE_TYPE::luminous_intensity * POWER)>;

            };


            /// @brief Power of a prefix
            template <typename PREFIX_TYPE, uint POWER>
                requires (physics::is_prefix_v<PREFIX_TYPE>)
            struct pow<PREFIX_TYPE, POWER> {

                static constexpr auto value = std::pow(PREFIX_TYPE::num, POWER);
                static constexpr auto denom_pow = std::pow(PREFIX_TYPE::den, POWER);
                static constexpr std::size_t denom = denom_pow;
                static_assert(value <= std::numeric_limits<std::size_t>::max() / denom, "Overflow in constant expression");

                using _t = std::ratio<static_cast<std::size_t>(value), denom>;

            };

            template <typename PREFIX_TYPE, uint POWER>
                requires (physics::is_prefix_v<PREFIX_TYPE>)
            struct pow_impl<PREFIX_TYPE, POWER> : unary_function<pow_t<PREFIX_TYPE, POWER>, PREFIX_TYPE> {

                constexpr pow_t<PREFIX_TYPE, POWER> f(const PREFIX_TYPE&) const noexcept override {

                    return {};  

                }

            };


            /// @brief Power of an unit of measurement
            template <typename UNIT_TYPE, uint POWER>
                requires (physics::is_unit_v<UNIT_TYPE>)
            struct pow<UNIT_TYPE, POWER> {

                using _t = physics::unit<pow_t<typename UNIT_TYPE::base_t, POWER>, 
                                         pow_t<typename UNIT_TYPE::prefix_t, POWER>>;

            };

            template <typename UNIT_TYPE, uint POWER>
                requires (physics::is_unit_v<UNIT_TYPE>)
            struct pow_impl<UNIT_TYPE, POWER> : unary_function<pow_t<UNIT_TYPE, POWER>, UNIT_TYPE> {

                constexpr pow_t<UNIT_TYPE, POWER> f(const UNIT_TYPE&) const noexcept override {

                    return {};  

                }

            };


            /// @brief Power of a number
            template <typename NUMBER_TYPE, uint POWER>
                requires (is_number_v<NUMBER_TYPE>)
            struct pow<NUMBER_TYPE, POWER> {

                using _t = NUMBER_TYPE; 

            };

            template <typename NUMBER_TYPE, uint POWER>
                requires (is_number_v<NUMBER_TYPE>)
            struct pow_impl<NUMBER_TYPE, POWER> : unary_function<NUMBER_TYPE, NUMBER_TYPE> {

                constexpr NUMBER_TYPE f(const NUMBER_TYPE& x) const noexcept override {

                    return std::pow(static_cast<double>(x), POWER); 

                }

            };
                

            /// @brief Power of a measurement
            template <typename MEAS_TYPE, uint POWER>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            struct pow<MEAS_TYPE, POWER> {

                using _t = physics::measurement<pow_t<typename MEAS_TYPE::base_t, POWER>>;

            };

            template <typename MEAS_TYPE, uint POWER>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            struct pow_impl<MEAS_TYPE, POWER> : unary_function<pow_t<MEAS_TYPE, POWER>, MEAS_TYPE> {

                constexpr pow_t<MEAS_TYPE, POWER> f(const MEAS_TYPE& x) const noexcept override {

                    return std::pow(x.value, POWER); 

                }

            };


            /// @todo 
            /// @brief Power of a umeasurement
            template <typename UMEAS_TYPE, uint POWER>
                requires (physics::is_umeasurement_v<UMEAS_TYPE>)
            struct pow<UMEAS_TYPE, POWER> {

                using _t = physics::umeasurement<pow_t<typename UMEAS_TYPE::base_t, POWER>>;

            };


            /// @brief Power of a cmeasurement
            template <typename CMEAS_TYPE, uint POWER>
                requires (physics::is_scalar_cmeasurement_v<CMEAS_TYPE>)
            struct pow_impl<CMEAS_TYPE, POWER> : unary_function<pow_t<CMEAS_TYPE, POWER>, CMEAS_TYPE> {

                constexpr pow_t<CMEAS_TYPE, POWER> f(const CMEAS_TYPE& other) const noexcept override {

                    const auto z = op::log(other);
                    return CMEAS_TYPE::polar(op::exp(POWER * z.real), POWER * z.imag);

                }

            };

            template <typename CMEAS_TYPE, uint POWER>
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct pow<CMEAS_TYPE, POWER> {

                using _t = physics::cmeasurement<pow_t<typename CMEAS_TYPE::measurement_t, POWER>>;

            };
    

            template <typename T, typename U>   
            struct pow_impl2; 

            template <typename CMEAS_TYPE1, typename CMEAS_TYPE2>
                requires (physics::are_scalar_cmeasurements_v<CMEAS_TYPE1, CMEAS_TYPE2>)
            struct pow_impl2<CMEAS_TYPE1, CMEAS_TYPE2> : binary_function<CMEAS_TYPE1, CMEAS_TYPE1, CMEAS_TYPE2> {

                constexpr CMEAS_TYPE1 f(const CMEAS_TYPE1& base, const CMEAS_TYPE2& exp) const noexcept override {
                    
                    return (base == CMEAS_TYPE1()) ? CMEAS_TYPE1() : op::exp(exp * op::log(base));

                }

            };


            /// @brief Power of a geometry::vector
            template <typename VEC_TYPE, uint POWER>
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct pow<VEC_TYPE, POWER> {

                using _t = geometry::vector<pow_t<typename VEC_TYPE::measurement_t, POWER>, VEC_TYPE::dim>;

            };

            template <typename VEC_TYPE, uint POWER>
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct pow_impl<VEC_TYPE, POWER> : unary_function<pow_t<VEC_TYPE, POWER>, VEC_TYPE> {

                constexpr pow_t<VEC_TYPE, POWER> f(const VEC_TYPE& other) const noexcept override {

                    pow_t<VEC_TYPE, POWER> result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::pow<POWER>(other[i]);

                    return result;

                }

            };


            // template <typename T>    
            // struct square_impl;

            // template <typename T>    
            // struct cube_impl;

            template <typename T>
            using square_t = pow_t<T, 2>;

            template <typename T>
            using cube_t = pow_t<T, 3>;




        // ===================================================
        // take the root of a type
        // ===================================================

            template <typename T, uint POWER>    
            struct root;

            template <typename T, uint POWER>    
            struct root_impl;

            template <typename T, uint POWER>
            using root_t = typename root<T, POWER>::_t;


            template <typename T>    
            struct sqrt_impl;

            template <typename T>    
            struct cbrt_impl;

            template <typename T>
            using sqrt_t = root_t<T, 2>;

            template <typename T>
            using cbrt_t = root_t<T, 3>;


            /// @brief Root power of a base_quantity
            template <typename BASE_TYPE, uint POWER>
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


            /// @brief Root power of a prefix
            template <typename PREFIX_TYPE, uint POWER>
                requires (physics::is_prefix_v<PREFIX_TYPE>)
            struct root<PREFIX_TYPE, POWER> {

                static constexpr auto num_pow = std::pow(PREFIX_TYPE::num, 1. / POWER);
                static_assert(num_pow <= std::numeric_limits<std::size_t>::max(), "Overflow in constant expression");
                static constexpr auto denom_pow = std::pow(PREFIX_TYPE::den, 1. / POWER);

                using _t = std::ratio<static_cast<std::size_t>(num_pow), static_cast<std::size_t>(denom_pow)>;

            };
            
            template <typename PREFIX_TYPE, uint POWER>
                requires (physics::is_prefix_v<PREFIX_TYPE>)
            struct root_impl<PREFIX_TYPE, POWER> : unary_function<root_t<PREFIX_TYPE, POWER>, PREFIX_TYPE> {

                constexpr root_t<PREFIX_TYPE, POWER> f(const PREFIX_TYPE&) const noexcept override {

                    return {};  

                }

            };


            /// @brief Root power of an unit
            template <typename UNIT_TYPE, uint POWER>
                requires (physics::is_unit_v<UNIT_TYPE>)
            struct root<UNIT_TYPE, POWER> {

                using _t = physics::unit<root_t<typename UNIT_TYPE::base_t, POWER>, 
                                         root_t<typename UNIT_TYPE::prefix_t, POWER>>;

            };

            template <typename UNIT_TYPE, uint POWER>
                requires (physics::is_unit_v<UNIT_TYPE>)
            struct root_impl<UNIT_TYPE, POWER> : unary_function<root_t<UNIT_TYPE, POWER>, UNIT_TYPE> {

                constexpr root_t<UNIT_TYPE, POWER> f(const UNIT_TYPE&) const noexcept override {

                    return {};  

                }

            };


            /// @brief Root power of a number
            template <typename NUMBER_TYPE, uint POWER>
                requires (is_number_v<NUMBER_TYPE>)
            struct root<NUMBER_TYPE, POWER> {

                using _t = NUMBER_TYPE; 

            };

            template <typename NUMBER_TYPE, uint POWER>
                requires (is_number_v<NUMBER_TYPE>)
            struct root_impl<NUMBER_TYPE, POWER> : unary_function<NUMBER_TYPE, NUMBER_TYPE> {

                constexpr NUMBER_TYPE f(const NUMBER_TYPE& x) const noexcept override {

                    return std::pow(static_cast<double>(x), 1. / static_cast<double>(POWER)); 

                }

            };
                

            /// @brief Root power of a measurement
            template <typename MEAS_TYPE, uint POWER>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            struct root<MEAS_TYPE, POWER> {

                using _t = physics::measurement<root_t<typename MEAS_TYPE::base_t, POWER>>;

            };

            template <typename MEAS_TYPE, uint POWER>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            struct root_impl<MEAS_TYPE, POWER> : unary_function<root_t<MEAS_TYPE, POWER>, MEAS_TYPE> {

                constexpr root_t<MEAS_TYPE, POWER> f(const MEAS_TYPE& x) const noexcept override {

                    return std::pow(x.value, 1. / static_cast<double>(POWER)); 

                }

            };


            template <typename UMEAS_TYPE, uint POWER>
                requires (physics::is_umeasurement_v<UMEAS_TYPE>)
            struct root<UMEAS_TYPE, POWER> {

                using _t = physics::umeasurement<root_t<typename UMEAS_TYPE::base_t, POWER>>;

            };


            template <typename CMEAS_TYPE, uint POWER>
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct root<CMEAS_TYPE, POWER> {

                using _t = physics::cmeasurement<root_t<typename CMEAS_TYPE::measurement_t, POWER>>;

            };


            template <typename VEC_TYPE, uint POWER>
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct root<VEC_TYPE, POWER> {

                using _t = geometry::vector<root_t<typename VEC_TYPE::measurement_t, POWER>, VEC_TYPE::dim>;

            };
    
            template <typename VEC_TYPE, uint POWER>
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct root_impl<VEC_TYPE, POWER> : unary_function<root_t<VEC_TYPE, POWER>, VEC_TYPE> {

                constexpr root_t<VEC_TYPE, POWER> f(const VEC_TYPE& other) const noexcept override {

                    root_t<VEC_TYPE, POWER> result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::root<POWER>(other[i]);

                    return result;

                }

            };


        // ====================================================
        // ABS
        // ====================================================

            template <typename T>
            struct abs_impl;


            template <typename T>  
                requires (is_number_v<T> || physics::is_measurement_v<T> || physics::is_umeasurement_v<T>)
            struct abs_impl<T> : unary_function<T, T> {

                constexpr T f(const T& x) const noexcept override {

                    return (x > T{}) ? x : -x; 

                }

            };


            template <typename CMEAS_TYPE>  
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct abs_impl<CMEAS_TYPE> : unary_function<square_t<typename CMEAS_TYPE::measurement_t>, CMEAS_TYPE> {

                constexpr square_t<typename CMEAS_TYPE::measurement_t> f(const CMEAS_TYPE& x) const noexcept override {

                    return op::square(x.real) + op::square(x.imag);

                }

            };
             

            template <typename VEC_TYPE>  
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct abs_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {


            constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                using measurement_t = typename VEC_TYPE::measurement_t;

                VEC_TYPE result{};
                for (std::size_t i{}; i < VEC_TYPE::dim; ++i) {
                    measurement_t x = other[i];
                    result[i] = (x > measurement_t::zero) ? x : -x;
                }

                return result;

            }

        };


        // ====================================================
        // INV -> @todo umeasurement
        // ====================================================

        // ====================================================
        // POW -> @todo umeasurement, complex^complex
        // ====================================================

        // ====================================================
        // ROOT
        // ====================================================
            
        // ====================================================
        // exp_impl
        // ====================================================
            
            template <typename T>
            struct exp_impl;


            template <typename MEAS_TYPE>
                requires (physics::is_measurement_v<MEAS_TYPE>)
            struct exp_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const noexcept override {
                    
                    return std::exp(other); 

                }

            };


            template <typename CMEAS_TYPE>
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct exp_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {
                    
                    auto rho = op::exp(other.real); 
                    return { rho * op::cos(other.imag), rho * op::sin(other.imag) };

                }

            };


            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct exp_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::exp(other[i]);

                    return result;

                }

            };


        // ====================================================
        // log_impl
        // ====================================================
            
            template <typename T>
            struct log_impl;


            template <typename MEAS_TYPE>
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct log_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const override {
                    
                    return std::log(other); 

                }

            };


            template <typename CMEAS_TYPE>
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct log_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {   
                    
                    return { std::log(op::abs(other)), other.arg() };

                }

            };


            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct log_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::log(other[i]);

                    return result; 

                }

            };


        // ====================================================
        // SIN
        // ====================================================

            template <typename T>
            struct sin_impl;

            template <typename MEAS_TYPE>  
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct sin_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const noexcept override {

                    return std::sin(other); 

                }

            };


            template <typename CMEAS_TYPE>  
                requires (physics::is_scalar_cmeasurement_v<CMEAS_TYPE>)
            struct sin_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {

                    return { std::sin(other.real) * std::cosh(other.imag), 
                             std::cos(other.real) * std::sinh(other.imag) };

                }

            };


            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct sin_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::sin(other[i]);

                    return result; 
                    
                }

            };


        // ====================================================
        // COS
        // ====================================================

            template <typename T>
            struct cos_impl;


            template <typename MEAS_TYPE>  
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct cos_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const noexcept override {

                    return std::cos(other); 

                }

            };


            template <typename CMEAS_TYPE>  
                requires (physics::is_scalar_cmeasurement_v<CMEAS_TYPE>)
            struct cos_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {

                    return { std::cos(other.real) * std::cosh(other.imag), 
                            -std::sin(other.real) * std::sinh(other.imag) };

                }

            };


            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct cos_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::cos(other[i]);

                    return result; 
                    
                }

            };


        // ====================================================
        // TAN
        // ====================================================

            template <typename T>
            struct tan_impl;

            template <typename MEAS_TYPE>  
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct tan_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const noexcept override {

                    return std::tan(other); 

                }

            };


            template <typename CMEAS_TYPE>  
                requires (is_number_v<CMEAS_TYPE> && physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct tan_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {
                    
                    using measurement_t = typename CMEAS_TYPE::measurement_t;

                    if (other.imag == measurement_t::zero)
                        return op::tan(other.real);

                    else if (other.real == measurement_t::zero)
                        return { measurement_t::zero, std::tanh(other.imag) };

                    else if (other.real == measurement_t::pi / 2) {
                        std::cerr << "Cannot compute tan of " << other << "\n";
                        throw std::domain_error(); 
                    }

                    else return op::sin(other) / op::cos(other);

                }

            };


            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct tan_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::tan(other[i]);

                    return result; 
                    
                }

            };


        // ====================================================
        // SIN
        // ====================================================
            
            template <typename T>
            struct sinh_impl;


            template <typename MEAS_TYPE>  
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct sinh_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const noexcept override {

                    return std::sinh(other); 

                }

            };


            template <typename CMEAS_TYPE>  
                requires (is_number_v<CMEAS_TYPE> && physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct sinh_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {
                    
                    return { std::sinh(other.real) * std::cos(other.imag), 
                             std::cosh(other.real) * std::sin(other.imag) };

                }

            };


            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct sinh_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::sinh(other[i]);

                    return result; 
                    
                }

            };


        // ====================================================
        // COSH
        // ====================================================
            
            template <typename T>
            struct cosh_impl;


            template <typename MEAS_TYPE>  
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct cosh_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const noexcept override {

                    return std::cosh(other); 

                }

            };


            template <typename CMEAS_TYPE>  
                requires (is_number_v<CMEAS_TYPE> && physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct cosh_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {
                    
                    return { std::cosh(other.real) * std::cos(other.imag), 
                             std::sinh(other.real) * std::sin(other.imag) };

                }

            };


            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct cosh_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::cosh(other[i]);

                    return result; 
                    
                }

            };


        // ====================================================
        // TANH
        // ====================================================
            
            template <typename T>
            struct tanh_impl;


            template <typename MEAS_TYPE>  
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct tanh_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const noexcept override {

                    return std::tanh(other); 

                }

            };
            
            
            template <typename CMEAS_TYPE>  
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct tanh_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {
                    
                    return op::sinh(other) / op::cosh(other);

                }

            };


            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct tanh_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::tanh(other[i]);

                    return result; 
                    
                }

            };


        // ====================================================
        // ASIN
        // ====================================================
            
            template <typename T>
            struct asin_impl;


            template <typename MEAS_TYPE>  
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct asin_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const noexcept override {

                    return std::asin(other); 

                }

            };


            template <typename CMEAS_TYPE>  
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct asin_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {

                    auto z = op::asinh(CMEAS_TYPE(-other.imag, other.real));
                    return { z.imag, -z.real };

                }

            };


            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct asin_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::asin(other[i]);

                    return result; 
                    
                }

            };

        // ====================================================
        // ACOS
        // ====================================================
            
            template <typename T>
            struct acos_impl;


            template <typename MEAS_TYPE>  
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct acos_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const noexcept override {

                    return std::acos(other); 

                }

            };


            template <typename CMEAS_TYPE>  
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct acos_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {

                    auto z = op::asin(other);
                    return { M_PI_2 - z.real, -z.imag };

                }

            };


            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct acos_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::acos(other[i]);

                    return result; 
                    
                }

            };


        // ====================================================
        // ATAN
        // ====================================================
            
            template <typename T>
            struct atan_impl;


            template <typename MEAS_TYPE>  
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct atan_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const noexcept override {

                    return std::atan(other); 

                }

            };


            template <typename CMEAS_TYPE>  
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct atan_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {
                    
                    using measurement_t = typename CMEAS_TYPE::measurement_t;
                    
                    const auto r2 = op::square(other.real);
                    const auto x = square_t<measurement_t>::one - r2 - op::square(other.imag);

                    return { op::atan(CMEAS_TYPE(2.0) * other.real / (2.0 * x)), 
                             op::log((r2 + op::square(other.imag + measurement_t::one)) / (other.imag - measurement_t::one)) / 4.0 };
                        
                }

            };


            template <typename T>
            struct atan_impl2; 


            template <typename MEAS_TYPE>  
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct atan_impl2<MEAS_TYPE> : binary_function<MEAS_TYPE, MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& y, const MEAS_TYPE& x) const noexcept override {

                    return std::atan2(y, x); 

                }

            };


            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct atan_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::atan(other[i]);

                    return result; 
                    
                }

            };


        // ====================================================
        // ASINH
        // ====================================================
            
            template <typename T>
            struct asinh_impl;


            template <typename MEAS_TYPE>  
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct asinh_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const noexcept override {

                    return std::asinh(other); 

                }

            };


            template <typename CMEAS_TYPE>  
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct asinh_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {

                    using measurement_t = typename CMEAS_TYPE::measurement_t;
                    
                    square_t<CMEAS_TYPE> z((other.real - other.imag) * (other.real + other.imag) + square_t<measurement_t>::one, 2.0 * other.real * other.imag);

                    return op::log(op::sqrt(z) + other);

                }

            };
            

            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct asinh_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::asinh(other[i]);

                    return result; 
                    
                }

            };


        // ====================================================
        // ACOSH
        // ====================================================
            
            template <typename T>
            struct acosh_impl;


            template <typename MEAS_TYPE>  
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct acosh_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const noexcept override {

                    return std::acosh(other); 

                }

            };


            template <typename CMEAS_TYPE>  
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct acosh_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {

                    using measurement_t = typename CMEAS_TYPE::measurement_t;

                    return 2.0 * op::log(op::sqrt(0.5 * (other + measurement_t::one)) + op::sqrt(0.5 * (other - measurement_t::one)));

                }

            };


            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct acosh_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::acosh(other[i]);

                    return result; 
                    
                }

            };


        // ====================================================
        // ATANH
        // ====================================================
            
            template <typename T>
            struct atanh_impl;


            template <typename MEAS_TYPE>  
                requires (is_number_v<MEAS_TYPE> || physics::is_measurement_v<MEAS_TYPE>)
            struct atanh_impl<MEAS_TYPE> : unary_function<MEAS_TYPE, MEAS_TYPE> {

                constexpr MEAS_TYPE f(const MEAS_TYPE& other) const noexcept override {

                    return std::atanh(other); 

                }

            };


            template <typename CMEAS_TYPE>  
                requires (physics::is_cmeasurement_v<CMEAS_TYPE>)
            struct atanh_impl<CMEAS_TYPE> : unary_function<CMEAS_TYPE, CMEAS_TYPE> {

                constexpr CMEAS_TYPE f(const CMEAS_TYPE& other) const noexcept override {

                    using measurement_t = typename CMEAS_TYPE::measurement_t;

                    const auto i2 = op::square(other.imag);

                    return { op::log((i2 + op::square(measurement_t::one + other.real)) / (i2 + op::square(measurement_t::one - other.real))) / 4.0,
                             op::atan(2.0 * other.imag / (decltype(i2)::one - i2 - op::square(other.real))) / 2.0 };

                }

            };


            template <typename VEC_TYPE>    
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct atanh_impl<VEC_TYPE> : unary_function<VEC_TYPE, VEC_TYPE> {

                constexpr VEC_TYPE f(const VEC_TYPE& other) const noexcept override {

                    VEC_TYPE result;
                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result[i] = op::atanh(other[i]);

                    return result; 
                    
                }

            };


        // ====================================================
        // NORM
        // ====================================================

            template <typename T>
            struct norm_impl;

            /// @brief Get the norm of the vector
            template <typename VEC_TYPE>
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct norm_impl<VEC_TYPE> : unary_function<typename VEC_TYPE::measurement_t, VEC_TYPE> { 

                constexpr typename VEC_TYPE::measurement_t f(const VEC_TYPE& other) const noexcept override {

                    if constexpr (VEC_TYPE::dim == 1) 
                        return other.data[0];

                    square_t<typename VEC_TYPE::measurement_t> result;

                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result += op::square(other.data[i]);

                    return op::sqrt(result);

                }

            };


            template <typename T>
            struct norm2_impl;

            /// @brief Get the norm of the vector
            template <typename VEC_TYPE>
                requires (geometry::is_vector_v<VEC_TYPE>)
            struct norm2_impl<VEC_TYPE> : unary_function<square_t<typename VEC_TYPE::measurement_t>, VEC_TYPE> { 

                constexpr square_t<typename VEC_TYPE::measurement_t> f(const VEC_TYPE& other) const noexcept override {

                    if constexpr (VEC_TYPE::dim == 1) 
                        return other.data[0];

                    square_t<typename VEC_TYPE::measurement_t> result;

                    for (std::size_t i{}; i < VEC_TYPE::dim; ++i) 
                        result += op::square(other.data[i]);

                    return result;

                }

            };


        // template <std::size_t N>
        // struct factorial : unary_function<physics::scalar_m, physics::scalar_m> {

        //     constexpr physics::scalar_m operator()(const physics::scalar_m& x) const noexcept override {

        //         if constexpr (N == 0) 
        //             return 1;
        //         else
        //             return N * factorial<N - 1>(x);

        //     }

        // };


    } // namespace functions
    

} // namespace scipp::math