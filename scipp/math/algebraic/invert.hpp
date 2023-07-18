/**
 * @file    scipp/math/algebraic/invert.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-07-14
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
        struct invert_impl<calculus::expr_ptr<T>> {

            using result_t = calculus::expr_ptr<op::invert_t<T>>;

            static constexpr result_t f(const calculus::expr_ptr<T>& x) {

                return std::make_shared<calculus::invert_expr<T>>(1.0 / x->val, x);

            }

        };


        template <typename T>
        struct invert_impl<calculus::variable<T>> {

            using result_t = calculus::expr_ptr<op::invert_t<T>>;

            static constexpr result_t f(const calculus::variable<T>& x) {

                return 1. / x.expr; 

            }

        };


        template <typename T>
            requires is_number_v<T>
        struct invert_impl<T> {
            
            using result_t = double;

            static constexpr result_t f(const T& x) {

                if (x == T{})
                    throw std::runtime_error("Cannot invert zero");
                    
                return 1.0 / x;

            }       

        };


        template <typename T>
            requires physics::is_base_v<T>
        struct invert_impl<T> {
            
            using result_t = physics::base_quantity<-T::length, -T::time, -T::mass, -T::temperature, -T::elettric_current, -T::substance_amount, -T::luminous_intensity>;

            static constexpr result_t f(const T&) noexcept {

                return {};

            }                                             
            
        };


        template <typename T>
            requires physics::is_prefix_v<T>
        struct invert_impl<T> {

            using result_t = std::ratio<T::den, T::num>;

            static constexpr result_t f(const T&) noexcept {

                return {};

            }       

        };


        template <typename T>
            requires physics::is_unit_v<T>
        struct invert_impl<T> {
            
            using result_t = physics::unit<invert_t<typename T::base_t>, invert_t<typename T::prefix_t>>;

            static constexpr result_t f(const T&) noexcept {

                return {};

            }       

        };


        /// @brief Invert a measurement
        template <typename T>
            requires (physics::is_measurement_v<T>)
        struct invert_impl<T> {
            
            using result_t = physics::measurement<invert_t<typename T::base_t>, double>;

            static constexpr result_t f(const T& x) {

                if (x == T::zero)
                    throw std::runtime_error("Cannot invert zero");

                return 1.0 / x.value;

            }       

        };



        /// @brief Invert a vector
        template <typename VECTOR_TYPE>
            requires geometry::is_vector_v<VECTOR_TYPE>
        struct invert_impl<VECTOR_TYPE> {
            
            using result_t = geometry::vector<invert_t<typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>; 

            static constexpr result_t f(const VECTOR_TYPE& x) {

                result_t x_inv;
                std::transform(
                    std::execution::par, 
                    x.data.begin(), x.data.end(), 
                    x_inv.data.begin(), 
                    [](const auto& x_i) { 
                        return inv(x_i); 
                    }
                );

                return x_inv;

            }        


        }; 


    } // namespace op


} // namespace scipp::math



        // /// @brief Invert a umeasurement
        // template <typename T>
        //     requires (physics::is_umeasurement_v<T>)
        // struct invert_impl<T> {
            
        //     using result_t = physics::umeasurement<invert_t<typename T::base_t>>;
            
        //     static constexpr result_t f(const T& x) {

        //         if (x == T{})
        //             throw std::runtime_error("Cannot invert zero");

        //         return {1.0 / x.value, x.uncertainty / std::fabs(x.value) };

        //     }       

        // };


        // /// @brief Invert a complex number
        // template <typename T>
        //     requires (math::is_complex_v<T>)
        // struct invert_impl<T> {
            
        //     using result_t = complex<invert_t<typename T::value_t>>;

        //     static constexpr result_t f(const T& x) {

        //         if (x == T::value_t{})
        //             throw std::runtime_error("Cannot invert zero");

        //         return x * x.conj() / op::abs(x);

        //     }

        // };


        // /// @brief Invert a dual number
        // template <typename T>
        //     requires (math::is_dual_v<T>)
        // struct invert_impl<T> {
            
        //     using result_t = unary_function<T, dual<invert_t<typename T::value_t>>, dual<square_t<invert_t<typename T::value_t>>>>;

        //     static constexpr function_t::result_t f(const function_t::arg_t& x) {

        //         if (x == typename function_t::arg_t{})
        //             throw std::runtime_error("Cannot invert zero");

        //         auto real_inv = op::inv(x.real);
        //         return { real_inv, - x.imag * op::sq(real_inv) };

        //     }

        // };



        //     static constexpr function_t::result_t back(const function_t::arg_t& x) {

        //         typename function_t::back_t x_sq_inv;
        //         std::transform(std::execution::par, x.data.begin(), x.data.end(), x_sq_inv.data.begin(), 
        //             [](const auto& x_i) { return -op::sq(op::inv(x_i)); }
        //         );
        //         return x_sq_inv;

        //     }                
                
        // };


        // /// @brief Invert an unary function
        // template <typename FUNCTION_TYPE>
        //     requires (is_unary_function_v<typename FUNCTION_TYPE::function_t>)
        // struct invert_impl<FUNCTION_TYPE> {
            
        //     using result_t = unary_function<typename FUNCTION_TYPE::arg_t, invert_t<typename FUNCTION_TYPE::result_t>>;

        //     static constexpr function_t::result_t f(const function_t::arg_t& x) {

        //         return op::inv(FUNCTION_TYPE::f(x));

        //     }

        // };

        

