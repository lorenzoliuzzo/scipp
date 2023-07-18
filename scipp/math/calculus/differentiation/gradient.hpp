/**
 * @file    scipp/math/calculus/variable.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation
 * @date    2023-07-17
 *
 * @copyright Copyright (c) 2023
 */

namespace scipp::math {


    namespace calculus {


        template <typename T1, size_t DIM, bool FLAG, typename T2>
        auto gradient(const geometry::vector<variable<T1>, DIM, FLAG>& y, const variable<T2>& x) {

            using result_t = geometry::vector<op::divide_t<T1, T2>, DIM, FLAG>;
            result_t result;

            meta::for_<DIM>([&](auto i) {
                result.data[i.index] = derivatives(y.data[i.index], wrt(x));
            });

            return result;

        }

        template <typename T1, size_t DIM, bool FLAG, typename T2>
        auto gradient(const geometry::vector<expr_ptr<T1>, DIM, FLAG>& y, const variable<T2>& x) {

            using result_t = geometry::vector<op::divide_t<T1, T2>, DIM, FLAG>;
            result_t result;

            meta::for_<DIM>([&](auto i) {
                variable v = y.data[i];
                result.data[i] = derivatives(v, wrt(x));
            });

            return result;

        }

        template <typename T1, size_t DIM, bool FLAG, typename T2>
        auto gradient(const geometry::vector<expr_ptr<T1>, DIM, FLAG>& y, const T2& x) {

            using result_t = geometry::vector<op::divide_t<T1, T2>, DIM, FLAG>;
            result_t result;
            variable<T2> var_x = x;

            meta::for_<DIM>([&](auto i) {
                variable v = y.data[i];
                result.data[i] = derivatives(v, wrt(var_x));
            });

            return result;

        }



    } // namespace calculus


} // namespace scipp::math


        // /// Return the gradient vector of variable y with respect to variables x.
        // template <typename T, typename X>
        // auto gradient(const variable<T>& y, Eigen::DenseBase<X>& x) {

        //     using U = VariableValueType<T>;

        //     using ScalarX = typename X::Scalar;
        //     static_assert(isVariable<ScalarX>, "Argument x is not a vector with Variable<T> (aka var) objects..");

        //     constexpr auto isVec = X::IsVectorAtCompileTime;
        //     static_assert(isVec, "Argument x is not a vector.");

        //     constexpr auto Rows = X::RowsAtCompileTime;
        //     constexpr auto MaxRows = X::MaxRowsAtCompileTime;

        //     const auto n = x.size();
        //     using Gradient = Vec<U, Rows, MaxRows>;
        //     Gradient g = Gradient::Zero(n);

        //     for(auto i = 0; i < n; ++i)
        //         x[i].expr->bind_value(&g[i]);

        //     y.expr->propagate(1.0);

        //     for(auto i = 0; i < n; ++i)
        //         x[i].expr->bind_value(nullptr);

        //     return g;
        // }

