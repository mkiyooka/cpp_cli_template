#pragma once

class IGenerator {
public:
    virtual double generate(double x) const = 0;
    virtual ~IGenerator() = default;
};

