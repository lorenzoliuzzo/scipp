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
        inline static constexpr auto abs(const T& x) noexcept {

            return meta::abs_impl<T>()(x);

        }

        template <typename T>
        inline static constexpr auto inv(const T& x) {

            return meta::inv_impl<T>()(x);

        }


        template <uint POWER, typename T>
        inline static constexpr auto pow(const T& x) noexcept {
            
            return meta::pow_impl<T, POWER>()(x);

        }

        template <typename T>
        inline static constexpr auto square(const T& x) noexcept {

            return meta::pow_impl<T, 2>()(x);

        }        
        
        template <typename T>
        inline static constexpr auto cube(const T& x) noexcept {

            return meta::pow_impl<T, 3>()(x);

        }


        template <typename T, typename U>
        inline static constexpr auto pow(const T& base, const U& exp) noexcept {
            
            return meta::pow_impl2<T, U>()(base, exp);

        }


        template <typename T>
        inline static constexpr auto sqrt(const T& x) {

            return meta::sqrt_impl<T>()(x);

        }

        template <typename T>
        inline static constexpr auto cbrt(const T& x) {

            return meta::cbrt_impl<T>()(x);

        }


        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T exp(const T& x) noexcept {

            return meta::exp_impl<T>()(x);

        }


        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T log(const T& x) {

            return meta::log_impl<T>()(x);

        }


        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T sin(const T& x) noexcept {

            return meta::sin_impl<T>()(x);

        }

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T cos(const T& x) noexcept {

            return meta::cos_impl<T>()(x);

        }


        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T tan(const T& x) noexcept {

            return meta::tan_impl<T>()(x);

        }
        

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T sinh(const T& x) noexcept {

            return meta::sinh_impl<T>()(x);

        }

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T cosh(const T& x) noexcept {

            return meta::cosh_impl<T>()(x);

        }
        

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T tanh(const T& x) noexcept {

            return meta::tanh_impl<T>()(x);

        }


        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T asin(const T& x) noexcept {

            return meta::asin_impl<T>()(x);

        }

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T acos(const T& x) noexcept {

            return meta::acos_impl<T>()(x);

        }


        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T atan(const T& x) noexcept {

            return meta::atan_impl<T>()(x);

        }


        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr auto atan(const T& y, const T& x) noexcept {

            return meta::atan_impl2<T>()(y, x);

        }
        

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T asinh(const T& x) noexcept {

            return meta::asinh_impl<T>()(x);

        }

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T acosh(const T& x) noexcept {

            return meta::acosh_impl<T>()(x);

        }
        

        template <typename T>
            requires (is_scalar_v<T>)
        inline static constexpr T atanh(const T& x) noexcept {

            return meta::atanh_impl<T>()(x);

        }


        template <typename T>
        inline static constexpr auto norm(const T& x) noexcept {

            return meta::norm_impl<T>()(x);
            
        }

        template <typename T>
        inline static constexpr auto norm2(const T& x) noexcept {

            return meta::norm2_impl<T>()(x);
            
        }


        template <typename T>
        inline static constexpr auto normalize(const T& x) noexcept {

            return x / meta::norm_impl<T>()(x); 
            
        }


        /// @brief Dot product of two vectors
        template <typename VEC_TYPE1, typename VEC_TYPE2>
            requires (geometry::are_vectors_v<VEC_TYPE1, VEC_TYPE2> && 
                      geometry::have_same_dimension_v<VEC_TYPE1, VEC_TYPE2>)
        constexpr auto dot(const VEC_TYPE1& v1, const VEC_TYPE2& v2) noexcept 
            -> meta::multiply_t<typename VEC_TYPE1::measurement_t, typename VEC_TYPE2::measurement_t> {
            
            meta::multiply_t<typename VEC_TYPE1::measurement_t, typename VEC_TYPE2::measurement_t> result;

            for (std::size_t i{}; i < VEC_TYPE1::dim; ++i) 
                result += v1.data[i] * v2.data[i]; 

            return result;

        }


        /// @brief Cross product of two vectors
        template <typename VEC_TYPE1, typename VEC_TYPE2>
            requires (geometry::are_vectors_v<VEC_TYPE1, VEC_TYPE2> && 
                      geometry::have_same_dimension_v<VEC_TYPE1, VEC_TYPE2>)
        constexpr auto cross(const VEC_TYPE1& v1, const VEC_TYPE2& v2) noexcept 
            -> geometry::vector<meta::multiply<typename VEC_TYPE1::measurement_t, typename VEC_TYPE2::measurement_t>, VEC_TYPE1::dim> {
            
            geometry::vector<meta::multiply<typename VEC_TYPE1::measurement_t, typename VEC_TYPE2::measurement_t>, VEC_TYPE1::dim> result;

            for (std::size_t i{}; i < VEC_TYPE1::dim; ++i)
                result.data[i] = v1[(i + 1) % VEC_TYPE1::dim] * v2[(i + 2) % VEC_TYPE1::dim] - 
                                 v1[(i + 2) % VEC_TYPE1::dim] * v2[(i + 1) % VEC_TYPE1::dim]; 

            return result;

        }


    } // namespace op


} // namespace scipp::math