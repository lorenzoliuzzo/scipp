/**
 * @file linear_solver.hpp
 * @author Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief 
 * @date 2022-12-19
 * 
 * @copyright Copyright (c) 2023
 */





namespace scipp {


    namespace geometry {

        
        namespace linear_algebra {


    enum matrix_solver_methods {

        GEPP, // Gauss elimination with partial pivoting

        GJEPP, // Gauss-Jordan elimination with partial pivoting

        gauss_seidel,

        jacobi

    };

    /**
        * @brief Solve the linear system Ax = b
        * 
        * @tparam DIM: dimension of the vector b
        * @tparam rows: number of rows of the matrix A
        * @tparam cols: number of columns of the matrix A
        * @param A: matrix<rows, cols> as l-value const reference
        * @param b: vector<DIM> as l-value const reference
        * @param method: matrix_solver_methods
        * 
        * @return vector<DIM> 
        */
    template <size_t DIM, size_t rows, size_t cols>
    vector<DIM> solve_matrix(const matrix<rows, cols>& A, const vector<DIM>& b, matrix_solver_methods method) {

        switch (method) {

            case matrix_solver_methods::GEPP: 
                return gauss_elimination(A, b);

            case matrix_solver_methods::GJEPP:
                return gauss_jordan_elimination(A, b);

            // case methods::gauss_seidel:
            //     return gauss_seidel(A, b);

            // case methods::jacobi:
            //     return jacobi(A, b);

            default:
                throw std::invalid_argument("The method is not implemented");

        }


    }; // struct matrix_solver


    /// @brief Solve the linear system Ax = b with the Gauss elimination method
    template <size_t DIM, size_t rows, size_t cols>
    vector<DIM> gauss_elimination(const matrix<rows, cols>& A, const vector<DIM>& b) {

        static_assert(cols >= DIM, "The matrix must have at least as many columns as the vector dimesion");

        matrix<DIM, DIM + 1> A_b = A.augmented(b); 
        vector<DIM> x;

        for (size_t k{}; k < DIM; k++) {
            
            size_t pivot{k};
            measurement maxPivot;

            // Find the best pivot
            for (size_t i{k}; i < DIM; i++) 
                if (abs(A_b(i, k) > maxPivot)) {

                    maxPivot = abs(A_b(i, k));
                    pivot = i;

                }

            // Swap rows k and p
            if (pivot != k)
                for (size_t i{k}; i < DIM + 1; i++)
                    std::swap(A_b(pivot, i), A_b(k, i));

            // Elimination of variables
            for (size_t i{k + 1}; i < DIM; i++) {

                measurement factor = A_b(i, k) / A_b(k, k);

                for (size_t j{k}; j < DIM + 1; j++)
                    A_b(i, j) -= factor * A_b(k, j);

            }

        }

        // Back substitution
        for (long int k = DIM - 1; k >= 0; k--) {

            measurement sum = A_b(k, DIM);
            for (size_t j = k + 1; j < DIM; j++)
                sum -= A_b(k, j) * x[j];

            x[k] = sum / A_b(k, k);

        }

        return x; 

    }


    /// @brief Solve the linear system Ax = b with the Gauss-Jordan elimination method
    template <size_t DIM, size_t rows, size_t cols>
    vector<DIM> gauss_jordan_elimination(const matrix<rows, cols>& A, const vector<DIM>& b) {

        matrix<rows, cols + 1> A_b = A.augmented(b);
        measurement element;
        vector<DIM> result;

        // partial pivoting
        for (int i = DIM - 1; i > 0; i--) 
            if (abs(A_b(i - 1, 0)) < abs(A_b(i, 0)))
                for (size_t j{}; j <= DIM; j++) 
                    std::swap(A_b(i - 1, j), A_b(i, j));

        // gauss elimination
        for (size_t j{}; j < DIM; j++) 
            for (size_t i{}; i < DIM; i++) 
                if (i != j) {

                    element = A_b(i, j) / A_b(j, j);
                    
                    for (size_t k{}; k <= DIM; k++) 
                        A_b(i, k) -= element * A_b(j, k);

                }

        // diagonal elements
        for (size_t i{}; i < DIM; i++) 
            result[i] = A_b(i, DIM) / A_b(i, i);

        return result;

    }


        } // namespace linear_algebra


    } // namespace geometry


} // namespace scipp