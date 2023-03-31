/**
 * @file    matrix.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   Example of matrix constructions
 * @date    2023-03-19
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"
#include <cassert>
#include <thread>

using namespace scipp; 
using namespace physics; 
using namespace physics::units; 
using namespace math; 
using namespace geometry;
using namespace tools;


int main() {


    timer sw; 
    sw.start();    
    
    std::cout << "sizeof matrix 2x2: " << sizeof(matrix<position2, 2>) << " bytes\n"; 
    std::cout << "sizeof matrix 3x3: " << sizeof(matrix<position3, 3>) << " bytes\n\n";

    auto mat1 = make_matrix<position2, 2>(position2(3.0m, 0.4m), 
                                          position2(-1.02m, -3.54m));

    // mat1.print(); 
    // mat2.print(); 

    // (-mat2).print(); 
    // (mat2 * 2.0).print(); 
    // (mat2 * 2.0m).print(); 
    // mat2.transpose().print(); 

    // auto id2 = make_matrix<position2, 2>(position2(1.0m, 0.0m), position2(0.0m, 1.0m)); 
    // (id2 * position2(3.0m, -3.0m)).print(); 

    // auto id3 = matrix<position3, 3>::identity(); 
    // id3.print(); 
    // id3.determinant().print();


    // matrix<vector<length_m, 4>, 4> mat4;

    // mat4.print();
    // mat4.determinant().print();

    // decltype(mat4)::identity().determinant().print(); 
    // decltype(mat4)::identity().trace().print(); 

    // mat1.inverse().print();
    // mat1.cofactors().print();

    // mat1.solve(lin_velocity2(1.0 * m_s, 2.0 * m_s)).print();
    // (mat1 * vector(0.146886 / s, 0.626714 / s)).print(); 

    auto mat2 = make_matrix<position2>(position2(1.0m, 2.0m), 
                                       position2(3.0m, 4.0m));
    mat2.print(); 
    mat2.determinant().print();
    mat2.inverse().print(); 
    (mat2.inverse() * mat2).print();

    auto mat3 = make_matrix<position3>(position3(3.0m, 0.4m, 0.0m), 
                                       position3(-1.02m, -3.54m, -1.0m), 
                                       position3(-1.0m, 0.5m, 12.4m)); 
    mat3.print(); 
    mat3.determinant().print();
    mat3.inverse().print(); 

    auto x = lin_velocity3(-5.2 * m_s, 34.5 * m_s, 0.2 * m_s);
    x.print(); 
    (mat3 * mat3.solve(x)).print(); 
    mat3.solve(x).print();

    mat2.lower_triangular().print();
    mat2.upper_triangular().print();

    sw.stop();
    std::cout << "trash time: " << sw.elapsed() << "\n\n";

    // auto y = position3(-5.2m, 34.5m, 0.2m);
    
    // sw.start();
    // auto solve_gj = mat3.gauss_jordan_solve(y); 
    // sw.stop(); 
    // std::cout << "solve_gauss_jordan: " << sw.elapsed() << '\n';

    // sw.start();
    // auto solve_det = mat3.solve(y); 
    // sw.stop();
    // std::cout << "solve_det: " << sw.elapsed() << '\n';

    // sw.start();
    // auto solve_g = mat3.gauss_solve(y); 
    // sw.stop(); 
    // std::cout << "solve_gauss: " << sw.elapsed() << '\n';

    sw.start(); 
    auto rand_mat = make_random_matrix<vector<length_m, 20>, 20>(); 
    sw.stop();
    std::cout << "rand_mat: " << sw.elapsed() << '\n';

    sw.start();
    auto det = rand_mat.determinant();
    sw.stop();
    std::cout << "det: " << sw.elapsed() << '\n';
    
    print("det", det);

    assert(det != 0.0);

    auto y = make_random_vector<length_m, 20>();
    

    sw.start();
    auto solve_det = rand_mat.solve(y); 
    sw.stop();
    print("solve_det", sw.elapsed());

    sw.start();
    auto solve_g = rand_mat.gauss_solve(y); 
    sw.stop(); 
    print("solve_gauss", sw.elapsed());

    sw.start();
    auto solve_gj = rand_mat.gauss_jordan_solve(y); 
    sw.stop(); 
    print("solve_gauss_jordan", sw.elapsed());

    print("print a vector", mat2.row(0));

    // mat3.inverse().print(); 

    // (mat3 * mat3.inverse()).print(); 
    // (mat3.inverse() * mat3).print(); 

    // auto x = lin_velocity2(1.0 * m_s, -1.0 * m_s);
    // (mat3 * x).print();
    // (mat3.inverse() * (mat3 * x)).print(); 
    // mat3.solve(vector(measurement(2.0, m2_s), measurement(-2.0, m2_s))).print();

    return 0; 

}