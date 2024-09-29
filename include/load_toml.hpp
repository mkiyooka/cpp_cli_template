#pragma once

#include <string>
#include <vector>

#include <toml.hpp>

struct plugin_t {
    std::string file;
    std::uint64_t number;
    plugin_t(const toml::value &v)
        : file(toml::find_or<std::string>(v, "file", "")),
          number(toml::find_or<std::uint64_t>(v, "number", 0)) {}
};

struct logger_config_t {
    std::string type;
    std::string file;
    std::string name;
    logger_config_t(const toml::value &v)
        : type(toml::find_or<std::string>(v, "type", "")),
          file(toml::find_or<std::string>(v, "file", "")),
          name(toml::find_or<std::string>(v, "name", "")) {}
};

struct conf_t {
    std::string title;
    std::vector<plugin_t> plugins;
    std::vector<logger_config_t> loggers;
};

void loadToml(const std::string &filePath, conf_t &conf);
