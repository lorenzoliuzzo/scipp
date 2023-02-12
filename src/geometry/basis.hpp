/**
 * @file    geometry/basis.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-02-11
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::geometry {


    template <typename... TYPES> requires (are_vectors_v<TYPES...>)
    struct basis : matrix<TYPES...> {


        // ===========================================================
        // aliases
        // ===========================================================

            using type = basis<TYPES...>;


        // ===========================================================
        // static members
        // ===========================================================

            static inline constexpr size_t dim = common_dimention_v<TYPES...>;



        // ===========================================================
        // methods
        // ===========================================================

            // /// @brief Check if the basis vectors are orthogonal and normalized
            // constexpr bool is_orthonormal() const {

            //     for (size_t i{}; i < dim; ++i) {

            //         for (size_t j{i + 1}; j < dim; ++j) 
            //             if (!math::is_zero(op::dot((*this)[i], (*this)[j]))) 
            //                 return false;

            //         if (!(*this)[i].is_normalized()) 
            //             return false;

            //     }

            //     return true;

            // }


            // /// @brief Check if the base is normalized
            // constexpr bool is_normalized() const noexcept {

            //     for (std::size_t i{}; i < DIM; ++i) 
            //         if (!this->column(i).is_normalized()) 
            //             return false; 

            //     return true; 

            // }


            // /**
            //     * @brief Get an ortho-normal base from the current base
            //     * 
            //     * @return constexpr base<DIM> 
            //     */
            // constexpr base<DIM> normalize() const noexcept {

            //     if (!this->is_normalized()) {

            //         matrix<DIM, DIM> ortho_normal(this->data());
            //         for (std::size_t i{}; i < DIM; ++i) 
            //             if (!this->column(i).is_normalized()) 
            //                 ortho_normal[i] /= this->column(i).norm(); 

            //         return ortho_normal; 

            //     } else 
            //         return *this; 

            // }


            // /**
            //     * @brief Decompose a vector  
            //     * 
            //     * @param vec: vector<DIM> as l-value const reference
            //     * 
            //     * @return 
            //     */
            // constexpr vector<DIM> decompose(const vector<DIM>& vec,     
            //                                 matrix_solver_methods method = matrix_solver_methods::GEPP) const {

            //     return solve_matrix(*this, vec, method);

            // }


    };



} // namespace scipp::geometry