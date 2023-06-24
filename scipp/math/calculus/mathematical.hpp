/**
 * @file    math/calculus/functions/mathematical.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation 
 * @date    2023-06-24
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace calculus {



        // template <typename T>
        // struct tan_expr : unary_expr<T, T> {

        //     // Using declarations for data members of base class
        //     using unary_expr<T, T>::x;


        //     constexpr tan_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}

        //     virtual constexpr void propagate(const T& wprime) override {

        //         const auto aux = 1.0 / cos(x->val);
        //         x->propagate(wprime * aux * aux);

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         const auto aux = 1.0 / cos(x);
        //         x->propagatex(wprime * aux * aux);

        //     }

        //     constexpr void update() override {

        //         x->update();
        //         this->val = tan(x->val);

        //     }
            
        // };


        // template <typename T>
        // struct sinh_expr : unary_expr<T, T> {

        //     // Using declarations for data members of base class
        //     using unary_expr<T, T>::x;


        //     constexpr sinh_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         x->propagate(wprime * cosh(x->val));
        //     }


        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         x->propagatex(wprime * cosh(x));
        //     }


        //     constexpr void update() override {

        //         x->update();
        //         this->val = sinh(x->val);
        //     }

        // };


        // template <typename T>
        // struct cosh_expr : unary_expr<T, T> {

        //     // Using declarations for data members of base class
        //     using unary_expr<T, T>::x;


        //     constexpr cosh_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         x->propagate(wprime * sinh(x->val));
            
        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         x->propagatex(wprime * sinh(x));

        //     }

        //     constexpr void update() override {

        //         x->update();
        //         this->val = cosh(x->val);

        //     }

        // };


        // template <typename T>
        // struct tanh_expr : unary_expr<T, T> {

        //     // Using declarations for data members of base class
        //     using unary_expr<T, T>::x;


        //     constexpr tanh_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         const auto aux = 1.0 / cosh(x->val);
        //         x->propagate(wprime * aux * aux);

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         const auto aux = 1.0 / cosh(x);
        //         x->propagatex(wprime * aux * aux);

        //     }

        //     constexpr void update() override {

        //         x->update();
        //         this->val = tanh(x->val);

        //     }

        // };


        // template <typename T>
        // struct arcsin_expr : unary_expr<T, T> {

        //     // Using declarations for data members of base class
        //     using unary_expr<T, T>::x;

            
        //     constexpr arcsin_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         x->propagate(wprime / sqrt(1.0 - x->val * x->val));

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         x->propagatex(wprime / sqrt(1.0 - x * x));

        //     }

        //     constexpr void update() override {

        //         x->update();
        //         this->val = asin(x->val);

        //     }

        // };


        // template <typename T>
        // struct arccos_expr : unary_expr<T, T> {

        //     // Using declarations for data members of base class
        //     using unary_expr<T, T>::x;


        //     constexpr arccos_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         x->propagate(-wprime / sqrt(1.0 - x->val * x->val));
            
        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         x->propagatex(-wprime / sqrt(1.0 - x * x));
            
        //     }

        //     constexpr void update() override {

        //         x->update();
        //         this->val = acos(x->val);
            
        //     }

        // };


        // template <typename T>
        // struct arctan_expr : unary_expr<T, T> {

        //     // Using declarations for data members of base class
        //     using unary_expr<T, T>::x;


        //     constexpr arctan_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         x->propagate(wprime / (1.0 + x->val * x->val));

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         x->propagatex(wprime / (1.0 + x * x));

        //     }

        //     constexpr void update() override {

        //         x->update();
        //         this->val = atan(x->val);

        //     }

        // };


        // template <typename T>
        // struct arctan2_expr : binary_expr<T> {

        //     using binary_expr<T>::val;
        //     using binary_expr<T>::l;
        //     using binary_expr<T>::r;


        //     constexpr arctan2_expr(const T& v, const expr_ptr<T>& ll, const expr_ptr<T>& rr) noexcept : binary_expr<T>(v, ll, rr) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         const auto aux = wprime / (l->val * l->val + r->val * r->val);
        //         l->propagate(r->val * aux);
        //         r->propagate(-l->val * aux);

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         const auto aux = wprime / (l * l + r * r);
        //         l->propagatex(r * aux);
        //         r->propagatex(-l * aux);

        //     }

        //     constexpr void update() override {

        //         l->update();
        //         r->update();
        //         this->val = atan2(l->val, r->val);

        //     }

        // };


        // template <typename T>
        // struct exp_expr : unary_expr<T, T> {

        //     // Using declarations for data members of base class
        //     using unary_expr<T, T>::unary_expr;
        //     using unary_expr<T, T>::val;
        //     using unary_expr<T, T>::x;


        //     virtual constexpr void propagate(const T& wprime) override {

        //         x->propagate(wprime * val); // exp(x)' = exp(x) * x'
            
        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         x->propagatex(wprime * exp(x));
            
        //     }

        //     constexpr void update() override {

        //         x->update();
        //         this->val = exp(x->val);
            
        //     }

        // };


        // template <typename T>
        // struct log_expr : unary_expr<T, T> {

        //     // Using declarations for data members of base class
        //     using unary_expr<T, T>::x;
        //     using unary_expr<T, T>::unary_expr;


        //     virtual constexpr void propagate(const T& wprime) override {

        //         x->propagate(wprime / x->val); // log(x)' = x'/x

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         x->propagatex(wprime / x);

        //     }

        //     constexpr void update() override {

        //         x->update();
        //         this->val = log(x->val);

        //     }

        // };


        // template <typename T>
        // struct log10_expr : unary_expr<T, T> {

        //     // Using declarations for data members of base class
        //     using unary_expr<T, T>::x;


        //     constexpr static auto ln10 = static_cast<variable_value_t<T>>(2.3025850929940456840179914546843);

        //     constexpr log10_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         x->propagate(wprime / (ln10 * x->val));

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         x->propagatex(wprime / (ln10 * x));

        //     }

        //     constexpr void update() override {

        //         x->update();
        //         this->val = log10(x->val);

        //     }

        // };


        // template <typename T>
        // struct pow_expr : binary_expr<T> {

        //     // Using declarations for data members of base class
        //     using binary_expr<T>::val;
        //     using binary_expr<T>::l;
        //     using binary_expr<T>::r;


        //     T log_l;


        //     constexpr pow_expr(const T& v, const expr_ptr<T>& ll, const expr_ptr<T>& rr) noexcept : binary_expr<T>(v, ll, rr), log_l(log(ll->val)) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         using U = variable_value_t<T>;
        //         constexpr auto zero = U(0.0);
        //         const auto lval = l->val;
        //         const auto rval = r->val;
        //         const auto aux = wprime * pow(lval, rval - 1);
        //         l->propagate(aux * rval);
        //         const auto auxr = lval == zero ? 0.0 : lval * log(lval); // since x*log(x) -> 0 as x -> 0
        //         r->propagate(aux * auxr);

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         using U = variable_value_t<T>;
        //         constexpr auto zero = U(0.0);
        //         const auto aux = wprime * pow(l, r - 1);
        //         l->propagatex(aux * r);
        //         const auto auxr = l == zero ? 0.0*l : l * log(l); // since x*log(x) -> 0 as x -> 0
        //         r->propagatex(aux * auxr);

        //     }

        //     constexpr void update() override {

        //         l->update();
        //         r->update();
        //         this->val = pow(l->val, r->val);

        //     }

        // };


        // template <typename T>
        // struct pow_constant_left_expr : binary_expr<T> {

        //     // Using declarations for data members of base class
        //     using binary_expr<T>::val;
        //     using binary_expr<T>::l;
        //     using binary_expr<T>::r;


        //     constexpr pow_constant_left_expr(const T& v, const expr_ptr<T>& ll, const expr_ptr<T>& rr) noexcept : binary_expr<T>(v, ll, rr) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         const auto lval = l->val;
        //         const auto rval = r->val;
        //         const auto aux = wprime * pow(lval, rval - 1);
        //         const auto auxr = lval == 0.0 ? 0.0 : lval * log(lval); // since x*log(x) -> 0 as x -> 0
        //         r->propagate(aux * auxr);

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         const auto aux = wprime * pow(l, r - 1);
        //         const auto auxr = l == 0.0 ? 0.0*l : l * log(l); // since x*log(x) -> 0 as x -> 0
        //         r->propagatex(aux * auxr);

        //     }

        //     constexpr void update() override {

        //         r->update();
        //         this->val = pow(l->val, r->val);
            
        //     }

        // };


        // template <typename T>
        // struct pow_constant_right_expr : binary_expr<T> {

        //     // Using declarations for data members of base class
        //     using binary_expr<T>::val;
        //     using binary_expr<T>::l;
        //     using binary_expr<T>::r;


        //     constexpr pow_constant_right_expr(const T& v, const expr_ptr<T>& ll, const expr_ptr<T>& rr) noexcept : binary_expr<T>(v, ll, rr) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         l->propagate(wprime * pow(l->val, r->val - 1) * r->val); // pow(l, r)'l = r * pow(l, r - 1) * l'

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         l->propagatex(wprime * pow(l, r - 1) * r);

        //     }

        //     constexpr void update() override {

        //         l->update();
        //         this->val = pow(l->val, r->val);

        //     }

        // };


        // template <typename T>
        // struct sqrt_expr : unary_expr<T, T> {

        //     // Using declarations for data members of base class
        //     using unary_expr<T, T>::x;


        //     constexpr sqrt_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T, T>(v, e) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         x->propagate(wprime / (2.0 * sqrt(x->val))); // sqrt(x)' = 1/2 * 1/sqrt(x) * x'

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         x->propagatex(wprime / (2.0 * sqrt(x)));
        //     }

        //     constexpr void update() override {

        //         x->update();
        //         this->val = sqrt(x->val);

        //     }

        // };


        // template <typename T>
        // struct abs_expr : unary_expr<T> {

        //     // Using declarations for data members of base class
        //     using unary_expr<T>::x;
        //     using U = variable_value_t<T>;


        //     constexpr abs_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T>(v, e) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         if (x->val < 0.0)
        //             x->propagate(-wprime);
        //         else if (x->val > 0.0)
        //             x->propagate(wprime);
        //         else 
        //             x->propagate(T(0));

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         if (x->val < 0.0)
        //             x->propagatex(-wprime);
        //         else if (x->val > 0.0)
        //             x->propagatex(wprime);
        //         else 
        //             x->propagate(T(0));

        //     }

        //     constexpr void update() override {

        //         x->update();
        //         this->val = abs(x->val);

        //     }

        // };


        // template <typename T>
        // struct erf_expr : unary_expr<T> {

        //     // Using declarations for data members of base class
        //     using unary_expr<T>::x;


        //     constexpr static auto sqrt_pi = static_cast<variable_value_t<T>>(1.7724538509055160272981674833411451872554456638435);


        //     constexpr erf_expr(const T& v, const expr_ptr<T>& e) noexcept : unary_expr<T>(v, e) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         const auto aux = 2.0 / sqrt_pi * exp(-(x->val) * (x->val)); // erf(x)' = 2/sqrt(pi) * exp(-x * x) * x'
        //         x->propagate(wprime * aux);

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         const auto aux = 2.0 / sqrt_pi * exp(-x * x);
        //         x->propagatex(wprime * aux);

        //     }

        //     constexpr void update() override {

        //         x->update();
        //         this->val = erf(x->val);

        //     }

        // };


        // template <typename T>
        // struct hypot2expr : binary_expr<T> {

        //     // Using declarations for data members of base class
        //     using binary_expr<T>::val;
        //     using binary_expr<T>::l;
        //     using binary_expr<T>::r;


        //     constexpr hypot2expr(const T& v, const expr_ptr<T>& ll, const expr_ptr<T>& rr) noexcept : binary_expr<T>(v, ll, rr) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         l->propagate(wprime * l->val / val); // sqrt(l*l + r*r)'l = 1/2 * 1/sqrt(l*l + r*r) * (2*l*l') = (l*l')/sqrt(l*l + r*r)
        //         r->propagate(wprime * r->val / val); // sqrt(l*l + r*r)'r = 1/2 * 1/sqrt(l*l + r*r) * (2*r*r') = (r*r')/sqrt(l*l + r*r)

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         l->propagatex(wprime * l / hypot(l, r));
        //         r->propagatex(wprime * r / hypot(l, r));

        //     }

        //     constexpr void update() override {

        //         l->update();
        //         r->update();
        //         this->val = hypot(l->val, r->val);

        //     }

        // };


        // template <typename T>
        // struct hypot3expr : ternary_expr<T> {

        //     // Using declarations for data members of base class
        //     using ternary_expr<T>::val;
        //     using ternary_expr<T>::l;
        //     using ternary_expr<T>::c;
        //     using ternary_expr<T>::r;


        //     constexpr hypot3expr(const T& v, const expr_ptr<T>& ll, const expr_ptr<T>& cc, const expr_ptr<T>& rr) noexcept : ternary_expr<T>(v, ll, cc, rr) {}


        //     virtual constexpr void propagate(const T& wprime) override {

        //         l->propagate(wprime * l->val / val);
        //         c->propagate(wprime * c->val / val);
        //         r->propagate(wprime * r->val / val);

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         l->propagatex(wprime * l / hypot(l, c, r));
        //         c->propagatex(wprime * c / hypot(l, c, r));
        //         r->propagatex(wprime * r / hypot(l, c, r));

        //     }

        //     constexpr void update() override {

        //         l->update();
        //         c->update();
        //         r->update();
        //         this->val = hypot(l->val, c->val, r->val);

        //     }

        // };



        // // Any expression yielding a boolean depending on arithmetic subexpressions
        // struct boolean_expr {

        //     std::function<bool()> expr;
        //     bool val = {};

        //     explicit boolean_expr(std::function<bool()> expression) : expr(std::move(expression)) { 
                
        //         update(); 
                
        //     }

        //     constexpr operator bool() const { 
                
        //         return val; 
                
        //     }

        //     void update() { 
                
        //         val = expr(); 
            
        //     }

        //     auto operator!() const { 
                
        //         return boolean_expr([&]() { 

        //             return !(expr()); 

        //         }); 

        //     }

        // };


        // /// Capture numeric comparison between two expression trees
        // template <typename T, typename Comparator>
        // constexpr auto expr_comparison(const expr_ptr<T>& l, const expr_ptr<T>& r, Comparator&& compare) {
            
        //     return boolean_expr([=]() mutable -> bool {
        //         l->update();
        //         r->update();
        //         return compare(l->val, r->val);
        //     });

        // }


        // template <typename Op> 
        // constexpr auto bool_expr_op(boolean_expr& l, boolean_expr& r, Op op) {

        //     return boolean_expr([=]() mutable -> bool {
        //         l.update();
        //         r.update();
        //         return op(l, r);
        //     });

        // }


        // inline auto operator&&(boolean_expr&& l, boolean_expr&& r) { 
            
        //     return bool_expr_op(l, r, std::logical_and<>{}); 
            
        // }


        // inline auto operator||(boolean_expr&& l, boolean_expr&& r) { 
            
        //     return bool_expr_op(l, r, std::logical_or<>{}); 
            
        // }


        // /// Select between expression branches depending on a boolean expression
        // template <typename T>
        // struct conditional_expr : expr<T> {

        //     // Using declarations for data members of base class
        //     using expr<T>::val;

            
        //     boolean_expr predicate;
        //     expr_ptr<T> l, r;


        //     constexpr conditional_expr(const boolean_expr& wrappedPred, const expr_ptr<T>& ll, const expr_ptr<T>& rr) noexcept : 
                
        //         expr<T>(wrappedPred ? ll->val : rr->val), predicate(wrappedPred), l(ll), r(rr) {}

                
        //     virtual constexpr void propagate(const T& wprime) override {

        //         if (predicate.val) 
        //             l->propagate(wprime);
        //         else 
        //             r->propagate(wprime);

        //     }

        //     virtual constexpr void propagatex(const expr_ptr<T>& wprime) override {

        //         l->propagatex(derive(wprime, constant<T>(0.0)));
        //         r->propagatex(derive(constant<T>(0.0), wprime));

        //     }

        //     constexpr void update() override {

        //         predicate.update();
        //         if (predicate.val) {
        //             l->update();
        //             this->val = l->val;
        //         } else {
        //             r->update();
        //             this->val = r->val;
        //         }

        //     }

        //     constexpr expr_ptr<T> derive(const expr_ptr<T>& left, const expr_ptr<T>& right) const {

        //         return std::make_shared<conditional_expr>(predicate, left, right);

        //     }

        // };


        // //------------------------------------------------------------------------------
        // // ARITHMETIC OPERATORS
        // //------------------------------------------------------------------------------


        // //------------------------------------------------------------------------------
        // // TRIGONOMETRIC FUNCTIONS
        // //------------------------------------------------------------------------------
        // template <typename T> 
        // inline constexpr expr_ptr<T> sin(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<sin_expr<T>>(std::sin(x->val), x);
        
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> cos(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<cos_expr<T>>(std::cos(x->val), x);
        
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> tan(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<tan_expr<T>>(tan(x->val), x);
        
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> asin(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<arcsin_expr<T>>(asin(x->val), x);

        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> acos(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<arccos_expr<T>>(acos(x->val), x);
        
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> atan(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<arctan_expr<T>>(atan(x->val), x);
        
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> atan2(const expr_ptr<T>& l, const expr_ptr<T>& r) { 
            
        //     return std::make_shared<arctan2_expr<T>>(atan2(l->val, r->val), l, r);
        
        // }
        
        // template <typename T, typename U> 
        //     requires std::is_arithmetic_v<U>
        // inline constexpr expr_ptr<T> atan2(const U& l, const expr_ptr<T>& r) { 
            
        //     return std::make_shared<arctan2_expr<T>>(atan2(l, r->val), constant<T>(l), r);
        
        // }
        
        // template <typename T, typename U>
        //     requires std::is_arithmetic_v<U>
        // inline constexpr expr_ptr<T> atan2(const expr_ptr<T>& l, const U& r) { 
            
        //     return std::make_shared<arctan2_expr<T>>(atan2(l->val, r), l, constant<T>(r));
        
        // }



        // //------------------------------------------------------------------------------
        // // HYPOT2 FUNCTIONS
        // //------------------------------------------------------------------------------
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> hypot(const expr_ptr<T>& l, const expr_ptr<T>& r) { 
            
        //     return std::make_shared<hypot2expr<T>>(hypot(l->val, r->val), l, r);
        
        // }
        
        // template <typename T, typename U>
        //     requires std::is_arithmetic_v<U>
        // inline constexpr expr_ptr<T> hypot(const U& l, const expr_ptr<T>& r) { 
            
        //     return std::make_shared<hypot2expr<T>>(hypot(l, r->val), constant<T>(l), r);
        
        // }
        
        // template <typename T, typename U>
        //     requires std::is_arithmetic_v<U>
        // inline constexpr expr_ptr<T> hypot(const expr_ptr<T>& l, const U& r) { 
            
        //     return std::make_shared<hypot2expr<T>>(hypot(l->val, r), l, constant<T>(r));
        
        // }


        // //------------------------------------------------------------------------------
        // // HYPOT3 FUNCTIONS
        // //------------------------------------------------------------------------------
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> hypot(const expr_ptr<T>& l, const expr_ptr<T>& c, const expr_ptr<T>& r) { 
            
        //     return std::make_shared<hypot3expr<T>>(hypot(l->val,c->val, r->val), l, c, r);
        
        // }
        
        // template <typename T, typename U>
        //     requires std::is_arithmetic_v<U>
        // inline constexpr expr_ptr<T> hypot(const expr_ptr<T>& l, const expr_ptr<T>& c, const U& r) { 
            
        //     return std::make_shared<hypot3expr<T>>(hypot(l->val, c->val, r), l, c, constant<T>(r));
        
        // }
        
        // template <typename T, typename U>
        //     requires std::is_arithmetic_v<U>
        // inline constexpr expr_ptr<T> hypot(const U& l, const expr_ptr<T>& c, const expr_ptr<T>& r) { 
            
        //     return std::make_shared<hypot3expr<T>>(hypot(l, c->val, r->val), constant<T>(l), c, r);
        
        // }
        
        // template <typename T, typename U>
        //     requires std::is_arithmetic_v<U>
        // inline constexpr expr_ptr<T> hypot(const expr_ptr<T>& l,const U& c, const expr_ptr<T>& r) { 
            
        //     return std::make_shared<hypot3expr<T>>(hypot(l->val, c, r->val), l, constant<T>(c), r);
        
        // }
        
        // template <typename T, typename U, typename V>
        //     requires std::is_arithmetic_v<U> && std::is_arithmetic_v<V>
        // inline constexpr expr_ptr<T> hypot(const expr_ptr<T>& l, const U& c, const V& r) { 
            
        //     return std::make_shared<hypot3expr<T>>(hypot(l->val, c, r), l, constant<T>(c), constant<T>(r));
        
        // }
        
        // template <typename T, typename U, typename V>
        //     requires std::is_arithmetic_v<U> && std::is_arithmetic_v<V>
        // inline constexpr expr_ptr<T> hypot(const U& l, const expr_ptr<T>& c, const V& r) { 
            
        //     return std::make_shared<hypot3expr<T>>(hypot(l, c->val, r), constant<T>(l), c, constant<T>(r));
        
        // }
        
        // template <typename T, typename U, typename V>
        //     requires std::is_arithmetic_v<U> && std::is_arithmetic_v<V>
        // inline constexpr expr_ptr<T> hypot(const V& l, const U& c, const expr_ptr<T>& r) { 
            
        //     return std::make_shared<hypot3expr<T>>(hypot(l, c, r->val), constant<T>(l), constant<T>(c), r);
        
        // }


        // //------------------------------------------------------------------------------
        // // HYPERBOLIC FUNCTIONS
        // //------------------------------------------------------------------------------
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> sinh(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<sinh_expr<T>>(sinh(x->val), x); 
        
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> cosh(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<cosh_expr<T>>(cosh(x->val), x); 
        
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> tanh(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<tanh_expr<T>>(tanh(x->val), x); 
        
        // }


        // //------------------------------------------------------------------------------
        // // EXPONENTIAL AND LOGARITHMIC FUNCTIONS
        // //------------------------------------------------------------------------------
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> exp(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<exp_expr<T>>(exp(x->val), x); 
        
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> log(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<log_expr<T>>(log(x->val), x); 
        
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> log10(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<log10_expr<T>>(log10(x->val), x); 
        
        // }


        // //------------------------------------------------------------------------------
        // // POWER FUNCTIONS
        // //------------------------------------------------------------------------------
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> sqrt(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<sqrt_expr<T>>(sqrt(x->val), x); 
        
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> pow(const expr_ptr<T>& l, const expr_ptr<T>& r) { 
            
        //     return std::make_shared<pow_expr<T>>(pow(l->val, r->val), l, r); 
        
        // }
        
        // template <typename T, typename U> 
        //     requires std::is_arithmetic_v<U>
        // inline constexpr expr_ptr<T> pow(const U& l, const expr_ptr<T>& r) { 
            
        //     return std::make_shared<pow_constant_left_expr<T>>(pow(l, r->val), constant<T>(l), r); 
        
        // }
        
        // template <typename T, typename U> 
        //     requires std::is_arithmetic_v<U>
        // inline constexpr expr_ptr<T> pow(const expr_ptr<T>& l, const U& r) { 
            
        //     return std::make_shared<pow_constant_right_expr<T>>(pow(l->val, r), l, constant<T>(r)); 
        
        // }


        // //------------------------------------------------------------------------------
        // // OTHER FUNCTIONS
        // //------------------------------------------------------------------------------
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> abs(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<abs_expr<T>>(abs(x->val), x);
            
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> abs2(const expr_ptr<T>& x) { 
            
        //     return x * x;
            
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> conj(const expr_ptr<T>& x) { 
            
        //     return x;
            
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> real(const expr_ptr<T>& x) { 
            
        //     return x;
            
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> imag(const expr_ptr<T>&) { 
            
        //     return constant<T>(0.0);
            
        // }
        
        // template <typename T> 
        // inline constexpr expr_ptr<T> erf(const expr_ptr<T>& x) { 
            
        //     return std::make_shared<erf_expr<T>>(erf(x->val), x);
            
        // }


    } // namespace calculus


} // namespace scipp::math