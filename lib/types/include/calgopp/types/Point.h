#pragma once

namespace calgopp::types {

struct Point
{
    Point() = default;

    template <typename T>
    Point(T x, T y)
        : x(double(x))
        , y(double(y))
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
