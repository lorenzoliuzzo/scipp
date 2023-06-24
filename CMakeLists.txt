cmake_minimum_required(VERSION 3.20)

project(sci++ VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-std=c++23 -O3 -g -pg --pedantic -ftemplate-backtrace-limit=0 -Wall -Wextra -Wno-literal-suffix -flto -ftree-loop-vectorize -fconstexpr-depth=4096 -I/usr/local/lib/python3.10/site-packages/numpy/core/include")

add_library(${PROJECT_NAME} 
    STATIC   
        ${PROJECT_SOURCE_DIR}/scipp/sci++.hpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        /usr/include/python3.10
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/scipp>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES 
        LINKER_LANGUAGE CXX)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/scipp/ DESTINATION include/scipp)
    
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
