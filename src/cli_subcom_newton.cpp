#include <cstdio>
#include <memory>

#include <CLI/CLI.hpp>

#include "cli_subcom_newton.hpp"
#include "solver_newton.hpp"
#include "igenerator.hpp"
#include "generator_linear.hpp"
#include "generator_quadratic.hpp"

void solve_newton(SubcomNewtonOptions &opt) { // bisection method
    std::unique_ptr<IGenerator> generator;
    if (opt.func == "linear") {
        printf("linear: %+.3f * x %+.3f\n", opt.coefs[0], opt.coefs[1]);
        auto gen1 = std::unique_ptr<GeneratorLinear>(new GeneratorLinear);
        gen1->setParam(opt.coefs[0], opt.coefs[1]);
        generator = std::move(gen1);
    } else {
        printf("quadratic: %+.3f * x^2 %+.3f * x %+.3f\n", opt.coefs[0], 0.0, opt.coefs[1]);
        auto gen2 = std::unique_ptr<GeneratorQuadratic>(new GeneratorQuadratic);
        gen2->setParam(opt.coefs[0], 0.0, opt.coefs[1]);
        generator = std::move(gen2);
    }

    SolverNewton solver(*generator);
    printf("method: newton, itr: %d, x: %f\n", opt.itr, solver.solve(opt.itr));
}

void cli_subcom_newton(CLI::App &app) {

    auto opt = std::make_shared<SubcomNewtonOptions>();
    auto *sub = app.add_subcommand("newton", "solver: newton method");

    sub->add_option("func", opt->func, "Function (default: linear)")->required();
    sub->add_option("itr", opt->itr, "Iteration")->required();
    sub->add_option("--coefs", opt->coefs, "Coefficient (default: 2.0, -3.0))");
    sub->add_flag("--flag", opt->flag, "Flag");

    sub->callback([opt]() { solve_newton(*opt); });
}
