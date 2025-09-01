## COPYRIGHT (C) HARRY CLARK 2025
## STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

cmake_minimum_required(VERSION 3.20)

project(aquinas)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_VERBOSE_TRACE "MMU VERBOSE TRACE" OFF)

add_executable(aquinas
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/mmu.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/mmu_mem.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/mmu_opcode.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/mmu_util.cc"
)

target_include_directories(aquinas PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_options(aquinas PRIVATE
    -Wall
    -Wextra
    -Wno-unused-parameter
    -std=c++17
)

if(ENABLE_VERBOSE_TRACE)
    target_compile_definitions(aquinas PRIVATE VERBOSE_TRACE_ENABLED=1)
    message(STATUS "MMU VERBOSE TRACE: ENABLED")
else()
    target_compile_definitions(aquinas PRIVATE VERBOSE_TRACE_ENABLED=0)
    message(STATUS "MMU VERBOSE TRACE: DISABLED")
endif()
