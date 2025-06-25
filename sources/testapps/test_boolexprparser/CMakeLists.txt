
cmake_minimum_required(VERSION 3.10)
project(test_boolexprparser)

add_executable(${PROJECT_NAME}
    src/test_uBoolExprParser.cpp
)

add_executable(${PROJECT_NAME}throw
    src/test_uBoolExprParserThrow.cpp
)

target_link_libraries(${PROJECT_NAME}
    uUtils
)

target_link_libraries(${PROJECT_NAME}throw
    uUtils
)
