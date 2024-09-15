#include <iostream>

#include "IGenerator.hpp"

// GeneratorB クラス
class GeneratorB : public IGenerator {
private:
    int _a;
    int _b;
    int _c;

public:
    GeneratorB() { std::cout << "GeneratorB constructor" << std::endl; };
    void setParam(double a, double b, double c);
    double generate(double x) const override;
    ~GeneratorB() { std::cout << "GeneratorB destructor" << std::endl; };
};

