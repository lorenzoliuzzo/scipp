/**
 * @file    test/math/statistics.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-17
 * 
 * @copyright Copyright (c) 2023
 */



#include "scipp"

using namespace scipp;

using namespace tools; 
using namespace math; 
using namespace math::statistics;
using namespace geometry;
using namespace physics;


int main() { 

    timer t;
    timer total_t;

    total_t.start();
    std::mt19937 gen(std::random_device{}());
    std::normal_distribution<double> d(5, 1);
    vector<double, 520000> v;  

    t.start();
    t.stop();
    // print("trash time", t.elapsed());

    t.start();
    std::generate(v.data.begin(), v.data.end(), [&]() { return d(gen); });
    t.stop();
    // print("generation time", t.elapsed());


    vector<length_m, 520000> v2;
    std::transform(v.data.begin(), v.data.end(), v2.data.begin(), [](const auto& val) { return val * units::m; });
    
    t.start();
    auto av2 = average(v2);
    t.stop();
    print("average", av2); 
    print("elapsed time", t.elapsed());

    t.start();
    auto av = average(v);
    t.stop();
    print("average", av); 
    print("elapsed time", t.elapsed());

    t.start();
    auto va = variance(v);
    t.stop();
    print("variance", va); 
    print("elapsed time", t.elapsed());

    t.start();
    auto va2 = variance(v2);
    t.stop();
    print("variance", va2); 
    print("elapsed time", t.elapsed());

    // print("standard deviation", standard_deviation(v)); 
    // print("median", median(v)); 
    // print("mode", mode(v)); 

    // std::cout << "skewness: " << skewness(v) << std::endl;
    // std::cout << "kurtosis: " << kurtosis(v) << std::endl;
    // std::cout << "min: " << min(v) << std::endl;
    // std::cout << "max: " << max(v) << std::endl;
    // std::cout << "range: " << range(v) << std::endl;
    // std::cout << "sum: " << sum(v) << std::endl;
    // std::cout << "product: " << product(v) << std::endl;
    // std::cout << "cumulative sum: " << cumulative_sum(v) << std::endl;
    // std::cout << "cumulative product: " << cumulative_product(v) << std::endl;

    total_t.stop();
    print("total elapsed", total_t.elapsed());

    return 0;

}