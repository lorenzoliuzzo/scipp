/**
 * @file    hermite.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-02
 * 
 * @copyright Copyright (c) 2023
 */


#include "sci++.hpp"


using namespace scipp;
using namespace physics; 
using namespace math; 
using namespace geometry; 
using namespace tools; 


int main(int argc, char** argv) {
    
    if (argc < 4) {

        std::cerr << "usage: hermite max_index start stop num_samples";
        return 1; 

    }

    timer sw; 

    std::size_t max_index = std::atoi(argv[1]);
    auto x_values = linspace<100>(static_cast<scalar_m>(std::atof(argv[2])), 
                                  static_cast<scalar_m>(std::atof(argv[3])));
        
    for (std::size_t i = 0; i < max_index; ++i) {

        vector<scalar_m, x_values.dim> v;    

        sw.start();
        for (std::size_t j = 0; j < x_values.dim; ++j)
            v[j] = hermite(i, x_values[j].value); 
        sw.stop();

        print("index", i); 
        print("elapsed time", sw.elapsed());

        plt::named_plot("H_" + std::to_string(i), static_cast<std::vector<double>>(x_values), static_cast<std::vector<double>>(v));

    }

    plt::title("Hermite polynomials");
    plt::legend();
    plt::tight_layout();
    plt::grid(true);
    // plt::ylim(-5000, 5000);
    plt::save("images/hermite.png");
    plt::show();
    
    return 0; 

}