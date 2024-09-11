#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "modA/modA2.hpp"

TEST_CASE("testing sub function") {
    CHECK(sub(2, 3) == -1);
    CHECK(sub(2, 3) == 0);
}
