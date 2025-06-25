
cmake_minimum_required(VERSION 3.10)
project(test_iniparser)

add_executable(${PROJECT_NAME}
    src/test_uIniParser.cpp
)

add_executable(${PROJECT_NAME}ex
    src/test_uIniParserEx.cpp
)

target_link_libraries(${PROJECT_NAME}
    uUtils
)

target_link_libraries(${PROJECT_NAME}ex
    uUtils
)
