#include <memory>
#include <string>

#include <toml.hpp>

#include "cli.hpp"
#include "setup_logger.hpp"

void func1(const std::shared_ptr<ILogger> &logger) { logger->info("this is log@func1"); }

void func2(const std::shared_ptr<ILogger> &logger) { logger->info("this is log@func2"); }

int main(int argc, char *argv[]) {
    cli(argc, argv); // Parse arguments for CLI

    std::shared_ptr<ILogger> logger = nullptr;
    const std::string s = "console";
    if (s == "file") {
        logger = std::make_shared<FileLogger>("Logger2", "./log/basic.log");
    } else {
        logger = std::make_shared<ConsoleLogger>("Logger1");
    }
    logger->info("this is log@main");
    func1(logger);
    func2(logger);

    auto paramLogger = std::make_shared<ConsoleLogger>("param");
    auto p = paramLogger->get();
    auto conf = toml::parse("../conf/example.toml", toml::spec::v(1, 0, 0));

    // title = "TOML Example"
    auto title = toml::find<std::string>(conf, "title");
    p->info(title);

    // [owner]
    // name = "Tom Preston-Werner"
    // dob = 1979-05-27T07:32:00-08:00 # First class dates
    auto owner_name = toml::find<std::string>(conf, "owner", "name");
    p->info(owner_name);
    auto dob = toml::find<toml::offset_datetime>(conf, "owner", "dob");
    p->info(
        "{:04d}-{:02d}-{:02d}T{:02d}:{:02d}:{:02d}{:+03d}:{:02d}", dob.date.year, dob.date.month, dob.date.day,
        dob.time.hour, dob.time.minute, dob.time.second, dob.offset.hour, dob.offset.minute);

    // [database]
    // server = "192.168.1.1"
    // ports = [ 8000, 8001, 8002 ]
    // connection_max = 5000
    // enabled = true
    auto database_server = toml::find<std::string>(conf, "database", "server");
    p->info("database.server: {}", database_server);
    auto database_ports = toml::find<std::vector<int>>(conf, "database", "ports");
    p->info("database.ports: {}, {}, {}", database_ports[0], database_ports[1], database_ports[2]);
    auto database_connection_max = toml::find<int>(conf, "database", "connection_max");
    p->info("database.connection_max: {}", database_connection_max);

    // [servers]
    //   # Indentation (tabs and/or spaces) is allowed but not required
    //   [servers.alpha]
    //   ip = "10.0.0.1"
    //   dc = "eqdc10"
    //   [servers.beta]
    //   ip = "10.0.0.2"
    //   dc = "eqdc10"
    auto alpha_ip = toml::find<std::string>(conf, "servers", "alpha", "ip");
    auto alpha_dc = toml::find<std::string>(conf, "servers", "alpha", "dc");
    p->info("alpha.ip: {}", alpha_ip);
    p->info("alpha.dc: {}", alpha_dc);
    auto beta_ip = toml::find<std::string>(conf, "servers", "beta", "ip");
    auto beta_dc = toml::find<std::string>(conf, "servers", "beta", "dc");
    p->info("beta.ip: {}", beta_ip);
    p->info("beta.dc: {}", beta_dc);

    // [clients]
    // data = [ ["gamma", "delta"], [1, 2] ]

    // # Line breaks are OK when inside arrays
    // hosts = [
    //   "alpha",
    //   "omega"
    // ]
    auto clients_hosts = toml::find<std::vector<std::string>>(conf, "clients", "hosts");
    p->info("clients_hosts: {} {}",
            clients_hosts[0],
            clients_hosts[1]
            );
    return 0;
}
