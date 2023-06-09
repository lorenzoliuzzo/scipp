/**
 * @file    test/eigen.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-02
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"

using namespace scipp; 
using namespace geometry; 
using namespace physics;
using namespace math;
using namespace tools;


int main() {

    vector<length_m, 3> v1 = make_vector(3.0m, 2.m, 1.0m);
    vector<length_m, 3> v2 = make_vector(2.m, 3.m, -1.m);
    vector<length_m, 3> v3 = make_vector(1.m, -1.m, 0.m);

    matrix<vector<length_m, 3>, 3> A(v1, v2, v3);

    print("A", A);

    // Perform QR decomposition on the matrix
    auto [Q, R] = gram_schmidt_qr(A);

    // Print the results
    print("Q", Q); 
    print("Q.transpose()", Q.transpose()); 
    print("Q.determinant()", Q.determinant());
    print("Q.transpose() * Q", Q.transpose() * Q); 
    print("R", R); 

    // Verify the result by reconstructing the original matrix
    auto A_reconstructed = Q * R;
    print("A_reconstructed", A_reconstructed);

    print("eigenvalues", R.diagonal());


    // auto [eval, evec] = eigen_qr(A); 
    // print("eigenvalues", eval);
    // print("eigenvectors", evec);

    return 0; 

}


int jacobi() {

    // std::vector<complex<scalar_m>> coeffs({complex<scalar_m>(1.0), 
    //                                             complex<scalar_m>(0.0), 
    //                                             complex<scalar_m>(-2.0), 
    //                                             complex<scalar_m>(0.0), 
    //                                             complex<scalar_m>(1.0)}); // x^4 - 2x^2 + 1 = 0
    // auto roots = math::find_roots<5>(coeffs);
    // for (const auto& r : roots.data) 
    //     print("Root", r); 


    // matrix<position3, 3> mat(position3(1.0m, 0.0m, 1.0m), position3(2.0m, 2.0m, -2.0m), position3(1.0m, 0.0m, 1.0m));
    // print("matrix", mat);

    // auto [eval, evec] = jacobi(mat); 

    // for (uint i = 0; i < 3; ++i) {
    //     print("eigenvalue", eval[i]);
    //     print("eigenvector", evec[i]);
    //     print("eigenvector * matrix", mat * evec[i]);
    //     print("eigenvector * eigenvalue", eval[i] * evec[i]);
    //     print("\n");
    // }


    // matrix<position2, 2> mat2(position2(5.0m, 3.0m), position2(-8.0m, -5.0m));
    // print("matrix", mat2);

    // auto [eval2, evec2] = jacobi(mat2);
    // for (uint i = 0; i < 2; ++i) {
    //     print("eigenvalue", eval2[i]);
    //     print("eigenvector", evec2[i]);
    //     print("matrix * eigenvector", mat2 * evec2[i]);
    //     print("eigenvalue * eigenvector", eval2[i] * evec2[i]);

    // }

    // auto x = mat2.eigenvectors(eval2);
    // print("eigenvectors", x);
    // print("\n");


    // matrix<position2, 2> mat4(position2(-1.0m, 5.0m), position2(1.0m, 3.0m));
    // auto y = gauss_jordan_solve(mat4, position2(0.0m, 0.0m));
    // print("gauss solve", y);
    // print("real", mat4 * y);





    return 0; 

}