#include "GeneratorA.hpp"

void GeneratorA::setParam(double a, double b) {
    _a = a;
    _b = b;
}

double GeneratorA::generate(double x) const { return _a * x + _b; }
