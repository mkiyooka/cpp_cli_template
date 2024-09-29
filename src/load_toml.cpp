#include "load_toml.hpp"

void loadToml(const std::string &filePath, conf_t &conf) {
    auto tomlData = toml::parse(filePath, toml::spec::v(1, 0, 0));
    conf.title = toml::find<std::string>(tomlData, "title");
    conf.plugins = toml::find<std::vector<plugin_t>>(tomlData, "plugin");
    conf.loggers = toml::find<std::vector<logger_config_t>>(tomlData, "logger");
}
