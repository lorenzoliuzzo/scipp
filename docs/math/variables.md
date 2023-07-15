---
title: Variables
layout: default
permalink: /math/calculus/variables/
parent: Calculus namespace
author_profile: true
---

# Variables


This is the variable struct: 
    
```cpp
template <typename T>
struct variable {


    using value_t = T; 

    /// The pointer to the expression tree of variable operations
    expr_ptr<value_t> expr;


    /// Construct a default variable object
    constexpr variable() noexcept : variable(0.0) {}

    /// Construct a copy of a variable object
    constexpr variable(const variable& other) noexcept : variable(other.expr) {}

    /// Construct a copy of a variable object
    constexpr variable(variable&& other) noexcept : variable(std::move(other.expr)) {}


    /// Construct a variable object with given arithmetic value
    template <typename U>
    constexpr variable(const U& val) noexcept :
        expr(std::make_shared<independent_variable_expr<value_t>>(val)) {}

    /// Construct a variable object with given expression
    constexpr variable(const expr_ptr<value_t>& e) noexcept :
        expr(std::make_shared<dependent_variable_expr<value_t>>(e)) {}


    /// Destruct a variable object
    constexpr ~variable() {}


    /// Assign an arithmetic value to this variable.
    template <typename U>
    constexpr variable& operator=(const U& val) noexcept {

        *this = variable(val);
        return *this;

    }

    /// Assign an expression to this variable.
    constexpr variable& operator=(const expr_ptr<value_t>& x) noexcept {

        *this = variable(x);
        return *this;

    }

    /// Default copy assignment
    constexpr variable& operator=(const variable& x) noexcept {

        this->expr = x.expr;
        return *this;

    }


    /// Implicitly convert this variable object into an expression pointer.
    constexpr operator const expr_ptr<value_t>&() const {

        return expr;

    }

    constexpr explicit operator value_t() const {

        return this->expr->val;

    }


    /// Update the value of this variable with changes in its expression tree
    constexpr void update() {

        expr->update();
        
    }

    constexpr void update(T value) {

        if (auto independent_expr = std::dynamic_pointer_cast<independent_variable_expr<value_t>>(expr)) {

            independent_expr->val = value;
            independent_expr->update();

        } else
            throw std::logic_error("Cannot update the value of a dependent expression stored in a variable");

    }


}; // struct variable


```
# Variables