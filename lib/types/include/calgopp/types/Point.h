#ifndef POINT_H
#define POINT_H

namespace calgopp::types {

struct Point
{
    Point() = default;

    Point(long double x, long double y)
        : x(x)
        , y(y)
    {}

    long double x{};
    long double y{};

    Point& operator+=(const Point& other);

    Point& operator-=(const Point& other);
};

bool operator==(const Point& lhs, const Point& rhs);

bool operator==(const Point&& lhs, const Point&& rhs);

bool operator!=(const Point& lhs, const Point& rhs);

bool operator!=(const Point&& lhs, const Point&& rhs);

Point operator+(const Point& lhs, const Point& rhs);

Point operator-(const Point& lhs, const Point& rhs);

} // namespace calgopp::types

#endif /* POINT_H */
