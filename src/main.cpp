#include <memory>
#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/fmt/bundled/core.h>

#include "cli.hpp"
#include "setup_logger.hpp"

void func1(const std::shared_ptr<ILogger> &logger) {
    logger->info("this is log@func1");
}

void func2(const std::shared_ptr<ILogger> &logger) {
    logger->info("this is log@func2");
}

int main(int argc, char *argv[]) {
    cli(argc, argv); // Parse arguments for CLI

    std::shared_ptr<ILogger> logger = nullptr;
    const std::string s = "file";
    if (s == "file") {
        logger = std::make_shared<FileLogger>("Logger2", "./log/basic.log");
    } else {
        logger = std::make_shared<ConsoleLogger>("Logger1");
    }
    logger->info("this is log@main");
    func1(logger);
    func2(logger);

    return 0;
}
