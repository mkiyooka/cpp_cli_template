#pragma once

#include <cstdint>

#include "igenerator.hpp"

class SolverBisection {
private:
    IGenerator &_generator;

public:
    SolverBisection(IGenerator &generator) : _generator(generator) {}
    ~SolverBisection() {}
    double solve(int32_t itr);
};

