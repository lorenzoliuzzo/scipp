cmake_minimum_required(VERSION 3.20)

project(scipp VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-std=c++23 -O3 -g -pg --pedantic -ftemplate-backtrace-limit=0 -ftemplate-depth=4096 -Wall -Wextra -Wno-literal-suffix -flto -ftree-loop-vectorize -fconstexpr-depth=4096 -I/usr/include/python3.10/ -lpython3.10")

find_package(benchmark REQUIRED)

add_library(${PROJECT_NAME} 
    STATIC   
        ${PROJECT_SOURCE_DIR}/scipp/scipp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/scipp>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/benchmark/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(${PROJECT_NAME} 
    PROPERTIES 
        LINKER_LANGUAGE CXX)
        
                
install(DIRECTORY ${PROJECT_SOURCE_DIR}/scipp/ DESTINATION include/scipp)
    
add_subdirectory(test)
add_subdirectory(examples)
# add_subdirectory(benchmark)