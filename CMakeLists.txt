cmake_minimum_required(VERSION 3.20)

project(sci++ VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-std=c++20 -O3 -g -Wall --pedantic -I/home/lorenzo/miniconda3/envs/cling/include/python3.11 -lpython3.11")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/math)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tools)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/geometry)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/physics)

add_library(${PROJECT_NAME} 
    INTERFACE 
        ${PROJECT_SOURCE_DIR}/include/sci++.hpp)

target_link_libraries(${PROJECT_NAME} 
    INTERFACE 
        math 
        tools 
        geometry
        physics)

target_include_directories(${PROJECT_NAME} 
    INTERFACE
        ${PROJECT_SOURCE_DIR}
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES 
        LINKER_LANGUAGE CXX)
            
add_executable(bench ${PROJECT_SOURCE_DIR}/bench/bench.cpp)
target_link_libraries(bench PRIVATE ${PROJECT_NAME})

add_executable(timer_overhead ${PROJECT_SOURCE_DIR}/bench/timer_overhead.cpp)
target_link_libraries(timer_overhead PRIVATE ${PROJECT_NAME})
