#include <iostream>
#include <memory>

#include <CLI/CLI.hpp>

#include <cli_subcomA.hpp>

void cli_subcom_a(CLI::App &app) {

    auto opt = std::make_shared<SubcomAOptions>();
    auto *sub = app.add_subcommand("subA", "subcommand a");

    sub->add_option("-f,--file", opt->file, "File name")->required();
    sub->add_flag("--flag", opt->flag, "Counter");

    return;
}
