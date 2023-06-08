/**
 * @file    math/functions/types/operations.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-20
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
        inline static constexpr auto round(const T& x) noexcept {

            return functions::round<T>::f(x);
            
        }
        

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto add(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

            return functions::add<ARG_TYPE1, ARG_TYPE2>::f(x, y);

        }      
        
        
        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto sub(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

            auto y_neg = functions::negate<ARG_TYPE2>::f(y);
            return functions::add<ARG_TYPE1, ARG_TYPE2>::f(x, y_neg);

        } 


        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto mult(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

            return functions::multiply<ARG_TYPE1, ARG_TYPE2>::f(x, y);

        } 


        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto div(const ARG_TYPE1& x, const ARG_TYPE2& y) {

            return functions::divide<ARG_TYPE1, ARG_TYPE2>::f(x, y);

        } 


        template <typename ARG_TYPE>
        inline static constexpr auto neg(const ARG_TYPE& x) noexcept {

            return functions::negate<ARG_TYPE>::f(x);

        } 


        template <typename T>
        inline static constexpr auto abs(const T& x) noexcept {

            return functions::modulo<T>::f(x);

        }        


        template <typename T>
        inline static constexpr auto inv(const T& x) {

            return functions::invert<T>::f(x);

        }


        template <size_t POWER, typename T>
        inline static constexpr auto pow(const T& x) noexcept {
            
            return functions::power<POWER, T>::f(x);

        }


        template <typename T>
        inline static constexpr auto sq(const T& x) noexcept {

            return pow<2>(x);

        }  

        template <typename T>
        inline static constexpr auto cb(const T& x) noexcept {

            return pow<3>(x);

        }

        
        template <size_t POWER, typename T>
        inline static constexpr auto rt(const T& x) {
            
            return functions::root<POWER, T>::f(x);

        }
        

        template <typename T>
        inline static constexpr auto sqrt(const T& x) {

            return rt<2>(x); 

        }

        template <typename T>
        inline static constexpr auto cbrt(const T& x) {

            return rt<3>(x); 

        }

        
        template <typename T>
        inline static constexpr auto exp(const T& x) noexcept {  

            return functions::exponential<T>::f(x);

        }


        template <typename T>
        inline static constexpr auto log(const T& x) {

            return functions::logarithm<T>::f(x);

        }


        template <typename T>
        inline static constexpr auto sin(const T& x) noexcept {

            return functions::sine<T>::f(x);

        }


        template <typename T>
        inline static constexpr auto cos(const T& x) noexcept {

            return functions::cosine<T>::f(x);

        }


        template <typename T>
        inline static constexpr auto tan(const T& x) noexcept {

            return functions::tangent<T>::f(x);

        }


        template <typename T>
        inline static constexpr auto tan(const T& x, const T& y) noexcept {

            return functions::tangent<T>::f(x, y);

        }


        template <typename T>
        inline static constexpr auto cot(const T& x) noexcept {

            return functions::cotangent<T>::f(x);

        }

        template <typename T>
        inline static constexpr auto sec(const T& x) noexcept {

            return functions::secant<T>::f(x);

        }

        template <typename T>
        inline static constexpr auto csc(const T& x) noexcept {

            return functions::cosecant<T>::f(x);

        }


        template <typename T>
        inline static constexpr auto asin(const T& x) noexcept {

            return functions::arcsine<T>::f(x);

        }


        template <typename T>
        inline static constexpr auto acos(const T& x) noexcept {

            return functions::arccosine<T>::f(x);

        }


        template <typename T>
        inline static constexpr auto atan(const T& x) noexcept {

            return functions::arctangent<T>::f(x);

        }



        template <typename T>
        inline static constexpr auto acot(const T& x) noexcept {

            return functions::arccotangent<T>::f(x);

        }

        template <typename T>
        inline static constexpr auto asec(const T& x) noexcept {

            return functions::arcsecant<T>::f(x);

        }

        template <typename T>
        inline static constexpr auto acsc(const T& x) noexcept {

            return functions::arccosecant<T>::f(x);

        }


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
        


} // namespace scipp::math