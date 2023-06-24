/**
 * @file    math/functions/logical/equal.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * 
 * @brief   Equal function implementation
 * 
 * @date    2023-06-09
 * @copyright Copyright (c) 2023
 */

    

namespace scipp::math {


    namespace functions {



        template <typename T1, typename T2>
        struct equal {

            using function_t = binary_function<T1, T2, bool>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return (x == y);   
            
            }

        };


        template <typename T>
            requires (is_number_v<T>)
        struct equal<T, T> {

            using function_t = binary_function<T, T, bool>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return (x == y);   
            
            }

        };


        template <typename T>
            requires (is_complex_v<T> || is_dual_v<T>)
        struct equal<T, T> {

            using function_t = binary_function<T, T, bool>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept { 

                return (x.real == y.real && x.imag == y.imag);   
            
            }

        };


        template <typename BASE_TYPE1, typename BASE_TYPE2 >
            requires (physics::are_base_v<BASE_TYPE1, BASE_TYPE2>)
        struct equal<BASE_TYPE1, BASE_TYPE2> {
            
            using function_t = binary_function<BASE_TYPE1, BASE_TYPE2, bool>;

            inline static constexpr function_t::result_t f(const function_t::first_arg_t&, const function_t::second_arg_t&) noexcept {

                return physics::are_same_base_v<BASE_TYPE1, BASE_TYPE2>;

            }                                             
            
        };


        // template <typename PREFIX_TYPE>
        //     requires (physics::is_prefix_v<PREFIX_TYPE>)
        // struct equal<PREFIX_TYPE> {

        //     using function_t = unary_function<PREFIX_TYPE, std::ratio<PREFIX_TYPE::den, PREFIX_TYPE::num>>;

        //     inline static constexpr function_t::result_t f(const function_t::arg_t&) noexcept {

        //         return {};

        //     }       

        // };


        // template <typename UNIT_TYPE>
        //     requires (physics::is_unit_v<UNIT_TYPE>)
        // struct equal<UNIT_TYPE> {
            
        //     using function_t = unary_function<UNIT_TYPE, physics::unit<equal_t<typename UNIT_TYPE::base_t>, equal_t<typename UNIT_TYPE::prefix_t>>>;

        //     inline static constexpr function_t::result_t f(const function_t::arg_t&) noexcept {

        //         return {};

        //     }       

        // };


        // template <typename T>
        //     requires (is_number_v<T>)
        // struct equal<T> {
            
        //     using function_t = unary_function<T, double>;

        //     inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

        //         if (x == typename function_t::arg_t{})
        //             throw std::runtime_error("Cannot equal zero");
                    
        //         return 1.0 / x;

        //     }       

        // };


        template <typename ARG_TYPE1, typename ARG_TYPE2>
            requires (physics::are_measurements_v<ARG_TYPE1, ARG_TYPE2>)
        struct equal<ARG_TYPE1, ARG_TYPE2> {
            
            using function_t = binary_function<ARG_TYPE1, ARG_TYPE2, bool>; 

            inline static constexpr function_t::result_t f(const function_t::first_arg_t& x, const function_t::second_arg_t& y) noexcept {

                if constexpr (physics::are_same_base_v<ARG_TYPE1, ARG_TYPE2>)
                    return (x.value == y.value);
                
                return false; 

            }       

        };


        // template <typename UMEAS_TYPE>
        //     requires (physics::is_umeasurement_v<UMEAS_TYPE>)
        // struct equal<UMEAS_TYPE> {
            
        //     using function_t = unary_function<UMEAS_TYPE, physics::umeasurement<equal_t<typename UMEAS_TYPE::base_t>>>;
            
        //     inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

        //         if (x == typename function_t::arg_t{})
        //             throw std::runtime_error("Cannot equal zero");

        //         return {1.0 / x.value, x.uncertainty / std::fabs(x.value) };

        //     }       

        // };


        // template <typename CMEAS_TYPE>
        //     requires (math::is_complex_v<CMEAS_TYPE>)
        // struct equal<CMEAS_TYPE> {
            
        //     using function_t = unary_function<CMEAS_TYPE, complex<equal_t<typename CMEAS_TYPE::value_t>>>;

        //     inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

        //         if (x == typename function_t::arg_t{})
        //             throw std::runtime_error("Cannot equal zero");

        //         return x * x.conj() / op::abs(x);

        //     }

        // };


        // template <typename VECTOR_TYPE>
        //     requires (geometry::is_vector_v<VECTOR_TYPE>)
        // struct equal<VECTOR_TYPE> {
            
        //     using function_t = unary_function<VECTOR_TYPE, geometry::vector<equal_t<typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>>;

        //     inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

        //         typename function_t::result_t x_inv;
        //         std::transform(std::execution::par, x.data.begin(), x.data.end(), x_inv.data.begin(), [](const auto& x_i) { return op::inv(x_i); });
        //         return x_inv;

        //     }
        
        // };


    } // namespace functions


} // namespace scipp::math