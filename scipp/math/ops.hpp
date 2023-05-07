/**
 * @file    math/ops.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-26
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {




    namespace op {


        template <typename T>
        inline static constexpr auto inv(const T& x) {

            return functions::invert<T>::f(x);

        }


        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto add(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

            return functions::add<ARG_TYPE1, ARG_TYPE2>::f(x, y);

        }        
        
        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr decltype(auto) add(ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

            return functions::add<ARG_TYPE1, ARG_TYPE2>::f(x, y);

        }   
        
        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto sub(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

            return functions::subtract<ARG_TYPE1, ARG_TYPE2>::f(x, y);

        } 


        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto mult(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

            return functions::multiply<ARG_TYPE1, ARG_TYPE2>::f(x, y);

        } 


        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto div(const ARG_TYPE1& x, const ARG_TYPE2& y) {

            return functions::divide<ARG_TYPE1, ARG_TYPE2>::f(x, y);

        } 


        template <size_t POWER, typename T>
        inline static constexpr auto pow(const T& x) noexcept {
            
            return functions::power<POWER, T>::f(x);

        }


        template <typename T>
        inline static constexpr auto square(const T& x) noexcept {

            return pow<2>(x);

        }  

        template <typename T>
        inline static constexpr auto cube(const T& x) noexcept {

            return pow<3>(x);

        }

        
        template <size_t POWER, typename T>
        inline static constexpr auto root(const T& x) {
            
            return functions::root<POWER, T>::f(x);

        }
        

        template <typename T>
        inline static constexpr auto sqrt(const T& x) {

            return root<2>(x); 

        }

        template <typename T>
        inline static constexpr auto cbrt(const T& x) {

            return root<3>(x); 

        }



        template <typename T>
        inline static constexpr auto abs(const T&) noexcept;

        
        template <typename T>
        inline static constexpr T exp(const T&) noexcept;

        template <typename T>
        inline static constexpr T log(const T&);


        template <typename T>
        inline static constexpr T sin(const T&) noexcept;

        template <typename T>
        inline static constexpr T cos(const T&) noexcept;

        template <typename T>
        inline static constexpr T tan(const T&) noexcept;

        template <typename T>
        inline static constexpr T sinh(const T&) noexcept;

        template <typename T>
        inline static constexpr T cosh(const T&) noexcept;

        template <typename T>
        inline static constexpr T tanh(const T&) noexcept;


        template <typename T>
        inline static constexpr T asin(const T&) noexcept;

        template <typename T>
        inline static constexpr T acos(const T&) noexcept;

        template <typename T>
        inline static constexpr T atan(const T&) noexcept;

        template <typename T>
        inline static constexpr auto atan(const T&, const T&) noexcept; 

        template <typename T>
        inline static constexpr T asinh(const T&) noexcept;

        template <typename T>
        inline static constexpr T acosh(const T&) noexcept;

        template <typename T>
        inline static constexpr T atanh(const T&) noexcept;


        template <typename T1, typename T2>
        inline static constexpr auto dot(const T1&, const T2&) noexcept; 

        template <typename T1, typename T2>
        inline static constexpr auto cross(const T1&, const T2&) noexcept; 



        template <typename T1, typename T2>
        inline static constexpr auto proj(const T1&, const T2&) noexcept; 


        template <typename T>
        inline static constexpr auto norm(const T&) noexcept; 

        template <typename T>
        inline static constexpr auto norm2(const T&) noexcept; 

        template <typename T>
        inline static constexpr auto normalize(const T&) noexcept; 


    } // namespace op
        

        // template <typename T>
        // inline static constexpr auto abs(const T& x) noexcept {

        //     return meta::abs_impl<T>()(x);

        // }

        // template <typename T>
        // inline static constexpr int sign(const T& x) noexcept {

        //     return meta::sign_impl<T>()(x);

        // }



        // template <typename T>
        // inline static constexpr auto square(const T& x) noexcept {

        //     return meta::pow_impl<T, 2>()(x);

        // }        
        
        // template <typename T>
        // inline static constexpr auto cube(const T& x) noexcept {

        //     return meta::pow_impl<T, 3>()(x);

        // }


        // template <typename T, typename U>
        // inline static constexpr auto pow(const T& base, const U& exp) noexcept {
            
        //     return meta::pow_impl2<T, U>()(base, exp);

        // }


        // template <typename T>
        // inline static constexpr auto sqrt(const T& x) {

        //     return meta::sqrt_impl<T>()(x);

        // }

        // template <typename T>
        // inline static constexpr auto cbrt(const T& x) {

        //     return meta::cbrt_impl<T>()(x);

        // }


        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T exp(const T& x) noexcept {

        //     return meta::exp_impl<T>()(x);

        // }


        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T log(const T& x) {

        //     return meta::log_impl<T>()(x);

        // }


        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T sin(const T& x) noexcept {

        //     return meta::sin_impl<T>()(x);

        // }

        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T cos(const T& x) noexcept {

        //     return meta::cos_impl<T>()(x);

        // }


        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T tan(const T& x) noexcept {

        //     return meta::tan_impl<T>()(x);

        // }
        

        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T sinh(const T& x) noexcept {

        //     return meta::sinh_impl<T>()(x);

        // }

        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T cosh(const T& x) noexcept {

        //     return meta::cosh_impl<T>()(x);

        // }
        

        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T tanh(const T& x) noexcept {

        //     return meta::tanh_impl<T>()(x);

        // }


        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T asin(const T& x) noexcept {

        //     return meta::asin_impl<T>()(x);

        // }

        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T acos(const T& x) noexcept {

        //     return meta::acos_impl<T>()(x);

        // }


        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T atan(const T& x) noexcept {

        //     return meta::atan_impl<T>()(x);

        // }


        // template <typename T>
        // inline static constexpr auto atan(const T& y, const T& x) noexcept {

        //     return meta::atan_impl2<T>()(y, x);

        // }
        

        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T asinh(const T& x) noexcept {

        //     return meta::asinh_impl<T>()(x);

        // }

        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T acosh(const T& x) noexcept {

        //     return meta::acosh_impl<T>()(x);

        // }
        

        // template <typename T>
        //     requires (is_scalar_v<T>)
        // inline static constexpr T atanh(const T& x) noexcept {

        //     return meta::atanh_impl<T>()(x);

        // }


        // template <typename T>
        // inline static constexpr auto norm(const T& x) noexcept {

        //     return meta::norm_impl<T>()(x);
            
        // }

        // template <typename T>
        // inline static constexpr auto norm2(const T& x) noexcept {

        //     return meta::norm2_impl<T>()(x);
            
        // }


        // template <typename T>
        // inline static constexpr auto normalize(const T& x) noexcept {

        //     return x / meta::norm_impl<T>()(x); 
            
        // }


        // // template <typename VECTOR_TYPE>
        // //     requires (geometry::is_vector_v<VECTOR_TYPE>)
        // // inline static constexpr auto normalize(const VECTOR_TYPE& x) noexcept {

        // //     std::array<double, VECTOR_TYPE::dim> result;
        // //     auto norm = op::norm(x);
        // //     for (size_t i{}; i < VECTOR_TYPE::dim; ++i) 
        // //         result[i] = x.data[i] / norm;

        // //     return result;
            
        // // }


        // // template <typename MATRIX_TYPE>
        // //     requires (geometry::is_matrix_v<MATRIX_TYPE>)
        // // inline static constexpr auto normalize(const MATRIX_TYPE& x) noexcept {
            
        // //     geometry::matrix<geometry::vector<physics::measurement<physics::base_quantity<0,0,0,0,0,0,0>>, MATRIX_TYPE::rows>, MATRIX_TYPE::columns> result;
        // //     for (size_t i{}; i < MATRIX_TYPE::columns; ++i) 
        // //         result.data[i] = op::normalize(x.data[i]);

        // //     return result;
            
        // // }


        // /// @brief Dot product of two vectors
        // template <typename VEC_TYPE1, typename VEC_TYPE2>
        //     requires (geometry::are_vectors_v<VEC_TYPE1, VEC_TYPE2> && 
        //               geometry::have_same_dimension_v<VEC_TYPE1, VEC_TYPE2>)
        // constexpr auto dot(const VEC_TYPE1& v1, const VEC_TYPE2& v2) noexcept 
        //     -> multiply_t<typename VEC_TYPE1::measurement_t, typename VEC_TYPE2::measurement_t> {
            
        //     multiply_t<typename VEC_TYPE1::measurement_t, typename VEC_TYPE2::measurement_t> result;

        //     for (size_t i{}; i < VEC_TYPE1::dim; ++i) 
        //         result += v1.data[i] * v2.data[i]; 

        //     return result;

        // }


        // /// @brief Cross product of two vectors
        // template <typename VEC_TYPE1, typename VEC_TYPE2>
        //     requires (geometry::are_vectors_v<VEC_TYPE1, VEC_TYPE2> && 
        //               geometry::have_same_dimension_v<VEC_TYPE1, VEC_TYPE2>)
        // constexpr auto cross(const VEC_TYPE1& v1, const VEC_TYPE2& v2) noexcept 
        //     -> geometry::vector<multiply<typename VEC_TYPE1::measurement_t, typename VEC_TYPE2::measurement_t>, VEC_TYPE1::dim> {
            
        //     geometry::vector<multiply<typename VEC_TYPE1::measurement_t, typename VEC_TYPE2::measurement_t>, VEC_TYPE1::dim> result;

        //     for (size_t i{}; i < VEC_TYPE1::dim; ++i)
        //         result.data[i] = v1[(i + 1) % VEC_TYPE1::dim] * v2[(i + 2) % VEC_TYPE1::dim] - 
        //                          v1[(i + 2) % VEC_TYPE1::dim] * v2[(i + 1) % VEC_TYPE1::dim]; 

        //     return result;

        // }


        // template <typename T>
        // inline static constexpr auto proj(const T& a, const T& b) noexcept {

        //     return (dot(a, b) / dot(a, a)) * a;

        // }

        
        // template <typename NUMBER_TYPE>
        //     requires (is_number_v<NUMBER_TYPE>)
        // inline static constexpr NUMBER_TYPE factorial(NUMBER_TYPE x) noexcept {

        //     if (x == 0) 
        //         return 1;

        //     return x * factorial(x - 1);

        // };


    // } // namespace op


} // namespace scipp::math