#include "generator_quadratic.hpp"

// GeneratorQuadratic クラス
void GeneratorQuadratic::setParam(double a, double b, double c) {
    _a = a;
    _b = b;
    _c = c;
}
double GeneratorQuadratic::generate(double x) const { return _a * x * x + _b * x + _c; }
