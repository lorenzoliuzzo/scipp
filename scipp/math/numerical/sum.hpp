/**
 * @file    math/numerical/round.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-07-18
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        template <typename T>
            requires geometry::is_vector_v<T>
        static constexpr auto sum(const T& x) {
                
            return std::accumulate(
                x.data.begin(), x.data.end(), 
                typename T::value_t{}, 
                [](const auto& a, const auto& b) {
                    return a + b;
                }
            );

        }


    } // namespace op


} // namespace scipp::math