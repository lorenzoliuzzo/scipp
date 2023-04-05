#pragma once


#include <atomic>
#include <iostream>
#include <string>
#include <type_traits>


namespace scipp::tools {


    template <class T>
    class copy_counter {


        static_assert(std::is_copy_constructible_v<T>);
        static_assert(std::is_copy_assignable_v<T>);
        static_assert(std::is_move_constructible_v<T>);
        static_assert(std::is_move_assignable_v<T>);
        static_assert(std::is_destructible_v<T>);
        static_assert(std::is_default_constructible_v<T>);
        static_assert(std::is_same_v<T, std::decay_t<T>>);
        

        public:


            copy_counter() = default;


            copy_counter(const copy_counter& other) {
                ++copy_count;
            }


            copy_counter& operator=(const copy_counter& other) {
                ++copy_count;
                return *this;
            }


            copy_counter(copy_counter&& other) {
                ++move_count;
            }


            copy_counter& operator=(copy_counter&& other) {
                ++move_count;
                return *this;
            }


            ~copy_counter() {
                ++destructor_count;
            }


            static void reset() {
                copy_count = 0;
                move_count = 0;
                destructor_count = 0;
            }


            static std::size_t copy_count;

            static std::size_t move_count;

            static std::size_t destructor_count;


    };


    template <class T>
    std::size_t copy_counter<T>::copy_count = 0;


    template <class T>
    std::size_t copy_counter<T>::move_count = 0;


    template <class T>
    std::size_t copy_counter<T>::destructor_count = 0;


} // namespace scipp::tools