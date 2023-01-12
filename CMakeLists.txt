cmake_minimum_required(VERSION 3.20)

project(sci++ VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-std=c++20 -O3 -g -Wall -Wextra --pedantic")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/measurements)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/math)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tools)

add_library(sci++ SHARED)
target_sources(sci++ INTERFACE ${PROJECT_SOURCE_DIR}/sci++.hpp)
target_include_directories(sci++ PUBLIC)


# add_executable(main ${PROJECT_SOURCE_DIR}/test/main.cpp)
# target_link_libraries(main PRIVATE sci++)
# target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR})