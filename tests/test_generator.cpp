#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "generator_linear.hpp"
#include "generator_quadratic.hpp"

class GenQuadraticTestsFixture {
protected:
    GeneratorQuadratic *gen2;

public:
    GenQuadraticTestsFixture() : gen2(new GeneratorQuadratic) {};
    ~GenQuadraticTestsFixture(){};
};

TEST_CASE("testing GeneratorLinear") {
    GeneratorLinear gen1;
    gen1.setParam(2.0, 3.0);
    CHECK(gen1.generate(3.0) == doctest::Approx(9.0).epsilon(0.01));
}

TEST_CASE_FIXTURE(GenQuadraticTestsFixture, "testing GeneratorQuadratic") {
    gen2->setParam(2.0, 3.0, 4.0);
    CHECK(gen2->generate(3.0) == doctest::Approx(31.0).epsilon(0.01));
}
