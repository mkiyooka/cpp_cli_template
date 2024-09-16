cmake_minimum_required(VERSION 3.0)
project(MyProject VERSION 0.1.0 DESCRIPTION "Very nice project" LANGUAGES CXX)

if(NOT DEFINED CLI11_DIR)
    set (CLI11_DIR "mod/CLI11" CACHE STRING "CLI11 git repository")
endif()
if(NOT DEFINED SPDLOG_DIR)
    set (SPDLOG_DIR "mod/spdlog" CACHE STRING "spdlog git repository")
endif()
if(NOT DEFINED FMT_DIR)
    set (FMT_DIR "mod/fmt" CACHE STRING "fmt git repository")
endif()

if(NOT DEFINED DOCTEST)
    set (DOCTEST "mod/doctest/doctest" CACHE STRING "doctest git repository")
endif()
if(NOT DEFINED NANOBENCH)
    set (NANOBENCH "mod/nanobench/src" CACHE STRING "nanobench git repository")
endif()

include_directories(include)
include_directories(${CLI11_DIR}/include)
include_directories(${SPDLOG_DIR}/include)
include_directories(${FMT_DIR}/include)

add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)
add_executable(cmd
    src/main.cpp
    src/cli.cpp include/cli.hpp
    src/cli_subcom_a.cpp include/cli_subcom_a.hpp
    src/generator_a.cpp include/generator_a.hpp
    src/generator_b.cpp include/generator_b.hpp
    src/solver.cpp include/solver.hpp
    src/setup_logger.cpp include/setup_logger.hpp
    )
add_subdirectory(${CLI11_DIR})
add_subdirectory(${SPDLOG_DIR})
add_subdirectory(${FMT_DIR})
target_link_libraries(cmd PUBLIC spdlog)
target_link_libraries(cmd PUBLIC fmt)
target_compile_features(cmd PUBLIC cxx_std_11)

# --- test ---
enable_testing()
add_executable(test_generator
    tests/test_generator.cpp
    src/generator_a.cpp include/generator_a.hpp
    src/generator_b.cpp include/generator_b.hpp
    )
target_include_directories(test_generator PUBLIC include)

include_directories(${DOCTEST})

# Add the test which is simply run the application.
add_test(
    NAME test_generator
    COMMAND $<TARGET_FILE:test_generator>)

add_executable(bench_generator
    bench/bench_generator.cpp
    src/generator_a.cpp include/generator_a.hpp
    src/generator_b.cpp include/generator_b.hpp
    )
target_include_directories(bench_generator PUBLIC ${NANOBENCH}/include)
