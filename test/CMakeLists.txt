add_executable(core main.cpp)
add_executable(matrix matrix.cpp)
add_executable(integral integral.cpp)

target_link_libraries(core ${PROJECT_NAME})
target_link_libraries(matrix ${PROJECT_NAME})
target_link_libraries(integral ${PROJECT_NAME})
