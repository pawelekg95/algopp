#ifndef POINT_H
#define POINT_H

namespace algopp::types {

struct Point
{
    double x{};
    double y{};

    Point& operator+=(const Point& other);

    Point& operator-=(const Point& other);
};

bool operator==(const Point& lhs, const Point& rhs);

bool operator==(const Point&& lhs, const Point&& rhs);

bool operator!=(const Point& lhs, const Point& rhs);

bool operator!=(const Point&& lhs, const Point&& rhs);

Point operator+(const Point& lhs, const Point& rhs);

Point operator-(const Point& lhs, const Point& rhs);

} // namespace algopp::types

#endif /* POINT_H */