cmake_minimum_required(VERSION 3.10)
project(thermo)

include_directories(inc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}
    inc/thermo/thermometer.hpp
    inc/thermo/naive_thermometer.hpp
    src/main.cpp
    src/thermometer.cpp
    src/naive_thermometer.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)