#include <string>

#include "cli.hpp"
#include "spdlog/common.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/fmt/bundled/core.h>

class Logger {
private:
    // std::shared_ptr<spdlog::sinks::basic_file_sink_st> _sink;
    // std::shared_ptr<spdlog::logger> _loggerA;
    // std::shared_ptr<spdlog::logger> _loggerB;
    std::vector<std::shared_ptr<spdlog::logger>> _loggers;

public:
    explicit Logger() {
        auto _sink = std::make_shared<spdlog::sinks::basic_file_sink_st>("./logs/basicAB.log");
        auto _loggerA = std::make_shared<spdlog::logger>("loggerA", _sink);
        spdlog::initialize_logger(_loggerA);
        auto _loggerB = std::make_shared<spdlog::logger>("loggerB", _sink);
        spdlog::initialize_logger(_loggerB);
        // _sink->set_pattern("[%L][%E.%f][%n] %v");
        _sink->set_pattern("[%L][%Y-%m-%d %T.%f][%n] %v");
        // _sink->set_pattern("[%Y-%m-%d %T.%f][%n] %v");

        _loggerA->set_level(spdlog::level::debug);
        _loggerB->set_level(spdlog::level::info);
        // _loggers.push_back(_loggerA);
        // _loggers.push_back(_loggerB);
    }
    Logger &operator=(Logger const &) = delete;
    Logger(Logger &&) = delete;
    Logger &operator=(Logger &&) = delete;
    ~Logger() = default;
};

void func1() {
    auto logger1 = spdlog::get("logger1");
    logger1->debug("logger1@func1 debug");
    logger1->info("logger1@func1 info");
    auto logger2 = spdlog::get("logger2");
    logger2->debug("logger2@func1 debug");
    logger2->info("logger2@func1 info");

    auto loggerA = spdlog::get("loggerA");
    loggerA->debug("loggerA@func1 debug");
    loggerA->info("loggerA@func1 info");
    auto loggerB = spdlog::get("loggerB");
    loggerB->debug("loggerB@func1 debug");
    loggerB->info("loggerB@func1 info");
}

int main(int argc, char *argv[]) {

    auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("./logs/basic12.log");
    auto logger1 = std::make_shared<spdlog::logger>("logger1", sink);
    spdlog::initialize_logger(logger1);
    auto logger2 = std::make_shared<spdlog::logger>("logger2", sink);
    spdlog::initialize_logger(logger2);
    // sink->set_pattern("[%^%L%$][%E.%f][%n] %v"); // epoch time
    sink->set_pattern("[%^%L%$][%Y-%m-%d %T.%f][%n] %v");
    logger1->set_level(spdlog::level::debug);

    // auto logger1 = spdlog::get("logger1");
    // auto logger2 = spdlog::get("logger2");
    logger1->info("logger1@main info");
    logger2->info("logger2@main info");
    logger1->debug("logger1@main debug");
    logger2->debug("logger2@main debug");

    Logger logger;

    auto loggerA = spdlog::get("loggerA");
    auto loggerB = spdlog::get("loggerB");
    loggerA->info("loggerA@main info");
    loggerB->info("loggerB@main info");
    loggerA->debug("loggerA@main debug");
    loggerB->debug("loggerB@main debug");

    func1();

    // Parse arguments for CLI
    cli(argc, argv);

    return 0;
}
