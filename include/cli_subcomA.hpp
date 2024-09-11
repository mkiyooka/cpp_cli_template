#pragma once

#include <string>
#include <CLI/CLI.hpp>

/// Collection of all options of Subcommand A.
struct SubcomAOptions {
    std::string file;
    bool flag;
};

void cli_subcom_a(CLI::App &app);
