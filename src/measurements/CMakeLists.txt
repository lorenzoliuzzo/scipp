add_library(measurements
    SHARED 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/measurements.hpp)

target_include_directories(measurements       
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(measurements
    PROPERTIES 
        LINKER_LANGUAGE CXX)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)

add_executable(size ${CMAKE_CURRENT_SOURCE_DIR}/test/size.cpp)  
target_link_libraries(size PRIVATE ${PROJECT_NAME})