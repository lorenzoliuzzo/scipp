cmake_minimum_required(VERSION 3.20)

project(sci++ VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-std=c++20 -O3 -g -Wall --pedantic")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/math)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tools)

add_library(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include/sci++.hpp)
target_link_libraries(sci++ INTERFACE math tools)

target_include_directories(${PROJECT_NAME} 

    INTERFACE
        ${PROJECT_SOURCE_DIR}
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES 
        LINKER_LANGUAGE CXX)
    

add_executable(include_test ${PROJECT_SOURCE_DIR}/test/main.cpp)
target_link_libraries(include_test PRIVATE ${PROJECT_NAME})

add_executable(bench ${PROJECT_SOURCE_DIR}/test/bench.cpp)
target_link_libraries(bench PRIVATE ${PROJECT_NAME})