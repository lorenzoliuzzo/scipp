/**
 * @file    math/polynomials/polynomial.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-28
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace polynomials {


        template <typename T>
        struct polynomial : virtual meta::unary_function<T, T> {


            constexpr auto three_term_recursion(const ) const noexcept {

                auto result = geometry::make_vector(P_kp1, P_k); 
                auto recursive_matrix = geometry::make_matrix(geometry::make_vector((x - b_k) / a_k, T{1.}), geometry::make_vector(- c_k / a_k, T{0.}));

                return result;

            }


        }





    } // namespace polynomials


} // namespace scipp::math