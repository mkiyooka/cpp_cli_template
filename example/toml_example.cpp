#include <memory>
#include <string>

#include <toml.hpp>

#include "setup_logger.hpp"

struct conf_t {
    std::string title;
    std::string owner_name;
};

void loadToml(conf_t &conf, const std::string &filePath);

int main(int argc, char *argv[]) {
    conf_t conf;
    loadToml(conf, "../conf/example.toml");

    return 0;
}

void loadToml(conf_t &conf, const std::string &filePath) {
    auto paramLogger = std::make_shared<ConsoleLogger>("param");
    auto p = paramLogger->get();

    auto tomlData = toml::parse("../conf/example.toml", toml::spec::v(1, 0, 0));

    // title = "TOML Example"
    conf.title = tomlData.at("title").as_string();
    p->info("title: {}", conf.title);

    // [owner]
    // name = "Tom Preston-Werner"
    // dob = 1979-05-27T07:32:00-08:00 # First class dates
    conf.owner_name = tomlData.at("owner").at("name").as_string();
    auto dob1 = toml::find<toml::offset_datetime>(tomlData, "owner", "dob");
    auto dob2 = tomlData.at("owner").at("dob").as_offset_datetime();
    p->info("owner.name: {}", conf.owner_name);
    p->info(
        "{:04d}-{:02d}-{:02d}T{:02d}:{:02d}:{:02d}{:+03d}:{:02d}", dob1.date.year, dob1.date.month, dob1.date.day,
        dob1.time.hour, dob1.time.minute, dob1.time.second, dob1.offset.hour, dob1.offset.minute);
    p->info(
        "{:04d}-{:02d}-{:02d}T{:02d}:{:02d}:{:02d}{:+03d}:{:02d}", dob2.date.year, dob2.date.month, dob2.date.day,
        dob2.time.hour, dob2.time.minute, dob2.time.second, dob2.offset.hour, dob2.offset.minute);


    // [database]
    // server = "192.168.1.1"
    // ports = [ 8000, 8001, 8002 ]
    // connection_max = 5000
    // enabled = true
    auto database_server1 = toml::find<std::string>(tomlData, "database", "server");
    auto database_server2 = tomlData.at("database").at("server").as_string();
    p->info("database.server: {} {}", database_server1, database_server2);
    auto database_ports = toml::find<std::vector<int>>(tomlData, "database", "ports");
    p->info("database.ports: {}, {}, {}", database_ports[0], database_ports[1], database_ports[2]);
    auto database_connection_max = toml::find<int>(tomlData, "database", "connection_max");
    p->info("database.connection_max: {}", database_connection_max);

    // [servers]
    //   # Indentation (tabs and/or spaces) is allowed but not required
    //   [servers.alpha]
    //   ip = "10.0.0.1"
    //   dc = "eqdc10"
    //   [servers.beta]
    //   ip = "10.0.0.2"
    //   dc = "eqdc10"
    auto alpha_ip = toml::find<std::string>(tomlData, "servers", "alpha", "ip");
    auto alpha_dc = toml::find<std::string>(tomlData, "servers", "alpha", "dc");
    p->info("alpha.ip: {}", alpha_ip);
    p->info("alpha.dc: {}", alpha_dc);
    auto beta_ip = toml::find<std::string>(tomlData, "servers", "beta", "ip");
    auto beta_dc = toml::find<std::string>(tomlData, "servers", "beta", "dc");
    p->info("beta.ip: {}", beta_ip);
    p->info("beta.dc: {}", beta_dc);

    // [clients]
    // data = [ ["gamma", "delta"], [1, 2] ]

    // # Line breaks are OK when inside arrays
    // hosts = [
    //   "alpha",
    //   "omega"
    // ]
    auto clients = tomlData.at("clients");
    auto data = clients.at("data");
    p->info("[{} {}]",
            data.at(0).at(0).as_string(),
            data.at(0).at(1).as_string());
    p->info("[{} {}]",
            data.at(1).at(0).as_integer(),
            data.at(1).at(1).as_integer());
    auto Pair = toml::find<std::pair<std::vector<std::string>, std::vector<int>>>(clients, "data");
    p->info("[{} {}]",
            Pair.first[0],
            Pair.first[1]);
    p->info("[{} {}]",
            Pair.second[0],
            Pair.second[1]);
    auto Tuple = toml::find<std::tuple<std::vector<std::string>, std::vector<int>>>(clients, "data");
    p->info("[{} {}]",
            std::get<0>(Tuple)[0],
            std::get<0>(Tuple)[1]);
    p->info("[{} {}]",
            std::get<1>(Tuple)[0],
            std::get<1>(Tuple)[1]);

    auto clients_hosts = toml::find<std::vector<std::string>>(tomlData, "clients", "hosts");
    p->info("clients_hosts: {} {}",
            clients_hosts[0],
            clients_hosts[1]
            );
}
