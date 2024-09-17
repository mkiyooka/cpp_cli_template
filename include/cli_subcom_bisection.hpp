#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>

/// Collection of all options of Subcommand Bisection Method.
struct SubcomBisectionOptions {
    std::string func;
    int32_t itr;
    std::vector<double> coefs;
    bool flag;
};

void cli_subcom_bisection(CLI::App &app);
