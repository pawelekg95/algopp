#include "calgopp/types/Point.h"
#include "calgopp/algorithm/numeric.h"

namespace calgopp::types {

Point& Point::operator+=(const Point& other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Point& Point::operator-=(const Point& other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

bool operator==(const Point& lhs, const Point& rhs)
{
    return algorithm::numeric::abs(lhs.x - rhs.x) < algorithm::numeric::cEpsilon &&
           algorithm::numeric::abs(lhs.y - rhs.y) < algorithm::numeric::cEpsilon;
}

bool operator==(const Point&& lhs, const Point&& rhs)
{
    return algorithm::numeric::abs(lhs.x - rhs.x) < algorithm::numeric::cEpsilon &&
           algorithm::numeric::abs(lhs.y - rhs.y) < algorithm::numeric::cEpsilon;
}

bool operator!=(const Point& lhs, const Point& rhs)
{
    return !(lhs == rhs);
}

bool operator!=(const Point&& lhs, const Point&& rhs)
{
    return !(lhs == rhs);
}

Point operator+(const Point& lhs, const Point& rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

Point operator-(const Point& lhs, const Point& rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

} // namespace calgopp::types
