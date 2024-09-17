#pragma once

#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/bundled/core.h>

class SpdLogger {
private:
    std::shared_ptr<spdlog::logger> _logger;

public:
    explicit SpdLogger(const std::string &name) {
        auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        _logger = std::make_shared<spdlog::logger>(name, sink);
        _logger->set_pattern("[%^%L%$][%Y-%m-%d %T.%F][%t][%n] %v");
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
    void setPatternDefault() { _logger->set_pattern("[%Y-%m-%d %T.%e][%^%L%$][%n] %v"); }
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
