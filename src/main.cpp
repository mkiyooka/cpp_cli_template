#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <cli.hpp>
#include <modA/modA1.hpp>
#include <modA/modA2.hpp>
#include <modB/modB1.hpp>
#include <modB/modB2.hpp>

int main(int argc, char *argv[]) {
    // Parse arguments for CLI
    cli(argc, argv);

    // spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e][%^%L%$][%n] %v");
    spdlog::set_pattern("[%^%L%$] %v");
    try {
        auto console_logger = spdlog::get("console");
        console_logger->trace("trace log");
        console_logger->debug("debug log");
        console_logger->info("info log");
        console_logger->warn("warn log");
        console_logger->error("erro log");
        console_logger->critical("critical log");
    } catch (const spdlog::spdlog_ex &ex) {
        std::cerr << "Log init failed: " << ex.what() << std::endl;
    }

    spdlog::trace("trace log");
    spdlog::debug("debug log");
    spdlog::info("info log");
    spdlog::warn("warn log");
    spdlog::error("erro log");
    spdlog::critical("critical log");

    spdlog::info("fmt int:{} double:{} char:{} chars:{}", 10, 3.14, 'c', "text");

    spdlog::info("add(2, 3)    = {}", add(2, 3));
    spdlog::info("sub(2, 3)    = {}", sub(2, 3));
    spdlog::info("mul(2, 3)    = {}", mul(2, 3));
    spdlog::info("divide(2, 3) = {}", divide(2, 3));

    return 0;
}
