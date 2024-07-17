#include "calgopp/function/LinearFunction.h"

#include <cmath>

namespace calgopp::function {

double LinearFunction::slope() const
{
    return std::atan(a());
}

double LinearFunction::angle(const LinearFunction& other) const
{
    if (std::abs(a() - other.a()) <= std::numeric_limits<double>::epsilon())
    {
        return 0;
    }
    if (std::abs((a() * other.a()) - 1.0) <= std::numeric_limits<double>::epsilon())
    {
        return toRadians(90);
    }
    return std::atan((other.a() - a()) / (1 + (a() * other.a())));
}

bool LinearFunction::operator==(const LinearFunction& other) const
{
    return std::abs(a() - other.a()) <= std::numeric_limits<double>::epsilon() &&
           std::abs(b() - other.b()) <= std::numeric_limits<double>::epsilon();
}

bool LinearFunction::operator!=(const LinearFunction& other) const
{
    return !(*this == other);
}

} // namespace calgopp::function
