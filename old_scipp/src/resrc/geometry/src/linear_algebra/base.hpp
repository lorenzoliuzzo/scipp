/**
 * @file base.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2022-12-19
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp {


    namespace geometry {


        namespace linear_algebra {

            
            /**
             * @brief Class to represent a base of a vectorial space as a matrix of l.i. vectors
             * 
             * @tparam DIM: std::size_t dimesion of the vectorial space
             */
            template <std::size_t DIM>
            class base : public matrix<DIM, DIM> {

                
                public: 

                    // =======================================
                    // ====== CONSTRUCTORS & DESTRUCTOR ======
                    // =======================================


                    /// @brief Construct a new base object as a canonical base
                    explicit constexpr base() noexcept : 

                        matrix<DIM, DIM>() {

                            for (std::size_t i = 0; i < DIM; ++i) 
                                this->element(i, i) = measurement(1.);

                        }


                    /**
                     * @brief Construct a new base from a pack of vectors
                     * 
                     * @param vec: list of all the vector
                     * 
                     * @note The number of components must be the same as the dimesion of the space
                     */
                    template <typename... vectors>
                    explicit constexpr base(vectors... vec) : 
                        
                        matrix<DIM, DIM>(vec...) {

                        if (this->determinant() == 0) 
                            throw std::invalid_argument("Cannot instantiate a base with linearly dependent vectors");

                    }


                    /**
                     * @brief Construct a new base object
                     * 
                     * @param mat: std::array<vector<DIM>, DIM> as l-value const reference
                     */
                    constexpr base(const std::array<vector<DIM>, DIM>& mat) :

                        matrix<DIM, DIM>(mat) {

                        if (this->determinant() == 0) 
                            throw std::invalid_argument("Cannot instantiate a base with linearly dependent vectors");

                    }


                    /**
                     * @brief Construct a new base object
                     * 
                     * @param mat: std::array<vector<DIM>, DIM> as r-value reference
                     */
                    constexpr base(std::array<vector<DIM>, DIM>&& mat) :

                        matrix<DIM, DIM>(std::move(mat)) {

                        if (this->determinant() == 0) 
                            throw std::invalid_argument("Cannot instantiate a base with linearly dependent vectors");

                    }

                    
                    /**
                     * @brief Construct a new base object from a square matrix
                     * 
                     * @param mat: square matrix as l-value const reference
                     */
                    constexpr base(const matrix<DIM, DIM>& mat) : 

                        matrix<DIM, DIM>(mat) {

                        if (this->determinant() == 0) 
                            throw std::invalid_argument("Cannot instantiate a base with linearly dependent vectors");

                    }


                    /**
                     * @brief Construct a new base object from a square matrix
                     * 
                     * @param mat: square matrix as r-value reference
                     */
                    constexpr base(matrix<DIM, DIM>&& mat) : 

                        matrix<DIM, DIM>(std::move(mat)) {

                        if (this->determinant() == 0) 
                            throw std::invalid_argument("Cannot instantiate a base with linearly dependent vectors");

                    }


                    /**
                     * @brief Copy construct a new base object from another base
                     * 
                     * @param other: base as l-value const reference
                     */
                    constexpr base(const base& other) noexcept :

                        matrix<DIM, DIM>(other) {}


                    /**
                     * @brief Move construct a new base object from another base
                     * 
                     * @param other: base as r-value reference
                     */
                    constexpr base(base&& other) noexcept :

                        matrix<DIM, DIM>(std::move(other)) {}

                    
                    /// @brief Destroy the base object
                    ~base() = default;


                    // =======================================
                    // ============ BASE METHODS =============
                    // =======================================

                    /**
                     * @brief Access a vector of the base
                     * 
                     * @param i: std::size_t 
                     * 
                     * @return constexpr vector<DIM>
                     */
                    constexpr vector<DIM> operator[](const std::size_t& i) const {
                        
                        if (i > DIM) 
                            throw std::out_of_range("Cannot access a vector element of the base with an index out of range");

                        else 
                            return this->column(i); 
                        
                    }


                    /**
                     * @brief Print the base vectors to the standard output
                     * 
                     * @param os: ostream as l-value reference
                     * @param base: base as l-value const reference
                     * 
                     * @return std::ostream&
                     */
                    friend std::ostream& operator<<(std::ostream& os, const base& base) noexcept {

                        os << "base: < ";
                        for (std::size_t i{}; i < DIM; ++i)
                            os << base[i] << ((i != DIM - 1) ? ", ": " >\n"); 
                        
                        return os;

                    }


                    /**
                     * @brief Get the dimesion of the space
                     * 
                     * @return std::size_t 
                     */
                    static constexpr std::size_t dimesions() {

                        return DIM; 

                    }


                    /// @brief Check if the base is normalized
                    constexpr bool is_normalized() const noexcept {

                        for (std::size_t i{}; i < DIM; ++i) 
                            if (!this->column(i).is_normalized()) 
                                return false; 

                        return true; 

                    }


                    /**
                     * @brief Get an ortho-normal base from the current base
                     * 
                     * @return constexpr base<DIM> 
                     */
                    constexpr base<DIM> normalize() const noexcept {

                        if (!this->is_normalized()) {

                            matrix<DIM, DIM> ortho_normal(this->data());
                            for (std::size_t i{}; i < DIM; ++i) 
                                if (!this->column(i).is_normalized()) 
                                    ortho_normal[i] /= this->column(i).norm(); 

                            return ortho_normal; 

                        } else 
                            return *this; 

                    }


                    /**
                     * @brief Decompose a vector  
                     * 
                     * @param vec: vector<DIM> as l-value const reference
                     * 
                     * @return 
                     */
                    constexpr vector<DIM> decompose(const vector<DIM>& vec,     
                                                    matrix_solver_methods method = matrix_solver_methods::GEPP) const {

                        return solve_matrix(*this, vec, method);

                    }


                    /// @brief Print the base to the standard output
                    void print() const noexcept {

                        std::cout << "base: < ";
                        for (std::size_t i{}; i < DIM; ++i)
                            std::cout << this->element(i) << ((i != DIM - 1) ? ", ": " >\n"); 
                        
                    }


            }; // class base


            /// @brief Template deduction guide for a list of vectors
            template <typename... vectors>
            base(const vectors&...) -> base<sizeof...(vectors)>;


            /// @brief Template deduction guide for an array of vectors
            template <class T, class... U>
            base(const std::array<T, sizeof...(U) + 1>&, const U&...) -> base<sizeof...(U) + 1>;


            /**
             * @brief Extract an orthogonal base from a matrix of vectors using the Gram-Schmidt algorithm
             * 
             * @tparam DIM 
             * @param system: square matrix<DIM> 
             * 
             * @return base<DIM> 
             */
            template <std::size_t DIM>
            constexpr base<DIM> extract_orthogonal_base(const matrix<DIM, DIM>& system) noexcept {

                matrix<DIM, DIM> ortho_base(system); 

                for (std::size_t i{}; i < DIM; ++i)
                    for (std::size_t j{1}; j < i; ++j)
                        ortho_base[i] -= system[j].projection(system[i]);

                return ortho_base; 

            }


        } // namespace linear_algebra


    } // namespace geometry


} // namespace scipp