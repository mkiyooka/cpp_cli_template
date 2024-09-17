#include <string>

#include "cli.hpp"

#include "setup_logger.hpp"

int main(int argc, char *argv[]) {
    // Parse arguments for CLI
    cli(argc, argv);

    SpdLogger logger("log1");
    logger.setLevelWarn();
    logger.debug("Debug");
    logger.info("Info");
    logger.warn("Warn");

    return 0;
}
