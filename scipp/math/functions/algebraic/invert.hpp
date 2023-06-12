/**
 * @file    math/functions/algebraic/invert.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-12
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace functions {


        /// @brief Invert a physics::base_quantity
        template <typename T>
            requires (physics::is_base_v<T>)
        struct invert<T> {
            
            using function_t = unary_function<T, physics::base_quantity<-T::length, 
                                                                        -T::time,
                                                                        -T::mass,
                                                                        -T::temperature,
                                                                        -T::elettric_current,
                                                                        -T::substance_amount,
                                                                        -T::luminous_intensity>>;

            inline static constexpr function_t::result_t f(const function_t::arg_t&) noexcept {

                return {};

            }                                             
            
        };


        /// @brief Invert a prefix
        template <typename T>
            requires (physics::is_prefix_v<T>)
        struct invert<T> {

            using function_t = unary_function<T, std::ratio<T::den, T::num>>;

            inline static constexpr function_t::result_t f(const function_t::arg_t&) noexcept {

                return {};

            }       

        };


        /// @brief Invert an unit of measurement
        template <typename T>
            requires (physics::is_unit_v<T>)
        struct invert<T> {
            
            using function_t = unary_function<T, physics::unit<invert_t<typename T::base_t>, invert_t<typename T::prefix_t>>>;

            inline static constexpr function_t::result_t f(const function_t::arg_t&) noexcept {

                return {};

            }       

        };


        /// @brief Invert a number
        template <typename T>
            requires (is_number_v<T>)
        struct invert<T> {
            
            using function_t = unary_function<T, double>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                if (x == typename function_t::arg_t{})
                    throw std::runtime_error("Cannot invert zero");
                    
                return 1.0 / x;

            }       

        };


        /// @brief Invert a measurement
        template <typename T>
            requires (physics::is_measurement_v<T>)
        struct invert<T> {
            
            using function_t = unary_function<T, physics::measurement<invert_t<typename T::base_t>, double>>; 

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                if (x == typename function_t::arg_t{})
                    throw std::runtime_error("Cannot invert zero");

                return 1.0 / x.value;

            }       

        };


        /// @brief Invert a umeasurement
        template <typename T>
            requires (physics::is_umeasurement_v<T>)
        struct invert<T> {
            
            using function_t = unary_function<T, physics::umeasurement<invert_t<typename T::base_t>>>;
            
            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                if (x == typename function_t::arg_t{})
                    throw std::runtime_error("Cannot invert zero");

                return {1.0 / x.value, x.uncertainty / std::fabs(x.value) };

            }       

        };


        /// @brief Invert a complex number
        template <typename T>
            requires (math::is_complex_v<T>)
        struct invert<T> {
            
            using function_t = unary_function<T, complex<invert_t<typename T::value_t>>>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                if (x == typename function_t::arg_t{})
                    throw std::runtime_error("Cannot invert zero");

                return x * x.conj() / op::abs(x);

            }

        };


        /// @brief Invert a dual number
        template <typename T>
            requires (math::is_dual_v<T>)
        struct invert<T> {
            
            using function_t = unary_function<T, dual<invert_t<typename T::value_t>>>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                if (x == typename function_t::arg_t{})
                    throw std::runtime_error("Cannot invert zero");

                auto real_inv = op::inv(x.real);
                return { real_inv, - x.imag * op::sq(real_inv) };

            }

        };


        /// @brief Invert a vector
        template <typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        struct invert<VECTOR_TYPE> {
            
            using function_t = unary_function<VECTOR_TYPE, geometry::vector<invert_t<typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>>;

            inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

                typename function_t::result_t x_inv;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), x_inv.data.begin(), 
                    [](const auto& x_i) { return op::inv(x_i); }
                );
                return x_inv;

            }
        
        };


        // /// @brief Invert an unary function
        // template <typename FUNCTION_TYPE>
        //     requires (is_unary_function_v<typename FUNCTION_TYPE::function_t>)
        // struct invert<FUNCTION_TYPE> {
            
        //     using function_t = unary_function<typename FUNCTION_TYPE::arg_t, invert_t<typename FUNCTION_TYPE::result_t>>;

        //     inline static constexpr function_t::result_t f(const function_t::arg_t& x) {

        //         return op::inv(FUNCTION_TYPE::f(x));

        //     }

        // };
        

    } // namespace functions


} // namespace scipp::math