add_library(math
    SHARED 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/math.hpp)

target_include_directories(math
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(math
    PROPERTIES 
        LINKER_LANGUAGE CXX)