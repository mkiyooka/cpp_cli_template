#include <cstdint>

#include "igenerator.hpp"
#include "solver_newton.hpp"

double SolverNewton::solve(int32_t itr) {
    double d = 0.001;
    double xm = 2.5;
    for (auto i = 0; i < itr; i++) {
        double x1 = xm - d;
        double x2 = xm + d;
        double y = _generator.generate(xm);
        double dydx = (_generator.generate(x2) - _generator.generate(x1)) / (2.0 * d);
        xm = xm - y / dydx;
    }
    return xm;
}
