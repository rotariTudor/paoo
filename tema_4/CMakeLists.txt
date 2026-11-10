cmake_minimum_required(VERSION 3.14)
project(EffectiveCpp_Items_4_5_6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Activeaza ASan + UBSan" OFF)

add_executable(effective_cpp
    src/main.cpp
    src/item04.cpp
    src/item05.cpp
    src/item06.cpp)
target_include_directories(effective_cpp PRIVATE include)

if(MSVC)
    target_compile_options(effective_cpp PRIVATE /W4)
else()
    target_compile_options(effective_cpp PRIVATE -Wall -Wextra -Wpedantic -Wreorder)
    if(ENABLE_SANITIZERS)
        target_compile_options(effective_cpp PRIVATE -fsanitize=address,undefined -g)
        target_link_options(effective_cpp PRIVATE -fsanitize=address,undefined)
    endif()
endif()
