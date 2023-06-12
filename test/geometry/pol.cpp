#include "sci++.hpp"


using namespace scipp;
using namespace tools; 
using namespace physics;
using namespace geometry;
using namespace math;


int main() {

    auto r1 = make_vector<complex<double>>(1., 0., 0., 0.); 
    auto r2 = make_vector<complex<double>>(0., 0., 0., 0.);
    auto r3 = make_vector<complex<double>>(0., 0., 1., 0.);
    auto r4 = make_vector<complex<double>>(0., 0., 0., 0.);

    auto r5 = make_vector<complex<double>>(1., 0., math::constants::i, 0.);
    auto r6 = make_vector<complex<double>>(0., 0., 0., 0.);
    auto r7 = make_vector<complex<double>>(-math::constants::i, 0., 1., 0.);
    auto r8 = make_vector<complex<double>>(0., 0., 0., 0.);


    auto mat1 = make_matrix<column_vector<complex<double>, 4>>(r1, r2, r3, r4);
    auto mat2 = make_matrix<column_vector<complex<double>, 4>>(r5, r6, r7, r8);
    print(mat1);
    print(mat2);
    
    print(mat1 + 10 * mat2);
    // print(mat1.determinant());  

    auto x = complex<double>(1.0, 2.0);
    print(x.real);

    x.real = 2.0;
    print(x.real);

    print(x.conj());


    print("mat1", mat1); 
    mat1.row(0) = r3.transpose(); 
    print("mat1", mat1);



    return 0; 

}