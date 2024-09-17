#include <string>
#include <memory>

// #include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/bundled/core.h>

#include <kangaru/kangaru.hpp>

#include "cli.hpp"
#include "generator_a.hpp"
#include "generator_b.hpp"
#include "solver.hpp"

// #include "setup_logger.hpp"

class SpdLogger {
private:
    std::shared_ptr<spdlog::logger> _logger;

public:
    explicit SpdLogger(const std::string &name) {
        auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        _logger = std::make_shared<spdlog::logger>(name, sink);
    }
    SpdLogger(const std::string &name, const std::string &pattern) {
        auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        _logger = std::make_shared<spdlog::logger>(name, sink);
        _logger->set_pattern(pattern);
    }
    ~SpdLogger() = default;
    SpdLogger(const SpdLogger &) = delete;
    SpdLogger &operator=(SpdLogger const &) = delete;
    SpdLogger(SpdLogger &&) = delete;
    SpdLogger &operator=(SpdLogger &&) = delete;
    void setPattern() { _logger->set_pattern("[%Y-%m-%d %T.%e][%^%L%$][%n] %v"); }
    void setPattern(const std::string &pattern) { _logger->set_pattern(pattern); }

    void setLevelTrace() { _logger->set_level(spdlog::level::trace); }
    void setLevelDebug() { _logger->set_level(spdlog::level::debug); }
    void setLevelInfo() { _logger->set_level(spdlog::level::info); }
    void setLevelWarn() { _logger->set_level(spdlog::level::warn); }
    void setLevelError() { _logger->set_level(spdlog::level::err); }
    void setLevelCritical() { _logger->set_level(spdlog::level::critical); }
    void setLevel(const std::string &logLevel) {
        if (logLevel == "trace") {
            _logger->set_level(spdlog::level::trace);
        } else if (logLevel == "debug") {
            _logger->set_level(spdlog::level::debug);
        } else if (logLevel == "info") {
            _logger->set_level(spdlog::level::info);
        } else if (logLevel == "warning") {
            _logger->set_level(spdlog::level::warn);
        } else if (logLevel == "error") {
            _logger->set_level(spdlog::level::err);
        } else if (logLevel == "critical") {
            _logger->set_level(spdlog::level::critical);
        }
    }
    void trace(const std::string &s) const { _logger->trace(s); }
    void debug(const std::string &s) const { _logger->debug(s); }
    void info(const std::string &s) const { _logger->info(s); }
    void warn(const std::string &s) const { _logger->warn(s); }
    void error(const std::string &s) const { _logger->error(s); }
    void critical(const std::string &s) const { _logger->critical(s); }
    std::shared_ptr<spdlog::logger> get() const { return _logger; }
};

struct GeneratorAService : kgr::single_service<GeneratorA> { };

struct SolverService : kgr::service<Solver, kgr::dependency<GeneratorAService>> { };

int main(int argc, char *argv[]) {
    // Parse arguments for CLI
    cli(argc, argv);
    fmt::print("Hello, world!\n");
    std::string s = fmt::format("Hello, {}!\n", "world");
    fmt::print(s);


    SpdLogger logger("color", "%^[%L][%Y-%m-%d %T.%F][%P/%t][%n] %v%$"); // %e:ms, %f:us, %F:ns
    logger.setLevelDebug();

    logger.trace("Trace");
    logger.debug("Debug");
    logger.info("Info");
    logger.warn("Warning");
    logger.error("Error");
    logger.critical("Critical");

    SPDLOG_TRACE("SPDLOG_TRACE");
    SPDLOG_DEBUG("SPDLOG_DEBUG");
    SPDLOG_INFO("SPDLOG_INFO");
    SPDLOG_WARN("SPDLOG_WARN");
    SPDLOG_ERROR("SPDLOG_ERROR");
    SPDLOG_CRITICAL("SPDLOG_CRITICAL");

    SPDLOG_LOGGER_TRACE(logger.get(), "SPDLOG_TRACE");
    SPDLOG_LOGGER_DEBUG(logger.get(), "SPDLOG_DEBUG");
    SPDLOG_LOGGER_INFO(logger.get(), "SPDLOG_INFO");
    SPDLOG_LOGGER_WARN(logger.get(), "SPDLOG_WARN");
    SPDLOG_LOGGER_ERROR(logger.get(), "SPDLOG_ERROR");
    SPDLOG_LOGGER_CRITICAL(logger.get(), "SPDLOG_CRITICAL");

    std::unique_ptr<IGenerator> generator;
    const std::string generator_type = "B";
    if (generator_type == "A") {
        auto generatorA = std::unique_ptr<GeneratorA>(new GeneratorA);
        generatorA->setParam(2, -3);
        generator = std::move(generatorA);
    } else {
        auto generatorB = std::unique_ptr<GeneratorB>(new GeneratorB);
        generatorB->setParam(2, 3, -4);
        generator = std::move(generatorB);
    }

    Solver solver(*generator);
    solver.solve();

    kgr::container container;
    //GeneratorA generatorA = container.service<GeneratorAService>();
    Solver solver_a = container.service<SolverService>();
    fmt::println("-------------------- solver container --------------------");
    solver_a.solve();

    return 0;
}
