#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "modB/modB1.hpp"
#include "modB/modB2.hpp"

TEST_CASE("testing mul function") {
    CHECK(mul(2, 3) == 6);
}

TEST_CASE("testing div function") {
    CHECK(divide(2, 3) == 0);
}
