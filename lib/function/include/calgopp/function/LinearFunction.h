#pragma once

#include "calgopp/function/Function.h"
#include "calgopp/math/math.h"

namespace calgopp {
namespace function {

struct LinearFunctionImpl
{
    double a{};
    double b{};

    double operator()(double argument) { return a * argument + b; }
};

class LinearFunction : public Function<LinearFunctionImpl>
{
public:
    LinearFunction(double a, double b)
        : Function({a, b})
        , m_a(a)
        , m_b(b)
    {}

    double a() { return m_a; }

    double b() { return m_b; }

    double slope() { return math::atan(m_a); }

private:
    double m_a{};
    double m_b{};
};

} // namespace function
} // namespace calgopp
