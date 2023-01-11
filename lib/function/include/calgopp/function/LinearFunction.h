#pragma once

#include "calgopp/function/Function.h"

namespace calgopp {
namespace function {

struct LinearFunctionImpl
{
    double a{};
    double b{};

    double operator()(double argument)
    {
        return a * argument + b;
    }
};

class LinearFunction : public Function<LinearFunctionImpl>
{
public:
    LinearFunction(double a, double b)
        : Function({a, b})
    {}
};


} // namespace function
} // namespace calgopp
