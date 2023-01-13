#include "sci++.hpp"

using namespace scipp;


int main() {


    tools::timer sw; 
    std::vector<measurement> vec;
    for (int i{}; i < 1000000; ++i) 
        vec.push_back(measurement(i * m));

    sw.start(); 
        auto mean = math::statistics::mean(vec);
    sw.stop();
    std::cout << mean << '\n';
    std::cout << sw.elapsed(ns) << '\n';
    std::cout << "sdom: " << math::statistics::sdom(vec) << '\n';
    

    return 0; 

}