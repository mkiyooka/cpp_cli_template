cmake_minimum_required(VERSION 3.0)
project(MyProject VERSION 0.1.0 DESCRIPTION "Very nice project" LANGUAGES CXX)

if(NOT DEFINED CLI11_DIR)
    set (CLI11_DIR "mod/CLI11" CACHE STRING "CLI11 git repository")
endif()
if(NOT DEFINED SPDLOG_DIR)
    set (SPDLOG_DIR "mod/spdlog" CACHE STRING "spdlog git repository")
endif()
if(NOT DEFINED DOCTEST)
    set (DOCTEST "mod/doctest/doctest" CACHE STRING "doctest git repository")
endif()
if(NOT DEFINED NANOBENCH)
    set (NANOBENCH "mod/nanobench/src" CACHE STRING "nanobench git repository")
endif()

add_library(modA STATIC
    src/modA/modA1.cpp include/modA/modA1.hpp
    src/modA/modA2.cpp include/modA/modA2.hpp)
target_include_directories(modA PUBLIC include)
target_compile_features(modA PUBLIC cxx_std_11)

add_library(modB STATIC
    src/modB/modB1.cpp include/modB/modB1.hpp
    src/modB/modB2.cpp include/modB/modB2.hpp)
target_include_directories(modB PUBLIC include)
target_compile_features(modB PUBLIC cxx_std_11)

add_library(cli STATIC
    src/cli.cpp include/cli.hpp
    src/cli_subcomA.cpp include/cli_subcomA.hpp)
target_include_directories(cli PUBLIC include)
target_compile_features(cli PUBLIC cxx_std_11)
add_subdirectory(${CLI11_DIR})
include_directories(${CLI11_DIR}/include)

add_executable(cmd src/main.cpp)
add_subdirectory(${SPDLOG_DIR})
include_directories(${SPDLOG_DIR}/include)
target_link_libraries(cmd PUBLIC modA)
target_link_libraries(cmd PUBLIC modB)
target_link_libraries(cmd PUBLIC cli)
target_link_libraries(cmd PUBLIC spdlog)

# --- test ---
enable_testing()
add_executable(
    unit_test_add
    tests/test_modA1.cpp src/modA/modA1.cpp include/modA/modA1.hpp
    )
target_include_directories(unit_test_add PUBLIC include)

add_executable(
    unit_test_sub
    tests/test_modA2.cpp src/modA/modA2.cpp include/modA/modA2.hpp
    )
target_include_directories(unit_test_sub PUBLIC include)

add_executable(
    unit_test_mul_div
    tests/test_modB.cpp
    src/modB/modB1.cpp include/modB/modB1.hpp
    src/modB/modB2.cpp include/modB/modB2.hpp
    )
target_include_directories(unit_test_mul_div PUBLIC include)

include_directories(${DOCTEST})

# Add the test which is simply run the application.
add_test(
    NAME test_add
    COMMAND $<TARGET_FILE:unit_test_add>)
add_test(
    NAME test_sub
    COMMAND $<TARGET_FILE:unit_test_sub>)
add_test(
    NAME test_mul_div
    COMMAND $<TARGET_FILE:unit_test_mul_div>)

add_executable(
    bench_modA
    bench/bench_modA.cpp
    src/modA/modA1.cpp include/modA/modA1.hpp
    src/modA/modA2.cpp include/modA/modA2.hpp
    )
target_link_libraries(bench_modA PUBLIC modA)
target_link_libraries(bench_modA PUBLIC modB)
#add_subdirectory(${NANOBENCH})
include_directories(${NANOBENCH}/include)
#target_link_libraries(bench_modA PUBLIC nanobench)
