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


        template <typename T>
        inline static constexpr auto sign(const T& x) noexcept {

            return functions::sign<T>::f(x);
            
        }
        

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto equal(ARG_TYPE1&& x, ARG_TYPE2&& y) noexcept {

            return functions::equal<ARG_TYPE1, ARG_TYPE2>::f(std::forward<ARG_TYPE1>(x), std::forward<ARG_TYPE2>(y));

        }      



        // template <typename ARG_TYPE>
        // inline static constexpr auto greater(ARG_TYPE&& x, ARG_TYPE&& y) noexcept {

        //     return functions::greater<ARG_TYPE>::f(std::forward<ARG_TYPE>(x), std::forward<ARG_TYPE>(y));

        // }


        // template <typename ARG_TYPE>
        // inline static constexpr auto greater_equal(ARG_TYPE&& x, ARG_TYPE&& y) noexcept {

        //     return functions::greater_equal<ARG_TYPE>::f(std::forward<ARG_TYPE>(x), std::forward<ARG_TYPE>(y));

        // }


        // template <typename ARG_TYPE>
        // inline static constexpr auto less(ARG_TYPE&& x, ARG_TYPE&& y) noexcept {

        //     return functions::less<ARG_TYPE>::f(std::forward<ARG_TYPE>(x), std::forward<ARG_TYPE>(y));

        // }


        // template <typename ARG_TYPE>
        // inline static constexpr auto less_equal(ARG_TYPE&& x, ARG_TYPE&& y) noexcept {

        //     return functions::less_equal<ARG_TYPE>::f(std::forward<ARG_TYPE>(x), std::forward<ARG_TYPE>(y));

        // }
        

        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto add(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

            return functions::add<ARG_TYPE1, ARG_TYPE2>::f(x, y);

        }      
        
        template <typename ARG_TYPE1, typename ARG_TYPE2>
        inline static constexpr auto sub(const ARG_TYPE1& x, const ARG_TYPE2& y) noexcept {

            return functions::add<ARG_TYPE1, ARG_TYPE2>::f(x, functions::invert<y);

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



        template <typename T1, typename T2>
        inline static constexpr auto dot(const T1&, const T2&) noexcept; 

        template <typename T1, typename T2>
        inline static constexpr auto cross(const T1&, const T2&) noexcept; 


        template <typename T, typename SCALAR_TYPE>
            requires (is_number_v<SCALAR_TYPE> || physics::is_scalar_measurement_v<SCALAR_TYPE> || physics::is_scalar_umeasurement_v<SCALAR_TYPE>)
        inline static constexpr auto polar(const T& rho, const SCALAR_TYPE& theta) noexcept {

            return { rho * cos(theta), rho * sin(theta) };

        }

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