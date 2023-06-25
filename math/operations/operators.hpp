/**
 * @file    math/operations/operators.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-24
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {
    
    
    // /// @brief Equal operator
    // inline static constexpr auto operator==(const auto& x, const auto& y) noexcept { 

    //     return op::equal(x, y);
        
    // }


    // /// @brief Disqual operator
    // inline static constexpr auto operator!=(auto x, auto y) noexcept { 

    //     return !op::equal(x, y);
        
    // }


    // /// @brief Greater than operator
    // inline static constexpr auto operator>(auto&& x, auto&& y) noexcept { 

    //     return op::greater(std::move(x), std::move(y));
        
    // }


    // /// @brief Less than operator
    // inline static constexpr auto operator<(auto&& x, auto&& y) noexcept { 

    //     return op::less(std::move(x), std::move(y));
        
    // }


    // /// @brief Greater than or equal operator
    // inline static constexpr auto operator>=(auto&& x, auto&& y) noexcept { 

    //     return op::greater_equal(std::move(x), std::move(y));
        
    // }


    // /// @brief Less than or equal operator
    // inline static constexpr auto operator<=(auto&& x, auto&& y) noexcept { 

    //     return op::less_equal(std::move(x), std::move(y));
        
    // }


    /// @brief Negate operator 
    inline static constexpr auto operator-(auto x) noexcept { 
        
        return op::negate(x);
        
    }
    

    /// @brief Addition operator
    inline static constexpr auto operator+(auto x, auto y) noexcept { 

        return op::add(x, y);
        
    }


    /// @brief Subtraction operator
    inline static constexpr auto operator-(auto x, auto y) noexcept { 
        
        return op::sub(x, y);
        
    }


    /// @brief Multiplication operator
    inline static constexpr auto operator*(auto x, auto y) noexcept { 
        
        return op::multiply(x, y);
        
    }


    /// @brief Division operator
    inline static constexpr auto operator/(auto x, auto y) noexcept { 

        return op::divide(x, y);
        
    }


    /// @brief Increment operator
    inline static constexpr auto operator+=(auto& x, const auto& y) noexcept { 
        
        return x = op::add(x, y);
        
    }

    /// @brief Decrement operator
    inline static constexpr auto operator-=(auto& x, const auto& y) noexcept { 
        
        return x = op::sub(x, y);
        
    }

    /// @brief Scale operator
    template <typename T>
        requires physics::is_scalar_v<T>
    inline static constexpr auto operator*=(auto& x, const T& y) noexcept { 

        return x = op::multiply(x, y);
        
    }


    /// @brief Scale operator
    template <typename T>
        requires physics::is_scalar_v<T>
    inline static constexpr auto operator/=(auto& x, const T& y) {

        return x = op::divide(x, y);
        
    }


} // namespace scipp::math