#include <cstdint>

#include "igenerator.hpp"
#include "solver_bisection.hpp"

double SolverBisection::solve(int32_t itr) {
    double xl = 0.0;
    double xr = 5.0;
    double y;
    double xm;
    for (auto i = 0; i < itr; i++) {
        xm = (xl + xr) / 2.0;
        y = _generator.generate(xm);
        if (y < 0.0) {
            xl = xm;
        } else {
            xr = xm;
        }
    }
    return xm;
}
