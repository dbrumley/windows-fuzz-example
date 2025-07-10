cmake_minimum_required(VERSION 3.10)
project(FuzzExample)

set(CMAKE_CXX_STANDARD 17)

option(WITH_FUZZING "Enable fuzzing instrumentation" OFF)

if(WITH_FUZZING AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-fsanitize=fuzzer,address)
    add_link_options(-fsanitize=fuzzer,address)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")


add_executable(fuzz_target fuzz_target.cpp)