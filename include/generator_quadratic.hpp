#include "igenerator.hpp"

// GeneratorQuadratic クラス
class GeneratorQuadratic : public IGenerator {
private:
    int _a;
    int _b;
    int _c;

public:
    GeneratorQuadratic(){};
    void setParam(double a, double b, double c);
    double generate(double x) const override;
    ~GeneratorQuadratic(){};
};

