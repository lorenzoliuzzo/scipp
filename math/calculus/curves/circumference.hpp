/**
 * @file    math/calculus/curves/circumference.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-09
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {
    

    namespace curves {

        template <typename T>
            requires (is_complex_v<T> || (geometry::is_vector_v<T> && T::dim == 2))
        struct circumference<T> : curve<T, 2> {


            using value_t = T;

            using radius_t = typename T::value_t;

            using param_t = double; 


            value_t center;

            radius_t radius;

        
            constexpr circumference(value_t center, radius_t radius) noexcept : 
                
                center{std::forward<value_t>(center)}, radius{std::forward<radius_t>(radius)} {}


            inline constexpr auto f(const param_t& t) {
                
                if (t < 0.0 || t > 1.0) {
                    std::cerr << "Cannot evaluate circumference at t = " << t << '\n';
                    throw std::out_of_range("All scalar parameters must be in the range [0, 1]");
                }

                return value_t{center.x() + radius * op::cos(2.0 * constants::pi * t), center.y() + radius * op::sin(2.0 * constants::pi * t)};

            }

        
        }; // struct circumference

    
    } // namespace curves


} // namespace scipp::math