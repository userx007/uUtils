
cmake_minimum_required(VERSION 3.10)
project(calculator)

add_executable(${PROJECT_NAME}
    src/Calculator.cpp
)

add_executable(test_${PROJECT_NAME}
    src/test_uCalculator.cpp
)


target_link_libraries(test_${PROJECT_NAME}
    uUtils
)

target_link_libraries(${PROJECT_NAME}
    uUtils
)
