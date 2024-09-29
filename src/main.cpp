#include <memory>
#include <string>
#include <thread>
#include <chrono>

#include <toml.hpp>
#include <indicators/cursor_control.hpp>
#include <indicators/block_progress_bar.hpp>
#include <indicators/progress_bar.hpp>

#include "cli.hpp"
#include "setup_logger.hpp"
#include "load_toml.hpp"

void progress_bar1();
void progress_bar2();

int main(int argc, char *argv[]) {
    cli(argc, argv); // Parse arguments for CLI

    std::shared_ptr<ILoggerMaker> loggerMaker = nullptr;

    conf_t conf;

    loadToml("../conf/example_sub1.toml", conf);
    // for(const auto &m: conf.plugins) {
    //  m.file, m.number;
    // }
    std::shared_ptr<spdlog::logger> A;
    for (const auto &m : conf.loggers) {
        if (m.type == "file") {
            loggerMaker = std::make_shared<FileLogger>(m.file);
            A = loggerMaker->build(m.name);
        } else {
            loggerMaker = std::make_shared<ConsoleLogger>();
        }
    }

    auto B = loggerMaker->build("B");
    auto C = loggerMaker->build("C");
    A->set_level(spdlog::level::warn);

    A->warn("AA");
    B->warn("BB");
    C->info("CC");
    progress_bar1();
    progress_bar2();

    return 0;
}

void progress_bar1() {
    using namespace indicators;

    show_console_cursor(false);

    ProgressBar bar{
        option::BarWidth{50},
        option::Start{"["},
        option::Fill{"="},
        option::Lead{">"},
        option::Remainder{" "},
        option::End{"]"},
        option::PrefixText{"Progress "},
        option::PostfixText{"Loading dependency 1/4"},
        option::ForegroundColor{Color::cyan},
        option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}};

    bar.set_progress(10); // 10% done

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    bar.set_option(option::PostfixText{"Loading dependency 2/4"});
    bar.set_progress(30); // 30% done

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    bar.set_option(option::PostfixText{"Loading dependency 3/4"});
    bar.set_progress(65); // 65% done

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    bar.set_option(option::PostfixText{"Loaded dependencies!"});
    bar.set_progress(100); // all done

    show_console_cursor(true);
}

void progress_bar2() {
    indicators::show_console_cursor(false);

    std::vector<size_t> numbers;
    for (size_t i = 0; i < 2200; ++i) {
        numbers.push_back(i);
    }

    std::string s = "Progress ";
    using namespace indicators;
    ProgressBar bar{
        option::BarWidth{50},
        option::Start{"["},
        option::Fill{"="},
        option::Lead{">"},
        option::Remainder{" "},
        option::End{"]"},
        option::PrefixText{s},
        option::PostfixText{"Loading dependency 1/4"},
        option::ForegroundColor{Color::cyan},
        option::FontStyles{std::vector<FontStyle>{FontStyle::bold}},
        option::MaxProgress{numbers.size()}};

    std::vector<size_t> result;
    for (size_t i = 0; i < numbers.size(); ++i) {

        result.push_back(numbers[i] * numbers[i]);

        bar.set_option(
                option::PostfixText{
                std::to_string(i+1) + "/" + std::to_string(numbers.size())});

        bar.tick();
    }

    indicators::show_console_cursor(true);
}
