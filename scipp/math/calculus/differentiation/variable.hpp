/**
 * @file    math/calculus/variable.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation
 * @date    2023-07-15
 *
 * @copyright Copyright (c) 2023
 */

namespace scipp::math {


    namespace calculus {


        template <typename T>
        struct variable_expr : expr<T> {

            std::shared_ptr<void> grad_ptr;
            std::shared_ptr<void> gradx_ptr;


            constexpr variable_expr(const T& v) noexcept : expr<T>(v) {}


            virtual constexpr void bind_value(std::shared_ptr<void> grad) {   

                grad_ptr = grad;

            }

            virtual constexpr void bind_expr(std::shared_ptr<void> gradx) {

                gradx_ptr = std::static_pointer_cast<expr<T>>(gradx);

            }

        };

        template <typename T>
        struct independent_variable_expr : variable_expr<T> {

            using variable_expr<T>::grad_ptr;
            using variable_expr<T>::gradx_ptr;


            constexpr independent_variable_expr(const T& v) noexcept : variable_expr<T>(v) {}


            virtual constexpr void propagate(std::shared_ptr<void> wprime) {

                if (grad_ptr.get()) {

                    auto derivative = std::static_pointer_cast<T>(wprime);
                    auto value = std::static_pointer_cast<T>(grad_ptr);

                    *value += *derivative;
                    
                }

            }


            virtual constexpr void update() override {}

        };

        template <typename T>
        struct dependent_variable_expr : variable_expr<T> {

            using variable_expr<T>::grad_ptr;
            using variable_expr<T>::gradx_ptr;

            expr_ptr<T> expr;

            constexpr dependent_variable_expr(const expr_ptr<T>& e) noexcept
                : variable_expr<T>(e->val), expr(e) {}


            constexpr void propagate(std::shared_ptr<void> wprime) override {

                if (grad_ptr.get()) {

                    auto derivative = std::static_pointer_cast<T>(wprime);
                    auto value = std::static_pointer_cast<T>(grad_ptr);

                    *value += *derivative;

                }

                expr->propagate(wprime);

            }


            constexpr void update() override {

                this->expr->update();
                this->val = this->expr->val;

            }
            
        };


        /// @brief The variable type used for reverse mode automatic differentiation.
        template <typename T>
        struct variable {


            using value_t = T; 

            
            expr_ptr<value_t> expr; //< The pointer to the expression tree of variable operations


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

                return *this = variable(val);

            }

            /// Assign an expression to this variable.
            constexpr variable& operator=(const expr_ptr<value_t>& x) noexcept {

                return *this = variable(x);

            }

            /// Default copy assignment
            constexpr variable& operator=(const variable& x) noexcept {

                this->expr = x.expr;
                return *this;

            }


            /// Implicitly convert this variable object into an expression pointer.
            constexpr operator const expr_ptr<value_t>&() const {

                return this->expr;

            }       

            /// Implicitly convert this variable object into an arithmetic value.
            constexpr explicit operator value_t() const {

                return this->expr->val;

            }


            /// Update the value of this variable with changes in its expression tree
            constexpr void update() {

                this->expr->update();
                
            }

            /// Update the value of this variable with a given arithmetic value
            constexpr void update(T value) {

                if (auto independent_expr = std::dynamic_pointer_cast<independent_variable_expr<value_t>>(this->expr)) {

                    independent_expr->val = value;
                    independent_expr->update();

                } else
                    throw std::logic_error("Cannot update the value of a dependent expression stored in a variable");

            }


        }; // struct variable

        //------------------------------------------------------------------------------
        // EXPRESSION TRAITS
        //------------------------------------------------------------------------------


        template <typename T, typename U>
        using expr_common_t = std::common_type_t<decltype(expr_value(std::declval<T>())), decltype(expr_value(std::declval<U>()))>;

        template <class>
        struct sfinae_true : std::true_type {};

        // template <typename T>
        // static auto is_expr_test(int) -> sfinae_true<decltype(expr_value(std::declval<T>()))>;

        // template <typename T>
        // static auto is_expr_test(long) -> std::false_type;

        // template <typename T>
        // struct is_expr : decltype(is_expr_test<T>(0)) {};

        // template <typename T>
        // constexpr bool is_expr_v = is_expr<T>::value;

        template <typename T, typename U>
            requires std::is_arithmetic_v<U>
        constexpr expr_ptr<T> coerce_expr(const U &u) {

            return constant<T>(u);

        }

        template <typename T>
        expr_ptr<T> coerce_expr(const expr_ptr<T> &t) {

            return t;

        }

        template <typename T>
        expr_ptr<T> coerce_expr(const variable<T> &t) {

            return t.expr;

        }

        template <typename T, typename U>
        struct is_binary_expr : std::conditional_t<!(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>)&&is_expr_v<T> && is_expr_v<U>, std::true_type, std::false_type> {};

        template <typename T, typename U>
        constexpr bool is_binary_expr_v = is_binary_expr<T, U>::value;

        //------------------------------------------------------------------------------
        // COMPARISON OPERATORS
        //------------------------------------------------------------------------------

        // template <typename Comparator, typename T, typename U>
        // constexpr auto comparison_operator(const T &t, const U &u) {

        //     using C = expr_common_t<T, U>;
        //     return expr_comparison(coerce_expr<C>(t), coerce_expr<C>(u), Comparator{});

        // }

        // template <typename T, typename U>
        //     requires is_binary_expr_v<T, U>
        // constexpr auto operator==(const T &t, const U &u) {

        //     return comparison_operator<std::equal_to<>>(t, u);
        // }

        // template <typename T, typename U>
        //     requires is_binary_expr_v<T, U>
        // constexpr auto operator!=(const T &t, const U &u) {

        //     return comparison_operator<std::not_equal_to<>>(t, u);
        // }

        // template <typename T, typename U>
        //     requires is_binary_expr_v<T, U>
        // constexpr auto operator<=(const T &t, const U &u) {

        //     return comparison_operator<std::less_equal<>>(t, u);
        // }

        // template <typename T, typename U>
        //     requires is_binary_expr_v<T, U>
        // constexpr auto operator>=(const T &t, const U &u) {

        //     return comparison_operator<std::greater_equal<>>(t, u);
        // }

        // template <typename T, typename U>
        //     requires is_binary_expr_v<T, U>
        // constexpr auto operator<(const T &t, const U &u) {

        //     return comparison_operator<std::less<>>(t, u);
        // }

        // template <typename T, typename U>
        //     requires is_binary_expr_v<T, U>
        // constexpr auto operator>(const T &t, const U &u) {

        //     return comparison_operator<std::greater<>>(t, u);
        // }

        // //------------------------------------------------------------------------------
        // // CONDITION AND RELATED FUNCTIONS
        // //------------------------------------------------------------------------------

        // template <typename T, typename U>
        //     requires(is_expr_v<T> && is_expr_v<U>)
        // constexpr auto condition(boolean_expr &&p, const T &t, const U &u)
        // {

        //     using C = expr_common_t<T, U>;
        //     expr_ptr<C> expr = std::make_shared<conditional_expr<C>>(std::forward<boolean_expr>(p), coerce_expr<C>(t), coerce_expr<C>(u));
        //     return expr;
        // }

        // template <typename T, typename U>
        //     requires is_binary_expr_v<T, U>
        // inline constexpr auto min(const T &x, const U &y)
        // {

        //     return condition(x < y, x, y);
        // }

        // template <typename T, typename U>
        //     requires is_binary_expr_v<T, U>
        // inline constexpr auto max(const T &x, const U &y)
        // {

        //     return condition(x > y, x, y);
        // }

        // template <typename T>
        // inline constexpr expr_ptr<T> sgn(const expr_ptr<T> &x)
        // {

        //     return condition(x < 0, -1.0, condition(x > 0, 1.0, 0.0));
        // }

        // template <typename T>
        // inline constexpr expr_ptr<T> sgn(const variable<T>& x) {

        //     return condition(x.expr < 0, -1.0, condition(x.expr > 0, 1.0, 0.0));

        // }

        //------------------------------------------------------------------------------
        // ARITHMETIC OPERATORS (DEFINED FOR ARGUMENTS OF TYPE variable)
        //------------------------------------------------------------------------------


        //------------------------------------------------------------------------------
        // TRIGONOMETRIC FUNCTIONS (DEFINED FOR ARGUMENTS OF TYPE variable)
        //------------------------------------------------------------------------------

        // template <typename T>
        // inline constexpr expr_ptr<T> sin(const variable<T> &x)
        // {

        //     return sin(x.expr);
        // }

        // template <typename T>
        // inline constexpr expr_ptr<T> cos(const variable<T> &x)
        // {

        //     return cos(x.expr);
        // }

        template <typename T>
        inline constexpr expr_ptr<T> tan(const variable<T> &x)
        {

            return tan(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> asin(const variable<T> &x)
        {

            return asin(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> acos(const variable<T> &x)
        {

            return acos(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> atan(const variable<T> &x)
        {

            return atan(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> atan2(const variable<T> &l, const variable<T> &r)
        {

            return atan2(l.expr, r.expr);
        }

        template <typename T, typename U>
            requires std::is_arithmetic_v<U>
        inline constexpr expr_ptr<T> atan2(const U &l, const variable<T> &r)
        {

            return atan2(l, r.expr);
        }
        template <typename T, typename U>
            requires std::is_arithmetic_v<U>
        inline constexpr expr_ptr<T> atan2(const variable<T> &l, const U &r)
        {

            return atan2(l.expr, r);
        }

        //------------------------------------------------------------------------------
        // HYPOT2 FUNCTIONS (DEFINED FOR ARGUMENTS OF TYPE variable)
        //------------------------------------------------------------------------------
        template <typename T>
        inline constexpr expr_ptr<T> hypot(const variable<T> &l, const variable<T> &r)
        {

            return hypot(l.expr, r.expr);
        }

        template <typename T, typename U>
            requires std::is_arithmetic_v<U>
        inline constexpr expr_ptr<T> hypot(const U &l, const variable<T> &r)
        {

            return hypot(l, r.expr);
        }

        template <typename T, typename U>
            requires std::is_arithmetic_v<U>
        inline constexpr expr_ptr<T> hypot(const variable<T> &l, const U &r)
        {

            return hypot(l.expr, r);
        }

        //------------------------------------------------------------------------------
        // HYPOT3 FUNCTIONS (DEFINED FOR ARGUMENTS OF TYPE variable)
        //------------------------------------------------------------------------------
        template <typename T>
        inline constexpr expr_ptr<T> hypot(const variable<T> &l, const variable<T> &c, const variable<T> &r)
        {

            return hypot(l.expr, c.expr, r.expr);
        }

        template <typename T, typename U, typename V>
            requires(std::is_arithmetic_v<U> && std::is_arithmetic_v<V>)
        inline constexpr expr_ptr<T> hypot(const variable<T> &l, const U &c, const V &r)
        {

            return hypot(l.expr, c, r);
        }

        template <typename T, typename U, typename V>
            requires(std::is_arithmetic_v<U> && std::is_arithmetic_v<V>)
        inline constexpr expr_ptr<T> hypot(const U &l, const variable<T> &c, const V &r)
        {

            return hypot(l, c.expr, r);
        }

        template <typename T, typename U, typename V>
            requires(std::is_arithmetic_v<U> && std::is_arithmetic_v<V>)
        inline constexpr expr_ptr<T> hypot(const U &l, const V &c, const variable<T> &r)
        {

            return hypot(l, c, r.expr);
        }

        template <typename T, typename U>
            requires std::is_arithmetic_v<U>
        inline constexpr expr_ptr<T> hypot(const variable<T> &l, const variable<T> &c, const U &r)
        {

            return hypot(l.expr, c.expr, r);
        }

        template <typename T, typename U>
            requires std::is_arithmetic_v<U>
        inline constexpr expr_ptr<T> hypot(const U &l, const variable<T> &c, const variable<T> &r)
        {

            return hypot(l, c.expr, r.expr);
        }

        template <typename T, typename U>
            requires std::is_arithmetic_v<U>
        inline constexpr expr_ptr<T> hypot(const variable<T> &l, const U &c, const variable<T> &r)
        {

            return hypot(l.expr, c, r.expr);
        }

        //------------------------------------------------------------------------------
        // HYPERBOLIC FUNCTIONS (DEFINED FOR ARGUMENTS OF TYPE variable)
        //------------------------------------------------------------------------------

        template <typename T>
        inline constexpr expr_ptr<T> sinh(const variable<T> &x)
        {

            return sinh(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> cosh(const variable<T> &x)
        {

            return cosh(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> tanh(const variable<T> &x)
        {

            return tanh(x.expr);
        }

        //------------------------------------------------------------------------------
        // EXPONENTIAL AND LOGARITHMIC FUNCTIONS (DEFINED FOR ARGUMENTS OF TYPE variable)
        //------------------------------------------------------------------------------

        template <typename T>
        inline constexpr expr_ptr<T> exp(const variable<T> &x)
        {

            return exp(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> log(const variable<T> &x)
        {

            return log(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> log10(const variable<T> &x)
        {

            return log10(x.expr);
        }

        //------------------------------------------------------------------------------
        // POWER FUNCTIONS (DEFINED FOR ARGUMENTS OF TYPE variable)
        //------------------------------------------------------------------------------

        template <typename T>
        inline constexpr expr_ptr<T> sqrt(const variable<T> &x)
        {

            return sqrt(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> pow(const variable<T> &l, const variable<T> &r)
        {

            return pow(l.expr, r.expr);
        }

        template <typename T, typename U>
            requires std::is_arithmetic_v<U>
        inline constexpr expr_ptr<T> pow(const U &l, const variable<T> &r)
        {

            return pow(l, r.expr);
        }

        template <typename T, typename U>
            requires std::is_arithmetic_v<U>
        inline constexpr expr_ptr<T> pow(const variable<T> &l, const U &r)
        {

            return pow(l.expr, r);
        }

        //------------------------------------------------------------------------------
        // OTHER FUNCTIONS (DEFINED FOR ARGUMENTS OF TYPE variable)
        //------------------------------------------------------------------------------

        template <typename T>
        inline constexpr expr_ptr<T> abs(const variable<T> &x)
        {

            return abs(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> abs2(const variable<T> &x)
        {

            return abs2(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> conj(const variable<T> &x)
        {

            return conj(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> real(const variable<T> &x)
        {

            return real(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> imag(const variable<T> &x)
        {

            return imag(x.expr);
        }

        template <typename T>
        inline constexpr expr_ptr<T> erf(const variable<T> &x)
        {

            return erf(x.expr);
        }


        // /// Output a variable object to the output stream.
        // template <typename T>
        // std::ostream& operator<<(std::ostream& out, const variable<T>& x)
        // {
        //     out << val(x);
        //     return out;
        // }

        // /// Output an ExprPrt object to the output stream.
        // template <typename T>
        // std::ostream& operator<<(std::ostream& out, const expr_ptr<T>& x)
        // {
        //     out << val(x);
        //     return out;
        // }

        // //=====================================================================================================================
        // //
        // // HIGHER-ORDER VAR NUMBERS
        // //
        // //=====================================================================================================================

        // template <size_t N, typename T>
        // struct AuxHigherOrdervariable;

        // template <typename T>
        // struct AuxHigherOrdervariable<0, T>
        // {
        //     using type = T;
        // };

        // template <size_t N, typename T>
        // struct AuxHigherOrdervariable
        // {
        //     using type = variable<typename AuxHigherOrdervariable<N - 1, T>::type>;
        // };

        // template <size_t N, typename T>
        // using HigherOrdervariable = typename AuxHigherOrdervariable<N, T>::type;

        // } // namespace detail

        // using detail::wrt;
        // using detail::derivatives;
        // using detail::variable;
        // using detail::val;

        // inline detail::BooleanExpr boolref(const bool& v) { return detail::BooleanExpr([&]() { return v; }); }

        using var = variable<double>;

    } // namespace calculus

} // namespace scipp::math