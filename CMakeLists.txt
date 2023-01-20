cmake_minimum_required(VERSION 3.20)

project(sci++ VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-std=c++2a -O3 -g -Wall --pedantic -pthread")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

add_library(${PROJECT_NAME} 
    SHARED 
        ${PROJECT_SOURCE_DIR}/include/sci++.hpp)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        )

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES 
        LINKER_LANGUAGE CXX)