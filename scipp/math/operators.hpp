/**
 * @file    math/operations/operators.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-24
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp::math {
    
    
    /// @brief Equal operator
    inline static constexpr auto operator==(const auto& x, const auto& y) noexcept { 

        return op::equal(x, y);
        
    }


    /// @brief Disqual operator
    inline static constexpr auto operator!=(auto x, auto y) noexcept { 

        return !op::equal(x, y);
        
    }


    /// @brief Greater than operator
    inline static constexpr auto operator>(const auto& x, const auto& y) noexcept { 

        return op::greater(x, y);
        
    }


    /// @brief Less than operator
    inline static constexpr auto operator<(const auto& x, const auto& y) noexcept { 

        return op::less(x, y);
        
    }


    /// @brief Greater than or equal operator
    inline static constexpr auto operator>=(const auto& x, const auto& y) noexcept { 

        return op::greater_equal(x, y);
        
    }


    /// @brief Less than or equal operator
    inline static constexpr auto operator<=(const auto& x, const auto& y) noexcept { 

        return op::less_equal(x, y);
        
    }


    /// @brief Negate operator 
    inline static constexpr auto operator-(auto x) noexcept { 
        
        return op::neg(x);
        
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
        
        return op::mult(x, y);
        
    }


    /// @brief Division operator
    inline static constexpr auto operator/(auto x, auto y) noexcept { 

        return op::div(x, y);
        
    }


    /// @brief Increment operator
    inline static constexpr auto operator+=(auto& x, const auto& y) noexcept { 
        
        return x = op::add(x, y);
        // return x; 
        
    }

    /// @brief Decrement operator
    inline static constexpr auto operator-=(auto& x, const auto& y) noexcept { 
        
        x = op::sub(x, y);
        return x; 
        
    }

    /// @brief Scale operator
    template <typename T>
        requires physics::is_scalar_v<T>
    inline static constexpr auto operator*=(auto& x, const T& y) noexcept { 

        return x = op::mult(x, y);
        
    }


    /// @brief Scale operator
    template <typename T>
        requires physics::is_scalar_v<T>
    inline static constexpr auto operator/=(auto& x, const T& y) {

        return x = op::div(x, y);
        
    }


} // namespace scipp::math