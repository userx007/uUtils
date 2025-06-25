
cmake_minimum_required(VERSION 3.10)
project(test_hexdumper)

add_executable(${PROJECT_NAME}
    src/test_uHexdumpUtils.cpp
)

target_link_libraries(${PROJECT_NAME}
    uUtils
)
