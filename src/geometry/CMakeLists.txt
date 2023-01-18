add_library(geometry
    SHARED 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/geometry.hpp)

target_include_directories(geometry       
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(geometry
    PROPERTIES 
        LINKER_LANGUAGE CXX)