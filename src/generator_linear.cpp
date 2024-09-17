#include "generator_linear.hpp"

void GeneratorLinear::setParam(double a, double b) {
    _a = a;
    _b = b;
}

double GeneratorLinear::generate(double x) const { return _a * x + _b; }
