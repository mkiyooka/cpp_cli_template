#pragma once

#include <map>
#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/fmt/bundled/core.h>

class ILoggerMaker {
protected:
    std::map<std::string, std::shared_ptr<spdlog::logger>> _loggers;

public:
    // clang-format off
    void setLevel(const std::string &name, const std::string &logLevel) {
        if (logLevel == "trace") {
            _loggers.at(name)->set_level(spdlog::level::trace);
        } else if (logLevel == "debug") {
            _loggers.at(name)->set_level(spdlog::level::debug);
        } else if (logLevel == "info") {
            _loggers.at(name)->set_level(spdlog::level::info);
        } else if (logLevel == "warning") {
            _loggers.at(name)->set_level(spdlog::level::warn);
        } else if (logLevel == "error") {
            _loggers.at(name)->set_level(spdlog::level::err);
        } else if (logLevel == "critical") {
            _loggers.at(name)->set_level(spdlog::level::critical);
        }
    }
    void setLevelTrace(const std::string &name)    { _loggers.at(name)->set_level(spdlog::level::trace);    }
    void setLevelDebug(const std::string &name)    { _loggers.at(name)->set_level(spdlog::level::debug);    }
    void setLevelInfo(const std::string &name)     { _loggers.at(name)->set_level(spdlog::level::info);     }
    void setLevelWarn(const std::string &name)     { _loggers.at(name)->set_level(spdlog::level::warn);     }
    void setLevelError(const std::string &name)    { _loggers.at(name)->set_level(spdlog::level::err);      }
    void setLevelCritical(const std::string &name) { _loggers.at(name)->set_level(spdlog::level::critical); }
    // clang-format on
    std::shared_ptr<spdlog::logger> get(const std::string &name) const { return _loggers.at(name); }
    virtual std::shared_ptr<spdlog::logger> build(const std::string &name) = 0;
};

class ConsoleLogger : public ILoggerMaker {
private:
    std::shared_ptr<spdlog::sinks::sink> _sink;

public:
    explicit ConsoleLogger(const std::string &pattern = "[%L][%Y-%m-%d %T.%f][%n] %v") {
        _sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    }
    ConsoleLogger(const ConsoleLogger &) = delete;            // copy constructor
    ConsoleLogger(ConsoleLogger &&) = delete;                 // move constructor
    ConsoleLogger &operator=(ConsoleLogger const &) = delete; // copy
    ConsoleLogger &operator=(ConsoleLogger &&) = delete;      // move
    ~ConsoleLogger() = default;

    std::shared_ptr<spdlog::logger> build(const std::string &name) override {
        auto logger = std::make_shared<spdlog::logger>(name, _sink);
        logger->set_pattern("[%L][%Y-%m-%d %T.%f][%n] %v");
        //spdlog::register_logger(logger);
        _loggers.insert({name, logger});
        return logger;
    }
};

class FileLogger : public ILoggerMaker {
private:
    std::shared_ptr<spdlog::sinks::sink> _sink;

public:
    explicit FileLogger(
        const std::string &filename = "./log/basic.log", const std::string &pattern = "[%L][%Y-%m-%d %T.%f][%n] %v") {
        _sink = std::make_shared<spdlog::sinks::basic_file_sink_st>(filename);
    }
    FileLogger(const FileLogger &) = delete;            // copy constructor
    FileLogger(FileLogger &&) = delete;                 // move constructor
    FileLogger &operator=(FileLogger const &) = delete; // copy
    FileLogger &operator=(FileLogger &&) = delete;      // move
    ~FileLogger() = default;

    std::shared_ptr<spdlog::logger> build(const std::string &name) override {
        auto logger = std::make_shared<spdlog::logger>(name, _sink);
        spdlog::initialize_logger(logger);
        logger->set_pattern("[%L][%Y-%m-%d %T.%f][%n] %v");
        _loggers.insert({name, logger});
        return logger;
    }
};

