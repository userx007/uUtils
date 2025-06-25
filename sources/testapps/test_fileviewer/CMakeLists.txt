
cmake_minimum_required(VERSION 3.10)
project(test_fileviewer)

add_executable(${PROJECT_NAME}
    src/test_fileviewer.cpp
)

target_link_libraries(${PROJECT_NAME}
    uUtils
)
