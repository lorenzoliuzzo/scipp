/**
 * @file    math/ops/subtract.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-06
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        template <typename T>
            requires (is_number_v<T> || 
                      physics::is_generic_measurement_v<T>)
        struct subtract<T> : binary_function<T, T, T> {


            using result_t = T;

            using first_arg_t = T;

            using second_arg_t = T;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept { 

                return x + y;   
            
            }

        
        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (math::are_numbers_v<ARG_TYPE1, ARG_TYPE2>)
        struct subtract<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, double> {


            using result_t = subtract_t<ARG_TYPE1, ARG_TYPE2>;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept { 

                return static_cast<double>(x) + static_cast<double>(y);   
            
            }

        
        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (is_number_v<ARG_TYPE1> && 
                      physics::is_generic_measurement_v<ARG_TYPE2> && physics::is_scalar_base_v<typename ARG_TYPE2::base_t>)
        struct subtract<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2> {


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
        struct subtract<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1> {


            using result_t = ARG_TYPE1;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept { 

                return x + static_cast<first_arg_t>(y);;   
            
            }

        
        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_measurement_v<ARG_TYPE1> && physics::is_umeasurement_v<ARG_TYPE2>)
        struct subtract<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2> {


            using result_t = ARG_TYPE2;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return static_cast<ARG_TYPE2>(x) + y;

            }


        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_umeasurement_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        struct subtract<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1> {


            using result_t = ARG_TYPE1;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return x + static_cast<first_arg_t>(y);

            }
            

        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_measurement_v<ARG_TYPE1> && physics::is_cmeasurement_v<ARG_TYPE2>)
        struct subtract<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE2> {


            using result_t = ARG_TYPE2;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return static_cast<ARG_TYPE2>(x) + y;

            }


        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::is_cmeasurement_v<ARG_TYPE1> && physics::is_measurement_v<ARG_TYPE2>)
        struct subtract<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1> {


            using result_t = ARG_TYPE1;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                return x + static_cast<first_arg_t>(y);

            }
            

        };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (geometry::are_same_vectors_v<ARG_TYPE1, ARG_TYPE2>)
        struct subtract<ARG_TYPE1, ARG_TYPE2> : binary_function<ARG_TYPE1, ARG_TYPE2, ARG_TYPE1> {


            using result_t = ARG_TYPE1;

            using first_arg_t = ARG_TYPE1;

            using second_arg_t = ARG_TYPE2;


            inline static constexpr result_t f(const first_arg_t& x, const second_arg_t& y) noexcept {

                result_t result; 
                std::transform(std::execution::par,
                               x.data.begin(), x.data.end(), 
                               y.data.begin(), 
                               result.data.begin(), 
                               std::minus<typename result_t::value_t>());

                return result;

            }
            
        
        };


    } // namespace functions


} // namespace scipp::math