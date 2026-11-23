cmake_minimum_required(VERSION 3.20)

project(ZETTON_ENGINE
    VERSION 0.1.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(zetton_engine
    engine/core/main.cpp
    engine/core/Engine.cpp
)

target_compile_options(zetton_engine PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
