add_library(physics
    SHARED 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/physics.hpp)

target_include_directories(physics       
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(physics
    PROPERTIES 
        LINKER_LANGUAGE CXX)