/**
 * @file    math/ops/add.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-06
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        template <typename T>
            requires (is_number_v<T>)
        struct add<T> : binary_function<T, T, T> {


            using result_t = T;

            using first_arg_t = T;

            using second_arg_t = T;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept { 

                return x + y;   
            
            }

        
        };

        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (are_numbers_v<ARG_TYPE1, ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, double> {


            using result_t = add_t<ARG_TYPE1, ARG_TYPE2>;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept { 

                return static_cast<double>(x) + static_cast<double>(y);   
            
            }

        
        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_same_measurement_v<ARG_TYPE1, ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, 
                                        physics::measurement<typename ARG_TYPE1::base_t, decltype(static_cast<typename ARG_TYPE1::value_t>(1.0) + static_cast<typename ARG_TYPE2::value_t>(1.0))>> {


            using result_t = physics::measurement<typename ARG_TYPE1::base_t, decltype(static_cast<typename ARG_TYPE1::value_t>(1.0) + static_cast<typename ARG_TYPE2::value_t>(1.0))>;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept { 

                return x.value + y.value;   
            
            }


            inline static constexpr result_t f(first_arg_t& x, const second_arg_t& y) noexcept {

                x.value += y.value; 
                return x; 

            }

        
        };


        template <typename T>
            requires (physics::is_umeasurement_v<T>)
        struct add<T> : binary_function<T, T, T> {


            using result_t = T;

            using first_arg_t = T;

            using second_arg_t = T;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept { 
                
                return {x.value + y.value, std::hypot(x.uncertainty / x.value, y.uncertainty / y.value)};
            
            }


            inline static constexpr result_t& f(first_arg_t& x, const second_arg_t& y) noexcept {

                x.value += y.value; 
                x.uncertainty = std::hypot(x.uncertainty / x.value, y.uncertainty / y.value);
                return x; 
                
            }

        
        };


        template <typename T>
            requires (physics::is_cmeasurement_v<T>)
        struct add<T> : binary_function<T, T, T> {


            using result_t = T;

            using first_arg_t = T;

            using second_arg_t = T;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept { 
                
                return {x.real + y.real, x.imag + y.imag};
            
            }


            inline static constexpr result_t& f(first_arg_t& x, const second_arg_t& y) noexcept {

                x.real += y.real; 
                x.imag += y.imag;
                return x; 
                
            }

        
        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (is_number_v<ARG_TYPE1> && 
                      physics::is_generic_measurement_v<ARG_TYPE2> && physics::is_scalar_base_v<typename ARG_TYPE2::base_t>)
        struct add<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2> {


            using result_t = ARG_TYPE2;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept { 

                return static_cast<second_arg_t>(x) + y;   
            
            }

        
        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_generic_measurement_v<ARG_TYPE1> && physics::is_scalar_base_v<typename ARG_TYPE1::base_t> &&
                      is_number_v<ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1> {


            using result_t = ARG_TYPE1;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept { 

                return x + static_cast<first_arg_t>(y);   
            
            }


            inline static constexpr result_t f(first_arg_t& x, const second_arg_t& y) noexcept { 

                x += static_cast<first_arg_t>(y);
                return x;  
            
            }

        
        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_measurement_v<ARG_TYPE1> && physics::is_umeasurement_v<ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2> {


            using result_t = ARG_TYPE2;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return static_cast<second_arg_t>(x) + y;

            }


        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_umeasurement_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1> {


            using result_t = ARG_TYPE1;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return {x.value + y.value, x.uncertainty}; 

            }
            

            inline static constexpr result_t f(first_arg_t& x, const second_arg_t& y) noexcept {

                x.value += y.value;
                return x;

            }


        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_measurement_v<ARG_TYPE1> && physics::is_cmeasurement_v<ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2> {


            using result_t = ARG_TYPE2;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return static_cast<second_arg_t>(x) + y;

            }


        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_cmeasurement_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        struct add<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1> {


            using result_t = ARG_TYPE1;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return {x.real + y.value, x.imag};

            }
            

            inline static constexpr result_t f(first_arg_t& x, const second_arg_t& y) noexcept {
                
                x.real += y.value;
                return x;

            }


        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires ((geometry::are_column_vectors_v<ARG_TYPE1, ARG_TYPE2> || geometry::are_row_vectors_v<ARG_TYPE1, ARG_TYPE2>) &&
                      geometry::have_same_dimension_v<ARG_TYPE1, ARG_TYPE2> &&
                      physics::are_same_base_v<typename ARG_TYPE1::base_t, typename ARG_TYPE2::base_t>)
        struct add<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, geometry::vector<add_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>, ARG_TYPE1::dim, ARG_TYPE1::flag>> {


            using result_t = geometry::vector<add_t<typename ARG_TYPE1::value_t, typename ARG_TYPE2::value_t>, ARG_TYPE1::dim, ARG_TYPE1::flag>;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept { 

                result_t result;
                std::for_each(std::execution::par, 
                              result.data.begin(), result.data.end(), 
                              [&](auto& elem) { 
                                elem = op::add(x.data[&elem - result.data.data()], y.data[&elem - result.data.data()]); 
                              });

                return result;
            
            }

        
        };


        template <typename T>
            requires (geometry::is_matrix_v<T>)
        struct add<T> : binary_function<T, T, T> {


            using result_t = T;

            using first_arg_t = T;

            using second_arg_t = T;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept { 

                result_t result;
                std::transform(std::execution::par,
                               x.data.begin(), x.data.end(), 
                               y.data.begin(), 
                               result.data.begin(), 
                               std::plus<typename result_t::value_t>());
                
                return result;
            
            }


            inline static constexpr result_t& f(first_arg_t& x, const second_arg_t& y) noexcept {

                std::transform(std::execution::par,
                               x.data.begin(), x.data.end(), 
                               y.data.begin(), 
                               x.data.begin(), 
                               std::plus<typename result_t::value_t>());
                
                return x;

            }

        
        };


    } // namespace functions


} // namespace scipp::math