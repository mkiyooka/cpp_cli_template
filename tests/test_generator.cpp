#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "GeneratorA.hpp"
#include "GeneratorB.hpp"

int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }

TEST_CASE("testing the factorial function") {
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(10) == 3628800);
}

TEST_CASE("testing GeneratorA") {
    GeneratorA generatorA;
    generatorA.setParam(2.0, 3.0);
    CHECK(generatorA.generate(3.0) == doctest::Approx(9.0).epsilon(0.01));
}

TEST_CASE("testing GeneratorB") {
    GeneratorB generatorB;
    generatorB.setParam(2.0, 3.0, 4.0);
    CHECK(generatorB.generate(3.0) == doctest::Approx(31.0).epsilon(0.01));
}
