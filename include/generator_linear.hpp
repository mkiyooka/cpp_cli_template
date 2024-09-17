#include "igenerator.hpp"

// GeneratorLinear クラス
class GeneratorLinear : public IGenerator {
private:
    int _a;
    int _b;

public:
    GeneratorLinear(){};
    void setParam(double a, double b);
    double generate(double x) const override;
    ~GeneratorLinear(){};
};

