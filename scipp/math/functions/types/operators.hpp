/**
 * @file    math/functions/types/operators.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-20
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp {
    
    
    /// @brief Equal operator
    inline constexpr auto operator==(auto x, auto y) noexcept { 

        return math::op::equal(std::move(x), std::move(y));
        
    }


    /// @brief Disqual operator
    inline constexpr auto operator!=(auto x, auto y) noexcept { 

        return !math::op::equal(std::move(x), std::move(y));
        
    }


    // /// @brief Greater than operator
    // inline constexpr auto operator>(auto&& x, auto&& y) noexcept { 

    //     return math::op::greater(std::move(x), std::move(y));
        
    // }


    // /// @brief Less than operator
    // inline constexpr auto operator<(auto&& x, auto&& y) noexcept { 

    //     return math::op::less(std::move(x), std::move(y));
        
    // }


    // /// @brief Greater than or equal operator
    // inline constexpr auto operator>=(auto&& x, auto&& y) noexcept { 

    //     return math::op::greater_equal(std::move(x), std::move(y));
        
    // }


    // /// @brief Less than or equal operator
    // inline constexpr auto operator<=(auto&& x, auto&& y) noexcept { 

    //     return math::op::less_equal(std::move(x), std::move(y));
        
    // }
    
    /// @brief Addition operator
    template <typename T1, typename T2>
    inline constexpr auto operator+(T1 x, T2 y) noexcept { 

        return math::op::add(std::forward<T1>(x), std::forward<T2>(y));
        
    }


    /// @brief Subtraction operator
    template <typename T1, typename T2>
    inline constexpr auto operator-(T1 x, T2 y) noexcept { 
        
        return math::op::add(std::forward<T1>(x), math::op::neg(std::forward<T2>(y)));
        
    }


    /// @brief Negate operator 
    inline constexpr auto operator-(auto x) noexcept { 
        
        return math::op::neg(x);
        
    }
    

    /// @brief Multiplication operator
    template <typename T1, typename T2>
    inline constexpr auto operator*(T1 x, T2 y) noexcept { 
        
        return math::op::mult(std::forward<T1>(x), std::forward<T2>(y));
        
    }


    /// @brief Division operator
    template <typename T1, typename T2>
    inline constexpr auto operator/(T1 x, T2 y) noexcept { 

        return math::op::mult(std::forward<T1>(x), math::op::inv(std::forward<T2>(y)));
        
    }


    /// @brief Increment operator
    inline constexpr auto operator+=(auto& x, auto&& y) noexcept { 
        
        return x = math::op::add(x, std::move(y));
        
    }

    /// @brief Decrement operator
    inline constexpr auto operator-=(auto& x, auto&& y) noexcept { 
        
        return x = math::op::add(x, math::op::neg(std::move(y)));
        
    }


    /// @brief Scale operator
    template <typename T>
        requires (physics::is_scalar_v<T>)
    inline constexpr auto operator*=(auto& x, T&& y) noexcept { 

        return x = math::op::mult(x, std::forward<T>(y));
        
    }


    /// @brief Scale operator
    template <typename T>
        requires (physics::is_scalar_v<T>)
    inline constexpr auto operator/=(auto& x, T&& y) {

        return x =  math::op::mult(x, math::op::inv(std::forward<T>(y)));
        
    }
    
    
} // namespace scipp