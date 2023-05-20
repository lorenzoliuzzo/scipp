/**
 * @file    math/functions/operators.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-05-20
 * 
 * @copyright Copyright (c) 2023
 */


namespace scipp {
    
    
    /// @brief Addition operator
    inline static constexpr auto operator+(auto x, auto y) noexcept { 
        
        return math::op::add(x, y);
        
    }


    /// @brief Subtraction operator
    inline static constexpr auto operator-(auto x, auto y) noexcept { 
        
        return math::op::sub(x, y);
        
    }


    /// @brief Negate operator 
    inline static constexpr auto operator-(auto x) noexcept { 
        
        return math::op::neg(x);
        
    }
    

    /// @brief Multiplication operator
    inline static constexpr auto operator*(auto&& x, auto&& y) noexcept { 
        
        return math::op::mult(std::move(x), std::move(y));
        
    }


    /// @brief Division operator
    inline static constexpr auto operator/(auto&& x, auto&& y) { 

        return math::op::div(std::move(x), std::move(y));
        
    }


    /// @brief Increment operator
    inline static constexpr auto operator+=(auto& x, auto&& y) noexcept { 
        
        return x = math::op::add(x, std::move(y));
        
    }

    /// @brief Decrement operator
    inline static constexpr auto operator-=(auto& x, auto&& y) noexcept { 
        
        return x = math::op::sub(x, std::move(y));
        
    }


    /// @brief Scale operator
    template <typename T>
        requires (physics::is_scalar_v<T>)
    inline static constexpr auto operator*=(auto& x, T&& y) noexcept { 

        return x = math::op::mult(x, std::move(y));
        
    }


    /// @brief Scale operator
    template <typename T>
        requires (physics::is_scalar_v<T>)
    inline static constexpr auto operator/=(auto& x, T&& y) {

        return x *= math::op::inv(std::move(y));
        
    }
    
    
} // namespace scipp