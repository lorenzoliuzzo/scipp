---
title: Expressions and variables
layout: default
permalink: /math/calculus/expressions-and-variables/
parent: Calculus namespace
grand_parent: Math namespace
nav_order: 0
author_profile: true
---

# Expressions and variables

## Expressions

The abstract type of any node type in the expression tree is given by a simple virtual struct: 

```cpp
template <typename T>
struct expr {

    
    T val{}; ///< The value of this expression node.


    /// Construct an expr object with given value.
    explicit constexpr expr(const T& v) noexcept : val(v) {}

    virtual constexpr ~expr() {}


    /// Bind a value pointer for writing the derivative during propagation
    virtual constexpr void bind_value(std::shared_ptr<void>) {}

    /// Update the contribution of this expression in the derivative of the root node of the expression tree.
    /// @param wprime The derivative of the root expression node w.r.t. the child expression of this expression node.
    virtual constexpr void propagate(std::shared_ptr<void>) = 0;


    /// Update the value of this expression
    virtual constexpr void update() = 0;


}; /// struct expr

```

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