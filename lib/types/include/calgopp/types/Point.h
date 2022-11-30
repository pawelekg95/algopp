#pragma once

namespace calgopp::types {

/**
 * Point representation
 */
struct Point
{
    /**
     * Default constructor
     */
    Point() = default;

    /**
     * Constructs point from same numeric type of arguments
     * @tparam T                    Type of input arguments.
     * @param x                     X axis value.
     * @param y                     Y axis value.
     */
    template <typename T>
    Point(T x, T y)
        : x(double(x))
        , y(double(y))
    {}

    /**
     * Constructs point from different numeric types of arguments.
     * @tparam T                    First numeric type
     * @tparam Y                    Second numeric type
     * @param x                     X axis value.
     * @param y                     Y axis value.
     */
    template <typename T, typename Y>
    Point(T x, Y y)
        : x(double(x))
        , y(double(y))
    {}

    long double x{};
    long double y{};

    /**
     * Appending and assignment operator.
     * @param other                 Point to add.
     * @return This with added other point.
     */
    Point& operator+=(const Point& other);

    /**
     * Subtraction and assignment operator.
     * @param other                 Point to subtract.
     * @return This with subtracted other point.
     */
    Point& operator-=(const Point& other);
};

/**
 * Equality operator for lvalue reference.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return True if points equal, false otherwise.
 */
bool operator==(const Point& lhs, const Point& rhs);

/**
 * Equality operator for rvalue reference.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return True if points equal, false otherwise.
 */
bool operator==(const Point&& lhs, const Point&& rhs);

/**
 * Inequality operator for lvalue reference.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return True if points are not equal, false otherwise.
 */
bool operator!=(const Point& lhs, const Point& rhs);

/**
 * Inequality operator for rvalue reference.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return True if points are not equal, false otherwise.
 */
bool operator!=(const Point&& lhs, const Point&& rhs);

/**
 * Addition operator.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return New point from addition lhs and rhs.
 */
Point operator+(const Point& lhs, const Point& rhs);

/**
 * Subtraction operator.
 * @param lhs                       Left hand object.
 * @param rhs                       Right hand object.
 * @return New point from subtraction lhs and rhs.
 */
Point operator-(const Point& lhs, const Point& rhs);

} // namespace calgopp::types
