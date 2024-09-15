#pragma once

#include "IGenerator.hpp"

class Solver {
private:
    IGenerator &_generator;

public:
    Solver(IGenerator &generator) : _generator(generator) {}
    void solve();
    ~Solver() {}
};

