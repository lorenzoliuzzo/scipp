# add_executable(geometry geometry.cpp)
# target_link_libraries(geometry ${PROJECT_NAME} python3.10)

add_executable(matrix matrix.cpp)
target_link_libraries(matrix ${PROJECT_NAME})

add_executable(eigen eigen.cpp)
target_link_libraries(eigen ${PROJECT_NAME})