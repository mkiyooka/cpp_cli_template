#include <iostream>

#include "IGenerator.hpp"

// GeneratorA クラス
class GeneratorA : public IGenerator {
private:
    int _a;
    int _b;

public:
    GeneratorA() { std::cout << "GeneratorA constructor" << std::endl; };
    void setParam(double a, double b);
    double generate(double x) const override;
    ~GeneratorA() { std::cout << "GeneratorA destructor" << std::endl; };
};

