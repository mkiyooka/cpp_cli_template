#include "GeneratorB.hpp"

// GeneratorB クラス
void GeneratorB::setParam(double a, double b, double c) {
    _a = a;
    _b = b;
    _c = c;
}
double GeneratorB::generate(double x) const { return _a * x * x + _b * x + _c; }
