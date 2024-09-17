#include <memory>

#include <CLI/CLI.hpp>
#include <fmt/core.h>

#include "cli_subcom_bisection.hpp"
#include "solver_bisection.hpp"
#include "igenerator.hpp"
#include "generator_linear.hpp"
#include "generator_quadratic.hpp"

double solve_bisection(SubcomBisectionOptions &opt) { // bisection method
    std::unique_ptr<IGenerator> generator;
    if (opt.func == "linear") {
        fmt::println("linear: {:+.3f} * x {:+.3f}", opt.coefs[0], opt.coefs[1]);
        auto gen1 = std::unique_ptr<GeneratorLinear>(new GeneratorLinear);
        gen1->setParam(opt.coefs[0], opt.coefs[1]);
        generator = std::move(gen1);
    } else {
        fmt::println("quadratic: {:+.3f} * x^2 {:+.3f} * x {:+.3f}", opt.coefs[0], 0.0, opt.coefs[1]);
        auto gen2 = std::unique_ptr<GeneratorQuadratic>(new GeneratorQuadratic);
        gen2->setParam(opt.coefs[0], 0.0, opt.coefs[1]);
        generator = std::move(gen2);
    }

    SolverBisection solver(*generator);
    return solver.solve(opt.itr);
}

void cli_subcom_bisection(CLI::App &app) {

    auto opt = std::make_shared<SubcomBisectionOptions>();
    auto *sub = app.add_subcommand("bisection", "solver: bisection method");

    sub->add_option("func", opt->func, "Function (default: linear)")->required();
    sub->add_option("itr", opt->itr, "Iteration")->required();
    sub->add_option("--coefs", opt->coefs, "Coefficient (default: 2.0, -3.0))");
    sub->add_flag("--flag", opt->flag, "Flag");

    sub->callback([opt]() { fmt::println("method: bisection, itr: {}, x: {}", opt->itr, solve_bisection(*opt)); });
}

