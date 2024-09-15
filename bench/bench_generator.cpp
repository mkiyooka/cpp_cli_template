#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include "GeneratorA.hpp"
#include "GeneratorB.hpp"

int main() {
    GeneratorA generatorA;
    generatorA.setParam(2.0, 3.0);
    GeneratorB generatorB;
    generatorB.setParam(2.0, 3.0, 4.0);
    double r;
    ankerl::nanobench::Bench().run("generateA.generate 1000 times function", [&] {
        for (auto i = 0; i < 1000; i++) {
            r = generatorA.generate(2.0);
        }
        ankerl::nanobench::doNotOptimizeAway(r);
    });
    ankerl::nanobench::Bench().minEpochIterations(1000).run("generateA.generate 1000 times function", [&] {
        for (auto i = 0; i < 1000; ++i) {
            r = generatorA.generate(2.0);
            ankerl::nanobench::doNotOptimizeAway(r);
        }
    });
    ankerl::nanobench::Bench().run("generateB.generate 1000 times function", [&] {
        for (auto i = 0; i < 1000; i++) {
            r = generatorB.generate(2.0);
        }
        ankerl::nanobench::doNotOptimizeAway(r);
    });
    ankerl::nanobench::Bench().minEpochIterations(1000).run("generateB.generate 1000 times function", [&] {
        for (auto i = 0; i < 1000; ++i) {
            r = generatorB.generate(2.0);
            ankerl::nanobench::doNotOptimizeAway(r);
        }
    });
}
