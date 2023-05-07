/**
 * @file    math/polynomials/ruffini.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-05-03
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {

    auto ruffini(const std::vector<std::complex<double>>& a, const std::complex<double>& r) noexcept {

        // std::fill(result.data.begin(), result.data.begin() + N - 1, std::complex<double>{0});
        auto n = a.size();
        std::vector<std::complex<double>> result(n - 1);
        result[0] = a[0];
        for (size_t i = 1; i < n; ++i) 
            result[i] = a[i] + result[i - 1] * r;
        
        
        std::complex<double> remainder = a[n] + r * result[n - 1];
        
        return std::make_pair(result, remainder);   

    }


} // namespace scipp::math