/**
 * @file orthonormal_base.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2022-12-12
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp {


    namespace geometry {


        namespace linear_algebra {


            /**
             * @brief Class to represent an orthonormal base of a vectorial space as a matrix of l.i. normalized vectors
             * 
             * @tparam DIM: std::size_t dimesion of the vectorial space
             */
            template <std::size_t DIM>
            class orthonormal_base : public base<DIM> {

                
                public: 

                    /**
                     * @brief Construct a new ortho-normal base from a pack of vectors
                     * 
                     * @param vec: list of all the vector
                     * 
                     * @note The number of components must be the same as the dimesion of the space
                     */
                    template <typename... vectors>
                    explicit constexpr orthonormal_base(vectors... vec) {
                        
                        if (sizeof...(vec) != DIM)
                            throw std::invalid_argument("Cannot instantiate an ortho-normal base with a non-normalized base");
                        
                        else 
                            *this = {vec...}; 

                        if (!this->is_normalized()) 
                            throw std::invalid_argument("Cannot instantiate an ortho-normal base with a non-normalized base");

                    }


                    /**
                     * @brief Construct a new ortho-normal base object
                     * 
                     * @param mat: std::array<vector<DIM>, DIM> as l-value const reference
                     */
                    constexpr orthonormal_base(const std::array<vector<DIM>, DIM>& mat) :

                        base<DIM>(mat) {

                        if (!this->is_normalized()) 
                            throw std::invalid_argument("Cannot instantiate an ortho-normal base with a non-normalized base");

                    }


                    /**
                     * @brief Construct a new ortho-normal base object
                     * 
                     * @param mat: std::array<vector<DIM>, DIM> as r-value reference
                     */
                    constexpr orthonormal_base(std::array<vector<DIM>, DIM>&& mat) :

                        base<DIM>(std::move(mat)) {

                        if (!this->is_normalized()) 
                            throw std::invalid_argument("Cannot instantiate an ortho-normal base with a non-normalized base");

                    }

                    
                    /**
                     * @brief Construct a new ortho-normal base object from a square matrix
                     * 
                     * @param mat: square matrix as l-value const reference
                     */
                    constexpr orthonormal_base(const matrix<DIM, DIM>& mat) : 

                        base<DIM>(mat) {

                        if (!this->is_normalized()) 
                            throw std::invalid_argument("Cannot instantiate an ortho-normal base with a non-normalized base");

                    }


                    /**
                     * @brief Construct a new ortho-normal base object from a square matrix
                     * 
                     * @param mat: square matrix as r-value reference
                     */
                    constexpr orthonormal_base(matrix<DIM, DIM>&& mat) : 

                        base<DIM>(std::move(mat)) {

                        if (!this->is_normalized()) 
                            throw std::invalid_argument("Cannot instantiate an ortho-normal base with a non-normalized base");

                    }


                    /**
                     * @brief Construct a new ortho-normal base object from a base
                     * 
                     * @param base: base as l-value const reference
                     */
                    constexpr orthonormal_base(const base<DIM>& base) : 

                        base<DIM>(base) {

                        if (!this->is_normalized()) 
                            throw std::invalid_argument("Cannot instantiate an ortho-normal base with a non-normalized base");

                    }


                    /**
                     * @brief Construct a new ortho-normal base object from a base
                     * 
                     * @param base: base as r-value reference
                     */
                    constexpr orthonormal_base(base<DIM>&& base) : 

                        base<DIM>(std::move(base)) {

                        if (!this->is_normalized()) 
                            throw std::invalid_argument("Cannot instantiate an ortho-normal base with a non-normalized base");

                    }

                    
                    /// @brief Destroy the ortho-normal base object
                    ~orthonormal_base() = default;


            };


            /// @brief Template deduction guide for a list of vectors
            template <typename... vectors>
            orthonormal_base(const vectors&...) -> orthonormal_base<sizeof...(vectors)>;


            /// @brief Template deduction guide for an array of vectors
            template <class T, class... U>
            orthonormal_base(const std::array<T, sizeof...(U) + 1>&, const U&...) -> orthonormal_base<sizeof...(U) + 1>;


            /**
             * @brief Extract an orthonormal base from a matrix of vectors using the Gram-Schmidt algorithm
             * 
             * @tparam DIM 
             * @param system: square matrix<DIM> 
             * 
             * @return orthonormal_base<DIM> 
             */
            template <std::size_t DIM>
            constexpr orthonormal_base<DIM> extract_orthonormal_base(const matrix<DIM, DIM>& system) noexcept {

                matrix<DIM, DIM> ortho_base(system); 

                for (std::size_t i{}; i < DIM; ++i)
                    for (std::size_t j{1}; j < i; ++j)
                        ortho_base[i] -= system[j].projection(system[i]);

                base<DIM> base(ortho_base);
                return base.normalize();  

            }


        } // namespace linear_algebra


    } // namespace geometry


} // namespace scipp