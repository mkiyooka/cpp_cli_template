#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include "generator_linear.hpp"
#include "generator_quadratic.hpp"

int main() {
    GeneratorLinear gen1;
    gen1.setParam(2.0, 3.0);
    GeneratorQuadratic gen2;
    gen2.setParam(2.0, 3.0, 4.0);
    double r;
    ankerl::nanobench::Bench().run("generateA.generate 1000 times function", [&] {
        for (auto i = 0; i < 1000; i++) {
            r = gen1.generate(2.0);
        }
        ankerl::nanobench::doNotOptimizeAway(r);
    });
    ankerl::nanobench::Bench().minEpochIterations(100).run("generateA.generate 1000 times function", [&] {
        for (auto i = 0; i < 1000; ++i) {
            r = gen1.generate(2.0);
            ankerl::nanobench::doNotOptimizeAway(r);
        }
    });
    ankerl::nanobench::Bench().run("generateB.generate 1000 times function", [&] {
        for (auto i = 0; i < 1000; i++) {
            r = gen2.generate(2.0);
        }
        ankerl::nanobench::doNotOptimizeAway(r);
    });
    ankerl::nanobench::Bench().minEpochIterations(10).run("generateB.generate 1000 times function", [&] {
        for (auto i = 0; i < 1000; ++i) {
            r = gen2.generate(2.0);
            ankerl::nanobench::doNotOptimizeAway(r);
        }
    });
}
