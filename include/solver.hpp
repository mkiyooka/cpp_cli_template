#pragma once

#include "igenerator.hpp"

class Solver {
private:
    IGenerator &_generator;

public:
    Solver(IGenerator &generator) : _generator(generator) {}
    void solve();
    ~Solver() {}
};

