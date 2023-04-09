/**
 * @file    test/geometry.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-04
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"
#include <cassert>


using namespace scipp; 
using namespace geometry; 
using namespace physics; 
using namespace physics::units; 
using namespace math; 
using namespace tools;


int main() {


    // position2 A(-10.m, -10.m);
    // position2 B(10.m, 10.m); 

    // auto AB = segment(A, B);
    // print(AB(0.5));
    // print(AB(0.0));
    // print(AB(1.0));

    
    // auto r = line(position2(), B);
    // print(r(0.5));

    auto c = circumference(position2(), 2.m);
    print("L", integrals::length(c));
    auto aster = asteroid(position2(), 1.0);
    print("asteroL", integrals::length(aster));

    if (c.is_closed())
        print("closed");
    else
        print("not closed");

    auto A = c(scalar_m(0.0));
    auto B = c(scalar_m(1.0));
    print(B - A);


    auto e = ellipse(position2(), 2.m, 1.m);
    auto s = sphere(position3(), 2.m);
    print("N", s(make_vector(scalar_m(0.0), scalar_m(0.0))));
    print("N", s(make_vector(scalar_m(0.50000000), scalar_m(0.5))));
    print("N", s(make_vector(scalar_m(0.0), scalar_m(0.50000000))));



    vector<physics::angle_m, 200> angles;
    vector<physics::angle_m, 200> angles2;
    // vector<physics::scalar_m, 200> cosines;
    // vector<physics::scalar_m, 200> sines;
    matrix<position2, 200> circle_pts;
    matrix<position2, 200> ell_pts;
    matrix<position3, 200> s_pts;
    

    for (std::size_t i{}; i < 200; ++i) {

        angles[i] = static_cast<double>(i) / 200.;
        circle_pts.column(i) = c(angles[i]);
        ell_pts.column(i) = e(angles[i]);

    }


    // plt::named_plot("cos", static_cast<std::vector<double>>(angles), static_cast<std::vector<double>>(cosines));
    // plt::named_plot("sin", static_cast<std::vector<double>>(angles), static_cast<std::vector<double>>(sines));
    // plt::legend();
    // plt::show();

    // plt::plot(static_cast<std::vector<double>>(spiral_pts.row(0)), static_cast<std::vector<double>>(spiral_pts.row(1)));
    // plt::show();

    plt::figure_size(860, 860);
    plt::title("Curves");
    plt::named_plot("circle", static_cast<std::vector<double>>(circle_pts.row(0)), static_cast<std::vector<double>>(circle_pts.row(1)));
    plt::named_plot("ellipse", static_cast<std::vector<double>>(ell_pts.row(0)), static_cast<std::vector<double>>(ell_pts.row(1)));
    plt::legend(); 
    plt::save("images/curves.png");
    plt::show();

    // plt::plot3(static_cast<std::vector<double>>(s_pts.row(0)), static_cast<std::vector<double>>(s_pts.row(1)), static_cast<std::vector<double>>(s_pts.row(2)));
    // plt::show();


    // auto s = sphere(position3(), 2.m);
    // print(s(0.0, 0.0)); 


    // auto c2 = circle2<position2>(position2(), 2.m);
    // auto pts = linspace<100>(c2);
    // plt::plot(static_cast<std::vector<double>>(pts.row(0)), static_cast<std::vector<double>>(pts.row(1)));
    // plt::show();


    // auto segment_pts = linspace<250>(AB); 


    // auto r_segment_pts1 = linspace<100>(r(0.5), r(2.5));
    // auto r_segment_pts2 = linspace<100>(r(3.5), r(4.5));

    // auto s_pts = linspace<50>(s);

    // for (std::size_t i{}; i < s_pts.columns; ++i)
    //     print(std::to_string(i), s_pts.column(i)); 


    // std::map<std::string, std::string> keywords;
    // keywords["marker"] = "o";
    // keywords["color"] = "grey";

    // plt::figure_size(1200, 1200);
    // plt::title("circles");
    // plt::plot(static_cast<std::vector<double>>(s_pts.row(0)), static_cast<std::vector<double>>(s_pts.row(1)));
    // plt::show(); 
    // plt::plot(static_cast<std::vector<double>>(s_pts.row(0)), static_cast<std::vector<double>>(s_pts.row(2)));
    // plt::show(); 


    // plt::title("sphere");
    // plt::save("images/sphere.png");
    // plt::xlabel("x");
    // plt::ylabel("y");
    // plt::set_zlabel("z"); // set_zlabel rather than just zlabel, in accordance with the Axes3D method

    // plt::title("sphere");
    // plt::plot(static_cast<std::vector<double>>(s_pts.row(0)), static_cast<std::vector<double>>(s_pts.row(1)), keywords);
    // plt::show();


    // auto C = circle(B, 2.m);
    // auto circ_pts = linspace<100>(C); 

    // auto r = line(position2(), B); 
    // print(r.direction); 

    // plt::title("line"); 
    // plt::plot(static_cast<std::vector<double>>(r_segment_pts1.row(0)), static_cast<std::vector<double>>(r_segment_pts1.row(1)));
    // plt::plot(static_cast<std::vector<double>>(r_segment_pts2.row(0)), static_cast<std::vector<double>>(r_segment_pts2.row(1)));
    // plt::show(); 

    
    return 0; 

}