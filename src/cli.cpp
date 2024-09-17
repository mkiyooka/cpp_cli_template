#include <CLI/CLI.hpp>

#include "cli_subcom_bisection.hpp"
#include "cli_subcom_newton.hpp"

int cli(int argc, char *argv[]) {
    CLI::App app{"cmd description"};
    argv = app.ensure_utf8(argv);
    std::string filename = "default.txt";
    std::string loglevel = "error";
    app.add_option("-f,--file", filename, "default filename");
    app.add_option(
        "-l,--loglevel", loglevel,
        "log level: "
        "err trace debug info warn error critical");

    cli_subcom_bisection(app);
    cli_subcom_newton(app);

    try {
        app.parse(argc, argv);
    } catch (const CLI::CallForHelp &e) {
        exit(app.exit(e)); // app.exit(e) prints help
    }
    return 0;
}
