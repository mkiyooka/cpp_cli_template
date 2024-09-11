#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <cli_subcomA.hpp>

int cli(int argc, char *argv[]) {
    CLI::App app{"cmd description"};
    argv = app.ensure_utf8(argv);
    std::string filename = "default.txt";
    std::string loglevel = "error";
    app.add_option("-f,--file", filename, "default filename");
    app.add_option("-l,--loglevel", loglevel, "log level"
        "err trace debug info warn error critical");

    cli_subcom_a(app);

    try {
        app.parse(argc, argv);
    } catch(const CLI::CallForHelp &e) {
        exit(app.exit(e)); // app.exit(e) prints help
    }

    auto logger = spdlog::stdout_color_mt("console");
    if (loglevel == "trace") {
        logger->set_level(spdlog::level::trace);
    } else if (loglevel == "debug") {
        logger->set_level(spdlog::level::debug);
    } else if (loglevel == "info") {
        logger->set_level(spdlog::level::info);
    } else if (loglevel == "warning") {
        logger->set_level(spdlog::level::warn);
    } else if (loglevel == "error") {
        logger->set_level(spdlog::level::err);
    } else if (loglevel == "critical") {
        logger->set_level(spdlog::level::critical);
    }
    spdlog::register_logger(logger);
    spdlog::set_default_logger(logger);

    return 0;
}
