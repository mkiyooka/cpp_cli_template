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
    ankerl::nanobench::Bench().run("add, sub function", [&] {
        for (auto i = 0; i < 1000; i++) {
            r = add(2, 3);
            r = add(3, 4);
            r = sub(2, 3);
        }
        ankerl::nanobench::doNotOptimizeAway(r);
    });
}
