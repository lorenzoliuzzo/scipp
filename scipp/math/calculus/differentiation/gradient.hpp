/**
 * @file    math/calculus/variable.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation
 * @date    2023-07-03
 *
 * @copyright Copyright (c) 2023
 */

namespace scipp::math {


    namespace calculus {


        /// Return the gradient vector of variable y with respect to variables x.
        template <typename T, typename X>
        auto gradient(const variable<T>& y, Eigen::DenseBase<X>& x) {

            using U = VariableValueType<T>;

            using ScalarX = typename X::Scalar;
            static_assert(isVariable<ScalarX>, "Argument x is not a vector with Variable<T> (aka var) objects..");

            constexpr auto isVec = X::IsVectorAtCompileTime;
            static_assert(isVec, "Argument x is not a vector.");

            constexpr auto Rows = X::RowsAtCompileTime;
            constexpr auto MaxRows = X::MaxRowsAtCompileTime;

            const auto n = x.size();
            using Gradient = Vec<U, Rows, MaxRows>;
            Gradient g = Gradient::Zero(n);

            for(auto i = 0; i < n; ++i)
                x[i].expr->bind_value(&g[i]);

            y.expr->propagate(1.0);

            for(auto i = 0; i < n; ++i)
                x[i].expr->bind_value(nullptr);

            return g;
        }

/// Return the Hessian matrix of variable y with respect to variables x.
template<typename T, typename X, typename GradientVec>
auto hessian(const Variable<T>& y, Eigen::DenseBase<X>& x, GradientVec& g)
{
    using U = VariableValueType<T>;

    using ScalarX = typename X::Scalar;
    static_assert(isVariable<ScalarX>, "Argument x is not a vector with Variable<T> (aka var) objects.");

    using ScalarG = typename GradientVec::Scalar;
    static_assert(std::is_same_v<U, ScalarG>, "Argument g does not have the same arithmetic type as y.");

    constexpr auto Rows = X::RowsAtCompileTime;
    constexpr auto MaxRows = X::MaxRowsAtCompileTime;

    const auto n = x.size();

    // Form a vector containing gradient expressions for each variable
    using ExpressionGradient = Vec<ScalarX, Rows, MaxRows>;
    ExpressionGradient G(n);

    for(auto k = 0; k < n; ++k)
        x[k].expr->bind_expr(&G(k).expr);

    /* Build a full gradient expression in DFS tree traversal, updating
     * gradient expressions when encountering variables
     */
    y.expr->propagatex(constant<T>(1.0));

    for(auto k = 0; k < n; ++k) {
      x[k].expr->bind_expr(nullptr);
    }

    // Read the gradient value from gradient expressions' cached values
    g.resize(n);
    for(auto i = 0; i < n; ++i)
        g[i] = val(G[i]);

    // Form a numeric hessian using the gradient expressions
    using Hessian = Mat<U, Rows, Rows, MaxRows, MaxRows>;
    Hessian H = Hessian::Zero(n, n);
    for(auto i = 0; i < n; ++i)
    {
        for(auto k = 0; k < n; ++k)
            x[k].expr->bind_value(&H(i, k));

        // Propagate a second derivative value calculation down the gradient expression tree for variable i
        G[i].expr->propagate(1.0);

        for(auto k = 0; k < n; ++k)
            x[k].expr->bind_value(nullptr);
    }

    return H;
}

/// Return the Hessian matrix of variable y with respect to variables x.
template<typename T, typename X>
auto hessian(const Variable<T>& y, Eigen::DenseBase<X>& x)
{
    using U = VariableValueType<T>;
    constexpr auto Rows = X::RowsAtCompileTime;
    constexpr auto MaxRows = X::MaxRowsAtCompileTime;
    Vec<U, Rows, MaxRows> g;
    return hessian(y, x, g);
}

} // namespace detail

AUTODIFF_DEFINE_EIGEN_TYPEDEFS_ALL_SIZES(autodiff::var, var)

using detail::gradient;
using detail::hessian;

} // namespace autodiff