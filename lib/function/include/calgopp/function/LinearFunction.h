#pragma once

#include "calgopp/function/Function.h"

namespace calgopp::function {

struct LinearFunctionImpl
{
    double a{};
    double b{};

    double operator()(double argument) const { return a * argument + b; }
};

class LinearFunction : public Function<LinearFunctionImpl>
{
public:
    LinearFunction()
        : Function({0, 0})
    {}

    LinearFunction(double a, double b)
        : Function({a, b})
        , m_a(a)
        , m_b(b)
    {}

    double a() const { return m_a; }

    double b() const { return m_b; }

    double slope() const;

    double angle(const LinearFunction& other) const;

    bool operator==(const LinearFunction& other) const;

    bool operator!=(const LinearFunction& other) const;

private:
    double m_a{};
    double m_b{};
};

} // namespace calgopp::function
