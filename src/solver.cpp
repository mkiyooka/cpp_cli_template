#include <iostream>

#include "igenerator.hpp"
#include "solver.hpp"

void Solver::solve() {
    double xl = 0.0;
    double xr = 5.0;
    double y;
    double xm;
    for (auto i = 0; i < 100; i++) {
        xm = (xl + xr) / 2.0;
        y = _generator.generate(xm);
        if (y < 0.0) {
            xl = xm;
        } else {
            xr = xm;
        }
    }
    std::cout << "solve   x: " << xm << ", y: " << y << std::endl;
}
