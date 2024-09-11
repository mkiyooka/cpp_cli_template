#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include "modA/modA1.hpp"
#include "modA/modA2.hpp"

int main() {
    double d = 1.0;
    ankerl::nanobench::Bench().run("some double ops", [&] {
        d += 1.0 / d;
        if (d > 5.0) {
            d -= 5.0;
        }
        ankerl::nanobench::doNotOptimizeAway(d);
    });
    int r;
    ankerl::nanobench::Bench().run("add, sub x 1000 times function", [&] {
        for (auto i = 0; i < 1000; i++) {
            r = add(2, 3);
            r = sub(2, 3);
        }
        ankerl::nanobench::doNotOptimizeAway(r);
    });
    ankerl::nanobench::Bench().minEpochIterations(1000).run("sub func x 1000", [&] {
        for (auto i = 0; i < 1000; ++i) {
            r = sub(2, 3);
            ankerl::nanobench::doNotOptimizeAway(r);
        }
    });
}
