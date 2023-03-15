#include "calgopp/function/LinearFunction.h"

#include "calgopp/math/math.h"

namespace calgopp::function {

double LinearFunction::slope() const
{
    return math::atan(a());
}

double LinearFunction::angle(const LinearFunction& other) const
{
    if (math::abs(a() - other.a()) <= math::epsilon())
    {
        return 0;
    }
    if (math::abs((a() * other.a()) - 1.0) <= math::epsilon())
    {
        return math::toRadians(90);
    }
    return math::atan((other.a() - a()) / (1 + (a() * other.a())));
}

} // namespace calgopp::function
