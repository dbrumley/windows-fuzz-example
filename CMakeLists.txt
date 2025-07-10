cmake_minimum_required(VERSION 3.10)
project(FuzzExample)

set(CMAKE_CXX_STANDARD 17)

option(WITH_FUZZING "Enable fuzzing instrumentation" OFF)
option(WITH_ASAN "Enable AddressSanitizer" ON)

# Enable libFuzzer only with Clang
if(WITH_FUZZING AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-fsanitize=fuzzer,address)
    add_link_options(-fsanitize=fuzzer,address)
elseif(WITH_ASAN)
    # Handle AddressSanitizer for Clang or GCC
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(WARNING "ASAN is not fully supported with MSVC in all environments.")
        # Visual Studio 2019+ supports /fsanitize=address
        add_compile_options(/fsanitize=address /Zi /MDd)
        add_link_options(/fsanitize=address)
    endif()
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")


add_executable(fuzz_target fuzz_target.cpp)