/**
 * @file    math/functions/types/operators.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-20
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp {
    
    
    /// @brief Addition operator
    inline constexpr auto operator+(auto x, auto y) noexcept { 

        return math::op::add(std::move(x), std::move(y));
        
    }


    /// @brief Subtraction operator
    inline constexpr auto operator-(auto x, auto y) noexcept { 
        
        return math::op::add(std::move(x), math::op::neg(std::move(y)));
        
    }


    /// @brief Negate operator 
    inline constexpr auto operator-(auto x) noexcept { 
        
        return math::op::neg(x);
        
    }
    

    /// @brief Multiplication operator
    inline constexpr auto operator*(auto&& x, auto&& y) noexcept { 
        
        return math::op::mult(std::move(x), std::move(y));
        
    }


    /// @brief Division operator
    inline constexpr auto operator/(auto&& x, auto&& y) { 

        return math::op::mult(std::move(x), math::op::inv(std::move(y)));
        
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

        return x = math::op::mult(x, std::move(y));
        
    }


    /// @brief Scale operator
    template <typename T>
        requires (physics::is_scalar_v<T>)
    inline constexpr auto operator/=(auto& x, T&& y) {

        return x =  math::op::mult(x, math::op::inv(std::move(y)));
        
    }
    
    
} // namespace scipp