/**
 * @file    math/node.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-04-09
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace scipp::math {


    struct node {

        using type = node;

        virtual ~node() = default;

    };
    

} // namespace scipp::math