#pragma once

#include <cstdint>

#include "igenerator.hpp"

class SolverNewton {
private:
    IGenerator &_generator;

public:
    SolverNewton(IGenerator &generator) : _generator(generator) {}
    ~SolverNewton() {}
    double solve(int32_t itr);
};

