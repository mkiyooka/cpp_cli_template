#include <memory>
#include <string>

#include <toml.hpp>

#include "cli.hpp"
#include "setup_logger.hpp"
#include "load_toml.hpp"

int main(int argc, char *argv[]) {
    cli(argc, argv); // Parse arguments for CLI

    std::shared_ptr<ILoggerMaker> loggerMaker = nullptr;

    conf_t conf;

    loadToml("../conf/example_sub1.toml", conf);
    // for(const auto &m: conf.plugins) {
    //  m.file, m.number;
    // }
    std::shared_ptr<spdlog::logger> A;
    for (const auto &m : conf.loggers) {
        if (m.type == "file") {
            loggerMaker = std::make_shared<FileLogger>(m.file);
            A = loggerMaker->build(m.name);
        } else {
            loggerMaker = std::make_shared<ConsoleLogger>();
        }
    }

    auto B = loggerMaker->build("B");
    auto C = loggerMaker->build("C");
    A->set_level(spdlog::level::warn);

    A->warn("this is log@main");
    B->warn("this is log@main");
    C->info("this is log@main");

    return 0;
}
