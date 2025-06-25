
cmake_minimum_required(VERSION 3.10)
project(test_numeric)

add_executable(${PROJECT_NAME}
    src/test_uNumericUtils.cpp
)

target_link_libraries(${PROJECT_NAME}
    uUtils
)
