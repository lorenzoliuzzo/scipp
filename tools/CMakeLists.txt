add_library(tools 
    SHARED 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/tools.hpp)

target_include_directories(tools 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(tools 
    PROPERTIES 
        LINKER_LANGUAGE CXX)