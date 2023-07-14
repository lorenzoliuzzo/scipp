---
title: Expressions
layout: default
permalink: /math/calculus/expressions/
parent: Calculus namespace
author_profile: true
---

# Expressions

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