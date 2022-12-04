#include "calgopp/types/Point.h"
#include "calgopp/math/math.h"

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
    return math::abs(lhs.x - rhs.x) < math::cEpsilon &&
    	   math::abs(lhs.y - rhs.y) < math::cEpsilon;
}

bool operator==(const Point&& lhs, const Point&& rhs)
{
    return math::abs(lhs.x - rhs.x) < math::cEpsilon &&
    	   math::abs(lhs.y - rhs.y) < math::cEpsilon;
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
