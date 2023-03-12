cmake_minimum_required(VERSION 3.20)

project(sci++ VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-std=c++20 -O3 -g --pedantic -Wall -Wextra -Wno-literal-suffix -fopenmp -pg -fconcepts")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

add_library(${PROJECT_NAME} 
    STATIC   
        ${PROJECT_SOURCE_DIR}/include/sci++.hpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES 
        LINKER_LANGUAGE CXX)