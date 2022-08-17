#include "algopp/types/Point.h"

namespace algopp::types {

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
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator==(const Point&& lhs, const Point&& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
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

}
