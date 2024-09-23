#pragma once

#include <iostream>
#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/fmt/bundled/core.h>

class ILogger {
protected:
    std::shared_ptr<spdlog::logger> _logger;

public:
    // clang-format off
    void setPattern(const std::string &pattern) { _logger->set_pattern(pattern); }
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
    void setLevelTrace()    { _logger->set_level(spdlog::level::trace);    }
    void setLevelDebug()    { _logger->set_level(spdlog::level::debug);    }
    void setLevelInfo()     { _logger->set_level(spdlog::level::info);     }
    void setLevelWarn()     { _logger->set_level(spdlog::level::warn);     }
    void setLevelError()    { _logger->set_level(spdlog::level::err);      }
    void setLevelCritical() { _logger->set_level(spdlog::level::critical); }

    inline void trace    (const std::string &s) const { _logger->trace(s);    }
    inline void debug    (const std::string &s) const { _logger->debug(s);    }
    inline void info     (const std::string &s) const { _logger->info(s);     }
    inline void warn     (const std::string &s) const { _logger->warn(s);     }
    inline void error    (const std::string &s) const { _logger->error(s);    }
    inline void critical (const std::string &s) const { _logger->critical(s); }
    // clang-format on
    std::shared_ptr<spdlog::logger> get() const { return _logger; }
};

class ConsoleLogger : public ILogger {
public:
    explicit ConsoleLogger(const std::string &name, const std::string &pattern = "[%L][%Y-%m-%d %T.%f][%n] %v") {
        auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        _logger = std::make_shared<spdlog::logger>(name, sink);
        _logger->set_pattern(pattern);
        spdlog::register_logger(_logger);
    }
    ConsoleLogger(const ConsoleLogger &) = delete;            // copy constructor
    ConsoleLogger(ConsoleLogger &&) = delete;                 // move constructor
    ConsoleLogger &operator=(ConsoleLogger const &) = delete; // copy
    ConsoleLogger &operator=(ConsoleLogger &&) = delete;      // move
    ~ConsoleLogger() = default;
};

class FileLogger : public ILogger {
public:
    explicit FileLogger(
        const std::string &name, const std::string &filename = "./log/basic.log",
        const std::string &pattern = "[%L][%Y-%m-%d %T.%f][%n] %v") {
        auto sink = std::make_shared<spdlog::sinks::basic_file_sink_st>(filename);
        _logger = std::make_shared<spdlog::logger>(name, sink);
        spdlog::initialize_logger(_logger);
        sink->set_pattern("[%L][%Y-%m-%d %T.%f][%n] %v");
        // spdlog::register_logger(_logger);
    }
    FileLogger(const FileLogger &) = delete;            // copy constructor
    FileLogger(FileLogger &&) = delete;                 // move constructor
    FileLogger &operator=(FileLogger const &) = delete; // copy
    FileLogger &operator=(FileLogger &&) = delete;      // move
    ~FileLogger() = default;
};

