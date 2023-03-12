add_executable(core main.cpp)
add_executable(matrix matrix.cpp)

target_link_libraries(core ${PROJECT_NAME})
target_link_libraries(matrix ${PROJECT_NAME})