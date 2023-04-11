cmake_minimum_required(VERSION 3.20)

project(sci++ VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-std=c++23 -O3 -g --pedantic -Wall -Wextra -Wno-literal-suffix -fconcepts -flto -ftree-loop-vectorize -I/usr/local/lib/python3.10/site-packages/numpy/core/include")

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

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)