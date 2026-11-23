cmake_minimum_required(VERSION 3.22.1)

project(zetton_engine)

add_library(
    zetton_engine
    SHARED
    NativeEngine.cpp
)

find_library(log-lib log)

target_link_libraries(
    zetton_engine
    GLESv3
    ${log-lib}
)

target_compile_options(
    zetton_engine PRIVATE
    -Wall
    -Wextra
    -std=c++17
)
