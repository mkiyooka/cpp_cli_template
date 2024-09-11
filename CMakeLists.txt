cmake_minimum_required(VERSION 3.0)
project(MyProject VERSION 0.1.0 DESCRIPTION "Very nice project" LANGUAGES CXX)

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

if(NOT DEFINED CLI11_DIR)
    set (CLI11_DIR "mod/CLI11" CACHE STRING "CLI11 git repository")
endif()
if(NOT DEFINED SPDLOG_DIR)
    set (SPDLOG_DIR "mod/spdlog" CACHE STRING "spdlog git repository")
endif()

add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)
add_executable(cmd src/main.cpp)
add_subdirectory(${SPDLOG_DIR})
include_directories(${SPDLOG_DIR}/include)
target_link_libraries(cmd PUBLIC modA)
target_link_libraries(cmd PUBLIC modB)
target_link_libraries(cmd PUBLIC cli)
target_link_libraries(cmd PUBLIC spdlog)
