cmake_minimum_required(VERSION 3.0)
project(MyProject VERSION 0.1.0 DESCRIPTION "Very nice project" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11) # C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Disable GNU Extention

if(NOT DEFINED CLI11_DIR)
    set (CLI11_DIR "third_party/CLI11" CACHE STRING "CLI11 git repository")
endif()
if(NOT DEFINED SPDLOG_DIR)
    set (SPDLOG_DIR "third_party/spdlog" CACHE STRING "spdlog git repository")
endif()
if(NOT DEFINED TOML11_DIR)
    set (TOML11_DIR "third_party/toml11" CACHE STRING "toml11 git repository")
endif()
if(NOT DEFINED FMT_DIR)
    set (FMT_DIR "third_party/fmt" CACHE STRING "fmt git repository")
endif()

if(NOT DEFINED DOCTEST)
    set (DOCTEST "third_party/doctest/doctest" CACHE STRING "doctest git repository")
endif()
if(NOT DEFINED NANOBENCH)
    set (NANOBENCH "third_party/nanobench/src" CACHE STRING "nanobench git repository")
endif()

include_directories(include)
include_directories(${CLI11_DIR}/include)
include_directories(${SPDLOG_DIR}/include)
include_directories(${TOML11}/include)
include_directories(${FMT_DIR}/include)

add_executable(cmd
    src/main.cpp
    src/cli.cpp include/cli.hpp
    src/cli_subcom_bisection.cpp include/cli_subcom_bisection.hpp
    src/cli_subcom_newton.cpp include/cli_subcom_newton.hpp
    src/generator_linear.cpp include/generator_linear.hpp
    src/generator_quadratic.cpp include/generator_quadratic.hpp
    src/solver_newton.cpp include/solver_newton.hpp
    src/solver_bisection.cpp include/solver_bisection.hpp
    src/setup_logger.cpp include/setup_logger.hpp
    )
add_subdirectory(${CLI11_DIR})
add_subdirectory(${SPDLOG_DIR})
add_subdirectory(${TOML11_DIR})
add_subdirectory(${FMT_DIR})
target_link_libraries(cmd PUBLIC spdlog)
target_link_libraries(cmd PUBLIC toml11)
target_link_libraries(cmd PUBLIC fmt)

# --- test ---
enable_testing()
add_executable(test_generator
    tests/test_generator.cpp
    src/generator_linear.cpp include/generator_linear.hpp
    src/generator_quadratic.cpp include/generator_quadratic.hpp
    )
target_include_directories(test_generator PUBLIC include)

include_directories(${DOCTEST})

# Add the test which is simply run the application.
add_test(
    NAME test_generator
    COMMAND $<TARGET_FILE:test_generator>)

add_executable(bench_generator
    bench/bench_generator.cpp
    src/generator_linear.cpp include/generator_linear.hpp
    src/generator_quadratic.cpp include/generator_quadratic.hpp
    )
target_include_directories(bench_generator PUBLIC ${NANOBENCH}/include)
